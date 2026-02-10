#include "atm/bank/Money.h"
#include <gtest/gtest.h>

using namespace atm;

TEST(Money, AdditionAndGetCents) {
    Money a(100);
    Money b(50);
    Money sum = a + b;
    EXPECT_EQ(sum.getCents(), 150);
}

TEST(Money, Subtraction) {
    Money a(100);
    Money b(30);
    EXPECT_EQ((a - b).getCents(), 70);
}
