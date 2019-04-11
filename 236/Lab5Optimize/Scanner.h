#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner {
    
    friend class Token;
    friend class Parser;
    
    public:
    Scanner(string fileName);
    ~Scanner();
    
    void scanToken();
    int getCurrentLineNum();
    void printTokens();
    vector<Token> returnVector();

    private:
    int loc = 1;
    int numToks = 0;
    bool wsPresent = false;
    char currentChar;
    ifstream ifs;
    vector<Token> tokenVector;
};