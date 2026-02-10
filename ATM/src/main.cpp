// main.cpp - Entry point: build composition, seed demo data, create and run ATM.

#include "atm/machine/AtmComposition.h"

using namespace atm;

int main() {
    AtmComposition composition;
    composition.seedDemoData();

    std::unique_ptr<ATM> atm = composition.createAtm();
    atm->run();
    return 0;
}
