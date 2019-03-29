#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Scheme: public vector<string>{ /////PUBLIC VECTORSTRING SHOULD BE OKAY BUT THIS MAY BE AN ERROR SOURCE
public:
	Scheme();
	Scheme(string name, vector<string> headers);
	void setName(string name) {
		this->name = name;
	}
	string getName() {
		return name;
	}
	
	string name;
	vector<string> names;
};