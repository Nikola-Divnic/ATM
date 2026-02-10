// UserSession.cpp - Session state (card, PIN, accounts, selected option).

#include "atm/machine/UserSession.h"

namespace atm {

UserSession::UserSession(std::string card, int initialUnsuccessfulPinCount)
    : cardNumber_(std::move(card)), unsuccessfulPinCount_(initialUnsuccessfulPinCount) {}

void UserSession::setAccounts(const std::vector<Account>& accountsList) {
    accounts_ = accountsList;
    selectedAccountIndex_ = std::nullopt;
}

std::vector<Account>& UserSession::getAccounts() {
    return accounts_;
}

const std::vector<Account>& UserSession::getAccounts() const {
    return accounts_;
}

void UserSession::setSelectedAccount(size_t index) {
    if (index < accounts_.size()) {
        selectedAccountIndex_ = index;
    }
}

std::vector<std::string> UserSession::getAccountNames() const {
    std::vector<std::string> result;
    for (const auto& account : accounts_) {
        result.push_back(account.getName());
    }
    return result;
}

void UserSession::setPin(const std::string& pin) {
    storedPin_ = pin;
}

std::string UserSession::getStoredPin() const {
    return storedPin_;
}

void UserSession::setUserAuthenticated(bool auth) {
    userAuthenticated_ = auth;
}

bool UserSession::getUserAuthenticated() const {
    return userAuthenticated_;
}

Account* UserSession::getSelectedAccount() {
    if (!selectedAccountIndex_.has_value() || selectedAccountIndex_.value() >= accounts_.size()) {
        return nullptr;
    }
    return &accounts_[selectedAccountIndex_.value()];
}

const Account* UserSession::getSelectedAccount() const {
    if (!selectedAccountIndex_.has_value() || selectedAccountIndex_.value() >= accounts_.size()) {
        return nullptr;
    }
    return &accounts_[selectedAccountIndex_.value()];
}

std::string UserSession::getCardNumber() const {
    return cardNumber_;
}

void UserSession::incrementUnsuccessfulPinCount() {
    unsuccessfulPinCount_++;
}

int UserSession::getUnsuccessfulPinCount() const {
    return unsuccessfulPinCount_;
}

void UserSession::setSelectedOption(MenuOption opt) {
    selectedOption_ = opt;
}

MenuOption UserSession::getSelectedOption() const {
    return selectedOption_;
}

}  // namespace atm
