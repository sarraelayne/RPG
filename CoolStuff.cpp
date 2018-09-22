/*
Sarra Smith CS235 section 1
   -default is a.out unless overridden by -o
   -./ to run program
   search "how to use bash"
   learn to use command prompt
*/

#include <iostream>
#include <string>

using namespace std;

int main(int grande, char *estupido[]) {
    cout << grande << endl;
    
    int i;
for (i = 1; i < grande; ++i) {
    cout << estupido[i] << " ";
}    
cout << endl;
/*    string somethinglovely;
    
    cout << "Tell me something lovely" << endl;
    getline(cin, somethinglovely);
    cout << somethinglovely << endl;
    */
    
    return 0;
}