#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Parameter {
    
    public:
    Parameter();
    Parameter(string ident, string value);
    ~Parameter();
    
    string parameterToString();
    void updateParameterString(string info);
    void updateParameterID(string info);
    void updateParameterExpression(string info);
    
    private:
    string parameterString;
    string paramID;
    string paramExpr;
    bool isString = false;
    bool isID = false;
    bool isExpression = false;
    bool isConst = false;
};