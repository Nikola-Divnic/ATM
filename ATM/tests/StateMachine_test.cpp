#include "atm/bank/Account.h"
#include "atm/bank/AuthService.h"
#include "atm/bank/SavingAccount.h"
#include "atm/bank/Bank.h"
#include "atm/bank/Money.h"
#include "atm/bank/TransactionManager.h"
#include "atm/machine/ATM.h"
#include "atm/machine/AtmConstants.h"
#include "atm/machine/Gateway.h"
#include "atm/machine/Hardware.h"
#include "atm/machine/IUserInterface.h"
#include "atm/machine/MenuOption.h"
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

using namespace atm;

// Fake UI: returns configured values and records all calls for assertions.
class FakeUserInterface : public IUserInterface {
public:
    std::string nextCard;
    std::string nextPin;
    int nextAccountChoice = 1;
    MenuOption nextMenuOption = MenuOption::CheckBalance;
    int nextWithdrawCents = 100;
    int nextDepositCents = 50;

    std::vector<std::string> log;

    void logCall(const std::string& call) { log.push_back(call); }

    std::string readCard() override {
        logCall("readCard");
        return nextCard;
    }
    void showCardInsertedSuccess(const std::string&) override { logCall("showCardInsertedSuccess"); }
    void showCardInsertedFailure(const std::string&) override { logCall("showCardInsertedFailure"); }
    std::string readPin() override {
        logCall("readPin");
        return nextPin;
    }
    void showPinAccepted(const std::string&) override { logCall("showPinAccepted"); }
    void showPinRejected(const std::string&) override { logCall("showPinRejected"); }
    void showCardBlocked(const std::string&) override { logCall("showCardBlocked"); }
    void showCardEjected(const std::string&) override { logCall("showCardEjected"); }
    int promptAccountChoice(const std::vector<std::string>&) override {
        logCall("promptAccountChoice");
        return nextAccountChoice;
    }
    MenuOption promptMenuOption() override {
        logCall("promptMenuOption");
        return nextMenuOption;
    }
    void showOptionSelected(MenuOption) override { logCall("showOptionSelected"); }
    void showBalance(Money balance) override {
        logCall("showBalance:" + std::to_string(balance.getCents()));
    }
    Money promptWithdrawAmount() override {
        logCall("promptWithdrawAmount");
        return Money(nextWithdrawCents);
    }
    void showWithdrawAmount(Money amount) override {
        logCall("showWithdrawAmount:" + std::to_string(amount.getCents()));
    }
    Money promptDepositAmount() override {
        logCall("promptDepositAmount");
        return Money(nextDepositCents);
    }
    void showDepositAmount(Money) override { logCall("showDepositAmount"); }
    void promptTakeCard() override { logCall("promptTakeCard"); }
    void showInsufficientAtmFunds() override { logCall("showInsufficientAtmFunds"); }
    void showInsufficientAccountFunds() override { logCall("showInsufficientAccountFunds"); }
    void promptInsertEnvelope() override { logCall("promptInsertEnvelope"); }
    void showDepositSuccess() override { logCall("showDepositSuccess"); }
    void showDepositRejected() override { logCall("showDepositRejected"); }
    void showInvalidAccountSelection() override { logCall("showInvalidAccountSelection"); }
    void showInvalidNumericInput() override { logCall("showInvalidNumericInput"); }
};

// Build ATM with real bank (seeded) and fake UI. Uses runOnce() to drive one step at a time.
static void runUntilState(ATM& atm, FakeUserInterface& fake, const std::string& targetState,
                          int maxSteps = 50) {
    for (int i = 0; i < maxSteps; ++i) {
        if (atm.getCurrentStateName() == targetState)
            return;
        atm.runOnce();
    }
    FAIL() << "Did not reach state " << targetState << " after " << maxSteps << " steps. "
           << "Current: " << atm.getCurrentStateName();
}

static bool logContains(const std::vector<std::string>& log, const std::string& substring) {
    for (const auto& entry : log) {
        if (entry.find(substring) != std::string::npos)
            return true;
    }
    return false;
}

TEST(StateMachine, StartsInIdleState) {
    TransactionManager tm;
    AuthService auth;
    Bank bank(tm, auth);
    auto gateway = std::make_shared<Gateway>(bank);
    auto dispenser = std::make_shared<CashDispenser>(Money(10000));
    auto depositSlot = std::make_shared<DepositSlot>(*dispenser);
    auto fakeUi = std::make_shared<FakeUserInterface>();

    ATM atm(fakeUi, dispenser, depositSlot, gateway, AtmConfig{});
    EXPECT_EQ(atm.getCurrentStateName(), "IdleState");
}

