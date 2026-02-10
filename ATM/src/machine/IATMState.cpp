// IATMState.cpp - State handlers: Idle, CardInserted, AskForPIN, and all other states.

#include "atm/bank/Account.h"
#include "atm/bank/Bank.h"
#include "atm/bank/Money.h"
#include "atm/machine/ATM.h"
#include "atm/machine/IATMState.h"
#include "atm/machine/Logger.h"
#include "atm/machine/MenuOption.h"
#include "atm/machine/UserSession.h"

namespace atm {

IATMState::IATMState(ATM* context) : atm_(context) {}

// Idle and card handling.

std::string IdleState::name() const { return "IdleState"; }
void IdleState::handle() {
    std::string cardNumber = atm_->getUI()->readCard();
    if (cardNumber.empty()) {
        return;
    }
    atm_->createSession(cardNumber);
    atm_->setState(std::make_unique<CardInsertedState>(atm_));
}

std::string CardInsertedState::name() const { return "CardInsertedState"; }
void CardInsertedState::handle() {
    if (atm_->getGateway()->checkIfCardExist(atm_->getSession()->getCardNumber())) {
        atm_->setState(std::make_unique<AskForPINState>(atm_));
    }
    else {
        atm_->setState(std::make_unique<CardNotExistInSystemState>(atm_));
    }
}

std::string CardNotExistInSystemState::name() const { return "CardNotExistInSystemState"; }
void CardNotExistInSystemState::handle() {
    std::string cardNumber = atm_->getSession()->getCardNumber();
    atm_->getUI()->showCardInsertedFailure(cardNumber);
    atm_->setState(std::make_unique<EjectCardState>(atm_));
}

std::string AskForPINState::name() const { return "AskForPINState"; }
void AskForPINState::handle() {
    std::string pin = atm_->getUI()->readPin();
    atm_->getSession()->setPin(pin);
    if (atm_->getGateway()->checkPIN(pin, atm_->getSession()->getCardNumber())) {
        atm_->setState(std::make_unique<SuccessfulPinState>(atm_));
    }
    else {
        atm_->setState(std::make_unique<UnsuccessfulPinState>(atm_));
    }
}

std::string SuccessfulPinState::name() const { return "SuccessfulPinState"; }
void SuccessfulPinState::handle() {
    atm_->getUI()->showPinAccepted(atm_->getSession()->getStoredPin());
    atm_->getSession()->setUserAuthenticated(true);
    atm_->setState(std::make_unique<ChooseAccountState>(atm_));
}

std::string UnsuccessfulPinState::name() const { return "UnsuccessfulPinState"; }
void UnsuccessfulPinState::handle() {
    atm_->getUI()->showPinRejected(atm_->getSession()->getStoredPin());
    atm_->getSession()->incrementUnsuccessfulPinCount();
    if (atm_->getSession()->getUnsuccessfulPinCount() >= atm_->getConfig().maxPinAttempts) {
        atm_->setState(std::make_unique<BlockCardState>(atm_));
    }
    else {
        atm_->setState(std::make_unique<AskForPINState>(atm_));
    }
}

std::string BlockCardState::name() const { return "BlockCardState"; }
void BlockCardState::handle() {
    std::string cardNumber = atm_->getSession()->getCardNumber();
    Logger::log("Card blocked", cardNumber);
    atm_->getUI()->showCardBlocked(cardNumber);
    atm_->getGateway()->blockCard(cardNumber);
    atm_->setState(std::make_unique<EjectCardState>(atm_));
}

std::string ChooseAccountState::name() const { return "ChooseAccountState"; }
void ChooseAccountState::handle() {
    std::string cardNumber = atm_->getSession()->getCardNumber();
    std::vector<Account> accounts = atm_->getGateway()->getAccountListForCard(cardNumber);
    atm_->getSession()->setAccounts(accounts);
    std::vector<std::string> accountNames = atm_->getSession()->getAccountNames();
    const int count = static_cast<int>(accountNames.size());
    int accountIndex;
    do {
        accountIndex = atm_->getUI()->promptAccountChoice(accountNames);
        if (accountIndex < 1 || accountIndex > count) {
            atm_->getUI()->showInvalidAccountSelection();
        }
    } while (accountIndex < 1 || accountIndex > count);
    atm_->getSession()->setSelectedAccount(static_cast<size_t>(accountIndex - 1));
    atm_->setState(std::make_unique<ShowOptionsState>(atm_));
}

std::string ShowOptionsState::name() const { return "ShowOptionsState"; }
void ShowOptionsState::handle() {
    MenuOption option = atm_->getUI()->promptMenuOption();
    atm_->getUI()->showOptionSelected(option);
    atm_->getSession()->setSelectedOption(option);
    atm_->setState(std::make_unique<DecideOptionState>(atm_));
}

std::string DecideOptionState::name() const { return "DecideOptionState"; }
void DecideOptionState::handle() {
    switch (atm_->getSession()->getSelectedOption()) {
        case MenuOption::CheckBalance:
            atm_->setState(std::make_unique<CheckBalanceState>(atm_));
            break;
        case MenuOption::Withdraw:
            atm_->setState(std::make_unique<WithdrawFundsState>(atm_));
            break;
        case MenuOption::Deposit:
            atm_->setState(std::make_unique<DepositFundsState>(atm_));
            break;
        case MenuOption::Exit:
            atm_->setState(std::make_unique<ExitState>(atm_));
            break;
    }
}

std::string CheckBalanceState::name() const { return "CheckBalanceState"; }
void CheckBalanceState::handle() {
    Account* account = atm_->getSession()->getSelectedAccount();
    if (!account) {
        atm_->getUI()->showInvalidAccountSelection();
        atm_->setState(std::make_unique<ShowOptionsState>(atm_));
        return;
    }
    Money balance = atm_->getGateway()->showBalance(account);
    atm_->getUI()->showBalance(balance);
    atm_->setState(std::make_unique<ShowOptionsState>(atm_));
}

std::string WithdrawFundsState::name() const { return "WithdrawFundsState"; }
void WithdrawFundsState::handle() {
    Account* account = atm_->getSession()->getSelectedAccount();
    if (!account) {
        atm_->getUI()->showInvalidAccountSelection();
        atm_->setState(std::make_unique<ShowOptionsState>(atm_));
        return;
    }
    Money amount = atm_->getUI()->promptWithdrawAmount();
    if (atm_->getDispenser()->hasEnoughCash(amount)) {
        if (!atm_->getGateway()->withdrawCash(account, amount)) {
            atm_->getUI()->showInsufficientAccountFunds();
        }
        else {
            atm_->getDispenser()->dispense(amount);
            atm_->getUI()->showWithdrawAmount(amount);
        }
    }
    else {
        Logger::log("Withdraw failed", "insufficient ATM cash");
        atm_->getUI()->showInsufficientAtmFunds();
    }
    atm_->setState(std::make_unique<ShowOptionsState>(atm_));
}

std::string DepositFundsState::name() const { return "DepositFundsState"; }
void DepositFundsState::handle() {
    Account* account = atm_->getSession()->getSelectedAccount();
    if (!account) {
        atm_->getUI()->showInvalidAccountSelection();
        atm_->setState(std::make_unique<ShowOptionsState>(atm_));
        return;
    }
    Money amount = atm_->getUI()->promptDepositAmount();
    if (!atm_->getGateway()->depositCash(account, amount)) {
        atm_->getUI()->showDepositRejected();
    }
    else {
        atm_->getDepositSlot()->processDeposit(amount);
        atm_->getUI()->showDepositSuccess();
    }
    atm_->setState(std::make_unique<ShowOptionsState>(atm_));
}

std::string ExitState::name() const { return "ExitState"; }
void ExitState::handle() {
    atm_->setState(std::make_unique<EjectCardState>(atm_));
}

std::string EjectCardState::name() const { return "EjectCardState"; }
void EjectCardState::handle() {
    std::string cardNumber = atm_->getSession()->getCardNumber();
    atm_->getUI()->showCardEjected(cardNumber);
    atm_->setState(std::make_unique<ResetState>(atm_));
}

std::string ResetState::name() const { return "ResetState"; }
void ResetState::handle() {
    atm_->resetSession();
    atm_->setState(std::make_unique<IdleState>(atm_));
}

}  // namespace atm
