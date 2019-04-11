//g++ -std=c++11 -Wall -Werror -g -o storage *.cpp
//./storage tester.txt
//./fishstory Example1.txt
//cd ..  to back out of a directory
//$ valgrind ./filename
//$ zip lab4.zip *.h *.cpp
//make 2> log          prints out errors to a file

//lab 4 passes test 61


//38, 204, 240, 282, 292 currentlinenumber problem
//blank file out line 1
//EOF always one greater than number of lines in the file

//test single line comment line 285

#include <iostream>//<ifstream>
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
    //cout << queryy.size() << ": queryy size\n";
    /*
    Scheme one; Scheme two;
    one.push_back("1"); two.push_back("2");
    one = two;
    for(unsigned int i = 0; i < one.size(); i++){
      cout << "one.at(" << i << "): " << one.at(i) << endl;
    }*/
    
    //cout << "before interpreter constructor call\n";
    Interpreter inter = Interpreter(datalog_program);
    //cout << "after interpreter constructor call\n";
    
    cout << "Rule Evaluation\n";
    inter.evalAllRules();
    
    
    
    cout << "\nQuery Evaluation\n";
    inter.evalAllQueries();
    
    
    
    /*Lab 4 testing join and union
    cout << "\n\n";
    Scheme alpha;
    alpha.push_back("cat");alpha.push_back("dog");alpha.push_back("fish");
    Scheme beta;
    beta.push_back("cat"); beta.push_back("fish");beta.push_back("bird");beta.push_back("bunny");
    string nameMe = "alpha"; string nameMeToo = "beta";
    Relation Alpha = Relation(nameMe, alpha);
    Relation Beta = Relation(nameMeToo, beta);
    Tuple al1; al1.push_back("1");al1.push_back("2");al1.push_back("5"); cout << al1.size() << " al1 size\n";
    Tuple al2; al2.push_back("1");al2.push_back("4");al2.push_back("1");
    Tuple al3; al3.push_back("2");al3.push_back("3");al3.push_back("2");
    Tuple al4; al4.push_back("3");al4.push_back("3");al4.push_back("2");
    Tuple al5; al5.push_back("6");al5.push_back("7");al5.push_back("4");
    Alpha.addTuple(al1);Alpha.addTuple(al2);Alpha.addTuple(al3);Alpha.addTuple(al4);Alpha.addTuple(al5);
    cout << Alpha.getTupSetSize() << " Alpha tupSetSize\n";
    
    Tuple be1; be1.push_back("3");be1.push_back("4");be1.push_back("2");be1.push_back("4"); cout << be1.size() << " be1 size\n";
    Tuple be2; be2.push_back("6");be2.push_back("4");be2.push_back("9");be2.push_back("2");
    Tuple be3; be3.push_back("4");be3.push_back("3");be3.push_back("2");be3.push_back("7");
    Tuple be4; be4.push_back("1");be4.push_back("5");be4.push_back("2");be4.push_back("4");
    Tuple be5; be5.push_back("1");be5.push_back("5");be5.push_back("8");be5.push_back("3");
    Beta.addTuple(be1);Beta.addTuple(be2);Beta.addTuple(be3);Beta.addTuple(be4);Beta.addTuple(be5);
    
    Relation Alpha2 = Alpha.join(Beta); //just doing Alpha = Alpha.join(Beta); doesn't work... why? 
    cout << Alpha2.getSchemeSize() << " Alpha2 scheme size\n";
    Alpha2.printRelScheme();
    cout << Alpha2.getTupSetSize() << " tupSet size\n";
    Alpha2.printTupSet();
    
    Scheme newSch = Alpha2.getScheme();
    //Scheme newSch; newSch.push_back("beaver");newSch.push_back("clam");newSch.push_back("otter");newSch.push_back("clampearl");newSch.push_back("otterbox");
    Relation Gamma = Relation(nameMe, newSch);
    Tuple ga1; ga1.push_back("1");ga1.push_back("1");ga1.push_back("1");ga1.push_back("1");ga1.push_back("1");
    Tuple ga2; ga2.push_back("2");ga2.push_back("2");ga2.push_back("2");ga2.push_back("2");ga2.push_back("2");
    Gamma.addTuple(ga1);Gamma.addTuple(ga2);
    
    Alpha2 = Alpha2.unionRelations(Gamma);
    cout << endl;
    Alpha2.printTupSet();
    */
    
    
    //Scheme resultSch = rel.combineSchemes(beta);
    //rel.setScheme(resultSch);
    //rel.printRelScheme();
}




/*
 //Token Testing
    cout << "Begin Token testing.\n";
    TokenType c = UNDEFINED;
    cout << c << " :TokenType c\n";
    string cc = ",";
    int x = 1;
    Token t(c, cc, x);// = Token; 
    string temp = t.getValue();
    cout << temp << endl;
    cout << t.getLine() << endl;
    cout << t.getMapName(c) << endl;
    cout << "End Token testing.\n\n";*/
    
    //Scanner Testing
    //cout << "Begin Scanner testing.\n";