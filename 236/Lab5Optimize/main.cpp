#include <iostream>
#include <string>
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Scheme.h"
#include "Relation.h"

using namespace std;

int main(int argc, char* argv[]){
    //cout << "start main\n";
    string name = argv[1];
    
    //name.push_back();
    Scanner scan(name);
    scan.scanToken();
    //scan.printTokens();  //Project 1
    vector<Token> temp = scan.returnVector();
    Parser parser = Parser(temp); //Token temp = Token(EOFile, 1);
    //parser.setVector(temp);
    try{
      parser.parse();
    }
    catch(Token brokenToken){
      cout << "Failure!" << endl;
      cout << "  " << brokenToken.toString() << endl;
    }
    
    
    //returning four vectors for use in project 3
    //DatalogProgram datalog_program;
    DatalogProgram datalog_program = parser.getDatalogProgram();
    vector<Predicate> schemey = datalog_program.getSchemes();
    //cout << schemey.size() << ": schemey size\n";
    vector<Predicate> facty = datalog_program.getFacts();
    //cout << facty.size() << ": facty size\n";
    vector<Predicate> queryy = datalog_program.getQueries();
    
    Interpreter inter = Interpreter(datalog_program);

    inter.smartEvalRules();

    cout << "\nQuery Evaluation\n";
    inter.evalAllQueries();
}