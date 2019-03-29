#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <cstdio>
#include "tokens.h"
#include "predicate.h"
#include "rule.h"

using namespace std;

class datalog {
public:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    set<string> dom;
    
    datalog();
    ~datalog();
    
    vector<Predicate> getSchemes();
    vector<Predicate> getQueries();
    vector<Predicate> getFacts();
    vector<Rule> getRules();
    void addScheme(Predicate sch);
    void addQuery(Predicate que);
    void addFact(Predicate fac);
    void addRule(Rule rul);
    void addDomain(vector<Parameter> parList);
    
    string schStr();
    string facStr();
    string rulStr();
    string queStr();
    string domStr();
    string dataString();
private: 

};