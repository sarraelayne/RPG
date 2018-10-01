#include"ExpressionManager.h"
#include<iostream>
#include<string>
#include<stack>
using namespace std;
	
bool ExpressionManager::isBalanced(string expression) {
    char x;
    for (int i = 0; i < expression.length(); i++) { //creates stack
        if (expression.at(i) == "("||expression.at(i) == "[" || expression.at(i) == "{") {
            balancedStack.push(i);
        }
        else if (expression.length() == 0) {
            return false;
        }
    }
    switch(expression.at(i)) {
        case ')': 
            x = expression.top();
            if (x == '[' || x == '{') {
                return false;
            }
            break;
        case ']':
            x = expression.top();
            if (x == '(' || x == '{') {
                return false;
            }
            break;
        case '}':
            x = expression.top();
            if (x == '[' || x == '(') {
                return false;
            }
            break;
        default: 
            return true;
    }
    return true;
}
string ExpressionManager::postfixToInfix(string postfixExpression) {
    return inExpression;
}	
string ExpressionManager::postfixEvaluate(string postfixExpression){
    return newInfix;
}
string ExpressionManager::infixToPostfix(string infixExpression){
    return newPostfix;
}