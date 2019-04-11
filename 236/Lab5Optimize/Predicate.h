

#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <iostream>
#include <vector>

//#include "Token.h"
//#include "Scanner.h"

using namespace std;

class Predicate {
    
    public:
    Predicate();
    Predicate(string set);
    ~Predicate();
    
    //type functionName(parameter);
    
    string predicateToString();
    void updatePredicateID(string info);
    void updatePredicateParameter(string info);
    void updatePredicateParameterList(string info);
    string getPredicateID();
    string getPredicateParameter();
    vector<string> getPredicateParameterList();
    
    
    //friend class Token;
    //friend class Scanner;
    
    
    private:
    //predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    string predicateID;
    string predicateLeftParen = "(";
    string predicateParameter;
    vector<string> predicateParameterList;
    string predicateRightParen = ")";
    bool isFact = false;
    bool isQuery = false;
    bool isScheme = false;
    bool inRule = false; //returning a Predicate object from the Rule recursion parsing
    bool inQuery = false; //returning a Predicate object from the Query recursion parsing
    
   
};

#endif