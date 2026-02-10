#pragma once
// AtmComposition.h - Composition root: creates and wires all ATM dependencies.

#include <memory>

#include "atm/bank/AuthService.h"
#include "atm/bank/Bank.h"
#include "atm/bank/TransactionManager.h"
#include "atm/machine/ATM.h"
#include "atm/machine/AtmConstants.h"
#include "atm/machine/ConsoleUserInterface.h"
#include "atm/machine/Gateway.h"
#include "atm/machine/Hardware.h"
#include "atm/machine/IUserInterface.h"

namespace atm {

class AtmComposition {
public:
    /// Constructs the composition with the given config.
    /// @param config Optional config (default: AtmConstants).
    explicit AtmComposition(AtmConfig config = AtmConfig{});

    /// Loads demo card and accounts (e.g. pera123 / 1234).
    void seedDemoData();
    /// Builds and returns a fully wired ATM instance.
    /// @return Fully wired ATM instance ready to run.
    std::unique_ptr<ATM> createAtm();

private:
    TransactionManager transactionManager_;
    AuthService authService_;
    Bank bank_;
    Keyboard keyboard_;
    Screen screen_;
    CardReader cardReader_;
    std::shared_ptr<CashDispenser> cashDispenser_;
    std::shared_ptr<DepositSlot> depositSlot_;
    std::shared_ptr<ConsoleUserInterface> ui_;
    std::shared_ptr<Gateway> gateway_;
    AtmConfig config_;
};

}  // namespace atm
