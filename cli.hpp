#pragma once

#include "modem.hpp"
#include "modem_creator.hpp"

class CLI {
private:
    Modem* _modem;
    ModemCreator* _creator;
public:
    CLI(ModemCreator* creator, ModemTypes type) {
        _creator = creator;
        _modem = _creator->CreateModem(type);
    }
    int ExecuteCommand(const string &command, const string &params) {
        int st = 1;
        // prepare ...
        st = _modem->ExecuteCommand(command, params);
        // post operations ...
        return st;
    }
    ~CLI() {
        delete _modem;
    }
};