TEST(StateMachine, IdleReadsCardAndTransitionsToCardInsertedState) {
    TransactionManager tm;
    AuthService auth;
    auth.setPinForCard("testcard", "1234");
    auth.addAccountToCard("testcard", SavingAccount("Savings", Money(5000)));
    Bank bank(tm, auth);
    auto gateway = std::make_shared<Gateway>(bank);
    auto dispenser = std::make_shared<CashDispenser>(Money(10000));
    auto depositSlot = std::make_shared<DepositSlot>(*dispenser);
    auto fakeUi = std::make_shared<FakeUserInterface>();
    fakeUi->nextCard = "testcard";

    ATM atm(fakeUi, dispenser, depositSlot, gateway, AtmConfig{});
    EXPECT_EQ(atm.getCurrentStateName(), "IdleState");

    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "CardInsertedState");
    EXPECT_TRUE(logContains(fakeUi->log, "readCard"));
}

TEST(StateMachine, FullFlowToCheckBalanceShowsCorrectBalance) {
    TransactionManager tm;
    AuthService auth;
    auth.setPinForCard("testcard", "1234");
    auth.addAccountToCard("testcard", SavingAccount("Savings", Money(5000)));
    Bank bank(tm, auth);
    auto gateway = std::make_shared<Gateway>(bank);
    auto dispenser = std::make_shared<CashDispenser>(Money(10000));
    auto depositSlot = std::make_shared<DepositSlot>(*dispenser);
    auto fakeUi = std::make_shared<FakeUserInterface>();
    fakeUi->nextCard = "testcard";
    fakeUi->nextPin = "1234";
    fakeUi->nextAccountChoice = 1;
    fakeUi->nextMenuOption = MenuOption::CheckBalance;

    ATM atm(fakeUi, dispenser, depositSlot, gateway, AtmConfig{});

    runUntilState(atm, *fakeUi, "ShowOptionsState");
    EXPECT_TRUE(logContains(fakeUi->log, "showPinAccepted"));
    EXPECT_TRUE(logContains(fakeUi->log, "promptAccountChoice"));

    atm.runOnce();
    EXPECT_TRUE(logContains(fakeUi->log, "promptMenuOption"));
    EXPECT_EQ(atm.getCurrentStateName(), "DecideOptionState");
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "CheckBalanceState");
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "ShowOptionsState");
    EXPECT_TRUE(logContains(fakeUi->log, "showBalance:5000"));
}

TEST(StateMachine, UnknownCardLeadsToCardNotExistAndEject) {
    TransactionManager tm;
    AuthService auth;
    auth.setPinForCard("othercard", "1234");
    Bank bank(tm, auth);
    auto gateway = std::make_shared<Gateway>(bank);
    auto dispenser = std::make_shared<CashDispenser>(Money(10000));
    auto depositSlot = std::make_shared<DepositSlot>(*dispenser);
    auto fakeUi = std::make_shared<FakeUserInterface>();
    fakeUi->nextCard = "unknowncard";

    ATM atm(fakeUi, dispenser, depositSlot, gateway, AtmConfig{});
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "CardInsertedState");
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "CardNotExistInSystemState");
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "EjectCardState");
    EXPECT_TRUE(logContains(fakeUi->log, "showCardInsertedFailure"));
    atm.runOnce();
    EXPECT_TRUE(logContains(fakeUi->log, "showCardEjected"));
}

TEST(StateMachine, WrongPinLeadsToUnsuccessfulPinState) {
    AtmConfig config;
    config.maxPinAttempts = 2;
    TransactionManager tm(config);
    AuthService auth;
    auth.setPinForCard("testcard", "1234");
    auth.addAccountToCard("testcard", SavingAccount("Savings", Money(5000)));
    Bank bank(tm, auth);
    auto gateway = std::make_shared<Gateway>(bank);
    auto dispenser = std::make_shared<CashDispenser>(Money(10000));
    auto depositSlot = std::make_shared<DepositSlot>(*dispenser);
    auto fakeUi = std::make_shared<FakeUserInterface>();
    fakeUi->nextCard = "testcard";
    fakeUi->nextPin = "wrong";

    ATM atm(fakeUi, dispenser, depositSlot, gateway, config);
    atm.runOnce();
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "AskForPINState");
    atm.runOnce();
    EXPECT_EQ(atm.getCurrentStateName(), "UnsuccessfulPinState");
    atm.runOnce();
    EXPECT_TRUE(logContains(fakeUi->log, "showPinRejected"));
}
