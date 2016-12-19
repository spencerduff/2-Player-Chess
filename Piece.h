#ifndef PIECE_H
#define PIECE_H

#include "coords.h"
#include "Representation.h"

class Piece{
public:
	Piece(int x, int y, bool w, int foregroundColor);
	virtual bool canMoveTo(Coords c, bool whitesTurn, Piece ***board);
	Representation* getRep(){ return rep; }
	void setRepBackground(int b);

	virtual ~Piece();

	bool isEmptySpace();
	bool isWhitePiece();


protected:
	Representation *rep;
	bool emptySpace;
	bool white;
	Coords coords;

	void takePiece(Coords c, Piece ***board);

	bool checkCollisionIteratively(int fromX, int fromY, int toX, int toY, Piece ***board);

private:

};


class Pawn : public Piece{
public:
	Pawn(int x, int y, bool w, int foregroundColor, int backgroundColor);
	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board) override;

private:
	bool hasMoved;

};

class Rook : public Piece{
public:
	Rook(int x, int y, bool w, int foregroundColor, int backgroundColor);
	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board) override;

private:

};

class Knight : public Piece{
public:
	Knight(int x, int y, bool w, int foregroundColor, int backgroundColor);
	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board) override;

private:

};

class Bishop : public Piece{
public:
	Bishop(int x, int y, bool w, int foregroundColor, int backgroundColor);
	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board) override;

private:

};

class Queen : public Piece{
public:
	Queen(int x, int y, bool w, int foregroundColor, int backgroundColor);
	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board) override;

private:

};

class King : public Piece{
public:
	King(int x, int y, bool w, int foregroundColor, int backgroundColor);
	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board) override;

private:

};


#endif