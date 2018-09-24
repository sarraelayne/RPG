#include "Arena.h"
#include <vector>
using namespace std;


bool Arena::addFighter(string info) {
    int arenaSize;
    stringstream ss(info);
    string name;
    string type;
    string hp;
    string strength;
    string speed;
    string magic;
    
    if (ss >> name >> type >> hp >> strength >> speed >> magic) {
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Specs: " << hp << " " << strength << " " << speed << " " << magic;
        if (type == "A") {
            cout << "Adding archer" << endl;
            fighterVec.push_back(new Archer(name, hp, strength, speed, magic));
        }
        else if (type == "C") {
            cout << "Adding cleric" << endl;
            fighterVec.push_back(new Cleric(name, hp, strength, speed, magic));
        }
        else if (type == "R") {
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
        if (fighterVec.at(i)->getname() == name) {
            fighterVec.erase(fighterVec.begin() + i);
            return true;
        }
    }
    return false;
}

FighterInterface* Arena::getFighter(string name) {
    for (Fighter* cp : fighterVec) {
        if (cp->getName() == name) {
            return cp
        }
    }
    return NULL;
}


int Arena::getSize () const {
    arenaSize = fighterVec.size();
    return arenaSize;
}