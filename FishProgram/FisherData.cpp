#include "FisherData.h"
#include <sstream>

FisherData::FisherData(){
    cout << "In the default" << endl;
}    

FisherData::FisherData(string line){
    stringstream ss(line);
    
    ss >> pangalan;
    ss >> weight;
    ss >> fishType;
}

FisherData::~FisherData(){
    
}             

string FisherData::getName() {
    return pangalan;
}

int FisherData::getWeight(){
    return weight;
}

string FisherData::getFishType(){
    return fishType;
}
    
void FisherData::printStuff(){
    cout << "We have a fisher person" << endl;
    cout << " Name: " << pangalan << endl;
    cout << " Weight: " << weight << endl;
    cout << " Fish Type: " << fishType << endl;
}