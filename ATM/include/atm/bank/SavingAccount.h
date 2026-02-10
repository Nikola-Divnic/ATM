#pragma once
// SavingAccount.h - Savings account type (concrete Account).

#include "atm/bank/Account.h"

namespace atm {

class SavingAccount : public Account {
public:
    /// Constructs a savings account with the given name and initial balance.
    /// @param accountName Display name of the savings account.
    /// @param initialAmount Initial balance in cents.
    SavingAccount(std::string accountName = "Saving Account", Money initialAmount = Money());
};

}  // namespace atm
