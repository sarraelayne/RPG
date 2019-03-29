#include <iostream>
#include <vector>
#include "predicate.h"

using namespace std;

Predicate::Predicate() {
    Id = "";
    paramList = vector<Parameter>();
}
Predicate::Predicate(string identifier) {
    Id = identifier;
    paramList = vector<Parameter>();
}
Predicate::Predicate(string identifier, vector<Parameter> parList) {
    Id = identifier;
    paramList = parList;
}
Predicate::~Predicate() {}

string Predicate::getId() {
    return Id;
}
vector<Parameter> Predicate::getParams() {
    return paramList;
}
vector<string> Predicate::getParamStrings()
{
	vector<string> pStr;
	for (unsigned i = 0; i < paramList.size(); i++) {
		pStr.push_back(paramList[i].getString());
	}
	return pStr;
}
void Predicate::addParam(Parameter param) {
    paramList.push_back(param);
}
void Predicate::addEx(Parameter param) {
    exList.push_back(param);
}
string Predicate::predString() {
    stringstream ss;
    ss << Id << "(";
    for(unsigned int i = 0; i < paramList.size(); i++) {
        if(i == 0) {
            ss << paramList.at(i).paramString();
        }
        else if(paramList.at(i-1).paramString() == "(") {
            ss << paramList.at(i).paramString();
        }
        else if (paramList.at(i).paramString() == ")") {
            ss << paramList.at(i).paramString();
        }
        else if (paramList.at(i).paramString() == "+" || paramList.at(i).paramString() == "*") {
            ss << paramList.at(i).paramString();
        }
        else if(paramList.at(i-1).paramString() == "+" || paramList.at(i-1).paramString() == "*") {
            ss << paramList.at(i).paramString();
        }
        else {
                ss << "," << paramList.at(i).paramString();
        }
    }
    ss << ")";
    return ss.str();
}