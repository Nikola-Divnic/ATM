# ATM

A console-based ATM simulation in C++20: state-machine flow, bank gateway, PIN auth, and balance/withdraw/deposit. Built with clean architecture, modern C++, and testability in mind.

## Features

- **State machine** – Idle → Card inserted → PIN → Account/menu → Balance, Withdraw, Deposit, Exit → Eject
- **Bank layer** – AuthService (cards, PIN, block), TransactionManager (withdraw/deposit limits, validation), Bank as facade
- **ATM layer** – ATM controller, Gateway to bank, ConsoleUserInterface, CashDispenser, DepositSlot
- **Tests** – Google Test; unit tests for Money, TransactionManager, AuthService, and state-machine flows

## Quick start

**Prerequisites:** CMake 3.16+, C++20 compiler (e.g. Visual Studio 2022, GCC 10+, Clang 10+)

From the **project root** (where `CMakeLists.txt` is):

```bash
# Configure
cmake -B build -S . -G "Visual Studio 17 2022" -A x64

# Build
cmake --build build --config Debug

# Run ATM
build\Debug\ATM.exe

# Run tests
build\Debug\ATM_Tests.exe
```

On Linux/macOS:

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ATM
./build/ATM_Tests
```

More detail (project structure, naming, Ninja, CTest): see [BUILD.md](BUILD.md).

## Project layout

| Path | Purpose |
|------|--------|
| `CMakeLists.txt` | Root CMake: `atm_core` lib, `ATM` executable, `ATM_Tests` (Google Test via FetchContent) |
| `ATM/include/atm/` | Headers: `bank/` (Account, AuthService, Bank, Money, …), `machine/` (ATM, Gateway, IATMState, …) |
| `ATM/src/` | Implementations: `bank/`, `machine/`, plus `main.cpp` |
| `ATM/tests/` | Test sources: Money, TransactionManager, AuthService, StateMachine |

## License

This project is for portfolio/assessment use.
