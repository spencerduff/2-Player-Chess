#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board{
public:
	static const int BOARD_SIZE = 8;

	Board();

	~Board();

	Board(const Board &other);

	Representation* getPieceAt(int row, int col);

	bool tryToMove(int fromX, int fromY, int toX, int toY, bool whitesTurn);

	bool kingInCheck(bool white);

private:

	Coords kingPosition(bool white);

	bool iterPieceAttackPos(Coords c, bool white);

	void swapPieces(int fromX, int fromY, int toX, int toY);

	Piece ***board;

};

#endif