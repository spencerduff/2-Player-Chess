#include "Piece.h"

Piece::Piece(int x, int y, bool w, int backgroundColor){
	white = w;
	coords = Coords(x, y);
	rep = new Representation(' ', 0, backgroundColor);
	emptySpace = true;
	king = false;
}

Piece::~Piece(){
	delete rep;
}

bool Piece::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	return false;
}

bool Piece::isEmptySpace(){
	return emptySpace;
}

bool Piece::isWhitePiece(){
	return white;
}

bool Piece::isKing(){
	return king;
}

bool Piece::isMyTeamThere(Coords c, Piece ***board){
	if (white && !board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){ // If I am white and the space isn't empty and he is white
		return true;
	}
	else if (!white && !board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){ // If I am black and the space isn't empty and he is black
		return true;
	}
	return false;
}

// TODO: Refactor
// The idea of this function is it checks if we're iterating a position and which way to iterate.
// Then it will keep going as long
bool Piece::checkCollisionIteratively(int fromX, int fromY, int toX, int toY, Piece ***board){
	bool posXIter = true;
	bool posYIter = true;
	if (fromX > toX){
		posXIter = false;
	}
	if (fromY > toY){
		posYIter = false;
	}
	bool iterX = false;
	bool iterY = false;
	if (fromX != toX){
		iterX = true;
	}
	if (fromY != toY){
		iterY = true;
	}
	int col = fromY;
	int row = fromX;
	int prevXDiff = 0;
	int prevYDiff = 0;
	int deltaX = 0; 
	int deltaY = 0;
	for (; deltaX <= prevXDiff && deltaY <= prevYDiff;){
		prevXDiff = abs(row - toX);
		prevYDiff = abs(col - toY);
		if (iterX){
			if (posXIter){
				++row;
			}
			else{
				--row;
			}
		}
		if (iterY){
			if (posYIter){
				++col;
			}
			else{
				--col;
			}
		}
		deltaX = abs(row - toX);
		deltaY = abs(col - toY);
		if (row == toX && col == toY){
			return false;
		}
		if (!board[row][col]->emptySpace){
			return true;
		}
	}
	return true;
}

void Piece::setRepBackground(int b){
	rep->changeBackground(b);
}

Pawn::Pawn(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('P', foregroundColor, backgroundColor);
	emptySpace = false;
	hasMoved = false;
	king = false;
}

void Piece::takePiece(Coords c, Piece ***board){
	int background = board[c.posX][c.posY]->getRep()->getBackground();
	delete board[c.posX][c.posY];
	board[c.posX][c.posY] = NULL;
	board[c.posX][c.posY] = new Piece(c.posX, c.posY, false, background);
}

// TODO: Work on logic to take pieces en-passant
bool Pawn::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if (white && whitesTurn){ 
		// if left or right
		if (c.posY == coords.posY - 1 || c.posY == coords.posY + 1){
			// if above
			if (c.posX == coords.posX + 1){
				// if there's something there that isn't a white piece
				if (!board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){
					// take it
					if (shouldTake){
						takePiece(c, board);
						hasMoved = true;
						coords = c;
					}
					return true;
				}
			}
		}

		if (c.posY != coords.posY){
			return false;
		}

		//Move two spaces
		if (!hasMoved && c.posX == coords.posX + 2){
			if (board[c.posX][c.posY]->isEmptySpace() && board[c.posX-1][c.posY]->isEmptySpace()){
				if (shouldTake){
					hasMoved = true;
					coords = c;
				}
				return true;
			}
		}

		//Move one space
		if (c.posX != coords.posX + 1){
			return false;
		}
		if (!board[c.posX][c.posY]->isEmptySpace()){
			return false;
		}
		if (shouldTake){
			hasMoved = true;
			coords = c;
		}
		return true;
	}
	else if (!white && !whitesTurn) {
		// if left or right
		if (c.posY == coords.posY - 1 || c.posY == coords.posY + 1){
			// if above
			if (c.posX == coords.posX - 1){
				// if there's something there that is a white piece
				if (!board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){
					// take it
					if (shouldTake){
						takePiece(c, board);
						hasMoved = true;
						coords = c;
					}
					return true;
				}
			}
		}


		if (c.posY != coords.posY){
			return false;
		}

		//Move two spaces
		if (!hasMoved && c.posX == coords.posX - 2){
			if (board[c.posX][c.posY]->isEmptySpace() && board[c.posX + 1][c.posY]->isEmptySpace()){
				if (shouldTake){
					hasMoved = true;
					coords = c;
				}
				return true;
			}
		}

		//Move one space
		if (c.posX != coords.posX - 1){
			return false;
		}
		if (!board[c.posX][c.posY]->isEmptySpace()){
			return false;
		}
		if (shouldTake){
			hasMoved = true;
			coords = c;
		}
		return true;
	}
	else{
		return false;
	}
}

Rook::Rook(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('R', foregroundColor, backgroundColor);
	emptySpace = false;
	hasMoved = false;
	king = false;
}

