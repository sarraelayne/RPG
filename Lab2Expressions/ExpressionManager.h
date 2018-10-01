#include #pragma once
#include "ExpressionManagerInterface.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class ExpressionManager: public ExpressionManagerInterface() {
    public: 
    ~ExpressionManagerInterface() {}
    
	bool isBalanced(string expression);
	string postfixToInfix(string postfixExpression);
	string postfixEvaluate(string postfixExpression);
	string infixToPostfix(string infixExpression);
	
	protected:
	string inExpression;
	string newInfix;
	string newPostfix;
	stack<string> balancedStack;
}