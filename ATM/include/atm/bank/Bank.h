#pragma once
// Bank.h - Bank facade implementing IBankService.
#include <vector>

#include "atm/bank/AuthService.h"
#include "atm/bank/IBankService.h"
#include "atm/bank/TransactionManager.h"

namespace atm {

class Bank : public IBankService {
public:
    /// Constructs the bank with the given transaction manager and auth service.
    /// @param transaction Transaction manager for balance/withdraw/deposit.
    /// @param auth Auth service for card/PIN and account list.
    Bank(TransactionManager& transaction, AuthService& auth);

    /// Returns true if the card exists and is not blocked.
    /// @param card Card number to check.
    /// @return true if card exists and is not blocked.
    bool checkIfCardExist(const std::string& card) override;
    /// Returns true if the PIN matches the one stored for the card.
    /// @param pin PIN entered by user.
    /// @param card Card number.
    /// @return true if PIN matches the one stored for the card.
    bool checkPIN(const std::string& pin, const std::string& card) override;
    /// Blocks the card so it can no longer be used.
    /// @param card Card number to block.
    void blockCard(const std::string& card) override;
    /// Returns the current balance of the account.
    /// @param account Account to query.
    /// @return Current balance in cents.
    Money showBalance(Account* account) override;
    /// Withdraws the amount from the account if valid and sufficient funds.
    /// @param account Account to debit.
    /// @param amount Amount in cents.
    /// @return true if withdrawal succeeded.
    bool withdrawCash(Account* account, Money amount) override;
    /// Deposits the amount into the account if non-negative.
    /// @param account Account to credit.
    /// @param amount Amount in cents.
    /// @return true if deposit succeeded.
    bool depositCash(Account* account, Money amount) override;
    /// Returns the list of accounts linked to the card.
    /// @param card Card number.
    /// @return List of accounts linked to the card.
    std::vector<Account> getAccountListForCard(const std::string& card) override;

private:
    TransactionManager& transactionManager_;
    AuthService& authService_;
};

}  // namespace atm
