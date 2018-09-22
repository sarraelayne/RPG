#ifndef ARENA_H_
#define ARENA_H_
#include "ArenaInterface.h"
#include "FighterInterface.h"
#include "Fighter.h"
#include "Cleric.h"
#include "Archer.h"
#include "Robot.h"
#include <vector>
#include <sstream>
using namespace std;

class Arena: public ArenaInterface{
    public:
        Arena() {}
        ~Arena[] {}
        
        bool addFighter(string info);
        bool removeFighter(string name);
        FighterInterface* getFighter(string name);
        int getSize () const;
    private:
        vector<Fighter*> fighterVec;
};
#endif