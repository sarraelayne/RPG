#include "Rule.h"

Rule::Rule(){}

Rule::~Rule(){}

string Rule::ruleToString(){
    //rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    string temp;
    //cout << "Rules(" << numOfRules << "):\n";
    temp += ruleHeadPredicate;
    temp += " :- ";
    temp += rulePredicate;
    for(unsigned int i = 0; i < rulePredicateList.size(); i++){
        string temp1 = rulePredicateList.at(i);
        temp += temp1;
    }
    temp += ".";
    //rules.push_back(temp);
    return temp;
}

void Rule::updateRuleHeadPredicate(string info){
    ruleHeadPredicate = info;
}

void Rule::updateRulePredicate(string info){
    rulePredicate = info;
}

void Rule::updateRulePredicateList(string info){
    rulePredicateList.push_back(info);
}

string Rule::getRuleHeadPredicate(){
    return ruleHeadPredicate;
}
string Rule::getRulePredicate(){
    return rulePredicate;
}
vector<string> Rule::getRulePredicateList(){
    return rulePredicateList;
}