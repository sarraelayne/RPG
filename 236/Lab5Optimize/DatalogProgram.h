#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

using namespace std;

class DatalogProgram {
    friend class Predicate;
    friend class Rule;
    friend class Parameter;
    
    public:
    DatalogProgram();
    ~DatalogProgram();
    
    string dpToString();
    void addToFacts(Predicate info);
    void addToQueries(Predicate info);
    void addToSchemes(Predicate info);
    void addToRules(Rule info);
    void addToDomain(string info);
    vector<Predicate> getFacts();
    vector<Predicate> getQueries();
    vector<Predicate> getSchemes();
    vector<Rule> getRules();
    int getFactsSize();
    int getQueriesSize();
    int getSchemesSize();
    int getRulesSize();
    void operator=(const DatalogProgram &temp);
    
    private:
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Predicate> schemes;
    vector<Rule> rules;
    set<string> domain;
    
   
};