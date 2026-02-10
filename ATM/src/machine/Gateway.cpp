// Gateway.cpp - Forwards ATM calls to the bank.

#include "atm/machine/Gateway.h"

namespace atm {

Gateway::Gateway(IBankService& service) : bankService_(service) {}

bool Gateway::checkIfCardExist(const std::string& card) const {
    return bankService_.checkIfCardExist(card);
}

bool Gateway::checkPIN(const std::string& pin, const std::string& card) const {
    return bankService_.checkPIN(pin, card);
}

void Gateway::blockCard(const std::string& card) {
    bankService_.blockCard(card);
}

Money Gateway::showBalance(Account* account) const {
    return bankService_.showBalance(account);
}

bool Gateway::withdrawCash(Account* account, Money amount) {
    return bankService_.withdrawCash(account, amount);
}

bool Gateway::depositCash(Account* account, Money amount) {
    return bankService_.depositCash(account, amount);
}

std::vector<Account> Gateway::getAccountListForCard(const std::string& card) const {
    return bankService_.getAccountListForCard(card);
}

}  // namespace atm
