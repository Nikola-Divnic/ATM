#pragma once
// Hardware.h - Console I/O and cash hardware (keyboard, screen, dispenser, deposit slot).

#include <optional>
#include <string>

#include "atm/bank/Money.h"

namespace atm {

class Keyboard {
public:
    /// Reads one line of text from the user.
    /// @return One line of text.
    std::string readLine();
    /// Reads and parses an integer; clears stream on failure.
    /// @return Parsed integer, or nullopt if input was invalid.
    std::optional<int> readInteger();
};

class Screen {
public:
    /// Displays a message to the user.
    /// @param message Text to display.
    void printMessage(const std::string& message);
};

class CardReader {
public:
    /// Reads the card number from the user.
    /// @return Card number read from user.
    std::string readCardNumber();
};

class CashDispenser {
public:
    /// Constructs the dispenser with the given initial cash.
    /// @param initialCash Starting cash in cents.
    explicit CashDispenser(Money initialCash = Money(10000));
    /// Returns true if the dispenser has at least the given amount.
    /// @param amount Amount to dispense.
    /// @return true if dispenser has at least that amount.
    bool hasEnoughCash(Money amount) const;
    /// Dispenses the amount (reduces available cash).
    /// @param amount Amount to dispense.
    void dispense(Money amount);
    /// Adds cash (e.g. from a deposit).
    /// @param amount Amount to add.
    void addCash(Money amount);
    /// Returns the current available cash.
    /// @return Current available cash in cents.
    Money getAvailableCash() const;

private:
    Money available_;
};

class DepositSlot {
public:
    /// Constructs the deposit slot with the dispenser to add cash to.
    /// @param disp Cash dispenser to add deposited cash to.
    explicit DepositSlot(CashDispenser& disp);
    /// Processes a deposit (adds amount to dispenser).
    /// @param amount Amount deposited.
    void processDeposit(Money amount);

private:
    CashDispenser& dispenser_;
};

}  // namespace atm
