// TransactionManager.cpp - Balance, withdraw, deposit; rejections logged to stderr.
#include "atm/bank/TransactionManager.h"
#include "atm/machine/AtmConstants.h"
#include "atm/machine/Logger.h"
#include <cstdint>

namespace atm {

TransactionManager::TransactionManager()
    : minWithdrawCents_(constants::kMinWithdrawCents),
      maxWithdrawPerTransactionCents_(constants::kMaxWithdrawPerTransactionCents) {}

TransactionManager::TransactionManager(const AtmConfig& config)
    : minWithdrawCents_(config.minWithdrawCents),
      maxWithdrawPerTransactionCents_(config.maxWithdrawPerTransactionCents) {}

Money TransactionManager::showBalance(const Account* account) const {
    return account->getAmount();
}

bool TransactionManager::withdrawCash(Account* account, Money amount) {
    if (!account) return false;
    const std::int64_t cents = amount.getCents();
    if (cents <= 0) {
        Logger::log("Withdraw rejected", "amount must be positive");
        return false;
    }
    if (cents < minWithdrawCents_) {
        Logger::log("Withdraw rejected", "amount below minimum");
        return false;
    }
    if (cents > maxWithdrawPerTransactionCents_) {
        Logger::log("Withdraw rejected", "amount exceeds per-transaction limit");
        return false;
    }
    if (account->getAmount() < amount) {
        Logger::log("Withdraw failed", "insufficient account funds");
        return false;
    }
    account->setAmount(account->getAmount() - amount);
    return true;
}

bool TransactionManager::depositCash(Account* account, Money amount) {
    if (!account) return false;
    if (amount.getCents() < 0) {
        Logger::log("Deposit rejected", "negative amount");
        return false;
    }
    account->setAmount(account->getAmount() + amount);
    return true;
}

}  // namespace atm
