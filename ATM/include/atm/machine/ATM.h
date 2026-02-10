#pragma once
// ATM.h - Main ATM controller (UI, hardware, gateway, state machine).

#include <memory>
#include <string>

#include "atm/machine/AtmConstants.h"
#include "atm/machine/Gateway.h"
#include "atm/machine/Hardware.h"
#include "atm/machine/IATMState.h"
#include "atm/machine/IUserInterface.h"
#include "atm/machine/UserSession.h"

namespace atm {

class ATM {
public:
    /// Constructs the ATM with the given components and config.
    /// @param ui User interface (console or test double).
    /// @param cd Cash dispenser.
    /// @param ds Deposit slot.
    /// @param gw Gateway to the bank.
    /// @param config PIN attempts, cash limits, etc.
    ATM(std::shared_ptr<IUserInterface> ui,
        std::shared_ptr<CashDispenser> cd,
        std::shared_ptr<DepositSlot> ds,
        std::shared_ptr<Gateway> gw,
        AtmConfig config = AtmConfig{});

    /// Sets the current state (used by state handlers to transition).
    /// @param newState Next state instance.
    void setState(std::unique_ptr<IATMState> newState);
    /// Creates a new session for the given card number.
    /// @param cardNumber Card read by the user.
    void createSession(const std::string& cardNumber);
    /// Clears the session (e.g. after eject).
    void resetSession();

    /// Returns the current session.
    /// @return Current session or nullptr.
    UserSession* getSession();
    /// Returns the current session.
    /// @return Current session or nullptr.
    const UserSession* getSession() const;
    /// Returns the ATM configuration.
    /// @return Configuration (PIN attempts, limits).
    const AtmConfig& getConfig() const;
    /// Returns the user interface.
    /// @return User interface.
    std::shared_ptr<IUserInterface> getUI();
    /// Returns the cash dispenser.
    /// @return Cash dispenser.
    std::shared_ptr<CashDispenser> getDispenser();
    /// Returns the deposit slot.
    /// @return Deposit slot.
    std::shared_ptr<DepositSlot> getDepositSlot();
    /// Returns the gateway to the bank.
    /// @return Gateway to the bank.
    std::shared_ptr<Gateway> getGateway();

    /// Runs one state-machine step (for tests).
    void runOnce();
    /// Returns the current state name (for tests).
    /// @return Current state name (e.g. "IdleState").
    std::string getCurrentStateName() const;
    /// Main loop: runs the state machine until process exits.
    void run();

private:
    std::shared_ptr<IUserInterface> ui_;
    std::shared_ptr<CashDispenser> dispenser_;
    std::shared_ptr<DepositSlot> depositSlot_;
    std::shared_ptr<Gateway> gateway_;
    AtmConfig config_;
    std::unique_ptr<IATMState> currentState_;
    std::unique_ptr<UserSession> session_;
};

}  // namespace atm
