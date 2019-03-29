#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include "Scheme.h"
#include "tuple.h"
using namespace std;

class Relation {
public:
	Relation();
	Relation(string name, vector<string> header);
	~Relation();
	
	Relation Select(int index, string value);
	Relation Select(vector<int> indexes);
	Relation Project(vector<int> indexes);
	Relation Rename(vector<string> names);
	Relation Join(Relation i, Relation ii);
	Relation Union(Relation i, Relation ii);
	void ProjectJoin(Relation &rel, Scheme &query);
	
	string getName();
	void setName(string name);
	set<Tuple> getTuples();
	void setTuples(set<Tuple> tuples);
	Scheme getScheme();
	
	set<Tuple> tuples;
	string toString(string query);
	Scheme theScheme;
	string name;
	vector<string> headers;
};