bool Rook::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if ((white && whitesTurn) || (!white && !whitesTurn)){ // White moving his own piece OR Black moving his own piece
		if ((c.posX != coords.posX) ^ (c.posY != coords.posY)){ // Only moving in X or Y plane
			if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY, board) && !isMyTeamThere(c, board)){ // No collision on our way there and my team doesn't occupy the space
				if (whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){ // White tries to take black piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (!whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){ // Black tries to take white piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (shouldTake){
					hasMoved = true;
					coords = c;
				}
				return true;
			}
			else{ // is collision
				return false;
			}
		}
		else{ // Moving in 2 or 0 planes
			return false;
		}
	}
	else{ // Someone not moving their own piece
		return false;
	}
}

Knight::Knight(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('N', foregroundColor, backgroundColor);
	emptySpace = false;
	king = false;
}

bool Knight::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if (!(abs(c.posX - coords.posX) == 1 && abs(c.posY - coords.posY) == 2)){ 
		if (!(abs(c.posX - coords.posX) == 2 && abs(c.posY - coords.posY) == 1)){ // If it's not a legal knight position to move to
			return false;
		}
	}

	if ((white && whitesTurn) || (!white && !whitesTurn)){ // White moving his own piece OR Black moving his own piece
		if (!isMyTeamThere(c, board)){ // My team doesn't occupy the space
			if (whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){ // White tries to take black piece if it's there
				if (shouldTake){
					takePiece(c, board);
				}
			}
			if (!whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){ // Black tries to take white piece if it's there
				if (shouldTake){
					takePiece(c, board);
				}
			}
			if (shouldTake){
				coords = c;
			}
			return true;
		}
		else{ // It is my own team
			return false;
		}
	}
	else{ //Someone not moving their own piece
		return false;
	}
}

Bishop::Bishop(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('B', foregroundColor, backgroundColor);
	emptySpace = false;
	king = false;
}

// Really similar to Rook, only change is the ^ operator in the second line to a & operator. Beautiful.
bool Bishop::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if ((white && whitesTurn) || (!white && !whitesTurn)){ // White moving his own piece OR Black moving his own piece
		if ((c.posX != coords.posX) & (c.posY != coords.posY)){ // Moving in both X and Y plane
			if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY, board) && !isMyTeamThere(c, board)){ // No collision on our way there and my team doesn't occupy the space
				if (whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){ // White tries to take black piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (!whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){ // Black tries to take white piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (shouldTake){
					coords = c;
				}
				return true;
			}
			else{ // is collision
				return false;
			}
		}
		else{ // Moving in 1 or 0 planes
			return false;
		}
	}
	else{ // Someone not moving their own piece
		return false;
	}
}

Queen::Queen(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('Q', foregroundColor, backgroundColor);
	emptySpace = false;
	king = false;
}

bool Queen::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if ((white && whitesTurn) || (!white && !whitesTurn)){ // White moving his own piece OR Black moving his own piece
		if (((c.posX != coords.posX) & (c.posY != coords.posY)) || ((c.posX != coords.posX) ^ (c.posY != coords.posY))){ // Moving in both X and Y plane or moving in either or
			if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY, board) && !isMyTeamThere(c, board)){ // No collision on our way there and my team doesn't occupy the space
				if (whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){ // White tries to take black piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (!whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){ // Black tries to take white piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (shouldTake){
					coords = c;
				}
				return true;
			}
			else{ // is collision
				return false;
			}
		}
		else{ // Not moving in exactly 2 planes or 1 plane exclusively
			return false;
		}
	}
	else{ // Someone not moving their own piece
		return false;
	}
}

King::King(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('K', foregroundColor, backgroundColor);
	emptySpace = false;
	hasMoved = false;
	king = true;
}

bool King::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if (abs(c.posX - coords.posX) > 1 || abs(c.posY - coords.posY) > 1){ // Trying to move too far
		return false;
	}
	//Queen's movement
	if ((white && whitesTurn) || (!white && !whitesTurn)){ // White moving his own piece OR Black moving his own piece
		if (((c.posX != coords.posX) & (c.posY != coords.posY)) || ((c.posX != coords.posX) ^ (c.posY != coords.posY))){ // Moving in both X and Y plane or moving in either or
			if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY, board) && !isMyTeamThere(c, board)){ // No collision on our way there and my team doesn't occupy the space
				if (whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){ // White tries to take black piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (!whitesTurn && !board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){ // Black tries to take white piece if it's there
					if (shouldTake){
						takePiece(c, board);
					}
				}
				if (shouldTake){
					hasMoved = true;
					coords = c;
				}
				return true;
			}
			else{ // is collision
				return false;
			}
		}
		else{ // Not moving in exactly 2 planes or 1 plane exclusively
			return false;
		}
	}
	else{ // Someone not moving their own piece
		return false;
	}
}