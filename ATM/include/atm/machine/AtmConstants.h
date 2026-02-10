#pragma once
// AtmConstants.h - Named limits and AtmConfig.

#include <cstdint>

namespace atm {

namespace constants {

/// Maximum wrong PIN attempts before card is blocked.
inline constexpr int kMaxPinAttempts = 3;
/// Default cash loaded into the dispenser at startup, in cents.
inline constexpr std::int64_t kDefaultInitialCashCents = 10000;
/// Minimum withdrawal amount per transaction, in cents.
inline constexpr std::int64_t kMinWithdrawCents = 1;
/// Maximum withdrawal amount per transaction, in cents.
inline constexpr std::int64_t kMaxWithdrawPerTransactionCents = 1'000'000;

}  // namespace constants

/// Configuration for an ATM instance (limits and initial cash).
struct AtmConfig {
    int maxPinAttempts = constants::kMaxPinAttempts;
    std::int64_t initialCashCents = constants::kDefaultInitialCashCents;
    std::int64_t minWithdrawCents = constants::kMinWithdrawCents;
    std::int64_t maxWithdrawPerTransactionCents = constants::kMaxWithdrawPerTransactionCents;
};

}  // namespace atm
