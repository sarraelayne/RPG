#include <iostream>
#include <vector>
#include "datalog.h"

using namespace std;

datalog::datalog() {
    schemes = vector<Predicate>();
    facts = vector<Predicate>();
    queries = vector<Predicate>();
    rules = vector<Rule>();
    dom = set<string>();
}
datalog::~datalog() {}

vector<Predicate> datalog::getSchemes() {
    return schemes;
}
vector<Predicate> datalog::getQueries() {
    return queries;
}
vector<Predicate> datalog::getFacts() {
    return facts;
}
vector<Rule> datalog::getRules() {
    return rules;
}
void datalog::addScheme(Predicate sch) {
    schemes.push_back(sch);
}
void datalog::addQuery(Predicate que) {
    queries.push_back(que);
}
void datalog::addFact(Predicate fac) {
    facts.push_back(fac);
    addDomain(fac.getParams());
}
void datalog::addRule(Rule rul) {
    rules.push_back(rul);
}
void datalog::addDomain(vector<Parameter> parList) {
    for(unsigned int i = 0; i < parList.size(); i++) {
        dom.insert(parList.at(i).getString());
    }
}


string datalog::schStr() {
    stringstream ss;
    ss << "Schemes(" << schemes.size() << "):";
    for(unsigned int i = 0; i < schemes.size(); i++) {
        ss << endl;
        ss << "  " << schemes.at(i).predString();
    }
    return ss.str();
}
string datalog::facStr() {
    stringstream ss;
    ss << "Facts(" << facts.size() << "):";
    for(unsigned int i = 0; i < facts.size(); i++) {
        ss << endl;
        ss << "  " << facts.at(i).predString() << ".";
    }
    return ss.str();
}
string datalog::rulStr() {
    stringstream ss;
    ss << "Rules(" << rules.size() << "):";
    for(unsigned int i = 0; i < rules.size(); i++) {
        ss << endl;
        ss << "  " << rules.at(i).ruleString();
    }
    return ss.str();
}
string datalog::queStr() {
    stringstream ss;
    ss << "Queries(" << queries.size() << "):";
    for(unsigned int i = 0; i < queries.size(); i++) {
        ss << endl;
        ss << "  " << queries.at(i).predString() << "?";
    }
    return ss.str();
}
string datalog::domStr() {
    stringstream ss;
    ss << "Domain(" << dom.size() << "):";
    set<string>::iterator itr;
    for(itr = dom.begin(); itr != dom.end(); itr++) {
        ss << endl;
        ss << "  " << (*itr);
    }
    return ss.str();
}
string datalog::dataString() {
    stringstream ss;
    ss << "Success!" << endl;
    ss << schStr() << endl;
    ss << facStr() << endl;
    ss << rulStr() << endl;
    ss << queStr() << endl;
    ss << domStr() << endl;
    return ss.str();
}