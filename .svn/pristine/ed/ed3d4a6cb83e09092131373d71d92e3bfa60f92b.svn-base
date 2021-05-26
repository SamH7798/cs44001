#include "tdice.hpp"
int main() {
	srand(time(nullptr));
		Game* gp = nullptr;
		/*
	// play chess 10 times
	for (int i = 0; i < 10; ++i) {
		gp = new Chess;
		gp->playGame();
		delete gp;
	}


	// play monopoly 5 times
	for (int i = 0; i < 5; ++i) {
		gp = new Monopoly;
		gp->playGame();
		delete gp;
	}
	*/
		//plays dice 3 times
		int round = 1;
		for (int i = 0; i < 3; ++i) {
			cout << "Round: " << round << endl;
			gp = new Dice;
			gp->playGame();
			delete gp;
			++round;
			cout << "-------------------------------" << endl;
		}
	

}

