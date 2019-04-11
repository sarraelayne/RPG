#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"

using namespace std;

class Parser {
        
    friend class Token;
    friend class Scanner;
    friend class DatalogProgram;
    
    public:
    Parser();
    Parser(vector<Token> input);
    ~Parser();
    
    string match(TokenType desiredToken);
    void setVector(vector<Token> input);
    void updateCurrentToken();
    DatalogProgram getDatalogProgram();
    
    void parse();
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    
    string headPredicate();
    Predicate predicate(string setter);
    vector<string> predicateList();
    vector<string> parameterList();
    vector<string> stringList();
    vector<string> idList();
    Parameter parameter();
    string expression(); 
    string operatorGrammar();
    
    private:
    unsigned int iteratorValue = 0;
    vector<Token> tokenStorage;
    Token currTok;
    TokenType currentTokenType;
    DatalogProgram dpObj;
};