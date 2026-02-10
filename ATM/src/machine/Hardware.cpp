// Hardware.cpp - Keyboard, Screen, CardReader, CashDispenser, DepositSlot.

#include "atm/machine/Hardware.h"
#include "atm/bank/Money.h"
#include <iostream>
#include <limits>

namespace atm {

std::string Keyboard::readLine() {
    std::string line;
    std::cin >> line;
    return line;
}

std::optional<int> Keyboard::readInteger() {
    int value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return std::nullopt;
    }
    return value;
}

void Screen::printMessage(const std::string& message) {
    std::cout << message;
}

std::string CardReader::readCardNumber() {
    std::string cardNumber;
    std::cin >> cardNumber;
    return cardNumber;
}

CashDispenser::CashDispenser(Money initialCash) : available_(initialCash) {}

bool CashDispenser::hasEnoughCash(Money amount) const {
    return amount <= available_;
}

void CashDispenser::dispense(Money amount) {
    if (hasEnoughCash(amount)) {
        available_ = available_ - amount;
    }
}

void CashDispenser::addCash(Money amount) {
    available_ = available_ + amount;
}

Money CashDispenser::getAvailableCash() const {
    return available_;
}

DepositSlot::DepositSlot(CashDispenser& disp) : dispenser_(disp) {}

void DepositSlot::processDeposit(Money amount) {
    dispenser_.addCash(amount);
}

}  // namespace atm
