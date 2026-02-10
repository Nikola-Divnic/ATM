#pragma once
// IUserInterface.h - Abstract interface for user input and output.

#include <string>
#include <vector>

#include "atm/bank/Money.h"
#include "atm/machine/MenuOption.h"

namespace atm {

class IUserInterface {
public:
    virtual ~IUserInterface() = default;

    /// Reads the card number from the user.
    /// @return Card number (empty if none).
    virtual std::string readCard() = 0;
    /// Shows that the card was accepted.
    /// @param cardNumber Card that was accepted.
    virtual void showCardInsertedSuccess(const std::string& cardNumber) = 0;
    /// Shows that the card was rejected.
    /// @param cardNumber Card that was rejected.
    virtual void showCardInsertedFailure(const std::string& cardNumber) = 0;
    /// Reads the PIN from the user.
    /// @return PIN entered by user.
    virtual std::string readPin() = 0;
    /// Shows that the PIN was accepted.
    /// @param pin PIN that was accepted.
    virtual void showPinAccepted(const std::string& pin) = 0;
    /// Shows that the PIN was rejected.
    /// @param pin PIN that was rejected.
    virtual void showPinRejected(const std::string& pin) = 0;
    /// Shows that the card was blocked.
    /// @param cardNumber Card that was blocked.
    virtual void showCardBlocked(const std::string& cardNumber) = 0;
    /// Shows that the card was ejected.
    /// @param cardNumber Card that was ejected.
    virtual void showCardEjected(const std::string& cardNumber) = 0;
    /// Prompts the user to choose an account by number.
    /// @param accountNames Names of accounts to choose from.
    /// @return 1-based index of selected account.
    virtual int promptAccountChoice(const std::vector<std::string>& accountNames) = 0;
    /// Prompts the user to choose a menu option.
    /// @return Menu option chosen by user.
    virtual MenuOption promptMenuOption() = 0;
    /// Shows the option that was selected.
    /// @param option Option that was selected.
    virtual void showOptionSelected(MenuOption option) = 0;
    /// Shows the current account balance.
    /// @param balance Current account balance to display.
    virtual void showBalance(Money balance) = 0;
    /// Prompts the user for the amount to withdraw.
    /// @return Amount to withdraw in cents.
    virtual Money promptWithdrawAmount() = 0;
    /// Shows the amount being dispensed.
    /// @param amount Amount being dispensed.
    virtual void showWithdrawAmount(Money amount) = 0;
    /// Prompts the user for the amount to deposit.
    /// @return Amount to deposit in cents.
    virtual Money promptDepositAmount() = 0;
    /// Shows the amount being deposited.
    /// @param amount Amount being deposited.
    virtual void showDepositAmount(Money amount) = 0;
    /// Prompts the user to take the card.
    virtual void promptTakeCard() = 0;
    /// Shows that the ATM has insufficient cash.
    virtual void showInsufficientAtmFunds() = 0;
    /// Shows that the account has insufficient funds.
    virtual void showInsufficientAccountFunds() = 0;
    /// Prompts the user to insert the deposit envelope.
    virtual void promptInsertEnvelope() = 0;
    /// Shows that the deposit was accepted.
    virtual void showDepositSuccess() = 0;
    /// Shows that the deposit was rejected.
    virtual void showDepositRejected() = 0;
    /// Shows that the account selection was invalid.
    virtual void showInvalidAccountSelection() = 0;
    /// Shows that the numeric input was invalid.
    virtual void showInvalidNumericInput() = 0;
};

}  // namespace atm
