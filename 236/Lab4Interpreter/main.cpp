#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include "tokens.h"
#include "lexer.h"
#include "datalog.h"
#include "parser.h"
#include "Database.h"
#include "Interpreter.h"
using namespace std;

int main (int argc, char *argv[]) {

    string input;
    ifstream inFile;
    input = argv[1];
    lexer lex(input);
    
    stringstream outstr;

    inFile.open(input);
    while (inFile.get() != EOF) {
        lex.tokenTyper();
    }
    vector<Token> toksVector = lex.getTokens();
    try {
//interpreter that accepts tokens
        parser p(toksVector);

        datalog data = p.getData();
//how to get each individual class
        datalog allData = p.getData();
        Interpreter intrp(allData);
        intrp.runDatalog();
    }
    catch(string s) {
        cout << "Failure!" << endl;
        cout << "  " << s;
    }
    inFile.close();
    return 0;
}

/*
PLEASE GO TO BED

PLEASE

PLEASE DO
*/