#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include "tokens.h"
#include "lexer.h"

using namespace std;

lexer::lexer(string name) {
    input.open(name);
}
lexer::~lexer() {}
string lexer::GetChar() {
    inStr.append(string(1,input.get()));
    return inStr;
}
bool evenChk(int n) {
    if (n%2 == 0) {
        return true;
    }
    else {
        return false;
    }
}
void lexer::tokenTyper() {
    while(input){
        if (input.peek() == '\n') {
            lineNum++;
        }
        idString.clear();
        if (isalpha(input.peek())) { //DONE
            while(isalnum(input.peek())) {
                idString.append(string(1,input.get()));
            }
            if (idString == "Schemes") {
                tokVector.push_back(Token(SCHEMES, idString, lineNum));
            }
            else if (idString == "Facts") {
                tokVector.push_back(Token(FACTS, idString, lineNum));
            }
            else if (idString == "Rules") {
                tokVector.push_back(Token(RULES, idString, lineNum));
            }
            else if (idString == "Queries") {
                tokVector.push_back(Token(QUERIES, idString, lineNum));
            }
            else {
                tokVector.push_back(Token(ID, idString, lineNum));
            }
            if(input.peek() == '\n') {
                lineNum++;
            }
        }
        char c = input.get();
        if (c == '.') {
            tokVector.push_back(Token(PERIOD, ".", lineNum));
        }
        if(c == ',') {
            tokVector.push_back(Token(COMMA, ",", lineNum));
        }
        if(c == '?') {
            tokVector.push_back(Token(Q_MARK, "?", lineNum));
        }
        if(c == '(') {
            tokVector.push_back(Token(LEFT_PAREN, "(", lineNum));
        }
        if(c == ')') {
            tokVector.push_back(Token(RIGHT_PAREN, ")", lineNum));
        }
        if(c == ':') {
            if (input.peek() == '-') {
                input.get();
                tokVector.push_back(Token(COLON_DASH, ":-", lineNum));
            }
            else {
                tokVector.push_back(Token(COLON, ":", lineNum));
            }
        }
        if(c == '*') {
            tokVector.push_back(Token(MULTIPLY, "*", lineNum));
        }
        if(c == '+') {
            tokVector.push_back(Token(ADD, "+", lineNum));
        }
        if(c == '\'') {///WORK W UNFINISHED STRINGS
            commNum = lineNum;
            bool isDone = false;
            sstring.append("\'");
            while (input.peek() != EOF) {
                if (input.peek() == '\'') {
                    isDone = true;
                    sstring.append(string(1,input.get()));
                    if (input.peek() == '\'') {
                        sstring.append(string(1,input.get()));
                        isDone = false;
                    }
                    if (isDone == true) {
                        tokVector.push_back(Token(STRING,sstring,commNum));
                        sstring.clear();
                        break;
                    }
                }
                else if (input.peek() == '\n') {
                    lineNum++;
                    sstring.append(string(1,input.get()));
                }
                else if (input.peek() == EOF) {
                    tokVector.push_back(Token(UNDEFINED, sstring, commNum));
                    tokVector.push_back(Token(END, "", lineNum));
                    sstring.clear();
                }
                else {
                    sstring.append(string(1,input.get()));
                    if (input.peek() == '\n') {
                        lineNum++;
                        sstring.append(string(1,input.get()));
                    }
                }
            }
            if (input.peek() == EOF) {
                tokVector.push_back(Token(UNDEFINED, sstring, commNum));
                sstring.clear();
            }
            sstring.clear();
        }
        if (c == '#') {
            bool isDone = false;
            commString = "#";
            if(input.peek() == '|') { //BLOCK COMMENT
                commNum = lineNum;
                commString.append(string(1,input.get())); //string: #|
                while (isDone == false) {
                    if(input.peek() == '|') {
                        commString.append(string(1,input.get()));    
                        if(input.peek() == '#') {
                            commString.append(string(1,input.get()));
                            //tokVector.push_back(Token(COMMENT, commString, commNum));
                            isDone = true;
                           }
                    }
                    else if (input.peek() == EOF) {
                        tokVector.push_back(Token(UNDEFINED, commString, commNum));
                        tokVector.push_back(Token(END, "", lineNum));
                        isDone = true;
                    }
                    else if (input.peek() == '\n') {
                        commString.append(string(1,input.get()));
                        lineNum++;
                    }
                    else {
                        commString.append(string(1,input.get()));
                    }
                }
            }
            else { //LINE COMMENT
                while(input.peek() != '\n' && input.peek() != EOF) {
                    commString.append(string(1,input.get()));
                }
                //tokVector.push_back(Token(COMMENT, commString, lineNum));
            }
        }
        if (!isspace(c) && !isalpha(c) && c != '\'' && c != '#' && c != '.' &&
            c!=',' && c!='?' && c!=':' && c!='(' && c!=')' && c!='+' && c!='*' && c!=EOF) {
            undefString.clear();
            undefString.append(string(1,c));
            tokVector.push_back(Token(UNDEFINED, undefString, lineNum));
        }
        if(c == EOF) {
            tokVector.push_back(Token(END, "", lineNum));
        }
    }
}
vector<Token> lexer::getTokens() {
    return tokVector;
}
void lexer::print() {
    for (int i = 0; i < signed(tokVector.size()); i++) {
        cout << tokVector.at(i).toString() << endl;
        totalTokens++;
    }
    totalTokens++;
    cout << "Total Tokens = " << totalTokens << endl;
}