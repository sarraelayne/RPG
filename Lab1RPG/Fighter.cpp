#include "Fighter.h"
using namespace std;

Fighter::Fighter(string inName) {
    cout << "Fighter(inName) constructor";
    name = inName;
}
Fighter::~Fighter() {
	cout << "in Fighter default"
}
string Fighter::getName() const {
	cout << "In Fighter getName"<<endl;
	return name;
}
bool Fighter::isValidMove(int game[3][3]/*size of tictactoe board*/, int action) {
	if (game[action /3][action % 3] == -1) {
		return true;
	}
	return false;
}