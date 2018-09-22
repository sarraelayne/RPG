#pragma once
#include "FighterInterface.h"
using namespace std;

class Fighter: public FighterInterface {
public:
    Fighter(string inName);
    ~Fighter();
    //virtual int selectAction(int game[3][3]) = 0;
    bool isValidMove(int game[3][3]. int action);
    
protected:
    string name;
    
}