cmake_minimum_required(VERSION 3.16)
project(ATM LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ATM_APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ATM)

# --- Core library (shared by ATM app and tests) ---
add_library(atm_core STATIC
  ${ATM_APP_DIR}/src/bank/Account.cpp
  ${ATM_APP_DIR}/src/bank/AuthService.cpp
  ${ATM_APP_DIR}/src/bank/Bank.cpp
  ${ATM_APP_DIR}/src/bank/TransactionManager.cpp
  ${ATM_APP_DIR}/src/bank/User.cpp
  ${ATM_APP_DIR}/src/machine/ATM.cpp
  ${ATM_APP_DIR}/src/machine/AtmComposition.cpp
  ${ATM_APP_DIR}/src/machine/ConsoleUserInterface.cpp
  ${ATM_APP_DIR}/src/machine/Gateway.cpp
  ${ATM_APP_DIR}/src/machine/Hardware.cpp
  ${ATM_APP_DIR}/src/machine/IATMState.cpp
  ${ATM_APP_DIR}/src/machine/MenuOption.cpp
  ${ATM_APP_DIR}/src/machine/UserSession.cpp
)
target_include_directories(atm_core PUBLIC ${ATM_APP_DIR}/include)

# --- Main ATM executable ---
add_executable(ATM ${ATM_APP_DIR}/src/main.cpp)
target_link_libraries(ATM PRIVATE atm_core)
target_include_directories(ATM PRIVATE ${ATM_APP_DIR}/include)

# --- Google Test (for ATM_Tests) ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# --- Test executable ---
add_executable(ATM_Tests
  ${ATM_APP_DIR}/tests/Money_test.cpp
  ${ATM_APP_DIR}/tests/TransactionManager_test.cpp
  ${ATM_APP_DIR}/tests/AuthService_test.cpp
  ${ATM_APP_DIR}/tests/StateMachine_test.cpp
)
target_link_libraries(ATM_Tests PRIVATE atm_core GTest::gtest_main)
target_include_directories(ATM_Tests PRIVATE ${ATM_APP_DIR}/include)
include(GoogleTest)
gtest_discover_tests(ATM_Tests)

# --- Compiler warnings ---
if(MSVC)
  target_compile_options(atm_core PRIVATE /W4 /utf-8)
  target_compile_options(ATM PRIVATE /W4 /utf-8)
  target_compile_options(ATM_Tests PRIVATE /W4 /utf-8)
else()
  target_compile_options(atm_core PRIVATE -Wall -Wextra -pedantic)
  target_compile_options(ATM PRIVATE -Wall -Wextra -pedantic)
  target_compile_options(ATM_Tests PRIVATE -Wall -Wextra -pedantic)
endif()
