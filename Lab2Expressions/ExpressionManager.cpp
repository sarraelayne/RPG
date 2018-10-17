#include"ExpressionManager.h"
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<sstream>
#include<iterator>
#include<cctype>
using namespace std;
	
bool ExpressionManager::isBalanced(string expression) {
    stringstream ss;
    string myString;
    stack<string> balancedStack;
    ss << expression;
    while (ss >> myString) {
        if (myString == "(" || myString == "[" || myString == "{") {
            balancedStack.push(myString);
        }
        else if (myString == ")" || myString == "]" || myString == "}") {
            if (balancedStack.empty()) {
                return false;
            }
            if(isPair(balancedStack.top(), myString)){
                balancedStack.pop();
            }
            else {
                return false;
            }
        }
    }
    if (!balancedStack.empty()) {
        return false;
    }
    return true;
}
bool ExpressionManager::isPair(string a, string b) {
    if (a == "(" && b == ")") {
        return true;
    }
    else if (a == "[" && b == "]") {
        return true;
    }
    else if (a == "{" && b == "}") {
        return true;
    }
    else {
        return false;
    }
}
string ExpressionManager::postfixToInfix(string postfixExpression) {
    istringstream iss(postfixExpression);
    istream_iterator<string> beg(iss), end;
    vector<string> pfVector(beg, end);
    string postfixString = postfixExpression;
    stack<string> operandStack;
    string isDigitCheck;
    
    for (int i = 0; i < pfVector.size(); i++) {
        isDigitCheck = pfVector[i];
        if (isdigit(isDigitCheck[0])) {
            if(isDigitCheck[1] == '.') {
                return "invalid";
            }
            else {
                operandStack.push(pfVector[i]);
            }
            
        }
        else if (pfVector[i] == "+" || pfVector[i] == "-" || pfVector[i] == "*" 
            || pfVector[i] == "/" || pfVector[i] == "%") {
            if (operandStack.size() < 2) {
                return "invalid";
            }
            else {
                string newString;
                
                string o1 = operandStack.top();
                operandStack.pop();
                string o2 = operandStack.top();
                operandStack.pop();
                newString = "( " + o2 + " " + pfVector[i] + " " + o1 + " )";
                operandStack.push(newString);
            }
        }
    }
    if (operandStack.size() == 1) {
        postfixString = operandStack.top();
        return postfixString;
    }
    else {
        return "invalid";
    }
}	
string ExpressionManager::postfixEvaluate(string postfixExpression){
    int a;
    int b;
    double c;
    int size;
    stringstream ss;
    ss << postfixExpression;
    string pfE;
    isValid = false;
    while (ss >> pfE) {
        if (pfE == ")" || pfE == "]" || pfE == "}") {
            return "invalid";
        }
        //check for operator
        if ((pfE == "+") || (pfE == "-") || (pfE == "*") || (pfE == "/") || (pfE == "%")) {
            if (evaluateStack.size() < 2) {
                return "invalid";
            }
            int a = evaluateStack.top();
            evaluateStack.pop();
            int b = evaluateStack.top();
            evaluateStack.pop();
            switch (pfE[0]) {
            case '+':
                evaluateStack.push(b + a);
                break;
            case '-':
                evaluateStack.push(b - a);
                break;
            case '*':
                evaluateStack.push(b * a);
                break;
            case '/':
                if (a == 0) {
                    return "invalid";
                }
                evaluateStack.push(b / a);
                break;
            case '%':
                if (a == 0) {
                    return "invalid";
                }
                evaluateStack.push(b % a);
                break;
            }
        }
        //check for numeric
        else if (isdigit(pfE[0])) {
            double num;
            num = stoi(pfE);
            evaluateStack.push(num);
            isValid = true;
        }
        else {
            cout << "invalid" << endl;
        }
    }
    if (evaluateStack.empty()) {
        return "invalid";
    }
    return to_string(evaluateStack.top());
}
bool ExpressionManager::isOpen(string nextToken) {
    if (nextToken == "(" || nextToken == "{" || nextToken == "[") {
        return true;
    }
    else {
        return false;
    }
}

bool ExpressionManager::isClosed(string nextToken) {
	if (nextToken == ")" || nextToken == "}" || nextToken == "]") {
	    return true;
	}
	else {
	    return false;
	}
}

