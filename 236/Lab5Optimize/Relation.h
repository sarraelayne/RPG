#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include "Tuple.h"
#include "Scheme.h"

using namespace std;

class Relation {
        
    friend class Tuple;
    friend class Scheme;
    
    public:
    Relation(string temp, Scheme temp2);
    Relation();
    ~Relation();

    //Project 4
    Relation join(Relation joinMe);
    Relation unionRelations(Relation unionMe);
    Scheme combineSchemes(Scheme combineMe);
    bool isJoinable(Tuple t1, Tuple t2);
    Tuple combineTuples(Tuple t1, Tuple t2);
    set<Tuple> getTupSet();
    void printTupSet();
    void setTupSet(set<Tuple> newSet);
    
    //Project 3
    void addTuple(Tuple tup);    
    void relationToString();
    void setName(string newName);
    void setScheme(Scheme newScheme);
    Scheme getScheme();
    void printRelScheme();
    int getSchemeSize();
    int getTupSetSize();
    void operator=(const Relation &temp);
    Relation select1(int index, string value);
    Relation select2(unsigned int index1, unsigned int index2);
    Relation project(vector<int> keepTheseColumns);
    Relation rename(Scheme newScheme);
    
    private:
    string name;
    Scheme relScheme;
    set<Tuple> tupSet;
    vector<int> colIndex1;
    vector<int> colIndex2;
    vector<int> colUnique2;
    
};