#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> { 
    
    public:
    Tuple();
    ~Tuple();

    void add(string info);
    int getSize();
    void printTuple();
    void printTuple(Scheme values);
};