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

	bool parseInput(std::string input);

private:
	Board gameBoard;
	bool whitesTurn;
	int turnNumber;


};


#endif