#pragma once
// Logger.h - Logging for ATM events. Output goes to stderr.

#include <iostream>
#include <sstream>
#include <string>

namespace atm {

class Logger {
public:
    /// Writes a single line to stderr with "[ATM] " prefix.
    /// @param message Full message to log.
    static void log(const std::string& message) {
        std::cerr << "[ATM] " << message << std::endl;
    }

    /// Writes "event: detail" to stderr.
    /// @param event Event name (e.g. "Card blocked").
    /// @param detail Detail (e.g. card number).
    template <typename T>
    static void log(const std::string& event, const T& detail) {
        std::ostringstream os;
        os << event << ": " << detail;
        log(os.str());
    }
};

}  // namespace atm
