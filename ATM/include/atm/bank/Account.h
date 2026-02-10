#pragma once
// Account.h - Base account with name and balance.

#include <string>

#include "atm/bank/Money.h"

namespace atm {

class Account {
public:
    /// Constructs an account with the given name and initial balance.
    /// @param accountName Display name of the account.
    /// @param initialAmount Initial balance in cents.
    Account(std::string accountName = "Default Account", Money initialAmount = Money());

    /// Returns the account display name.
    /// @return Account display name.
    std::string getName() const;
    /// Returns the current balance.
    /// @return Current balance in cents.
    Money getAmount() const;
    /// Sets the account display name.
    /// @param newName New display name.
    void setName(const std::string& newName);
    /// Sets the account balance.
    /// @param newAmount New balance (e.g. after withdraw/deposit).
    void setAmount(Money newAmount);

protected:
    std::string name;
    Money amount;
};

}  // namespace atm
