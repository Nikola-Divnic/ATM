#pragma once
// AuthService.h - Card and PIN validation, account list per card.
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "atm/bank/Account.h"

namespace atm {

class AuthService {
public:
    /// Returns true if the card is registered and not blocked.
    /// @param card Card number to check.
    /// @return true if card is registered and not blocked.
    bool checkIfCardExist(const std::string& card) const;
    /// Returns true if the PIN matches the one stored for the card.
    /// @param pin PIN to verify.
    /// @param card Card number.
    /// @return true if PIN matches.
    bool checkPIN(const std::string& pin, const std::string& card) const;
    /// Blocks the card so it can no longer be used.
    /// @param card Card number to block.
    void blockCard(const std::string& card);
    /// Returns the accounts linked to the card.
    /// @param card Card number.
    /// @return Accounts linked to the card (empty if unknown).
    std::vector<Account> getAccountListForCard(const std::string& card) const;
    /// Links an account to a card.
    /// @param card Card number.
    /// @param account Account to link.
    void addAccountToCard(const std::string& card, const Account& account);
    /// Sets the PIN for a card.
    /// @param card Card number.
    /// @param pin PIN to associate with the card.
    void setPinForCard(const std::string& card, const std::string& pin);

private:
    std::unordered_map<std::string, std::vector<Account>> cardAccount_;
    std::unordered_set<std::string> blockedCards_;
    std::unordered_map<std::string, std::string> cardToPIN_;
};

}  // namespace atm
