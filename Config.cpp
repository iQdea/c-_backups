#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <map>
#include <exception>
#include "Param.h"
#include "Config.h"
using namespace std;

const string patternName = "[a-zA-Z0-9_/\\-\\.]+";
const string patternString = "[^\\s;]*";
const regex regexEmpty("^\\s*(|;.*)$");
const regex regexSection("^\\s*\\[(" + patternName + ")\\]\\s*(|;.*)$");
const regex regexParamString("^\\s*(" + patternName + ")\\s*=\\s*(" + patternString + ")\\s*(|;.*)$");

void Config::readFile(const string& filename) {
    ifstream stream(filename);
    if (stream.is_open()) {
        readFile(stream);
        stream.close();
    }
    else {
        throw invalid_argument("cannot read file " + filename);
    }
}
Param& Config::lookup(string sectionName, string paramName) {
    if (paramList.count(sectionName) == 0) {
        throw invalid_argument("could find section " + sectionName);
    }
    if (paramList[sectionName].count(paramName) == 0) {
        throw invalid_argument("could find param " + paramName);
    }
    return paramList[sectionName][paramName];
}
bool Config::parseEmpty() {
    if (regex_match(line, matchParts, regexEmpty)) {
        return true;
    }
    return false;
}
bool Config::parseSection() {
    if (regex_match(line, matchParts, regexSection)) {
        sectionFound = true;
        sectionName = matchParts[1].str();
        return true;
    }
    return false;
}
bool Config::parseParam(regex _regex) {
    if (regex_match(line, matchParts, _regex)) {
        paramName = matchParts[1].str();
        paramValue = matchParts[2].str();
        return true;
    }
    return false;
}
void Config::addParam(string sectionName, Param& param) {
    paramList[sectionName][param.getName()] = param;
}
void Config::readFile(ifstream& stream) {
    sectionFound = false;
    while (getline(stream, line)) {
        if (!(parseSection() || parseEmpty())) {
            if (sectionFound && (parseParam(regexParamString)))
            {
                Param param;
                param = Param(paramName, paramValue);
                //cout << sectionName << "." << paramName << "=" << paramValue << endl;
                addParam(sectionName, param);
            }
            else {
                throw invalid_argument("wrong file format for line: " + line);
            }
        }
    }
}
