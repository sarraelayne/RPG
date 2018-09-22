#ifndef FISHERDATA_H //if not defined
#define FISHERDATA_H //then define as FISHERDATA_H

#include <iostream>
#include <string>
using namespace std;

class FisherData {
public:
    FisherData();              //Default Constructor
    FisherData(string line);   //Constructor
    ~FisherData();             //Destructor
    
    //getters
    string getName();
    int getWeight();
    string getFishType();
    
    void printStuff();
    
private:
    string pangalan;           //Name in Tagalog
    int weight;
    string fishType;
};

#endif