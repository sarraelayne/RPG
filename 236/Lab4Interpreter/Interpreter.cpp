#include "Interpreter.h"

Interpreter::Interpreter(datalog data) {
	allData = data;
}

void Interpreter::runDatalog() {
	iterateSchemes();
	iterateFacts();
	evalRules();
	iterateQueries();
}

void Interpreter::iterateSchemes() {
	for (unsigned i = 0; i < allData.schemes.size(); i++) {
		string name = allData.schemes[i].getId();
		vector<string> headers = allData.schemes[i].getParamStrings();
		Scheme myScheme(name, headers);
		Relation r(name, headers);
		r.theScheme = myScheme;
		database.store(name, r);
	}
}

void Interpreter::iterateFacts() {
	for (unsigned i = 0; i < allData.facts.size(); i++) {
		string name = allData.facts[i].getId();
		vector<string> parameters = allData.facts[i].getParamStrings();
		Tuple myTuple;
		for (unsigned j = 0; j < parameters.size(); j++) {
			myTuple.push_back(parameters[j]);
		}
		database.myMap.find(name)->second.tuples.insert(myTuple);
	}
}

void Interpreter::iterateQueries() {
	for (unsigned i = 0; i < allData.queries.size(); i++) {

		string queryName = allData.queries[i].getId();
		vector<string> parameters = allData.queries[i].getParamStrings();
		vector<int> projectVariables;

		// TAKE THE RELATION FROM THE DATABASE THAT HAS THE SAME NAME AS THE QUERY
		Relation r = database.myMap.find(queryName)->second;
		// We want to map new Variables (Not Constants) for each new query so we make a new one each time (erase it later)
		map<string, vector<int>> myVariables;
		// LOOP  THROUGH EACH PARAMETER IN THE QUERY
		for (unsigned j = 0; j < parameters.size(); j++) {
			if (parameters[j].at(0) == '\'') {  // IF THE PARAMETER IS A CONSTANT
				// We SELECT on to that relation and see the rows that contain the constant that we are looking for
				r = r.Select(j, parameters[j]);
			}
			else {   // IF IT IS A VARIABLE
				
				// IF THE VARIABLE IS IN OUR NEW MAP ("myVariables") AS A KEY THEN ENTER THIS "IF" STATEMENT
				if (myVariables.find(parameters[j]) != myVariables.end()) {
					myVariables.find(parameters[j])->second.push_back(j);
				}
				// ELSE MAKE A NEW VARIABLE KEY IN OUR MAP CALLED "myVariables"
				else {
					vector<int> indexes;
					indexes.push_back(j);
					myVariables.insert(pair<string, vector<int>>(parameters[j], indexes));
					projectVariables.push_back(j);
				}
			}
		}
		// USE SELECT FOR THE VARIABLES AFTER WE HAVE FOUND THEM ALL WITH THE VECTOR<INT>
		

		// NEW LOOP FOR THE VARIABLES MAP
		for (const auto &p : myVariables) {
			r = r.Select(p.second);
		}

		// PROJECT //
		if (myVariables.size() > 0) {
			r = r.Project(projectVariables);
		}
		
		// RENAME //
		r = r.Rename(parameters);

		// toString //
		string fullQuery = queryName;
		fullQuery += "(";
		for (unsigned k = 0; k < parameters.size(); k++) {
			fullQuery += parameters[k];
			if (k != parameters.size() - 1) {
				fullQuery += ",";
			}
		}
		fullQuery += ")";
		cout << r.toString(fullQuery);

	}
}
void Interpreter::evalRules() {
	cout << "evalRules" << endl;
}