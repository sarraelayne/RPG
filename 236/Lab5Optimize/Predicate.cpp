#include "Predicate.h"

Predicate::Predicate(){}

Predicate::Predicate(string set){
    if(set == "f"){//fact
        isFact = true;
    }
    else if(set == "q"){//querie
        isQuery = true;
    }
    else if(set == "s"){//scheme
        isScheme = true;
    }
    else if(set == "ir"){//rule: so a rule is made up of predicates, but rule has it's own class? 
        inRule = true;
    }
    else if(set == "iq"){
        inQuery = true;
    }
    else{
        //not a valid predicate type
    }
}

Predicate::~Predicate(){}

string Predicate::predicateToString(){
    //predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    string temp;
    temp += predicateID;
    temp += "(";
    temp += predicateParameter;
    for(unsigned int i = 0; i < predicateParameterList.size(); i++){  //maybe the parameter list should store parameter objects instead of strings? 
        string temp1 = predicateParameterList.at(i);
        temp += temp1;
    }
    temp += ")";
    if(isFact){
        temp+=".";
    }
    if(isQuery||inQuery){
        temp+="?";
    }
    return temp;
}

void Predicate::updatePredicateID(string info){
    predicateID = info;
}
void Predicate::updatePredicateParameter(string info){
    predicateParameter = info;
}
void Predicate::updatePredicateParameterList(string info){
    predicateParameterList.push_back(info);
}

string Predicate::getPredicateID(){
    return predicateID;
}
string Predicate::getPredicateParameter(){
    return predicateParameter;
}
vector<string> Predicate::getPredicateParameterList(){
    return predicateParameterList;
}