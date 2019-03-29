#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, 
    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END};

class Token {
public:
    Token() {}
    ~Token() {}
    Token(TokenType token, string tokenString, int lineNum) {
        this->token = token;
        this->tokenString = tokenString;
        this->lineNum = lineNum;
    }
    TokenType getTok() {
        return token;
    }
    string getString() {
        return tokenString;
    }
    int getLine() {
        return lineNum;
    }
    string toString() {
        string tokenNum = to_string(token);
        if (tokenNum == "0") {
            tokenT = "COMMA";
        }
        else if (tokenNum == "1") {
            tokenT = "PERIOD";
        }
        else if (tokenNum == "2") {
            tokenT = "Q_MARK";
        }
        else if (tokenNum == "3") {
            tokenT = "LEFT_PAREN";
        }
        else if (tokenNum == "4") {
            tokenT = "RIGHT_PAREN";
        }
        else if (tokenNum == "5") {
            tokenT = "COLON";
        }
        else if (tokenNum == "6") {
            tokenT = "COLON_DASH";
        }
        else if (tokenNum == "7") {
            tokenT = "MULTIPLY";
        }
        else if (tokenNum == "8") {
            tokenT = "ADD";
        }
        else if (tokenNum == "9") {
            tokenT = "SCHEMES";
        }
        else if (tokenNum == "10") {
            tokenT = "FACTS";
        }
        else if (tokenNum == "11") {
            tokenT = "RULES";
        }
        else if (tokenNum == "12") {
            tokenT = "QUERIES";
        }
        else if (tokenNum == "13") {
            tokenT = "ID";
        }
        else if (tokenNum == "14") {
            tokenT = "STRING";
        }
        else if (tokenNum == "15") {
            tokenT = "COMMENT";
        }
        else if (tokenNum == "16") {
            tokenT = "UNDEFINED";
        }
        else if (tokenNum == "17") {
            tokenT = "EOF";
        }
        finalString.append(string (1,'('));
        finalString.append(tokenT);
        finalString.append(string(1,','));
        finalString.append(string(1,'\"'));
        finalString.append(tokenString);
        finalString.append(string(1,'\"'));
        finalString.append(string(1,','));
        finalString.append(to_string(lineNum));
        finalString.append(string(1,')'));
        return finalString;
    }
    
protected:
    TokenType token;
    string tokenT;
    string finalString;
    //stringstream fstr;
    string tokenString;
    //string tokenS;
    int lineNum;
};