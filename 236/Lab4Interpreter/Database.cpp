#include "Database.h"

void Database::store(string name, Relation r) {
	myMap.insert(pair<string, Relation>(name, r));
}

void Database::giveTuple(Tuple t, string name) {
	//map.find(name)->second.tuples
}
