#pragma once
// IBankService.h - Bank interface used by the ATM.

#include <string>
#include <vector>

#include "atm/bank/Account.h"
#include "atm/bank/Money.h"

namespace atm {

class IBankService {
public:
    virtual ~IBankService() = default;

    /// Returns true if the card exists and is not blocked.
    /// @param card Card number.
    /// @return true if card exists and is not blocked.
    virtual bool checkIfCardExist(const std::string& card) = 0;
    /// Returns true if the PIN is correct for the card.
    /// @param pin PIN to verify.
    /// @param card Card number.
    /// @return true if PIN is correct.
    virtual bool checkPIN(const std::string& pin, const std::string& card) = 0;
    /// Blocks the card.
    /// @param card Card number to block.
    virtual void blockCard(const std::string& card) = 0;
    /// Returns the current balance of the account.
    /// @param account Account to query.
    /// @return Current balance.
    virtual Money showBalance(Account* account) = 0;
    /// Withdraws the amount from the account.
    /// @param account Account to debit.
    /// @param amount Amount in cents.
    /// @return true if withdrawal succeeded.
    virtual bool withdrawCash(Account* account, Money amount) = 0;
    /// Deposits the amount into the account.
    /// @param account Account to credit.
    /// @param amount Amount in cents.
    /// @return true if deposit succeeded.
    virtual bool depositCash(Account* account, Money amount) = 0;
    /// Returns the accounts linked to the card.
    /// @param card Card number.
    /// @return Accounts linked to the card.
    virtual std::vector<Account> getAccountListForCard(const std::string& card) = 0;
};

}  // namespace atm
