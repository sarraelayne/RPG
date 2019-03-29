#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "predicate.h"

using namespace std;

class Rule {
public:
    Rule();
    Rule(Predicate p);
    Rule(Predicate pr, vector<Predicate> pList);
    ~Rule();
    
    void addPred(Predicate p);
    string ruleString();
    vector<Predicate> getPredList();
    Predicate getPred();
    
    Predicate p;
    Predicate predicate;
    vector<Predicate> predList;
private:
};