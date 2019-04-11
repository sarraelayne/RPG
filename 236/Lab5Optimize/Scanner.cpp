#include "Scanner.h"
#include <map>

Scanner::Scanner(string fileName){
    ifs.open(fileName); 
}
Scanner::~Scanner(){}

void Scanner::scanToken(){
    while(ifs.good()){
        ifs.get(currentChar);
        if(ifs.eof()){ 
                if(numToks == 0 && !wsPresent){
                    Token temp = Token(EOFile, 1);
                    tokenVector.push_back(temp);
                    numToks++;
                }
                else if(numToks == 0 && wsPresent){
                    Token temp = Token(EOFile, loc);
                    tokenVector.push_back(temp);
                    numToks++;
                }
                else{
                    Token temp = Token(EOFile, loc);
                    tokenVector.push_back(temp);
                    numToks++;
                }
        }
        else if(isspace(currentChar)){
            wsPresent = true;
            
            if(currentChar == '\n'){
                loc++;
            }
            
        }
        else if(currentChar == ','){              
            Token temp = Token(COMMA, ",", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == '.'){
            Token temp = Token(PERIOD, ".", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == '?'){
            Token temp = Token(Q_MARK, "?", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == '('){
            Token temp = Token(LEFT_PAREN, "(", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == ')'){
            Token temp = Token(RIGHT_PAREN, ")", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == ':'){
            if(ifs.good()){
                if(ifs.peek() == '-'){
                    Token temp = Token(COLON_DASH, ":-", loc);
                    tokenVector.push_back(temp);
                    numToks++;
                    ifs.get();
                    if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                    }
                }
                else{
                    Token temp = Token(COLON, ":", loc);
                    tokenVector.push_back(temp);
                    numToks++;
                    if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                    }
                }
            }
            else{
                cout << "(COLON,\"" << currentChar << "\"," << loc << ")" << endl;
                Token temp = Token(COLON, ":", loc);
                tokenVector.push_back(temp);
                numToks++;
                if(ifs.eof()){
                    Token temp = Token(EOFile, loc);
                    tokenVector.push_back(temp);
                    numToks++;
                }
            }
        }
        else if(currentChar == '*'){
            Token temp = Token(MULTIPLY, "*", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == '+'){
            Token temp = Token(ADD, "+", loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(isalpha(currentChar)){
            string word;
            word.push_back(currentChar);
            while(ifs.good() && isalnum(ifs.peek())){
                ifs.get(currentChar);
                word += currentChar;
            }
            string temp = word;
            if(temp == "Schemes"){
                Token temp = Token(SCHEMES, "Schemes", loc);
                tokenVector.push_back(temp);
                numToks++;
                if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                }
                
            }
            else if(temp == "Facts"){
                Token temp = Token(FACTS, "Facts", loc);
                tokenVector.push_back(temp);
                numToks++;
                if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                }
            }
            else if(temp == "Rules"){
                Token temp = Token(RULES, "Rules", loc);
                tokenVector.push_back(temp);
                numToks++;
                if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                }
            }
            else if(temp == "Queries"){
                Token temp = Token(QUERIES, "Queries", loc);
                tokenVector.push_back(temp);
                numToks++;
                if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                }
            }
            else{
                Token temp = Token(ID, word, loc);
                tokenVector.push_back(temp);
                numToks++;
                if(ifs.eof()){
                        Token temp = Token(EOFile, loc);
                        tokenVector.push_back(temp);
                        numToks++;
                }
            }
        }
        else if(currentChar == '\''){
            int lineVar = loc;
            string info = "\'";
            bool notDone = true;
            bool ended = false;
            while(ifs.good() && notDone){
                if(ifs.peek() == '\''){
                    ifs.get(currentChar);
                    if(ifs.peek() == '\''){
                        info += "\'";
                        ifs.get(currentChar);
                        info += '\'';
                    }
                    else{
                        info += '\'';
                        notDone = false;
                    }
                }
                else if(ifs.peek() == '\n'){
                    loc++;
                    ifs.get(currentChar);
                    info += "\n";
                }
                else{
                    ifs.get(currentChar);
                    if(!ifs.eof()){
                        info.push_back(currentChar);
                    }
                }
                if(ifs.eof() && notDone && currentChar != '\''){
                    Token temp = Token(UNDEFINED, info, lineVar);
                    tokenVector.push_back(temp);
                    numToks++;
                    Token tempy = Token(EOFile, loc);
                    tokenVector.push_back(tempy);
                    numToks++;
                    ended = true;
                }
            }
            if(ended == false){
                Token temp = Token(STRING, info, lineVar);
                tokenVector.push_back(temp);
                numToks++;
            }
            if(ifs.eof() && ended == false){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
        else if(currentChar == '#'){
            int lineVar = loc;
            bool notDone = true;
            bool ended = false;
            string info = "#";
            if(ifs.peek() == '|'){//block comment*********
                while(ifs.good() && notDone){
                    if(currentChar == '\n'){
                        loc++;
                    }
                    if(ifs.peek() == '|'){
                        ifs.get(currentChar);
                        info.push_back(currentChar);
                        if(ifs.peek() == '#'){
                            ifs.get(currentChar);
                            info.push_back(currentChar);
                            notDone = false;
                            numToks++;
                        }
                    }
                    if(notDone && !ifs.eof()){
                        ifs.get(currentChar);
                        info.push_back(currentChar);
                    }
                    if(ifs.eof() && notDone && currentChar != '#'){
                        Token temp = Token(UNDEFINED, info, lineVar);
                        tokenVector.push_back(temp);
                        numToks++;
                        Token tempr = Token(EOFile, loc);
                        tokenVector.push_back(tempr);
                        numToks++;
                        ended = true;
                    }
                }
                if(ifs.eof() && ended == false){
                    Token temp = Token(EOFile, loc);
                    tokenVector.push_back(temp);
                    numToks++;
                }
            }
            else if(ifs.peek() != '\n'){//single line comment********
                while(ifs.good() && notDone){
                    if(ifs.peek() == '\n' || ifs.eof()){
                        notDone = false;
                    }
                    ifs.get(currentChar);
                    if(notDone){
                        info.push_back(currentChar);
                    }
                }
                numToks++;
                if(!ifs.eof()){loc++;}
                if(ifs.eof()){
                    Token temp = Token(EOFile, loc);
                    tokenVector.push_back(temp);
                    numToks++;
                }
            }
            else{//empty comment
                numToks++;
                ifs.get(currentChar);
                if(!ifs.eof()){loc++;}
                if(ifs.eof()){
                    Token temp = Token(EOFile, loc);
                    tokenVector.push_back(temp);
                    numToks++;
                }
            }
        }
        
        else{
            string input;
            input.push_back(currentChar);
            Token temp = Token(UNDEFINED, input, loc);
            tokenVector.push_back(temp);
            numToks++;
            if(ifs.eof()){
                Token temp = Token(EOFile, loc);
                tokenVector.push_back(temp);
                numToks++;
            }
        }
    }
    ifs.close();
}
int Scanner::getCurrentLineNum(){
    return loc;
}
void Scanner::printTokens(){
    string tstring;
    for(int i = 0; i < numToks; i++){
        Token temp = tokenVector[i];
        tstring = temp.toString();
        cout << tstring << endl;
    }
    cout << "Total Tokens = " << numToks << endl;
}
vector<Token> Scanner::returnVector(){
    return tokenVector;
}

