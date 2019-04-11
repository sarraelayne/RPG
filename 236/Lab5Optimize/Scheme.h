#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Scheme : public vector<string> {
    
    public:
    Scheme();
    ~Scheme();

    void operator=(const Scheme &temp);
};