#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "datalog.h"
#include "Relation.h"
#include "Database.h"
#include "tuple.h"

using namespace std;

class Interpreter {
public:
	Interpreter(datalog data);
	void runDatalog();
	void iterateSchemes();
	void iterateFacts();
	void iterateQueries();
	void evalRules();

private:
	datalog allData;
	Database database;
};
