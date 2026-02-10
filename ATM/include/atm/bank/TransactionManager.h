#pragma once
// TransactionManager.h - Balance, withdraw, deposit with configurable limits.

#include <cstdint>

#include "atm/bank/Account.h"
#include "atm/bank/Money.h"

namespace atm {

struct AtmConfig;

class TransactionManager {
public:
    /// Constructs with default limits from AtmConstants.
    TransactionManager();
    /// Constructs with limits from config (e.g. for tests or per-ATM).
    /// @param config Limits (min/max withdraw) and any future config.
    explicit TransactionManager(const AtmConfig& config);

    /// Returns the current balance of the account.
    /// @param account Account to query.
    /// @return Current balance.
    Money showBalance(const Account* account) const;
    /// Withdraws the amount from the account if valid and sufficient funds.
    /// @param account Account to debit.
    /// @param amount Amount in cents.
    /// @return false if amount invalid, insufficient funds, or account null.
    bool withdrawCash(Account* account, Money amount);
    /// Deposits the amount into the account if non-negative.
    /// @param account Account to credit.
    /// @param amount Amount in cents.
    /// @return false if amount negative or account null.
    bool depositCash(Account* account, Money amount);

private:
    std::int64_t minWithdrawCents_;
    std::int64_t maxWithdrawPerTransactionCents_;
};

}  // namespace atm
