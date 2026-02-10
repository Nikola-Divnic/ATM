#pragma once
// Money.h - Amount in cents (int64_t for exact arithmetic).

#include <cstdint>

namespace atm {

class Money {
public:
    Money() = default;
    /// Constructs from an amount in cents.
    /// @param cents Amount in cents (can be negative for intermediate calculations).
    explicit Money(std::int64_t cents) : cents_(cents) {}

    /// Creates a Money instance from cents.
    /// @param cents Amount in cents.
    /// @return Money instance.
    static Money fromCents(std::int64_t cents) { return Money(cents); }
    /// Returns the amount in cents.
    /// @return Amount in cents.
    std::int64_t getCents() const { return cents_; }

    Money& operator+=(Money other) { cents_ += other.cents_; return *this; }
    Money& operator-=(Money other) { cents_ -= other.cents_; return *this; }

    friend bool operator<(Money a, Money b) { return a.cents_ < b.cents_; }
    friend bool operator<=(Money a, Money b) { return a.cents_ <= b.cents_; }
    friend bool operator==(Money a, Money b) { return a.cents_ == b.cents_; }
    friend Money operator+(Money a, Money b) { return Money(a.cents_ + b.cents_); }
    friend Money operator-(Money a, Money b) { return Money(a.cents_ - b.cents_); }

private:
    /// Amount in cents; int64_t for exact arithmetic.
    std::int64_t cents_ = 0;
};

}  // namespace atm
