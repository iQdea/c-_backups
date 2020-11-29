#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <map>
#include "Param.h"

using namespace std;

class Config
{
public:
    void readFile(const string& filename);
    Param& lookup(string sectionName, string paramName);
private:
    smatch matchParts;
    bool sectionFound = false;
    string line;
    string sectionName;
    string paramName;
    string paramValue;
    map<string, map<string, Param>> paramList;
    bool parseEmpty();
    bool parseSection();
    bool parseParam(regex _regex);
    void addParam(string sectionName, Param& param);
    void readFile(ifstream& stream);
};

