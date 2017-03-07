#include "Piece.h"

Piece::Piece(int x, int y, bool w, int backgroundColor){
	white = w;
	coords = Coords(x, y);
	rep = new Representation(' ', 0, backgroundColor);
	emptySpace = true;
	king = false;
	pawn = false;
	jumpedTwo = false;
	hasMoved = false;
}

Piece::Piece(const Piece &other){
	this->white = other.white;
	this->coords = other.coords;
	this->rep = new Representation(*other.rep);
	this->emptySpace = other.emptySpace;
	this->king = other.king;
}

Piece::~Piece(){
	delete rep;
}

Piece* Piece::clone(){
	return new Piece(*this);
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

bool Piece::isPawn(){
	return pawn;
}

bool Piece::getHasMoved(){
	return hasMoved;
}

bool Piece::getJumpedTwo(){
	return jumpedTwo;
}

Coords Piece::getCoords(){
	return coords;
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
// Then it will keep going as long as it's getting closer to the position and there isn't something in the way
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
		if (row < 8 && row >= 0 && col < 8 && col >= 0 && !board[row][col]->emptySpace){
			return true;
		}
	}
	return true;
}

void Piece::setRepBackground(int b){
	rep->changeBackground(b);
}

void Piece::setCoords(Coords c){
	coords = Coords(c.posX, c.posY);
}

Pawn::Pawn(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('P', foregroundColor, backgroundColor);
	emptySpace = false;
	pawn = true;
}

Pawn::Pawn(const Pawn &other) : Piece(other){
	this->hasMoved = other.hasMoved;
}

Piece* Pawn::clone(){
	return new Pawn(*this);
}

void Piece::resetJumps(){
	jumpedTwo = false;
}

void Piece::takePiece(Coords c, Piece ***board){
	int background = board[c.posX][c.posY]->getRep()->getBackground();
	delete board[c.posX][c.posY];
	board[c.posX][c.posY] = NULL;
	board[c.posX][c.posY] = new Piece(c.posX, c.posY, false, background);
}

void Piece::promotePawn(Coords c, Piece ***board){
	std::cout << "Type the capitalized letter of the Piece you want to promote your pawn to: \n";
	char choice;
	std::cin >> choice;

	while (choice != 'N' && choice != 'Q' && choice != 'R' && choice != 'B'){
		std::cout << "Please choose B, Q, R, or N: \n";
		std::cin >> choice;
	}
	bool white = board[c.posX][c.posY]->isWhitePiece();
	int foreground = board[c.posX][c.posY]->getRep()->getForeground();
	int background = board[c.posX][c.posY]->getRep()->getBackground();
	delete board[c.posX][c.posY];
	board[c.posX][c.posY] = NULL;

	if (choice == 'N'){
		board[c.posX][c.posY] = new Knight(c.posX, c.posY, white, foreground, background);
	}
	else if (choice == 'B'){
		board[c.posX][c.posY] = new Bishop(c.posX, c.posY, white, foreground, background);
	}
	else if (choice == 'Q'){
		board[c.posX][c.posY] = new Queen(c.posX, c.posY, white, foreground, background);
	}
	else if (choice == 'R'){
		board[c.posX][c.posY] = new Rook(c.posX, c.posY, white, foreground, background);
	}

}

