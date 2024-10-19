#pragma once
#include "modem.hpp"

enum class ModemTypes {
    kFoo,
    kFoo2,
    kFoo3,
};

class ModemCreator {
public:
    virtual Modem* CreateModem(ModemTypes type) = 0;
    ModemCreator(){}
};

class ConcreteModemTypeCreator : public ModemCreator {
public:
    ConcreteModemTypeCreator() : ModemCreator() {

    }
    Modem* CreateModem(ModemTypes type) override {
        switch (type) {
            case ModemTypes::kFoo:
                return new ConcreteModem();
            case ModemTypes::kFoo2:
                return new SecondModem();
            case ModemTypes::kFoo3:
                return new DoubleInheritModem();
            default:
                return nullptr;
        }
    }
};