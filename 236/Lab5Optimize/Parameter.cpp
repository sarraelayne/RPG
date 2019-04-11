#include "Parameter.h"

Parameter::Parameter(){}

Parameter::Parameter(string ident, string value){
    if(ident == "STRING"){
        isString = true;
        isConst = true;
        parameterString = value;
    }
    else if(ident == "ID"){
        isID = true;
        isConst = false;
        paramID = value;
    }
    else{
        isExpression = true;
        paramExpr = value;
    }
}

Parameter::~Parameter(){}

string Parameter::parameterToString(){
    string temp;
    if(isString){
        temp = parameterString;
    }
    else if(isID){
        temp = paramID;
    }
    else{
        temp = paramExpr;
    }
    return temp;
}

void Parameter::updateParameterString(string info){
    parameterString = info;
}
void Parameter::updateParameterID(string info){
    paramID = info;
}
void Parameter::updateParameterExpression(string info){
    paramExpr = info;
}