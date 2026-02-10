// Account.cpp - Account, SavingAccount, and CheckingAccount implementations.

#include "atm/bank/Account.h"
#include "atm/bank/CheckingAccount.h"
#include "atm/bank/SavingAccount.h"

namespace atm {

Account::Account(std::string accountName, Money initialAmount)
    : name(std::move(accountName)), amount(initialAmount) {}

std::string Account::getName() const {
    return name;
}

Money Account::getAmount() const {
    return amount;
}

void Account::setName(const std::string& newName) {
    name = newName;
}

void Account::setAmount(Money newAmount) {
    amount = newAmount;
}

SavingAccount::SavingAccount(std::string accountName, Money initialAmount)
    : Account(std::move(accountName), initialAmount) {}

CheckingAccount::CheckingAccount(std::string accountName, Money initialAmount)
    : Account(std::move(accountName), initialAmount) {}

}  // namespace atm
