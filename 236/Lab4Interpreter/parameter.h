#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "tokens.h"


using namespace std;

class Parameter {
public:
    Parameter();
    Parameter(TokenType tokType, string tokString);
    ~Parameter();
    TokenType getTok();
    string getString();
    string paramString();
    
    TokenType tokType;
    string tokString;
private:
};