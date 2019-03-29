#pragma once
#include <iostream>
#include <vector>
#include "parameter.h"

using namespace std;

class Predicate {
public:
    Predicate();
    Predicate(string identifier);
    Predicate(string identifier, vector<Parameter>paramList);
    ~Predicate();
    
    string predString();
    string getId();
    vector<Parameter> getParams();
    vector<string> getParamStrings();
    void addParam(Parameter param);
    void addEx(Parameter param);
    
    vector<Parameter> paramList;
    vector<Parameter> exList;
    string identifier;
    string Id;
private:
};