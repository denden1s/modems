#include "cli.hpp"
#include "modem_creator.hpp"

int main() {
    // parse modem type
    ModemTypes type = ModemTypes::kFoo3;
    string command = "Foo1";
    string param = "test";
    int st;
    ModemCreator* creator = new ConcreteModemTypeCreator();
    CLI cli(creator, type);
    st = cli.ExecuteCommand(command, param);
    return st;
}