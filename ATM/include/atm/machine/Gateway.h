#pragma once
// Gateway.h - ATM-side gateway that forwards calls to the bank.
#include <string>
#include <vector>

#include "atm/bank/Account.h"
#include "atm/bank/IBankService.h"
#include "atm/bank/Money.h"

namespace atm {

class Gateway {
public:
    /// Constructs the gateway with the bank service to forward to.
    /// @param service Bank service to forward all calls to.
    explicit Gateway(IBankService& service);

    /// Returns true if the card exists and is not blocked.
    /// @param card Card number.
    /// @return true if card exists and is not blocked.
    bool checkIfCardExist(const std::string& card) const;
    /// Returns true if the PIN is correct for the card.
    /// @param pin PIN to verify.
    /// @param card Card number.
    /// @return true if PIN is correct.
    bool checkPIN(const std::string& pin, const std::string& card) const;
    /// Blocks the card.
    /// @param card Card number to block.
    void blockCard(const std::string& card);
    /// Returns the current balance of the account.
    /// @param account Account to query.
    /// @return Current balance.
    Money showBalance(Account* account) const;
    /// Withdraws the amount from the account.
    /// @param account Account to debit.
    /// @param amount Amount in cents.
    /// @return true if withdrawal succeeded.
    bool withdrawCash(Account* account, Money amount);
    /// Deposits the amount into the account.
    /// @param account Account to credit.
    /// @param amount Amount in cents.
    /// @return true if deposit succeeded.
    bool depositCash(Account* account, Money amount);
    /// Returns the accounts linked to the card.
    /// @param card Card number.
    /// @return Accounts linked to the card.
    std::vector<Account> getAccountListForCard(const std::string& card) const;

private:
    IBankService& bankService_;
};

}  // namespace atm
