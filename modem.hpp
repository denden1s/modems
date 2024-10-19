#pragma once
#include <map>
#include <string>
#include <functional>
#include <utility>
#include <iostream>

using namespace std;

class Modem {
private:
    map< const char*, function<int(string)> > _unique_funcs;
    map< const char*, function<int(string)> > _standart_funcs;
    int Foo(string str) { 
        cout << "Foo arg: " << str << endl;
        return 0;
    }

    int Foo1(string str){
        cout << "Foo1 arg: " << str << endl;
        return 1;
    }
protected:
    int ClearUnique() {
        _unique_funcs.clear();
        return 0;
    }

    int AddUniqueFunc(std::pair<const char*, function<int(string)>> func) {
        // validate ...
        _unique_funcs.insert(func);
        return 0;
    }

    int AddStandartFunc(std::pair<const char*, function<int(string)>> func) {
        // validate ...
        _standart_funcs.insert(func);
        return 0;
    }
public:
    Modem() {
        AddStandartFunc(make_pair("Foo", std::bind(&Modem::Foo, this, std::placeholders::_1)));
        AddStandartFunc(make_pair("Foo1", std::bind(&Modem::Foo1, this, std::placeholders::_1)));
    }

    virtual ~Modem() {
        // for delete all allocated memory
    }

    int ExecuteCommand(const string &command_name, const string &param) {
        cout << "Run CLI ExecuteCommand:" << command_name.c_str() << endl;
        map<const char*, function<int(string)>>::iterator it;

        for (it = _standart_funcs.begin(); it != _standart_funcs.end(); it++)
            if(command_name == it->first)
                return it->second(param);

        for (it = _unique_funcs.begin(); it != _unique_funcs.end(); it++)
            if(command_name == it->first)
                return it->second(param);

        cout << "Cant find command" << endl;
        return 1;
    }
};

class ConcreteModem : public Modem {
private:
    int Foo2(string str) {
        cout << "Foo2 arg: " << str << endl;
        return 2;
    }

    int Foo3(string str) {
        cout << "Foo3 arg: " << str << endl;
        return 3;
    }
public: 
    ConcreteModem() : Modem() {
        AddUniqueFunc(make_pair("Foo2", std::bind(&ConcreteModem::Foo2, this, std::placeholders::_1)));
        AddUniqueFunc(make_pair("Foo3", std::bind(&ConcreteModem::Foo3, this, std::placeholders::_1)));
    }  
    ~ConcreteModem() {
        // remove all allocated and go to parent destructor
    } 
};

class SecondModem : public Modem {
    private:
    int Foo2(string str) {
        cout << "Foo2 SecondModem arg: " << str << endl;
        return 2;
    }
    int Foo3(string str) {
        cout << "Foo3 SecondModem arg: " << str << endl;
        return 3;
    }
public: 
    SecondModem() : Modem() {
        AddUniqueFunc(make_pair("Foo2", std::bind(&SecondModem::Foo2, this, std::placeholders::_1)));
        AddUniqueFunc(make_pair("Foo3", std::bind(&SecondModem::Foo3, this, std::placeholders::_1)));
        cout << "Init SecondModem" << endl;
    }  
    ~SecondModem() {
        // remove all allocated and go to parent destructor
    } 
};

// Inherit for scale standart functional
class DoubleInheritModem : public SecondModem {
    private:
    int Foo4(string str) {
        cout << "Foo4 DoubleInheritModem arg: " << str << endl;
        return 2;
    }
    int Foo5(string str) {
        cout << "Foo5 DoubleInheritModem arg: " << str << endl;
        return 3;
    }
public: 
    DoubleInheritModem() : SecondModem() {
        ClearUnique(); // drop unique func from SecondModem mb bad realization
        AddUniqueFunc(make_pair("Foo4", std::bind(&DoubleInheritModem::Foo4, this, std::placeholders::_1)));
        AddUniqueFunc(make_pair("Foo5", std::bind(&DoubleInheritModem::Foo5, this, std::placeholders::_1)));
        cout << "Init SecondModem" << endl;
    }  
    ~DoubleInheritModem() {
        // remove all allocated and go to parent destructor
    } 
};