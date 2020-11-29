#pragma once
#include <string>
#include <sstream>
#include <exception>

using namespace std;

class Param {
public:
    Param() {}
    Param(string _name, string _value) { name = _name; value = _value; }
    string getName() { return name; }
    template<typename T> T getValue() {
        try {
            T res;
            stringstream ss;
            ss.exceptions(ios::failbit);
            ss << value;
            ss >> res;
            return res;
        }
        catch (...) {
            throw invalid_argument("type cast is impossible, value=" + value);
        }
    }
private:
    string name = "";
    string value = "";
};


