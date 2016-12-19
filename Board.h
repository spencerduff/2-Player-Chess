#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board{
public:
	static const int BOARD_SIZE = 8;

	Board();

	Representation* getPieceAt(int row, int col);

	bool tryToMove(int fromX, int fromY, int toX, int toY, bool whitesTurn);

private:
	Piece ***board;

};

#endif