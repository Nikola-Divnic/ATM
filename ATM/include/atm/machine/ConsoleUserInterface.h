#pragma once
// ConsoleUserInterface.h - Console implementation of IUserInterface.

#include "atm/machine/Hardware.h"
#include "atm/machine/IUserInterface.h"

namespace atm {

class ConsoleUserInterface : public IUserInterface {
public:
    /// Constructs the console UI with the given hardware.
    /// @param key Keyboard for text input.
    /// @param scr Screen for output.
    /// @param reader Card reader for card number.
    ConsoleUserInterface(Keyboard& key, Screen& scr, CardReader& reader);
    ~ConsoleUserInterface() override = default;

    std::string readCard() override;
    void showCardInsertedSuccess(const std::string& cardNumber) override;
    void showCardInsertedFailure(const std::string& cardNumber) override;
    std::string readPin() override;
    void showPinAccepted(const std::string& pin) override;
    void showPinRejected(const std::string& pin) override;
    void showCardBlocked(const std::string& cardNumber) override;
    void showCardEjected(const std::string& cardNumber) override;
    int promptAccountChoice(const std::vector<std::string>& accountNames) override;
    MenuOption promptMenuOption() override;
    void showOptionSelected(MenuOption option) override;
    void showBalance(Money balance) override;
    Money promptWithdrawAmount() override;
    void showWithdrawAmount(Money amount) override;
    Money promptDepositAmount() override;
    void showDepositAmount(Money amount) override;
    void promptTakeCard() override;
    void showInsufficientAtmFunds() override;
    void showInsufficientAccountFunds() override;
    void promptInsertEnvelope() override;
    void showDepositSuccess() override;
    void showDepositRejected() override;
    void showInvalidAccountSelection() override;
    void showInvalidNumericInput() override;

private:
    Keyboard& keyboard;
    Screen& screen;
    CardReader& cardReader;
};

}  // namespace atm
