#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Relation.h"
using namespace std;

class Database {
public:
	void store(string name, Relation r);
	void giveTuple(Tuple t, string name);
	map<string, Relation> myMap;
};
