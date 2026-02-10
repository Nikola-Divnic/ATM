// AtmComposition.cpp - Builds and wires all components; seedDemoData loads demo data.

#include "atm/machine/AtmComposition.h"
#include "atm/bank/CheckingAccount.h"
#include "atm/bank/Money.h"
#include "atm/bank/SavingAccount.h"

namespace atm {

AtmComposition::AtmComposition(AtmConfig config)
    : transactionManager_(config),
      bank_(transactionManager_, authService_),
      cashDispenser_(std::make_shared<CashDispenser>(Money(config.initialCashCents))),
      depositSlot_(std::make_shared<DepositSlot>(*cashDispenser_)),
      ui_(std::make_shared<ConsoleUserInterface>(keyboard_, screen_, cardReader_)),
      gateway_(std::make_shared<Gateway>(bank_)),
      config_(config) {}

void AtmComposition::seedDemoData() {
    authService_.setPinForCard("pera123", "1234");
    SavingAccount saving("Pera saving account", Money(200000));
    CheckingAccount checking;
    authService_.addAccountToCard("pera123", saving);
    authService_.addAccountToCard("pera123", checking);
}

std::unique_ptr<ATM> AtmComposition::createAtm() {
    return std::make_unique<ATM>(ui_, cashDispenser_, depositSlot_, gateway_, config_);
}

}  // namespace atm
