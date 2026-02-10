// MenuOption.cpp - MenuOptionHelper string labels and parsing.

#include "atm/machine/MenuOption.h"

namespace atm {

static const char* const LABEL_CHECK_BALANCE = "check_balance";
static const char* const LABEL_WITHDRAW = "withdraw";
static const char* const LABEL_DEPOSIT = "deposit";
static const char* const LABEL_EXIT = "exit";

std::string MenuOptionHelper::toString(MenuOption option) {
    switch (option) {
        case MenuOption::CheckBalance:
            return LABEL_CHECK_BALANCE;
        case MenuOption::Withdraw:
            return LABEL_WITHDRAW;
        case MenuOption::Deposit:
            return LABEL_DEPOSIT;
        case MenuOption::Exit:
            return LABEL_EXIT;
    }
    return "";
}

std::optional<MenuOption> MenuOptionHelper::parse(const std::string& input) {
    if (input == LABEL_CHECK_BALANCE) return MenuOption::CheckBalance;
    if (input == LABEL_WITHDRAW) return MenuOption::Withdraw;
    if (input == LABEL_DEPOSIT) return MenuOption::Deposit;
    if (input == LABEL_EXIT) return MenuOption::Exit;
    return std::nullopt;
}

std::vector<std::string> MenuOptionHelper::labels() {
    return {
        LABEL_CHECK_BALANCE,
        LABEL_WITHDRAW,
        LABEL_DEPOSIT,
        LABEL_EXIT
    };
}

}  // namespace atm
