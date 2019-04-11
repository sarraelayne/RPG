#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(){}
DatalogProgram::~DatalogProgram(){}


string DatalogProgram::dpToString(){
    string tempStr;
    string size;
    
    size = to_string(schemes.size());
    tempStr+="Schemes(";tempStr+=size;tempStr+="):\n";
    for(unsigned int i = 0; i < schemes.size();i++){
        tempStr+="  ";tempStr+=schemes.at(i).predicateToString();tempStr+="\n";
    }
    
    //Facts
    size = to_string(facts.size());
    tempStr+="Facts(";tempStr+=size;tempStr+="):\n";
    for(unsigned int i = 0; i < facts.size();i++){
        tempStr+="  ";tempStr+=facts.at(i).predicateToString();tempStr+="\n";
    }
    
    //Rules
    size = to_string(rules.size());
    tempStr+="Rules(";tempStr+=size;tempStr+="):\n";
    for(unsigned int i = 0; i < rules.size();i++){
        tempStr+="  ";tempStr+=rules.at(i).ruleToString();tempStr+="\n";
    }
    
    //Queries
    size = to_string(queries.size());
    tempStr+="Queries(";tempStr+=size;tempStr+="):\n";
    for(unsigned int i = 0; i < queries.size();i++){
        tempStr+="  ";tempStr+=queries.at(i).predicateToString();tempStr+="\n";
    }
    
    //Domain
    size = to_string(domain.size());
    tempStr+="Domain(";tempStr+=size;tempStr+="):\n";
    for(set<string>::iterator it=domain.begin(); it!=domain.end(); ++it){
        //cout << ' ' << *it;
        tempStr += "  ";tempStr += *it;tempStr+="\n";
    }
    return tempStr;
}

void DatalogProgram::addToFacts(Predicate info){
    facts.push_back(info);
}
void DatalogProgram::addToQueries(Predicate info){
    queries.push_back(info);
}
void DatalogProgram::addToSchemes(Predicate info){
    schemes.push_back(info);
}
void DatalogProgram::addToRules(Rule info){
    rules.push_back(info);
}
void DatalogProgram::addToDomain(string info){
    domain.insert(info);
}

vector<Predicate> DatalogProgram::getFacts(){
    return facts;
}
vector<Predicate> DatalogProgram::getQueries(){
    return queries;
}
vector<Predicate> DatalogProgram::getSchemes(){
    return schemes;
}
vector<Rule> DatalogProgram::getRules(){
    return rules;
}

int DatalogProgram::getFactsSize(){
    return facts.size();
}
int DatalogProgram::getQueriesSize(){
    return queries.size();
}
int DatalogProgram::getSchemesSize(){
    return schemes.size();
}
int DatalogProgram::getRulesSize(){
    return rules.size();
}

void DatalogProgram::operator=(const DatalogProgram &tempStr){
    this->facts = tempStr.facts;
    this->queries = tempStr.queries;
    this->schemes = tempStr.schemes;
    this->rules = tempStr.rules;
    this->domain = tempStr.domain;
}