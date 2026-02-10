# Building with CMake

## Project structure

The code is split to reflect a real ATM setup:

- **`atm/bank/`** – Bank service (not on the machine): accounts, auth, transactions, bank facade.
- **`atm/machine/`** – ATM device: controller, state machine, session, UI/hardware, and the gateway that talks to the bank.

### Key types

- **AtmComposition** – Composition root: it creates and wires all dependencies (TransactionManager, AuthService, Bank, Gateway, UI, CashDispenser, etc.). You call `seedDemoData()` to load demo card/accounts, then `createAtm()` to get a ready-to-run `ATM`. So you don’t build an ATM by hand; you build a composition and ask it for an ATM.
- **MenuOption** – Enum for the main menu (CheckBalance, Withdraw, Deposit, Exit). Used by the state machine and UI so we don’t rely on magic strings or numbers.
- **Money** – Amount stored as cents in `std::int64_t` to avoid floating-point rounding and to support large amounts; 64-bit integers are a common choice for money in C++.
- **Logger** – Writes to **standard error (stderr)**. When you run the ATM from a console, log lines (e.g. from TransactionManager: “Withdraw rejected”, “Card blocked”) appear on that console. There is no separate log file unless you redirect stderr.

### Naming

- **Member variables** use a trailing underscore (e.g. `ui_`, `config_`). This is a common C++ style (e.g. Google C++ Style) to avoid name shadowing and to distinguish data members from parameters/local variables.

## Prerequisites

- CMake 3.16 or later
- A C++20 compiler (e.g. Visual Studio 2022, GCC 10+, Clang 10+)

## Windows (Visual Studio)

From the project root:

```bat
cmake -B build -S . -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

Run the executable:

```bat
build\Debug\ATM.exe
```

For Release:

```bat
cmake --build build --config Release
build\Release\ATM.exe
```

## Windows (Ninja or other generator)

```bat
cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
build\ATM.exe
```

## Linux / macOS

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/ATM
```

## Tests

The project uses [Google Test](https://github.com/google/googletest). The first configure will download it via CMake FetchContent.

After building:

**Windows (Visual Studio generator):**
```bat
build\Debug\ATM_Tests.exe
```

**Windows (Ninja) / Linux / macOS:**
```bat
build\ATM_Tests
```

Or run all tests through CTest (from project root):
```bat
cd build
ctest -C Debug --output-on-failure
```
