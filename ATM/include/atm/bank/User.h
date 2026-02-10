#pragma once
// User.h - User entity with accounts and linked cards.

#include <string>
#include <vector>

#include "atm/bank/Account.h"

namespace atm {

class User {
public:
    /// Constructs a user with the given accounts and cards.
    /// @param userAccounts Initial list of accounts.
    /// @param userCards Initial list of card numbers.
    User(std::vector<Account> userAccounts = {}, std::vector<std::string> userCards = {});

    /// Returns the user's accounts.
    /// @return User's accounts.
    std::vector<Account> getAccounts() const;
    /// Returns the user's linked card numbers.
    /// @return User's linked card numbers.
    std::vector<std::string> getCards() const;
    /// Sets the user's accounts.
    /// @param newAccounts New account list.
    void setAccounts(const std::vector<Account>& newAccounts);
    /// Sets the user's card numbers.
    /// @param newCards New card list.
    void setCards(const std::vector<std::string>& newCards);

private:
    std::vector<Account> accounts;
    std::vector<std::string> cards;
};

}  // namespace atm
