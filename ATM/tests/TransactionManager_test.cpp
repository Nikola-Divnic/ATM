#include "atm/bank/Account.h"
#include "atm/bank/TransactionManager.h"
#include "atm/bank/Money.h"
#include "atm/machine/AtmConstants.h"
#include <gtest/gtest.h>

using namespace atm;

class TransactionManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Strict limits so we can test rejections: max 500 cents per withdrawal
        config_.minWithdrawCents = 1;
        config_.maxWithdrawPerTransactionCents = 500;
        manager_ = std::make_unique<TransactionManager>(config_);
    }

    AtmConfig config_;
    std::unique_ptr<TransactionManager> manager_;
};

TEST_F(TransactionManagerTest, ShowBalanceReturnsAccountAmount) {
    Account account("Test", Money(12345));
    EXPECT_EQ(manager_->showBalance(&account).getCents(), 12345);
}

TEST_F(TransactionManagerTest, ValidWithdrawUpdatesBalance) {
    Account account("Test", Money(10000));
    bool ok = manager_->withdrawCash(&account, Money(300));
    ASSERT_TRUE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 9700);
}

TEST_F(TransactionManagerTest, ValidDepositUpdatesBalance) {
    Account account("Test", Money(1000));
    bool ok = manager_->depositCash(&account, Money(500));
    ASSERT_TRUE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 1500);
}

TEST_F(TransactionManagerTest, NegativeWithdrawRejected) {
    Account account("Test", Money(10000));
    bool ok = manager_->withdrawCash(&account, Money(-100));
    EXPECT_FALSE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 10000);
}

TEST_F(TransactionManagerTest, ZeroWithdrawRejected) {
    Account account("Test", Money(10000));
    bool ok = manager_->withdrawCash(&account, Money(0));
    EXPECT_FALSE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 10000);
}

TEST_F(TransactionManagerTest, NegativeDepositRejected) {
    Account account("Test", Money(1000));
    bool ok = manager_->depositCash(&account, Money(-50));
    EXPECT_FALSE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 1000);
}

TEST_F(TransactionManagerTest, NullAccountWithdrawRejected) {
    bool ok = manager_->withdrawCash(nullptr, Money(100));
    EXPECT_FALSE(ok);
}

TEST_F(TransactionManagerTest, NullAccountDepositRejected) {
    bool ok = manager_->depositCash(nullptr, Money(100));
    EXPECT_FALSE(ok);
}

TEST_F(TransactionManagerTest, WithdrawOverConfigLimitRejected) {
    Account account("Test", Money(10000));
    // config max is 500
    bool ok = manager_->withdrawCash(&account, Money(501));
    EXPECT_FALSE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 10000);
}

TEST_F(TransactionManagerTest, WithdrawAtConfigLimitSucceeds) {
    Account account("Test", Money(10000));
    bool ok = manager_->withdrawCash(&account, Money(500));
    ASSERT_TRUE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 9500);
}

TEST_F(TransactionManagerTest, InsufficientFundsWithdrawRejected) {
    Account account("Test", Money(100));
    bool ok = manager_->withdrawCash(&account, Money(200));
    EXPECT_FALSE(ok);
    EXPECT_EQ(account.getAmount().getCents(), 100);
}

TEST_F(TransactionManagerTest, FullFlowBalanceConsistency) {
    Account account("Savings", Money(10000));  // 100.00

    EXPECT_EQ(manager_->showBalance(&account).getCents(), 10000);

    ASSERT_TRUE(manager_->withdrawCash(&account, Money(250)));
    EXPECT_EQ(account.getAmount().getCents(), 9750);

    ASSERT_TRUE(manager_->depositCash(&account, Money(100)));
    EXPECT_EQ(account.getAmount().getCents(), 9850);

    ASSERT_TRUE(manager_->withdrawCash(&account, Money(500)));  // at limit
    EXPECT_EQ(account.getAmount().getCents(), 9350);

    EXPECT_FALSE(manager_->withdrawCash(&account, Money(10000)));  // over balance
    EXPECT_EQ(account.getAmount().getCents(), 9350);

    EXPECT_EQ(manager_->showBalance(&account).getCents(), 9350);
}
