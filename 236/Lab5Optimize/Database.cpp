#include "Database.h"

Database::Database(){}
Database::~Database(){}


int Database::countTuples(){
    unsigned int numTups = 0;
    map<string, Relation>::iterator it;
    
    for ( it = this->begin(); it != this->end(); it++ ) {
        numTups = numTups + it->second.getTupSetSize();
    }
    return numTups;
}
void Database::databaseToString(){
    //map<string, Relation>
    //cout << "Begin databaseToString();\n";
    //Database::iterator it = this->begin();
    //cout << this->size() << ": database size\n";
    
    /*
    for(it=this->begin();it!=this->end();it++){//maybe delete first condition
        //cout << "start databaseToString() for loop\n";
        cout << it->first << "( ";//name of relation
        cout << ")\n";
        Relation temp = it->second;//relation
        temp.relationToString();
        //cout << "end databaseToString() for loop\n";
    }*/
}
