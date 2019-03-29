#include "Relation.h"

Relation::Relation() {

}
Relation::Relation(string newName, vector<string> header) {
	headers = header;
	name = newName;
	theScheme.name = newName;
	theScheme.names = header;
}
Relation::~Relation() {

}

Relation Relation::Select(int index, string value) {
	Relation newRelation(name, headers);
	
	for (unsigned i = 0; i < tuples.size(); i++) {
		auto currentTuple = tuples.begin(); // get iterator to 1st element
		advance(currentTuple, i);     // advance by i

		// e.g. FIRST TUPLE IS INSERTED INTO newRelation "('a','c')" BECAUSE IT FITS THE CRITERIA WITH 'c' AS A CONSTANT IN THE [1] SPOT OF OUR PREVIOUSLY INSERTED TUPLES (given by the facts)
		if (currentTuple->at(index) == value) {
			newRelation.tuples.insert(*currentTuple);
		}
	}
	return newRelation;
}

Relation Relation::Select(vector<int> indexes) {
	
	Relation newRelation(name, headers);
	// INDEXES ARE THE SPOTS WHERE THE VARIABLES ARE THE SAME NAME
	if (indexes.size() > 1) {

		// FIRST WE GO THROUGH EACH TUPLE
		for (unsigned i = 0; i < indexes.size() - 1; i++) {
			
			// THEN WE GO THROUGH EACH ELEMENT IN THE TUPLE WHERE THE VARIABLE IS THE SAME
			for (unsigned j = 0; j < tuples.size(); j++) {
				auto currentTuple = tuples.begin(); // get iterator to 1st element
				advance(currentTuple, j);     // advance by i
				bool good = true;

				if (currentTuple->at(indexes[i]) == currentTuple->at(indexes[i + 1])) {
					if (indexes.size() > 2) {

						for (unsigned k = 0; k < indexes.size() - 1; k++) {
							if (currentTuple->at(indexes[k]) != currentTuple->at(indexes[k + 1])) {
								good = false;
							}
						}
						if (good) {
							newRelation.tuples.insert(*currentTuple);
						}
					}
					else {
						newRelation.tuples.insert(*currentTuple);
					}
				}
			}
		}
	}
	else {
		for (unsigned i = 0; i < tuples.size(); i++) {
			auto currentTuple = tuples.begin(); // get iterator to 1st element
			advance(currentTuple, i);     // advance by i
			newRelation.tuples.insert(*currentTuple);
		}
	}
	return newRelation;
}


Relation Relation::Project(vector<int> indexes) {
	
	Relation newRelation(name, headers);
	// GO THROUGH EACH TUPLE IN THE CURRENT RELATION
	bool oneTime = false;
	vector<string> newHeaders;
	Scheme newScheme(name, newHeaders);
	
	for (unsigned i = 0; i < tuples.size(); i++) {
		// MAKE A NEW TUPLE TO INSERT WITH COLUMNS SPECIFIED IN OUR INDEXES VECTOR
		Tuple newTuple;
		auto currentTuple = tuples.begin(); // get iterator to 1st element
		advance(currentTuple, i);
		unsigned int k = 0;

		for (unsigned j = 0; j < indexes.size(); j++) {

			// I PUSH MY NEW VECTOR TUPLE WITH ONLY THE COMLUMNS THAT ARE IN MY INDEXES VECTOR (e.g. (0, 3))
			newTuple.push_back(currentTuple->at(indexes[j]));
			if (!oneTime) {
				newScheme.names.push_back(theScheme.names[indexes[j]]);
			}
		}
		oneTime = true;
		if (k < indexes.size()) {
			newRelation.tuples.insert(newTuple);
			k++;
		}
	}
	newRelation.theScheme = newScheme;
	
	return newRelation;
}

Relation Relation::Rename(vector<string> newNames) {
	Relation newRelation(name, headers);
	newRelation.tuples = tuples;
	newRelation.theScheme.names = newNames;
	
	return newRelation;
}

