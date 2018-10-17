#pragma once
#include "ExpressionManagerInterface.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class ExpressionManager: public ExpressionManagerInterface{
    public:
    ExpressionManager() {}
    ~ExpressionManager() {}
    
	bool isBalanced(string expression);
	bool isPair(string a, string b);
	bool process_operator(stack<string> &operatorStack, string &postfixString, string &op);
	string postfixToInfix(string postfixExpression);
	string postfixEvaluate(string postfixExpression);
	int getPrecedence(string next_thing);
	bool isOpen(string next_thing);
    bool isClosed(string next_thing);
    bool isInteger(string next_thing);
    bool isOperator(string next_thing);
    string infixToPostfix(string infixExpression);
	
	protected:
	stack<int> evaluateStack;
	bool isValid;
	string inExpression;
	string evalAns;
	string newPostfix;
};