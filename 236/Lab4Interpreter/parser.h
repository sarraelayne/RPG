#pragma once
#include <iostream>
#include <vector>
#include "datalog.h"
#include "tokens.h"
#include "lexer.h"

using namespace std;

class parser {
public:
    Predicate p;
    Rule r;
    datalog data;
    Token curr;
    unsigned int loc;
    vector<Token> tokens;
    
    parser();
    parser(vector<Token> tokVector);
    ~parser();
    
    
    bool match(TokenType type);
    void parseDLP();
    void parseSchemeList();
    void parseScheme();
    void parseIDList();
    void parseFactList();
    void parseFact();
    void parseRuleList();
    void parseRule();
    void parseQueryL();
    void parseQuery();
    void parseStringL();
    void parseHeadPred();
    void parsePred();
    void parsePredList();
    void parseParam();
    void parseParamL();
    void parseExpression();
    void parseOp();
    
    datalog getData();
};