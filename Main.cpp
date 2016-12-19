#include "Game.h"

int main(){
	Game g;

	bool quit = false;

	//Game loop
	while (!quit){
		if (g.isWhiteTurn()){
			g.printWhiteBoard();
		}
		else{
			g.printBlackBoard();
		}
		//std::cout << std::endl;

		std::string input;
		std::cin >> input;
		std::cout << std::endl;
		if (g.parseInput(input)){
			g.switchTurn();
			g.incTurnNum();
		}
	}


	/*
	std::cout << std::endl;

	g.printWhiteBoard();

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	g.printBlackBoard();
	*/
	return 0;
}