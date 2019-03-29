#include <iostream>
#include <vector>
#include "rule.h"

using namespace std;

Rule::Rule() {
    predicate = Predicate();
    predList = vector<Predicate>();
}
Rule::Rule(Predicate p) {
    predicate = p;
    predList = vector<Predicate>();
}
Rule::Rule(Predicate pr, vector<Predicate> pList) {
    predicate = p;
    predList = pList;
}
Rule::~Rule() {}


void Rule::addPred(Predicate p) {
    predList.push_back(p);
}
vector<Predicate> Rule::getPredList() {
    return predList;
}
Predicate Rule::getPred() {
    stringstream ss;
    ss << predicate.predString() << " :- ";
    for(unsigned int i; i < predList.size(); i++) {
        if(i == 0) {
            ss << predList[i].predString();
        }
        else {
            ss << "," << predList[i].predString();
        }
    }
    ss << ".";
    return ss.str();
}
string Rule::ruleString() {
    stringstream ss;
    ss << predicate.predString() << " :- ";
    for (unsigned int i = 0; i < predList.size(); i++) {
        if(i == 0) {
            ss << predList[i].predString();
        }
        else {
            ss << "," << predList[i].predString();
        }
    }
    ss << ".";
    return ss.str();
}