bool Pawn::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if (white && whitesTurn){ 
		// if left or right
		if (c.posY == coords.posY - 1 || c.posY == coords.posY + 1){
			// if above
			if (c.posX == coords.posX + 1){
				// check if it's next to me and just jumped 2 spaces, and it's not a white piece
				if (board[coords.posX][c.posY]->getJumpedTwo() && !board[coords.posX][c.posY]->isWhitePiece()){
					if (shouldTake){
						takePiece(Coords(coords.posX, c.posY), board);
						hasMoved = true;
						coords = c;
					}
					return true;
				}
				// if there's something there that isn't a white piece
				if (!board[c.posX][c.posY]->isEmptySpace() && !board[c.posX][c.posY]->isWhitePiece()){
					// take it
					if (shouldTake){
						takePiece(c, board);
						hasMoved = true;
						if (c.posX == 7){
							promotePawn(coords, board);
						}
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
					jumpedTwo = true;
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
			if (c.posX == 7){
				promotePawn(coords, board);
			}
			coords = c;
		}
		return true;
	}
	else if (!white && !whitesTurn) {
		// if left or right
		if (c.posY == coords.posY - 1 || c.posY == coords.posY + 1){
			// if above
			if (c.posX == coords.posX - 1){
				// check if it's next to me and just jumped 2 spaces, and it's a white piece
				if (board[coords.posX][c.posY]->getJumpedTwo() && board[coords.posX][c.posY]->isWhitePiece()){
					takePiece(Coords(coords.posX, c.posY), board);
					hasMoved = true;
					coords = c;
					return true;
				}
				// if there's something there that is a white piece
				if (!board[c.posX][c.posY]->isEmptySpace() && board[c.posX][c.posY]->isWhitePiece()){
					// take it
					if (shouldTake){
						takePiece(c, board);
						hasMoved = true;
						if (c.posX == 0){
							promotePawn(coords, board);
						}
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
					jumpedTwo = true;
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
			if (c.posX == 0){
				promotePawn(coords, board);
			}
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
}

Rook::Rook(const Rook &other) : Piece(other){
	this->hasMoved = other.hasMoved;
}

Piece* Rook::clone(){
	return new Rook(*this);
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
}

Knight::Knight(const Knight &other) : Piece(other){

}

Piece* Knight::clone(){
	return new Knight(*this);
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
				hasMoved = true;
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
}

Bishop::Bishop(const Bishop &other) : Piece(other){

}

Piece* Bishop::clone(){
	return new Bishop(*this);
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
					hasMoved = true;
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
}

Queen::Queen(const Queen &other) : Piece(other){

}

Piece* Queen::clone(){
	return new Queen(*this);
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

King::King(int x, int y, bool w, int foregroundColor, int backgroundColor) : Piece(x, y, w, backgroundColor){
	delete rep;
	rep = NULL;
	rep = new Representation('K', foregroundColor, backgroundColor);
	emptySpace = false;
	king = true;
}

King::King(const King &other) : Piece(other){
	this->hasMoved = other.hasMoved;
}

Piece* King::clone(){
	return new King(*this);
}

void swapPieces(int fromX, int fromY, int toX, int toY, Piece*** board){
	Piece *temp = board[toX][toY];
	int tempBG = board[toX][toY]->getRep()->getBackground();
	int tempBG2 = board[fromX][fromY]->getRep()->getBackground();
	Coords tempCoords(toX, toY);
	board[toX][toY]->setCoords(Coords(fromX, fromY));
	board[fromX][fromY]->setCoords(tempCoords);
	board[toX][toY] = board[fromX][fromY];
	board[toX][toY]->setRepBackground(tempBG);
	board[fromX][fromY] = temp;
	board[fromX][fromY]->setRepBackground(tempBG2);
}

bool King::canCastle(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	if (!hasMoved){
		if (!white && !whitesTurn){
			if (c.posX == 7 && c.posY == 6){ // Black king's side castling 
				if (!board[7][7]->getHasMoved()){
					if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY, board) && board[c.posX][c.posY]->isEmptySpace()){ // no collision and empty space
						if (shouldTake){
							coords = c;
							swapPieces(7, 7, 7, 5, board); // rook movement
							hasMoved = true;
						}
						return true;
					}
				}
			}
			else if (c.posX == 7 && c.posY == 2){
				if (!board[7][0]->getHasMoved()){
					if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY - 1, board) && board[c.posX][c.posY - 1]->isEmptySpace()){ // no collision and empty space
						if (shouldTake){
							coords = c;
							swapPieces(7, 0, 7, 3, board); // rook movement
							hasMoved = true;
						}
						return true;
					}
				}
			}
		}
		else if (white && whitesTurn){
			if (c.posX == 0 && c.posY == 6){ // White king's side castling 
				if (!board[0][7]->getHasMoved()){
					if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY, board) && board[c.posX][c.posY]->isEmptySpace()){ // no collision and empty space
						if (shouldTake){
							coords = c;
							swapPieces(0, 7, 0, 5, board); // rook movement
							hasMoved = true;
						}
						return true;
					}
				}
			}
			else if (c.posX == 0 && c.posY == 2){
				if (!board[0][0]->getHasMoved()){
					if (!checkCollisionIteratively(coords.posX, coords.posY, c.posX, c.posY - 1, board) && board[c.posX][c.posY - 1]->isEmptySpace()){ // no collision and empty space
						if (shouldTake){
							coords = c;
							swapPieces(0, 0, 0, 3, board); // rook movement
							hasMoved = true;
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool King::canMoveTo(Coords c, bool whitesTurn, Piece ***board, bool shouldTake){
	// Castling
	if (canCastle(c, whitesTurn, board, shouldTake)){
		return true;
	}
	
	if (abs(c.posX - coords.posX) > 1 || abs(c.posY - coords.posY) > 1){ // Trying to move too far
		return false;
	}
	// Queen's movement
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