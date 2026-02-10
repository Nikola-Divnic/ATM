#include "atm/bank/Account.h"
#include "atm/bank/AuthService.h"
#include "atm/bank/CheckingAccount.h"
#include "atm/bank/SavingAccount.h"
#include <gtest/gtest.h>

using namespace atm;

TEST(AuthService, CardDoesNotExistBeforeRegistration) {
    AuthService auth;
    EXPECT_FALSE(auth.checkIfCardExist("unknown"));
    EXPECT_TRUE(auth.getAccountListForCard("unknown").empty());
}

TEST(AuthService, SetPinAndCheckPin) {
    AuthService auth;
    auth.setPinForCard("card1", "1234");
    EXPECT_TRUE(auth.checkIfCardExist("card1"));
    EXPECT_TRUE(auth.checkPIN("1234", "card1"));
    EXPECT_FALSE(auth.checkPIN("0000", "card1"));
    EXPECT_FALSE(auth.checkPIN("1234", "other"));
}

TEST(AuthService, GetAccountListForCard) {
    AuthService auth;
    auth.setPinForCard("card1", "1234");
    SavingAccount saving("My Savings", Money(5000));
    CheckingAccount checking("My Checking", Money(1000));
    auth.addAccountToCard("card1", saving);
    auth.addAccountToCard("card1", checking);

    std::vector<Account> accounts = auth.getAccountListForCard("card1");
    ASSERT_EQ(accounts.size(), 2u);
    EXPECT_EQ(accounts[0].getName(), "My Savings");
    EXPECT_EQ(accounts[0].getAmount().getCents(), 5000);
    EXPECT_EQ(accounts[1].getName(), "My Checking");
    EXPECT_EQ(accounts[1].getAmount().getCents(), 1000);
}

TEST(AuthService, BlockedCardFailsCheckIfCardExistAndCheckPin) {
    AuthService auth;
    auth.setPinForCard("card1", "1234");
    EXPECT_TRUE(auth.checkIfCardExist("card1"));
    EXPECT_TRUE(auth.checkPIN("1234", "card1"));

    auth.blockCard("card1");
    EXPECT_FALSE(auth.checkIfCardExist("card1"));
    EXPECT_FALSE(auth.checkPIN("1234", "card1"));
}

TEST(AuthService, DemoFlowMatchesProductionSeed) {
    AuthService auth;
    auth.setPinForCard("pera123", "1234");
    SavingAccount saving("Pera saving account", Money(200000));
    CheckingAccount checking;
    auth.addAccountToCard("pera123", saving);
    auth.addAccountToCard("pera123", checking);

    EXPECT_TRUE(auth.checkIfCardExist("pera123"));
    EXPECT_TRUE(auth.checkPIN("1234", "pera123"));
    std::vector<Account> accounts = auth.getAccountListForCard("pera123");
    ASSERT_EQ(accounts.size(), 2u);
    EXPECT_EQ(accounts[0].getName(), "Pera saving account");
    EXPECT_EQ(accounts[0].getAmount().getCents(), 200000);
}
