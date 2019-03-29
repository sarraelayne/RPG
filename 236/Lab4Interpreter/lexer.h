#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "tokens.h"

using namespace std;

class lexer
{
public:
    lexer(string name);
    ~lexer();
    string GetChar();
    void tokenTyper();
    void print();
    vector<Token> getTokens();
    string toString(Token input);
    
    vector<Token> tokVector;
private:
    ifstream input;
    stringstream ss;
    string inStr;
    string sstring;
    string commString;
    string idString;
    string undefString;
    int commNum;
    string undefIn;
    int lineNum = 1;
    int totalTokens;
};