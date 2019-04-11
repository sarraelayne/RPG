

#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>
#include <vector>
#include "Predicate.h"
#include "Parameter.h"
//#include "DatalogProgram.h"
//#include "Token.h"
//#include "Scanner.h"

using namespace std;

class Rule {
    
    public:
    Rule();
    ~Rule();
    
    //type functionName(parameter);
    string ruleToString();
    void updateRuleHeadPredicate(string info);
    void updateRulePredicate(string info);
    void updateRulePredicateList(string info);
    string getRuleHeadPredicate();
    string getRulePredicate();
    vector<string> getRulePredicateList();
    
    
    //friend class Token;
    //friend class Scanner;
    friend class Predicate;
    friend class Parameter;
    friend class DatalogProgram;
    
    
    private:
    //rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    string ruleHeadPredicate;
    string ruleColonDash = ":-";
    string rulePredicate;
    vector<string> rulePredicateList;
    string rulePeriod = ".";
  
};

#endif