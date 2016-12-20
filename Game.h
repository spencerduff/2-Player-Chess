#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <string>

class Game{
public:
	Game();
	void printWhiteBoard();
	void printBlackBoard();

	bool isWhiteTurn();
	void switchTurn();

	void incTurnNum();
	int getTurnNum();

	bool playerInCheck();

	bool parseInput(std::string input);

private:
	Board gameBoard;
	bool whitesTurn;
	int turnNumber; // Starts at 2 and displays (turnNumber / 2) every turn. 
					// This way the turn goes up 1 every time it is incremented twice.

};


#endif