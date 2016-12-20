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
		if (g.playerInCheck()){
			std::cout << "There is a player in check\n";
			if (g.playerInMate()){
				std::cout << "There is a player in checkmate, gg.\n";
				system("PAUSE");
				return 0;
			}
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