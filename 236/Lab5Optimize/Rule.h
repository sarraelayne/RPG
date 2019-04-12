#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Predicate.h"
#include "Parameter.h"

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
    

    friend class Predicate;
    friend class Parameter;
    friend class DatalogProgram;
    
    
    private:
    string ruleHeadPredicate;
    string ruleColonDash = ":-";
    string rulePredicate;
    vector<string> rulePredicateList;
    string rulePeriod = ".";
  
};