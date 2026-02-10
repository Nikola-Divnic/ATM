#pragma once
// CheckingAccount.h - Checking account type (concrete Account).

#include "atm/bank/Account.h"

namespace atm {

class CheckingAccount : public Account {
public:
    /// Constructs a checking account with the given name and initial balance.
    /// @param accountName Display name of the checking account.
    /// @param initialAmount Initial balance in cents.
    CheckingAccount(std::string accountName = "Checking Account", Money initialAmount = Money());
};

}  // namespace atm
