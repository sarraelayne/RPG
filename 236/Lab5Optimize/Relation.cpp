#include "Relation.h"

Relation::Relation(string temp, Scheme temp2){
    name = temp;
    for(unsigned int i = 0; i < temp2.size(); i++){
        relScheme.push_back(temp2.at(i));
    }
}
Relation::Relation(){}
Relation::~Relation(){}


Relation Relation::join(Relation joinMe){
    Relation result;

    Scheme newScheme = this->combineSchemes(joinMe.getScheme());
    result.setScheme(newScheme);
	for(Tuple t1: tupSet){
	    for(Tuple t2: joinMe.getTupSet()){
    		if(isJoinable(t1, t2)){
    		    Tuple tempTup;
    		    tempTup = combineTuples(t1, t2);
    		    result.addTuple(tempTup);
    		}
	    }
	}
	if(this->getSchemeSize() == 0){
	    set<Tuple> tempTups = joinMe.getTupSet();
	    result.setTupSet(tempTups);
	    Scheme tempS = joinMe.getScheme();
	    result.setScheme(tempS);
	}
    return result;
}
Relation Relation::unionRelations(Relation unionMe){
    Relation result;
    result.setTupSet(unionMe.getTupSet());

    if(relScheme == unionMe.getScheme()){
        for(Tuple t: tupSet){
            if(result.getTupSet().count(t) == 0){
                t.printTuple(relScheme);
                result.addTuple(t);
            }
	    }
	    result.setScheme(unionMe.getScheme());
    }
    else{
        cout << "Schemes don't match; union impossible\n";
    }
    return result;
}
Scheme Relation::combineSchemes(Scheme combineMe){
    Scheme result = relScheme;
    for(unsigned int i = 0; i < combineMe.size(); i++){
        bool duplicated = false;
        for(unsigned int j = 0; j < relScheme.size(); j++){
            if(combineMe.at(i)==relScheme.at(j)){
                duplicated = true;
                colIndex1.push_back(j);
                colIndex2.push_back(i); 
            }
        }
        if(!duplicated){
            result.push_back(combineMe.at(i));
        }
    }
    set<int> colUnique2Set; 
    for(unsigned int k = 0; k < combineMe.size(); k++){
        colUnique2Set.insert(k);
    }
    for(unsigned int g = 0; g < colIndex2.size(); g++){
        colUnique2Set.erase(colUnique2Set.find(colIndex2.at(g)));
    }
    colUnique2.clear();
    for(int val: colUnique2Set){                 
        colUnique2.push_back(val);
    }
    return result;
}
bool Relation::isJoinable(Tuple t1, Tuple t2){
    bool result = false;
    for(unsigned int i = 0; i < colIndex1.size(); i++){
        if(t1.at(colIndex1.at(i)) == t2.at(colIndex2.at(i))){
            result = true;
        }
        else{
            return false;
        }
    }
    if(colIndex1.size() == 0){
        result = true;
        return result;
    }
    return result;
}
Tuple Relation::combineTuples(Tuple t1, Tuple t2){
    Tuple result = t1;
    for(unsigned int i = 0; i < colUnique2.size(); i++){
        result.push_back(t2.at(colUnique2.at(i)));
    }
    return result;
}
set<Tuple> Relation::getTupSet(){
    return tupSet;
}
void Relation::printTupSet(){
    for(Tuple t: tupSet){
         cout << "\'";
        for(unsigned int i = 0; i < t.size(); i++){
            cout << t.at(i) << " ";
        }
        cout << "\'" << endl;
	}
}
void Relation::setTupSet(set<Tuple> newSet){
    tupSet = newSet;
}
void Relation::addTuple(Tuple tup){
    tupSet.insert(tup);
}
void Relation::relationToString(){
    for(Tuple tup : tupSet){
        for (unsigned i = 0; i < tup.size(); i++)
        {
            if(i == 0){
                cout << "  ";
            }
            if(relScheme.size() > i){
                cout << relScheme.at(i) << "=";
            }
            cout << tup.at(i);
            if(i != tup.size() - 1){
                cout << ",";
            }
            if(i == tup.size() - 1){
                cout << endl;
            }
            else{
                cout << " ";
            }
        }
    }
}
void Relation::setName(string newName){
    name = newName;
}
void Relation::setScheme(Scheme newScheme){
    relScheme.clear();
    for(unsigned int i = 0; i < newScheme.size(); i++){
        relScheme.push_back(newScheme.at(i));
    }
}
Scheme Relation::getScheme(){
    return relScheme;
}
void Relation::printRelScheme(){
    for(unsigned int i = 0; i < relScheme.size(); i++){
        cout << relScheme.at(i) << " ";
    }
    cout << endl;
}
int Relation::getSchemeSize(){
    return relScheme.size();
}
int Relation::getTupSetSize(){
    return tupSet.size();
}
void Relation::operator=(const Relation &temp){
    this->name = temp.name;
    this->relScheme = temp.relScheme;
    this->tupSet = temp.tupSet;
}
Relation Relation::select1(int index, string value){
    Relation temp;
    for(Tuple tup: tupSet){
        if(tup.at(index) == value){
            temp.addTuple(tup);
        }
    }
    return temp;
}
Relation Relation::select2(unsigned int index1, unsigned int index2){
    cout << "start select2 Relation.cpp\n";
    Relation temp;
    cout << "TupSet size: " << tupSet.size() << endl;
    this->printTupSet();
    cout << "index1: " << index1 << "   index2: " << index2 << endl;
    for(Tuple tup: tupSet){
        cout << "start for loop select2";
        if(tup.at(index1) == tup.at(index2)){
            cout << "pre addTuple select2";
            temp.addTuple(tup);
            cout << "post addTuple select2";
        }
    }
    cout << "end select2 Relation.cpp\n";
    return temp;
}
Relation Relation::project(vector<int> keepTheseColumns){
    Relation tempRel;
    Scheme newScheme; 
    unsigned int count = 0;
    for(Tuple tup: tupSet){
        Tuple tempTup;
        for(unsigned int i = 0; i < keepTheseColumns.size(); i++){
            tempTup.push_back(tup.at(keepTheseColumns.at(i)));
            if(i == 0 && count == 0){
                for(unsigned int d = 0; d < keepTheseColumns.size(); d++){
                    newScheme.push_back(relScheme.at(keepTheseColumns.at(d)));
                }
            }
        }
        tempRel.addTuple(tempTup);
        count = 1;
    }
    relScheme.clear();
    tempRel.setScheme(newScheme);

    return tempRel;
}
Relation Relation::rename(Scheme newScheme){
    Relation temp;

    temp.setScheme(newScheme);

    for(Tuple tup: tupSet){
        temp.addTuple(tup);
    }
    
    Scheme relSchem = temp.getScheme();
    
    return temp;
}