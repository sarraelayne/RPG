#include <iostream>
#include <vector>
#include "parser.h"

using namespace std;

parser::parser () {
    data = datalog();
    tokens = vector<Token>();
    loc = 0;
    curr = Token();
}
parser::parser(vector<Token> tokVector) {
    tokens = tokVector;
    loc = 0;
    curr = tokens[0];
    p = Predicate();
    r = Rule();
    parseDLP();
}
parser::~parser() {}


bool parser::match(TokenType type) {
    if(curr.getTok() == type) {
        loc++;
        if (loc < tokens.size()) {
            curr = tokens.at(loc);
            return true;
        }
        else {
            throw string(curr.toString());
            return false;
        }
    }
    else {
        throw string(curr.toString());
        return false;
    }
    return false;
}


/* -----------------------------------------------------------
PARSERS
--------------------------------------------------------------*/
void parser::parseDLP() {
    match(SCHEMES);
    match(COLON);
    parseScheme();
    parseSchemeList();
    match(FACTS);
    match(COLON);
    parseFactList();
    match(RULES);
    match(COLON);
    parseRuleList();
    match(QUERIES);
    match(COLON);
    parseQuery();
    parseQueryL();
    //match(END);
}
//scheme schemesList | lambda
void parser::parseSchemeList() {
    if(curr.getTok() == ID) {
        parseScheme();
    }
    if(curr.getTok() == ID) {
        parseSchemeList();
    }
}
//ID LEFT_PAREN ID idList RIGHT_PAREN
void parser::parseScheme() {
    p = Predicate(curr.getString());
    match(ID);
    match(LEFT_PAREN);
    if(curr.getTok() == ID) {
        Parameter tempPar(curr.getTok(), curr.getString());
        p.addParam(tempPar);
    }
    match(ID);
    if(curr.getTok() == COMMA) {
        parseIDList();
    }
    match(RIGHT_PAREN);
    data.addScheme(p);
}
//COMMA ID idList | lambda
void parser::parseIDList() {
    match(COMMA);
    if(curr.getTok() == ID) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
    }
    match(ID);
    if(curr.getTok() == COMMA) {
        parseIDList();
    }
}
//fact factList | lambda
void parser::parseFactList() {
    if(curr.getTok() == ID) {
        parseFact();
        if(curr.getTok() == ID) {
            parseFactList();
        }
    }
}
//ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void parser::parseFact() {
    p = Predicate(curr.getString());
    match(ID);
    match(LEFT_PAREN);
    if(curr.getTok() == STRING) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
    }
    match(STRING);
    if(curr.getTok() == COMMA) {
        parseStringL();
    }
    match(RIGHT_PAREN);
    match(PERIOD);
    data.addFact(p);
}
//rule ruleList | lambda
void parser::parseRuleList() {
    if(curr.getTok() == ID) {
        parseRule();
        if(curr.getTok() == ID) {
            parseRuleList();
        }
    }
}
//headPredicate COLON_DASH predicate predicateList PERIOD
void parser::parseRule() {
    parseHeadPred();
    r = Rule(p);
    match(COLON_DASH);
    parsePred();
    if(curr.getTok() == COMMA) {
        parsePredList();
    }
    match(PERIOD);
    data.addRule(r);
}
//query queryList | lambda
void parser::parseQueryL() {
    if(curr.getTok() == END) {
        return;
    }
        parseQuery();
        if(curr.getTok() == ID) {
            parseQueryL();
        }
}
//predicate Q_MARK
void parser::parseQuery() {
    p = Predicate(curr.getString());
    parsePred();
    match(Q_MARK);
    data.addQuery(p);
}
//COMMA STRING stringList | lambda
void parser::parseStringL() {
    match(COMMA);
    if(curr.getTok() == STRING) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
    }
    match(STRING);
    if(curr.getTok() == COMMA) {
        parseStringL();
    }
}
//ID LEFT_PAREN ID idList RIGHT_PAREN
void parser::parseHeadPred() {
    p = Predicate(curr.getString());
    match(ID);
    match(LEFT_PAREN);
    if(curr.getTok() == ID) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
    }
    match(ID);
    if(curr.getTok() == COMMA) {
        parseIDList();
    }
    match(RIGHT_PAREN);
}
//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void parser::parsePred() {
    p = Predicate(curr.getString());
    match(ID);
    match(LEFT_PAREN);
    parseParam();
    if(curr.getTok() == COMMA) {
        parseParamL();
    }
    match(RIGHT_PAREN);
    r.addPred(p);
}
//COMMA predicate predicateList
void parser::parsePredList() {
    match(COMMA);
    parsePred();
    if(curr.getTok() == COMMA) {
        parsePredList();
    }
}
//STRING | ID | expression
void parser::parseParam() {
    if(curr.getTok() == STRING || curr.getTok() == ID) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
        match(curr.getTok());
    }
    if(curr.getTok() == LEFT_PAREN) {
        parseExpression();
    }
}
//COMMA parameter parameterList | lambda
void parser::parseParamL() {
    match(COMMA);
    parseParam();
    if(curr.getTok() == COMMA) {
        parseParamL();
    }
}
//LEFT_PAREN parameter operator parameter RIGHT_PAREN
void parser::parseExpression() {
    p.addParam(Parameter(curr.getTok(), curr.getString()));
    match(LEFT_PAREN);
    parseParam();
    if(curr.getTok() == ADD || curr.getTok() == MULTIPLY) {
        parseOp();
    }
    else {
        throw string(curr.toString());
    }
    //p.addParam(Parameter(exList));
    parseParam();
    p.addParam(Parameter(curr.getTok(), curr.getString()));
    match(RIGHT_PAREN);
}
//ADD | MULTIPLY
void parser::parseOp() {
    if(curr.getTok() == ADD) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
        match(ADD);
    }
    if(curr.getTok() == MULTIPLY) {
        p.addParam(Parameter(curr.getTok(), curr.getString()));
        match(MULTIPLY);
    }
}

datalog parser::getData() {
    return data;
}