bool ExpressionManager::isInteger(string nextToken) {
	stringstream isint;
	int num;
	isint << nextToken;
    isint >> num;
	return num;
}

bool ExpressionManager::isOperator(string nextToken) {
    if (nextToken == "*" || nextToken == "/" || nextToken == "%" || nextToken == "+" || nextToken == "-") {
        return true;
    }
	else {
	    return false;
	}
}
int ExpressionManager::getPrecedence(string nextToken) {
	int precedence = 0;
	if (nextToken == "*" || nextToken == "/" || nextToken == "%") {
		precedence = 3;
	} else if (nextToken == "+" || nextToken == "-") {
		precedence = 2;
	} else if (nextToken == "(" || nextToken == ")" || nextToken == "{" || nextToken == "}" || nextToken == "[" || nextToken == "]") {
		precedence = 1;
	}
	return precedence;
}
string ExpressionManager::infixToPostfix(string infixExpression){
	stringstream tt(infixExpression);
	stack<string> pfStack;
	string tempstr;
	stringstream temp;
	if (!isBalanced(infixExpression)) {
			return "invalid";
	}
	for (int i = 0; i < tt.str().length(); i++) {
			if (tt.str()[i] == '.') {
				return "invalid";
			}
			if (tt.str().length() == 1) {
				return "invalid";
			}
		}
	temp << infixExpression;
	while (temp >> tempstr) {
		if (isOperator(tempstr) == false && isOpen(tempstr) == false && isInteger(tempstr) == false && isClosed(tempstr) == false) {
		    return "invalid";
		}
	}
	string previous;
	string nextToken;
	string pfString;
	stringstream pf;
	pf << infixExpression;
	while (pf >> nextToken) {
		if (isOperator(previous) && isOperator(nextToken)) {
					return "invalid";
				}
		if (isOperator(previous) && isClosed(nextToken)) {
					return "invalid";
				}
		if (isInteger(nextToken)) {
			pfString.append(nextToken);
			pfString.append(" ");
		} else if (isOperator(nextToken) || isOpen(nextToken) || isClosed(nextToken)) {
				if (nextToken == "(" || nextToken == "{" || nextToken == "[") {
					pfStack.push(nextToken);
				}
				else if (pfStack.empty()) {
					pfStack.push(nextToken);
				}
				else if (getPrecedence(nextToken) == 3 && getPrecedence(pfStack.top()) != 3) {
					pfStack.push(nextToken);
				}
				else if (getPrecedence(nextToken) == getPrecedence(pfStack.top())) {
					if (pfStack.top() != "(" && pfStack.top() != "[" && pfStack.top() != "{" && pfStack.top() != ")" && pfStack.top() != "]" && pfStack.top() != "}") {
						pfString.append(pfStack.top());
						pfString.append(" ");
					}
					pfStack.pop();
					pfStack.push(nextToken);
				}
				else if (getPrecedence(nextToken) == 2 && getPrecedence(pfStack.top()) == 3) {
					if (pfStack.top() != "(" && pfStack.top() != "[" && pfStack.top() != "{" && pfStack.top() != ")" && pfStack.top() != "]" && pfStack.top() != "}") {
					pfString.append(pfStack.top());
					pfString.append(" ");
					}
					pfStack.pop();
					pfStack.push(nextToken);
				}
				else if (getPrecedence(nextToken) == 2 && getPrecedence(pfStack.top()) == 1) {
					pfStack.push(nextToken);
				}
				else if (nextToken == ")" || nextToken == "]" || nextToken == "}") {
					while (pfStack.top() != "(" && pfStack.top() != "{" && pfStack.top() != "[") {
					    if (pfStack.top() != "(" && pfStack.top() != "[" && pfStack.top() != "{" && pfStack.top() != ")" && pfStack.top() != "]" && pfStack.top() != "}") {
    						pfString.append(pfStack.top());
						    pfString.append(" ");
					    }
					    pfStack.pop();
					  }
					if (pfStack.top() == "(" || pfStack.top() == "{" || pfStack.top() == "[") {
						pfStack.pop();
					}
				}
		}
		previous = nextToken;
	}
	while (pfStack.size() != 0) {
		pfString.append(pfStack.top());
		if (pfStack.size() != 1) {
			pfString.append(" ");
		}
		pfStack.pop();
	}
	return pfString;
}

//telnet towel.blinkenlights.nl