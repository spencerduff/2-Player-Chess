#ifndef PIECE_H
#define PIECE_H

#include "coords.h"
#include "Representation.h"

class Piece{
public:
	Piece(int x, int y, bool w, int foregroundColor);
	Piece(const Piece &other);
	
	virtual Piece* clone();

	virtual bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake);
	Representation* getRep(){ return rep; }
	void setRepBackground(int b);

	virtual ~Piece();

	bool isEmptySpace();
	bool isWhitePiece();
	bool isKing();
	bool isPawn();
	bool getHasMoved();
	bool getJumpedTwo();

	void resetJumps();


protected:
	Representation *rep;
	bool emptySpace;
	bool white;
	bool king;
	bool pawn;
	bool hasMoved;
	bool jumpedTwo;
	Coords coords;

	bool isMyTeamThere(Coords c, Piece ***board);

	void takePiece(Coords c, Piece ***board);

	bool checkCollisionIteratively(int fromX, int fromY, int toX, int toY, Piece ***board);

private:

};


class Pawn : public Piece{
public:
	Pawn(int x, int y, bool w, int foregroundColor, int backgroundColor);
	Pawn(const Pawn &other);

	Piece* clone() override;

	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake) override;

private:

};

class Rook : public Piece{
public:
	Rook(int x, int y, bool w, int foregroundColor, int backgroundColor);
	Rook(const Rook &other);

	Piece* clone() override;

	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake) override;

private:
	bool hasMoved;

};

class Knight : public Piece{
public:
	Knight(int x, int y, bool w, int foregroundColor, int backgroundColor);
	Knight(const Knight &other);

	Piece* clone() override;

	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake) override;

private:

};

class Bishop : public Piece{
public:
	Bishop(int x, int y, bool w, int foregroundColor, int backgroundColor);
	Bishop(const Bishop &other);

	Piece* clone() override;

	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake) override;

private:

};

class Queen : public Piece{
public:
	Queen(int x, int y, bool w, int foregroundColor, int backgroundColor);
	Queen(const Queen &other);

	Piece* clone() override;

	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake) override;

private:

};

class King : public Piece{
public:
	King(int x, int y, bool w, int foregroundColor, int backgroundColor);
	King(const King &other);

	Piece* clone() override;

	bool canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake) override;

private:
	bool hasMoved;

	bool canCastle(Coords c, bool whitesTurn, Piece ***board, bool shouldTake);

};


#endif