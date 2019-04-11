#pragma once
#include <string>
#include <iostream>
#include "Scheme.h"
#include "Relation.h"
#include "Tuple.h"
#include "Database.h"
#include "DatalogProgram.h"
#include "Predicate.h"

using namespace std;

class Interpreter {
    friend class Scheme;
    friend class Relation;
    friend class Tuple;
    
    public:
    Interpreter(DatalogProgram var);
    ~Interpreter();
    
    //Lab4
    Relation evalRule(Rule ruleObj);
    void evalAllRules();
    Predicate parseRulePredicate(string predicate);
    
    //Lab3
    Relation evalQuery(Predicate queryPredicate);
    void evalAllQueries();
    
    private:
    DatalogProgram dp;
    Database db;
    vector<Relation> queryResults;
    vector<Relation> ruleResults;
};