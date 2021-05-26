// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#ifndef TDICE_H_
#define TDICE_H_
#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
	Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

	// template method
	void playGame(const int playersCount = 0) {
		playersCount_ = playersCount;
		movesCount_ = 0;

		initializeGame();

		for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
			makeMove(i);
			if (i == playersCount_ - 1)
				++movesCount_;
		}

		printWinner();
	}

	virtual ~Game() {}

protected:
	// primitive operations
	virtual void initializeGame() = 0;
	virtual void makeMove(int player) = 0;
	virtual void printWinner() = 0;
	virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
					// returns true if winner is decided
	static const int noWinner = -1;

	int playersCount_;
	int movesCount_;
	int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
	// implementing concrete methods
	void initializeGame() {
		playersCount_ = rand() % numPlayers_ + 1; // initialize players
	}

	void makeMove(int player) {
		if (movesCount_ > minMoves_) {
			const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
			if (chance < movesCount_) playerWon_ = player;
		}
	}

	void printWinner() {
		cout << "Monopoly, player " << playerWon_ << " won in "
			<< movesCount_ << " moves." << endl;
	}

private:
	static const int numPlayers_ = 8; // max number of players
	static const int minMoves_ = 20; // nobody wins before minMoves_
	static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
	void initializeGame() {
		playersCount_ = numPlayers_; // initalize players
		for (int i = 0; i < numPlayers_; ++i)
			experience_[i] = rand() % maxExperience_ + 1;
	}

	void makeMove(int player) {
		if (movesCount_ > minMoves_) {
			const int chance = (rand() % maxMoves_) / experience_[player];
			if (chance < movesCount_) playerWon_ = player;
		}
	}

	void printWinner() {
		cout << "Chess, player " << playerWon_
			<< " with experience " << experience_[playerWon_]
			<< " won in " << movesCount_ << " moves over"
			<< " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
			<< endl;
	}

private:
	static const int numPlayers_ = 2;
	static const int minMoves_ = 2; // nobody wins before minMoves_
	static const int maxMoves_ = 100; // somebody wins before maxMoves_
	static const int maxExperience_ = 3; // player's experience
							   // the higher, the greater probability of winning
	int experience_[numPlayers_];
};
class Dice : public Game {

public:
	void initializeGame() {
	  //initialized the player count
		playersCount_ = numPlayers_;
		
	}
	void makeMove(int player) {
		
	        int playerScore; //score of player or computer in a turn
		char rORp; // input char that determines if player rolls or pass
		int randPass; //random int that determines if computer rolls or passed

		if (movesCount_ < maxMoves_) {
		         // fills up array of 5 random number 1-6 for the roll
			for (int i = 0; i < 5; ++ i) {
				roll_[i] = rand() % 6 + 1;
			}
			        if (player == 0){  // computer's turn
					
					

				       if (!comPass_) { // if the computer hasn't passed
					       playerScore = roll_[0] + roll_[1] + roll_[2] + roll_[3] + roll_[4]; // calculates computers score for that roll
						
					       if (playerScore > comMaxScore_) { comMaxScore_ = playerScore; } // if the current roll is greater than the high score it overrides the current score
					                //outputs the computer's roll and its current high score
						cout << "Computer Rolled: " << roll_[0] << " " << roll_[1]
							<< " " << roll_[2] << " " << roll_[3] << " " << roll_[4]
							<< ", " << "Computers High Score = " << comMaxScore_ << endl;
						randPass = rand() % 4 + 1;// gives the computer a 1/4 chance of passing and keeping highscore

						if (randPass == 4) { 
						  comPass_ = true;  //makes the comPass_ true making the computer pass and keep score
							
						}
					}
				       else {    //if comuter passed and kept score outputs decision and high score
						cout << "Computer Rolled: Passed , Computer's High Score = " << comMaxScore_ << endl;
					
					}
				}
				

				if(player == 1){ //if it is the players score
				           if (!playerPass_) { //the player hasn't passed and kept score 
						playerScore = roll_[0] + roll_[1] + roll_[2] + roll_[3] + roll_[4];
						if (playerScore > playerMaxScore_) { playerMaxScore_ = playerScore; }
						        //outputs the players roll and player's highscore  
			    				cout << "You Rolled: " << roll_[0] << " " << roll_[1]
							<< " " << roll_[2] << " " << roll_[3] << " " << roll_[4]
							<< ", " << "Your High Score = " << playerMaxScore_ << endl;

						    if (movesCount_ != maxMoves_ - 1) { // makes sure program doesn't ask player to roll or pass on last turn
						      cout << "Roll Again [y/n]: ";  // ask player to roll again
						      cin >> rORp;

						      if (rORp == 'n') { playerPass_ = true; } // if player choses not to roll player pass is true making the player keep score

						
						}
					   }  // if player passes and keeps score and outputs highscore
					else { cout << "You Rolled: Passed, Your High Score = " << playerMaxScore_ << endl; }
				
				}
				
		}
		//if both player decide to keep score outputs both highscores
		if (comPass_ && playerPass_) {
			cout << "Both Players Decided To Keep Score, Computer Score:" << comMaxScore_ << " | Player Score: " << playerMaxScore_ << endl;
		}
	}
	
	 bool endOfGame() {
	         // ends game if move count is 3
		 if (movesCount_ >= 3) {
			 return true;
		 }
		 // ends game if both player chose to pass and keep score
		 else if (comPass_ && playerPass_) {
			 
			 return true;
		 }
		 //if no conditions are made game is not ended
		 else { return false; }
		 
		
	 }
	
	void printWinner() {
	         // outputs computer as winner if its score is greater
		if (comMaxScore_ > playerMaxScore_) {
			cout << "You Lose Computer Wins!" << endl;
		}

		//outputs computer as winner if score is tied
		else if (comMaxScore_ == playerMaxScore_ ) {
			cout << "You Lose Computer Wins!" << endl;
		}
		// outputs user as winner if no other losing conditions are met
		else {
			cout << "You Win" << endl;
		}
	}
private:
        int roll_[5] = {0,0,0,0,0}; // array on ints to hold dice roll
        int playerMaxScore_ = 0; //player highscore
        int comMaxScore_ = 0; //computer highscore
        bool comPass_ = false; // bool to decide of computer passed
        bool playerPass_ = false; //bool to decide of the player passes
         //intializes attributes from game class
        static const int numPlayers_ = 2;
	static const int minMoves_ = 1;
	static const int maxMoves_ = 3;
};

#endif
