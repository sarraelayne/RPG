#include "Arena.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


bool Arena::addFighter(string info) {
    stringstream ss(info);
    string name;
    string type;
    int hp;
    int strength;
    int speed;
    int magic;
    bool isRepeat = false;
    
    if (ss >> name >> type >> hp >> strength >> speed >> magic && ss.eof()) {
        for(int i = 0; i < fighterVec.size(); i++) {
            if (fighterVec.at(i) -> getName() == name) {
                i = fighterVec.size() + 1;
                isRepeat = true;
            }
        }
        if (type == "A" && !isRepeat) {
            cout << "Adding archer" << endl;
            fighterVec.push_back(new Archer(name, hp, strength, speed, magic));
        }
        else if (type == "C" && !isRepeat) {
            cout << "Adding cleric" << endl;
            fighterVec.push_back(new Cleric(name, hp, strength, speed, magic));
        }
        else if (type == "R" && !isRepeat) {
            cout << "Adding robot" << endl;
            fighterVec.push_back(new Robot(name, hp, strength, speed, magic));
        }
        else {
            return false;
        }
        return true;
    }
    return false;
}

bool Arena::removeFighter(string name) {
    for (int i = 0; i < fighterVec.size(); i++) {
        if (fighterVec.at(i)->getName() == name) {
            fighterVec.erase(fighterVec.begin() + i);
            return true;
        }
    }
    return false;
}

FighterInterface* Arena::getFighter(string name) {
    for (Fighter* cp : fighterVec) {
        if (cp->getName() == name) {
            return cp;
        }
    }
    return NULL;
}


int Arena::getSize () const {
    int arenaSize;
    
    arenaSize = fighterVec.size();
    return arenaSize;
}