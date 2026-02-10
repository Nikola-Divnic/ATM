#pragma once
// UserSession.h - Per-session state (card, PIN, accounts, selected option).

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "atm/bank/Account.h"
#include "atm/machine/MenuOption.h"

namespace atm {

class UserSession {
public:
    /// Constructs a session for the given card.
    /// @param card Card number for this session.
    /// @param initialUnsuccessfulPinCount For tests (default 0).
    explicit UserSession(std::string card, int initialUnsuccessfulPinCount = 0);

    /// Sets the accounts linked to the card (from bank).
    /// @param accountsList Accounts linked to the card.
    void setAccounts(const std::vector<Account>& accountsList);
    /// Returns the mutable account list.
    /// @return Mutable account list.
    std::vector<Account>& getAccounts();
    /// Returns the account list.
    /// @return Account list.
    const std::vector<Account>& getAccounts() const;
    /// Sets the selected account by index.
    /// @param index 0-based index into account list.
    void setSelectedAccount(size_t index);
    /// Returns account display names for prompting.
    /// @return Account display names.
    std::vector<std::string> getAccountNames() const;
    /// Sets the PIN entered by the user.
    /// @param pin PIN entered by user.
    void setPin(const std::string& pin);
    /// Returns the PIN stored for this session.
    /// @return PIN stored for this session.
    std::string getStoredPin() const;
    /// Sets whether the user has been authenticated.
    /// @param auth true after successful PIN verification.
    void setUserAuthenticated(bool auth);
    /// Returns true if the user has entered the correct PIN.
    /// @return true if authenticated.
    bool getUserAuthenticated() const;
    /// Returns the selected account.
    /// @return Selected account or nullptr if none or invalid index.
    Account* getSelectedAccount();
    /// Returns the selected account.
    /// @return Selected account or nullptr if none or invalid index.
    const Account* getSelectedAccount() const;
    /// Returns the card number for this session.
    /// @return Card number.
    std::string getCardNumber() const;
    /// Increments the failed PIN attempt count.
    void incrementUnsuccessfulPinCount();
    /// Returns the number of failed PIN attempts this session.
    /// @return Number of failed PIN attempts.
    int getUnsuccessfulPinCount() const;
    /// Sets the menu option chosen by the user.
    /// @param opt Menu option chosen by user.
    void setSelectedOption(MenuOption opt);
    /// Returns the last chosen menu option.
    /// @return Last chosen menu option.
    MenuOption getSelectedOption() const;

private:
    std::string cardNumber_;
    std::string storedPin_;
    std::vector<Account> accounts_;
    std::optional<size_t> selectedAccountIndex_;
    bool userAuthenticated_ = false;
    int unsuccessfulPinCount_ = 0;
    MenuOption selectedOption_ = MenuOption::CheckBalance;
};

}  // namespace atm
