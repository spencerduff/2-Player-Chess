#include "Game.h"
#include <iostream>

const char ROW[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

Game::Game(){
	turnNumber = 2;
	whitesTurn = true;
}

bool Game::isWhiteTurn(){
	return whitesTurn;
}

void Game::switchTurn(){
	whitesTurn = !whitesTurn;
}

void Game::incTurnNum(){
	turnNumber++;
}

int Game::getTurnNum(){
	return turnNumber;
}

void Game::printBlackBoard(){
	for (int i = 0; i < gameBoard.BOARD_SIZE; ++i){
		std::cout << i + 1 << " ";
		for (int j = gameBoard.BOARD_SIZE - 1; j >= 0; --j){
			std::cout << *gameBoard.getPieceAt(i, j);
			std::cout << ' ';
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int i = gameBoard.BOARD_SIZE - 1; i >= 0; --i){
		std::cout << " " << ROW[i];
	}
	std::cout << std::endl;
	std::cout << "Black's Turn" << " (#" << turnNumber / 2 << ")" << std::endl;
}

void Game::printWhiteBoard(){
	for (int i = gameBoard.BOARD_SIZE - 1; i >= 0; --i){
		std::cout << i + 1 << " ";
		for (int j = 0; j < gameBoard.BOARD_SIZE; ++j){
			std::cout << *gameBoard.getPieceAt(i, j);
			std::cout << ' ';
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int i = 0; i < gameBoard.BOARD_SIZE; ++i){
		std::cout << " " << ROW[i];
	}
	std::cout << std::endl;
	std::cout << "White's Turn" << " (#" << turnNumber / 2 << ")" << std::endl;
}

bool Game::parseInput(std::string input){
	if (input.length() != 4){
		std::cout << "Input's length is incorrect, must consist of 4 characters.\nCharacter 1: column of piece to move. (A-H)\n";
		std::cout << "Character 2: row of piece to move. (1-8)\n";
		std::cout << "Character 3: column of where to move piece. (A-H)\n";
		std::cout << "Character 4: row of where to move piece. (1-8)\n";
		return false;
	}
	else if (input[0] > 'H' || input[0] < 'A' || input[1] > '8' || input[1] < '1' || input[2] > 'H' || input[2] < 'A' || input[3] > '8' || input[3] < '1'){
		std::cout << "Input out of bounds.\nCharacter 1: column of piece to move. (A-H)\n";
		std::cout << "Character 2: row of piece to move. (1-8)\n";
		std::cout << "Character 3: column of where to move piece. (A-H)\n";
		std::cout << "Character 4: row of where to move piece. (1-8)\n";
		return false;
	}
	else{
		int fromPosY = input[0] - 'A';
		int fromPosX = input[1] - '1';
		int toPosY = input[2] - 'A';
		int toPosX = input[3] - '1';
		return gameBoard.tryToMove(fromPosX, fromPosY, toPosX, toPosY, whitesTurn);
	}



	return true;
}

