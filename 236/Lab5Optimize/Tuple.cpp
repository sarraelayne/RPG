#include "Tuple.h"

Tuple::Tuple(){}
Tuple::~Tuple(){}


void Tuple::add(string info){
    this->push_back(info);
}
int Tuple::getSize(){
    return this->size();
}
void Tuple::printTuple(){
    for(unsigned int i = 0; i < this->size(); i++){
        if(i != this->size()-1){
            cout << this->at(i) << " ";
        }
        else{
            cout << this->at(i);
        }
    }
    cout << endl;
}
void Tuple::printTuple(Scheme values){
    for(unsigned int i = 0; i < this->size(); i++){
        if(i == 0 && values.size()==1){
            cout << "  " << values.at(i) << "=";
            cout << this->at(i);
        }
        else if(i == 0){
            cout << "  " << values.at(i) << "=";
            cout << this->at(i) << ",";
        }
        else if(i != (this->size())-1){
            cout << " " << values.at(i) << "=";
            cout << this->at(i) << ",";
        }
        else{
            cout << " " << values.at(i) << "=";
            cout << this->at(i);
        }
    }
    cout << endl;
}