// User.cpp - User entity; accounts and cards getters/setters.

#include "atm/bank/User.h"

namespace atm {

User::User(std::vector<Account> userAccounts, std::vector<std::string> userCards)
    : accounts(std::move(userAccounts)), cards(std::move(userCards)) {}

std::vector<Account> User::getAccounts() const {
    return accounts;
}

std::vector<std::string> User::getCards() const {
    return cards;
}

void User::setAccounts(const std::vector<Account>& newAccounts) {
    accounts = newAccounts;
}

void User::setCards(const std::vector<std::string>& newCards) {
    cards = newCards;
}

}  // namespace atm
