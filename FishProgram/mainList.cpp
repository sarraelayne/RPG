#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"

using namespace std;

int main(int argc, char *argv[]) {
    LinkedList<string> theList;
    
    theList.append("awesome");
    theList.append("stupid");
    theList.append("smart");
    
    theList.insert(0, "The");
    theList.insert(2, "professor");
    theList.insert(4, "is a");
    theList.insert(6, "idiot");
    theList.remove(3);
    theList.remove(0);
    theList.remove(4);
    
    theList.append("pushover");
    
    theList.print();
    
    return 0;
}

//g++ -o link mainList.cpp
//valgrind ./link (valgrind runs and monitors this program)