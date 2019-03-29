#include <iostream>
#include <vector>
#include <string>
#include "parameter.h"

using namespace std;

Parameter::Parameter() {
    tokType = UNDEFINED;
    tokString = "";
}
Parameter::Parameter(TokenType type, string str) {
    tokType = type;
    tokString = str;
}
Parameter::~Parameter() {}

TokenType Parameter::getTok() {
    return tokType;
}
string Parameter::getString() {
    return tokString;
}
string Parameter::paramString() {
    return getString();
}