#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Relation.h"

using namespace std;

class Database : public map<string, Relation> {
    friend class Relation;
    
    public:
    Database();
    ~Database();
    void databaseToString();
    
    int countTuples();
};