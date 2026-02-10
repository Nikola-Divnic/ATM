#pragma once
// MenuOption.h - Main menu choices and helper for string conversion and parsing.

#include <optional>
#include <string>
#include <vector>

namespace atm {

/// Main menu options after the user has selected an account.
enum class MenuOption {
    CheckBalance,
    Withdraw,
    Deposit,
    Exit
};

/// Helper for converting between MenuOption and strings (UI prompts, display).
class MenuOptionHelper {
public:
    /// Returns the string label for the given option.
    /// @param option The menu option to convert.
    /// @return Label string (e.g. "check_balance"), or empty if unknown.
    static std::string toString(MenuOption option);

    /// Parses user input into a MenuOption.
    /// @param input User input (e.g. "withdraw", "exit").
    /// @return The corresponding MenuOption, or nullopt if not recognized.
    static std::optional<MenuOption> parse(const std::string& input);

    /// Returns all valid menu labels for prompting the user.
    /// @return Vector of strings in display order.
    static std::vector<std::string> labels();
};

}  // namespace atm
