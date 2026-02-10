// Bank.cpp - IBankService implementation; delegates to AuthService and TransactionManager.

#include "atm/bank/Bank.h"

namespace atm {

Bank::Bank(TransactionManager& transaction, AuthService& auth)
    : transactionManager_(transaction), authService_(auth) {}

bool Bank::checkIfCardExist(const std::string& card) {
    return authService_.checkIfCardExist(card);
}

bool Bank::checkPIN(const std::string& pin, const std::string& card) {
    return authService_.checkPIN(pin, card);
}

std::vector<Account> Bank::getAccountListForCard(const std::string& card) {
    return authService_.getAccountListForCard(card);
}

void Bank::blockCard(const std::string& card) {
    authService_.blockCard(card);
}

Money Bank::showBalance(Account* account) {
    return transactionManager_.showBalance(account);
}

bool Bank::withdrawCash(Account* account, Money amount) {
    return transactionManager_.withdrawCash(account, amount);
}

bool Bank::depositCash(Account* account, Money amount) {
    return transactionManager_.depositCash(account, amount);
}

}  // namespace atm
