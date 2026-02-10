// ConsoleUserInterface.cpp - IUserInterface implementation (console prompts and messages).

#include "atm/machine/ConsoleUserInterface.h"
#include "atm/machine/MenuOption.h"
#include "atm/bank/Money.h"

namespace atm {

ConsoleUserInterface::ConsoleUserInterface(Keyboard& key, Screen& scr, CardReader& reader)
    : keyboard(key), screen(scr), cardReader(reader) {}

std::string ConsoleUserInterface::readCard() {
    screen.printMessage("Please insert card\n");
    return cardReader.readCardNumber();
}

void ConsoleUserInterface::showCardInsertedSuccess(const std::string& cardNumber) {
    screen.printMessage("Card " + cardNumber + " successfully inserted\n");
}

void ConsoleUserInterface::showCardInsertedFailure(const std::string& cardNumber) {
    screen.printMessage("Card " + cardNumber + " was not recognized\n");
}

std::string ConsoleUserInterface::readPin() {
    screen.printMessage("Please enter PIN\n");
    return keyboard.readLine();
}

void ConsoleUserInterface::showPinAccepted(const std::string&) {
    screen.printMessage("PIN accepted\n");
}

void ConsoleUserInterface::showPinRejected(const std::string&) {
    screen.printMessage("PIN rejected. Try again.\n");
}

void ConsoleUserInterface::showCardBlocked(const std::string& cardNumber) {
    screen.printMessage("Card " + cardNumber + " has been blocked.\n");
}

void ConsoleUserInterface::showCardEjected(const std::string& cardNumber) {
    screen.printMessage("Card " + cardNumber + " ejected. Please take your card.\n");
}

MenuOption ConsoleUserInterface::promptMenuOption() {
    for (;;) {
        screen.printMessage("Choose option: check_balance, withdraw, deposit, exit\n");
        std::string input = keyboard.readLine();
        auto option = MenuOptionHelper::parse(input);
        if (option.has_value()) {
            return *option;
        }
        screen.printMessage("Invalid option. Please try again.\n");
    }
}

void ConsoleUserInterface::showOptionSelected(MenuOption option) {
    screen.printMessage("Selected: " + MenuOptionHelper::toString(option) + "\n");
}

void ConsoleUserInterface::showBalance(Money balance) {
    screen.printMessage("Balance (cents): " + std::to_string(balance.getCents()) + "\n");
}

Money ConsoleUserInterface::promptWithdrawAmount() {
    for (;;) {
        screen.printMessage("Enter amount to withdraw (cents, positive): ");
        auto value = keyboard.readInteger();
        if (value.has_value() && *value >= 0) {
            return Money(*value);
        }
        showInvalidNumericInput();
    }
}

void ConsoleUserInterface::showWithdrawAmount(Money amount) {
    screen.printMessage("Withdrawing amount (cents): " + std::to_string(amount.getCents()) + "\n");
}

Money ConsoleUserInterface::promptDepositAmount() {
    for (;;) {
        screen.printMessage("Enter amount to deposit (cents, non-negative): ");
        auto value = keyboard.readInteger();
        if (value.has_value() && *value >= 0) {
            return Money(*value);
        }
        showInvalidNumericInput();
    }
}

void ConsoleUserInterface::showDepositAmount(Money amount) {
    screen.printMessage("Deposit amount (cents): " + std::to_string(amount.getCents()) + "\n");
}

void ConsoleUserInterface::promptTakeCard() {
    screen.printMessage("Please take your card.\n");
}

void ConsoleUserInterface::showInsufficientAtmFunds() {
    screen.printMessage("Error: This ATM does not have enough cash. Try a smaller amount.\n");
}

void ConsoleUserInterface::showInsufficientAccountFunds() {
    screen.printMessage("Error: Insufficient funds in account. Try a smaller amount.\n");
}

void ConsoleUserInterface::promptInsertEnvelope() {
    screen.printMessage("Please insert your deposit envelope into the slot.\n");
}

void ConsoleUserInterface::showDepositSuccess() {
    screen.printMessage("Deposit received. Funds will be available after verification.\n");
}

void ConsoleUserInterface::showDepositRejected() {
    screen.printMessage("Deposit could not be completed. Invalid amount.\n");
}

void ConsoleUserInterface::showInvalidAccountSelection() {
    screen.printMessage("Invalid account selection. Please try again.\n");
}

void ConsoleUserInterface::showInvalidNumericInput() {
    screen.printMessage("Invalid number. Please enter a valid number.\n");
}

int ConsoleUserInterface::promptAccountChoice(const std::vector<std::string>& accountNames) {
    for (;;) {
        screen.printMessage("Choose your account by number:\n");
        for (size_t i = 0; i < accountNames.size(); ++i) {
            screen.printMessage("  " + std::to_string(i + 1) + ". " + accountNames[i] + "\n");
        }
        screen.printMessage("Your choice: ");
        auto value = keyboard.readInteger();
        if (value.has_value()) {
            return *value;
        }
        showInvalidNumericInput();
    }
}

}  // namespace atm
