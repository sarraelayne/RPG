

#include "Parser.h"

Parser::Parser(){
    currTok = tokenStorage.at(iteratorValue);
}
Parser::Parser(vector<Token> input){
    tokenStorage = input;
    if(iteratorValue < tokenStorage.size()){
        currTok = tokenStorage.at(iteratorValue);
    }
}
Parser::~Parser(){}


string Parser::match(TokenType desiredTokenType){
    string retVal = currTok.getValue();
    if(desiredTokenType == currTok.getTokenType()){
        updateCurrentToken();
        return retVal;
    }
    else{
        throw currTok;
    }
}
void Parser::setVector(vector<Token> input){
    tokenStorage = input;
}
void Parser::updateCurrentToken(){
    iteratorValue++;
    if(iteratorValue < tokenStorage.size()){
        currTok = tokenStorage.at(iteratorValue);
    }
}
DatalogProgram Parser::getDatalogProgram() {
    return dpObj;
}
void Parser::parse(){
    datalogProgram();
    string output;
}
void Parser::datalogProgram(){
    match(SCHEMES);
    match(COLON);
    scheme();
    schemeList();
    match(FACTS);
    match(COLON);
    factList();
    match(RULES);
    match(COLON);
    ruleList();
    match(QUERIES);
    match(COLON);
    query();
    queryList();
    match(EOFile);
}
void Parser::schemeList(){
    if(currTok.getTokenType() == ID){
        scheme();       
        schemeList();
    }
}
void Parser::factList(){
    if(currTok.getTokenType() == ID){
        fact();
        factList();
    }
}
void Parser::ruleList(){
    if(currTok.getTokenType() == ID){    
        rule();
        ruleList();
    }
}
void Parser::queryList(){
    if(currTok.getTokenType() == ID){    
        query();
        queryList();
    }
}
void Parser::scheme(){
    string schemeID1 = match(ID);
    match(LEFT_PAREN);
    string schemeID2 = match(ID);
    vector<string> ids;
    ids = idList();
    
    match(RIGHT_PAREN);
    Predicate schemeThing = Predicate("s");
    schemeThing.updatePredicateID(schemeID1);
    schemeThing.updatePredicateParameter(schemeID2);
    for(unsigned int i = 0; i < ids.size(); i++){
        schemeThing.updatePredicateParameterList(ids.at(i));
    }
    dpObj.addToSchemes(schemeThing);
}
void Parser::fact(){
    Predicate factThing = Predicate("f");
    string factID = match(ID);//match(ID);
    factThing.updatePredicateID(factID);
    match(LEFT_PAREN);
    string factString = match(STRING);//match(STRING);
    factThing.updatePredicateParameter(factString);
    dpObj.addToDomain(factString);
    vector<string> strings;
    strings = stringList();
    for(unsigned int i = 0; i < strings.size(); i++){
        factThing.updatePredicateParameterList(strings.at(i));
        if(strings.at(i)!=","){
            dpObj.addToDomain(strings.at(i));
        }
    }
    match(RIGHT_PAREN);
    match(PERIOD);
    dpObj.addToFacts(factThing);
}
void Parser::rule(){
    Rule ruleParse;
    ruleParse.updateRuleHeadPredicate(headPredicate());
    match(COLON_DASH);
    ruleParse.updateRulePredicate(predicate("ir").predicateToString());
    vector<string> predicates;
    predicates = predicateList();
    for(unsigned int i = 0; i < predicates.size(); i++){
        ruleParse.updateRulePredicateList(predicates.at(i));
    }
    match(PERIOD);
    dpObj.addToRules(ruleParse);
}
void Parser::query(){
    Predicate queryThing = Predicate("q");
    queryThing = predicate("iq");
    match(Q_MARK);
    dpObj.addToQueries(queryThing);
} 
string Parser::headPredicate(){
    string totalHeadPredicate;
    totalHeadPredicate+=match(ID);
    totalHeadPredicate+=match(LEFT_PAREN);
    totalHeadPredicate+=match(ID);
    
    vector<string> middle;
    middle = idList();
    for(unsigned int o=0;o<middle.size();o++){
        totalHeadPredicate+=middle.at(o);
    }
    totalHeadPredicate+=match(RIGHT_PAREN);
    return totalHeadPredicate;
}
Predicate Parser::predicate(string setter){
    Predicate temp = Predicate(setter);
    temp.updatePredicateID(match(ID));
    match(LEFT_PAREN);
    temp.updatePredicateParameter(parameter().parameterToString());
    vector<string> temp2;
    temp2 = parameterList();
    for(unsigned int i = 0; i < temp2.size(); i++){
        temp.updatePredicateParameterList(temp2.at(i));
    }
    match(RIGHT_PAREN);
    return temp;
}
vector<string> Parser::predicateList(){
    vector<string> predicates;
    if(currTok.getTokenType() == COMMA){    
        predicates.push_back(match(COMMA));
        predicates.push_back(predicate("ir").predicateToString());
        vector<string> middle;
        middle = predicateList();
        for(unsigned int o=0;o<middle.size();o++){
            predicates.push_back(middle.at(o));
        }
    }
    return predicates;
}
vector<string> Parser::parameterList(){
    vector<string> parameters;
    if(currTok.getTokenType() == COMMA){    
        parameters.push_back(match(COMMA));
        parameters.push_back(parameter().parameterToString());
        vector<string> middle;
        middle = parameterList();
        for(unsigned int o=0;o<middle.size();o++){
            parameters.push_back(middle.at(o));
        }
    }
    return parameters;
}
vector<string> Parser::stringList(){
    vector<string> strings;
    if(currTok.getTokenType() == COMMA){ 
        strings.push_back(match(COMMA));
        strings.push_back(match(STRING));
        vector<string> middle;
        middle = stringList();
        for(unsigned int o=0;o<middle.size();o++){
            strings.push_back(middle.at(o));
        }
    }
    return strings;
}
vector<string> Parser::idList(){
    vector<string> ids;
    if(currTok.getTokenType() == COMMA){ 
        ids.push_back(match(COMMA));
        ids.push_back(match(ID));
        vector<string> middle;
        middle = idList();
        for(unsigned int o=0;o<middle.size();o++){
            ids.push_back(middle.at(o));
        }
    }
    return ids;
}
Parameter Parser::parameter(){
    string totalParameter;
    if(currTok.getTokenType() == STRING){    
        Parameter temp ("STRING", match(STRING));    
        totalParameter += temp.parameterToString();
        return temp;
    }
    else if(currTok.getTokenType() == ID){
        Parameter temp("ID", match(ID));
        totalParameter += temp.parameterToString();
        return temp;
    }
    else{
        Parameter temp("EXPRESSION",expression());
        totalParameter += temp.parameterToString();
        return temp;
    }
    Parameter empty;
    return empty;
}
string Parser::expression(){
    string totExpr;
    totExpr += match(LEFT_PAREN);
    totExpr += parameter().parameterToString();
    totExpr += operatorGrammar();
    totExpr += parameter().parameterToString();
    totExpr += match(RIGHT_PAREN);
    return totExpr; 
}
string Parser::operatorGrammar(){
    string totalGrmr;
    if(currTok.getTokenType() == ADD){
        totalGrmr += match(ADD);
    }
    else if(currTok.getTokenType() == MULTIPLY){
        totalGrmr += match(MULTIPLY);
    }
    else{
        throw currTok;
    }
    return totalGrmr;
}