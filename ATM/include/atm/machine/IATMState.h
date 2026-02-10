#pragma once
// IATMState.h - ATM state machine base and concrete states.

#include <memory>
#include <string>
#include <vector>

namespace atm {

class ATM;
class Account;

/// Base class for all ATM states. Each state implements handle() and transitions via setState.
class IATMState {
public:
    /// Constructs the state with the ATM context.
    /// @param context ATM controller (for UI, gateway, session, setState).
    IATMState(ATM* context);
    virtual ~IATMState() = default;
    /// Run one step: read input, perform action, optionally set next state.
    virtual void handle() = 0;
    /// @return State name for tests, e.g. "IdleState".
    virtual std::string name() const = 0;

protected:
    ATM* atm_;
};

class IdleState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class CardInsertedState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class CardNotExistInSystemState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class AskForPINState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class SuccessfulPinState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class UnsuccessfulPinState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class BlockCardState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class ChooseAccountState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class ShowOptionsState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class DecideOptionState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class CheckBalanceState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class WithdrawFundsState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class DepositFundsState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class ExitState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class EjectCardState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

class ResetState : public IATMState {
public:
    using IATMState::IATMState;
    void handle() override;
    std::string name() const override;
};

}  // namespace atm
