// AuthService.cpp - Card and PIN validation; account list per card.

#include "atm/bank/AuthService.h"

namespace atm {

bool AuthService::checkIfCardExist(const std::string& card) const {
    if (blockedCards_.find(card) != blockedCards_.end()) {
        return false;
    }
    return cardToPIN_.find(card) != cardToPIN_.end() ||
           cardAccount_.find(card) != cardAccount_.end();
}

bool AuthService::checkPIN(const std::string& pin, const std::string& card) const {
    if (blockedCards_.find(card) != blockedCards_.end()) {
        return false;
    }
    auto it = cardToPIN_.find(card);
    if (it == cardToPIN_.end()) {
        return false;
    }
    return it->second == pin;
}

void AuthService::blockCard(const std::string& card) {
    blockedCards_.insert(card);
}

std::vector<Account> AuthService::getAccountListForCard(const std::string& card) const {
    auto it = cardAccount_.find(card);
    if (it == cardAccount_.end()) return {};
    return it->second;
}

void AuthService::addAccountToCard(const std::string& card, const Account& account) {
    cardAccount_[card].push_back(account);
}

void AuthService::setPinForCard(const std::string& card, const std::string& pin) {
    cardToPIN_[card] = pin;
}

}  // namespace atm
