#include "Token.h"

Token::Token(){}
Token::Token(TokenType t, int lineNum){
    tokenTypeName = names[t];
    lineNumber = lineNum;
    tokenType = t;
}
Token::Token(TokenType t, string v, int lineNum){
    value = v;
    lineNumber = lineNum;
    tokenTypeName = names[t];
    tokenType = t;
}
Token::~Token(){}


Token::Maps Token::names = {
    {UNDEFINED,"UNDEFINED"},
    {COMMA,"COMMA"},
    {PERIOD,"PERIOD"},
    {Q_MARK,"Q_MARK"},
    {LEFT_PAREN,"LEFT_PAREN"},
    {RIGHT_PAREN,"RIGHT_PAREN"},
    {COLON,"COLON"},
    {COLON_DASH,"COLON_DASH"},
    {MULTIPLY,"MULTIPLY"},
    {ADD,"ADD"},
    {SCHEMES,"SCHEMES"},
    {FACTS,"FACTS"},
    {RULES,"RULES"},
    {QUERIES,"QUERIES"},
    {ID,"ID"},
    {STRING,"STRING"},
    {COMMENT,"COMMENT"},
    {EOFile,"EOF"}
};

string Token::getValue(){
    return value;
}
string Token::getTokenTypeName(){
    return tokenTypeName;
}
TokenType Token::getTokenType(){
    return tokenType;
}
string Token::getMapName(TokenType type){
    return names[type];
}
int Token::getLine(){
    return lineNumber;
}
string Token::toString(){
    string str;
    str+="(";
    str+=getTokenTypeName();
    str+=",\"";
    str+=getValue();
    str+="\",";
    string lineNums = to_string(lineNumber);
    str+=lineNums;
    str+=")";
    return str;
}