#include "Board.h"
#include <Windows.h>

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)

// White is on rows 0 && 1, while black is on rows 6 && 7
Board::Board(){
	board = new Piece**[BOARD_SIZE];
	for (unsigned int row = 0; row < BOARD_SIZE; ++row){
		board[row] = new Piece*[BOARD_SIZE];
		for (unsigned int col = 0; col < BOARD_SIZE; ++col){
			int backgroundColor;
			if ((row + 1 + col + 1) % 2 == 0){
				backgroundColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			}
			else{
				backgroundColor = BACKGROUND_RED | BACKGROUND_INTENSITY;
			}

			//Initialize pieces
			if (row == 6){
				board[row][col] = new Pawn(row, col, false, 0, backgroundColor); // Try different colors for black
			}
			else if (row == 1){
				board[row][col] = new Pawn(row, col, true, FOREGROUND_WHITE | FOREGROUND_INTENSITY, backgroundColor);
			}
			else if (row == 0){
				if (col == 0 || col == 7){
					board[row][col] = new Rook(row, col, true, FOREGROUND_WHITE | FOREGROUND_INTENSITY, backgroundColor);
				}
				else if (col == 1 || col == 6){
					board[row][col] = new Knight(row, col, true, FOREGROUND_WHITE | FOREGROUND_INTENSITY, backgroundColor);
				}
				else if (col == 2 || col == 5){
					board[row][col] = new Bishop(row, col, true, FOREGROUND_WHITE | FOREGROUND_INTENSITY, backgroundColor);
				}
				else if (col == 3){ //Queen
					board[row][col] = new Queen(row, col, true, FOREGROUND_WHITE | FOREGROUND_INTENSITY, backgroundColor);
				}
				else if (col == 4){ //King
					board[row][col] = new King(row, col, true, FOREGROUND_WHITE | FOREGROUND_INTENSITY, backgroundColor);
				}
			}
			else if (row == 7){
				if (col == 0 || col == 7){
					board[row][col] = new Rook(row, col, false, 0, backgroundColor);
				}
				else if (col == 1 || col == 6){
					board[row][col] = new Knight(row, col, false, 0, backgroundColor);
				}
				else if (col == 2 || col == 5){
					board[row][col] = new Bishop(row, col, false, 0, backgroundColor);
				}
				else if (col == 3){ //Queen
					board[row][col] = new Queen(row, col, false, 0, backgroundColor);
				}
				else if (col == 4){ //King
					board[row][col] = new King(row, col, false, 0, backgroundColor);
				}
			}
			else{
				board[row][col] = new Piece(row, col, false, backgroundColor);
			}


		}

	}

}

Representation* Board::getPieceAt(int row, int col){
	return board[row][col]->getRep();
}

bool Board::tryToMove(int fromX, int fromY, int toX, int toY, bool whitesTurn){
	if (board[fromX][fromY]->canMoveTo(Coords(toX, toY), whitesTurn, board, true)){
		Piece *temp = board[toX][toY];
		int tempBG = board[toX][toY]->getRep()->getBackground();
		int tempBG2 = board[fromX][fromY]->getRep()->getBackground();
		board[toX][toY] = board[fromX][fromY];
		board[toX][toY]->setRepBackground(tempBG);
		board[fromX][fromY] = temp;
		board[fromX][fromY]->setRepBackground(tempBG2);
		return true;
	}
	else{
		return false;
	}
}

Coords Board::kingPosition(bool white){
	Coords c;
	// Find position of king
	for (int i = 0; i < BOARD_SIZE; ++i){
		for (int j = 0; j < BOARD_SIZE; ++j){
			if (board[i][j]->isKing()){
				if (white && board[i][j]->isWhitePiece()){ // White's turn and a white king
					c.posX = i;
					c.posY = j;
				}
				else if (!white && !board[i][j]->isWhitePiece()){ // Black's turn and a black king
					c.posX = i;
					c.posY = j;
				}
			}
		}
	}
	return c;
}

bool Board::iterPieceAttackPos(Coords c, bool white){
	for (int i = 0; i < BOARD_SIZE; ++i){
		for (int j = 0; j < BOARD_SIZE; ++j){
			if (white && board[i][j]->isWhitePiece()){ // White attacking
				if (board[i][j]->canMoveTo(c, white, board, false)){
					return true;
				}
			}
			else if (!white && !board[i][j]->isWhitePiece()){ // Black attacking
				if (board[i][j]->canMoveTo(c, white, board, false)){
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::kingInCheck(bool white){	
	// Find position of king
	Coords kingCoords = kingPosition(white);
	// Check if any opposing piece can move to the king
	// If they can, you're in check
	return iterPieceAttackPos(kingCoords, !white); // See if the opposite team can attack the king
}