string Relation::toString(string query) {
	ostringstream out;
	unsigned int variableTracker = 0;
	
	out << query + "? ";
	if (tuples.size() > 0) {
		out << "Yes(" << tuples.size() << ")" << endl;
		out << " ";
		
		for (unsigned int i = 0; i < tuples.size(); i++) {
			auto currentTuple = tuples.begin(); // get iterator to 1st element
			advance(currentTuple, i);
			variableTracker = 0;
			vector<string> alreadyCalled;

			for (unsigned int j = 0; j < currentTuple->size(); j++) {
				// GOES THROUGH AND GIVES ALL OF THE ACTUAL VARIABLES
				bool firstIt;
				
				if ((j + variableTracker != theScheme.names.size())) {
					variableTracker = 0;
				}
				while ((j + variableTracker != theScheme.names.size()) && (theScheme.names[j + variableTracker].at(0) == '\'')) {
					variableTracker++;
				}

				if (j + variableTracker != theScheme.names.size()) {
					if (alreadyCalled.size() < 1) {
						alreadyCalled.push_back(theScheme.names[j + variableTracker]);
					}
					else {
						for (unsigned k = 0; k < alreadyCalled.size(); k++) {
							if (theScheme.names[j + variableTracker] == alreadyCalled[k]) {
								variableTracker++;
								while (theScheme.names[j + variableTracker].at(0) == '\'') {
									variableTracker++;
								}
							}
						}
						alreadyCalled.push_back(theScheme.names[j + variableTracker]);
					}
				}
				if ((j + variableTracker != theScheme.names.size())) {
					if(firstIt) {
						out << " ";
					}
					out << " " << theScheme.names[j + variableTracker] << "=" << currentTuple->at(j);
					if (j == currentTuple->size() - 1) {
						out << endl;
						firstIt = true;
					}
					else {
						out << ",";
						firstIt = false;
					}
				}
			}
		}
	}
	else {
		out << "No" << endl;
	}

	return out.str();
}
Relation Relation::Join(Relation relI, Relation relII) {
	cout << "in join" << endl;
	Relation joinedRelation;
	set<Tuple> joinedTuples;
	set<Tuple> tupleSet1 = relI.getTuples();
	set<Tuple> tupleSet2 = relII.getTuples();
	Scheme joinedScheme;
	Scheme sch1 = relI.getScheme();
	Scheme sch2 = relII.getScheme();
	
	for(Tuple tupIt : tupleSet1) { // : ---> for (it = list.begin(); it != list.end(); it++)
		for(Tuple tupIt2 : tupleSet2) {
			map<string, string> usedVar;
			Tuple newTup;
			Scheme newSch;
			bool usable = true;
			
			for (unsigned int i = 0; i < sch1.size(); i++) {
				usedVar.emplace(sch1.at(i), tupIt.at(i));
				newTup.push_back(tupIt.at(i));
				newSch.push_back(sch1.at(i));
			}
			for (unsigned int i = 0; i < sch2.size(); i++) {
				string var = "";
				
				try {
					var = usedVar.at(sch2.at(i));
				}
				catch (out_of_range &e) {
					usedVar.emplace(sch2.at(i), tupIt.at(i));
					newTup.push_back(tupIt.at(i));
					newSch.push_back(sch2.at(i));
					var = tupIt.at(i);
				}
				if (var != tupIt.at(i)) {
					usable = false;
				}
			}
			if (usable) {
				joinedScheme = newSch;
				joinedTuples.insert(newTup);
				joinedScheme = newSch;
			}
		}
	}
	joinedRelation = Relation("", joinedScheme);
	joinedRelation.setTuples(joinedTuples);
	
	return joinedRelation;
}
Relation Relation::Union(Relation relI, Relation relII) {
	set<Tuple> allTups;
	if(relI.getName() == relII.getName()) {
		allTups = relI.getTuples();
		set<Tuple> tupleSet1 = relII.getTuples();
		allTups.insert(tupleSet1.begin(), tupleSet1.end());
	}
	else {
		throw logic_error("relation names don't match");
	}
	relI.setTuples(allTups);
	
	return relI;
}
void Relation::ProjectJoin(Relation &rel, Scheme &query) {
	string name = query.getName();
	Scheme sch = rel.getScheme();
	Scheme newSch;
	newSch.setName(name);
	vector<int> posTaken;
	set<Tuple> tupleSet = rel.getTuples();
	set<Tuple> newTups;
	
	for(string var : query) {
		if (var[0] != '\'') {
			for(unsigned int i = 0; i < sch.size(); i++) {
				if (var == sch.at(i)) {
					posTaken.push_back(i);
					newSch.push_back(sch.at(i));
				}
			}
		}
	}
	for(Tuple tuple : tuples) {
		Tuple newTuple;
		
		newTuple.setName(query.getName());
		for (int posit : posTaken) {
			newTuple.push_back(tuple.at(posit));
		}
		newTuple.setName(name);
		newTups.insert(newTuple);
	}
}

//SETTERS & GETTERS
string Relation::getName() {
	return name;
}
void Relation::setName(string name) {
	this->name = name;
}
set<Tuple> Relation::getTuples() {
	return tuples;
}
void Relation::setTuples(set<Tuple> tuples) {
	this->tuples = tuples;
}
Scheme Relation::getScheme() {
	return theScheme;
}