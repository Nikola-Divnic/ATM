// ATM.cpp - Main ATM controller; runs the state machine.

#include "atm/machine/ATM.h"
#include "atm/machine/IATMState.h"

namespace atm {

ATM::ATM(std::shared_ptr<IUserInterface> ui,
         std::shared_ptr<CashDispenser> cd,
         std::shared_ptr<DepositSlot> ds,
         std::shared_ptr<Gateway> gw,
         AtmConfig config)
    : ui_(ui), dispenser_(cd), depositSlot_(ds), gateway_(gw), config_(config) {
    setState(std::make_unique<IdleState>(this));
}

void ATM::setState(std::unique_ptr<IATMState> newState) {
    currentState_ = std::move(newState);
}

void ATM::createSession(const std::string& cardNumber) {
    session_ = std::make_unique<UserSession>(cardNumber);
}

void ATM::resetSession() {
    session_.reset();
}

void ATM::runOnce() {
    if (currentState_) {
        currentState_->handle();
    }
}

std::string ATM::getCurrentStateName() const {
    return currentState_ ? currentState_->name() : "";
}

UserSession* ATM::getSession() {
    return session_.get();
}

const UserSession* ATM::getSession() const {
    return session_.get();
}

const AtmConfig& ATM::getConfig() const {
    return config_;
}

std::shared_ptr<IUserInterface> ATM::getUI() {
    return ui_;
}

std::shared_ptr<CashDispenser> ATM::getDispenser() {
    return dispenser_;
}

std::shared_ptr<DepositSlot> ATM::getDepositSlot() {
    return depositSlot_;
}

std::shared_ptr<Gateway> ATM::getGateway() {
    return gateway_;
}

void ATM::run() {
    while (true) {
        runOnce();
    }
}

}  // namespace atm
