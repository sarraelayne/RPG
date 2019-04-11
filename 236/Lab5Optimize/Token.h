#pragma once
#include <string>
#include <iostream>
#include <map>

using namespace std;

enum TokenType {
    UNDEFINED, //0
    COMMA,     //1
    PERIOD,    //2
    Q_MARK,    //3
    LEFT_PAREN,//4
    RIGHT_PAREN,//5
    COLON,     //6    
    COLON_DASH,//7
    MULTIPLY,  //8
    ADD,       //9
    SCHEMES,   //10
    FACTS,     //11
    RULES,     //12
    QUERIES,   //13
    ID,        //14
    STRING,    //15
    COMMENT,   //16
    EOFile     //17
};

class Token {
    
    friend class Scanner;
    friend class Parser;
        
    public:
    Token();
    Token(TokenType t, int lineNum);
    Token(TokenType t, string value, int lineNum);
    ~Token();

    string getValue();
    string getTokenTypeName();
    TokenType getTokenType();
    string getMapName(TokenType type);
    int getLine();
    string toString();

    private:
    int lineNumber = 0; 
    string value;
    string tokenTypeName;
    TokenType tokenType;
    typedef map<TokenType, string> Maps;
    static Maps names;
};