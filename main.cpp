#include "Board.h"


/**
*getInt(): Reads a postive interger from the user. 
		   Only an interger is acceptable. 
		   No strings and no characters.
*return: A postive interger 				
*@param: None
*/
int getInt() 
{
	std::string str;
	int colNum = 0;
	while (true)
	{
		try
		{
			std::getline(std::cin, str);
			colNum = std::stoi(str);
			break;
		}
		catch (...) 
		{
			std::cout << ">> Invalid Input. No characters or strings. Can't be higher than 7.\n";
		}
	}
	return colNum;
}

///initiateTurn(): Completes a turn given a player and a board
/**
*initiateTurn(): Asks user for a interger that represents column.
*				 Passes that column number to addPoint() to place the player symbol inside the board
*				 Checks three conditions for the user input: 
*					1) If it's less than 0, indicate negative values aren't allowed
*					2) If it's 0 or greater than 7, indicate it's not in valid range of [1,7]
*					3) If it's greater than 0 and less than 8 add symbol to desired column.
*return: None
*@param: A Player and a Board.
*/
void initiateTurn(Player &p, Board &b)
{
	//Player One's turn
	std::cout << ">> " << p.getName() << "'s turn...\n";
	int column;
	while (true) 
	{
		std::cout << ">> Enter a positive interger between 1-7\n";
		column = getInt();
		if (column < 0) std::cout << ">> Negative interger not valid\n";
		else if (column == 0 || column > 7) std::cout << ">> Not in the range [1,7]\n";
		else if (column > 0 && column < 8) break;
	}

	//add location and print board
	b.addPoint(uint16_t(column - 1), p);
}

uint16_t main()
{
	Board newBoard;
	std::cout << ">> Player 1:\n";
	Player p1;
	std::cout << ">> Player 2:\n";
	Player p2;
	newBoard.print();
	while (true) {
		//player one's turn
		initiateTurn(p1, newBoard);
		newBoard.print();
		std::cout << '\n';
		//Check to see if user wins or if board is filled
		//if (p1.getWin()) { std::cout << ">> " << p1.getName() << "wins!\n"; break; }
		if (newBoard.checkBoardFill() == 6) { std::cout << ">> Board is filled. No winners\n"; break; }
	
		// Player Two's turn
		initiateTurn(p2, newBoard);
		newBoard.print();
		std::cout << '\n';
		//Check to see if user wins or if board is filled
		//if (p2.getWin()) { std::cout << ">> " << p2.getName() << "wins!\n"; break; }
		if (newBoard.checkBoardFill()==6) { std::cout << "Board is filled. No winners\n"; break; }
		
	
	}
	system("pause");
	return 0;

}