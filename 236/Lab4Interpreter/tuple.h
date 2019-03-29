#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tuple : public vector<string> {
public:
    Tuple(){}
    ~Tuple(){}
    void setName(string name) {
		this->name = name;
	}
	string getName() {
		return name;
	}
	
	string name = "";
};