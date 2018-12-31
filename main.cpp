#include "Board.h"
#include "Graph.h"
#include "Core.h"

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
	std::cout << ">> " << p.getName() << "'s turn...\n";
	int column;
	while (true) 
	{
		try {

			std::cout << ">> Enter a positive interger between 1-7\n";
			column = getInt();
			if (column < 0) std::cout << ">> Negative interger not valid\n";
			else if (column == 0 || column > 7) std::cout << ">> Not in the range [1,7]\n";
			//if acceptable value
			else if (column > 0 && column < 8)
			{
				b.addPoint(uint16_t(column - 1), p);
				break;

			}
		}
		catch (const Exception &e)
		{
			std::cout << e.message << '\n';
		}
	}

}

int main()
{

	Board newBoard;

	std::string name, symbol;
	std::cout << ">> Player 1:\n";
	std::cout << ">> What's your Name: ";
	std::getline(std::cin, name);
	std::cout << "\n>> What would you like your symbol to be: ";
	std::getline(std::cin, symbol);
	Player p1(name,symbol);
	//Create COM attributes--such as Adjacency List, Nodes for minimax Algorithm, Branching Factor, Depth,etc
	int totalNodes = calcTotalNodes(7, 2);
	std::vector<Node> listOfNodes(totalNodes);
	std::vector<std::vector<int>> adjList(totalNodes);
	newBoard.print();

	while (true) {
		//player one's turn
		initiateTurn(p1, newBoard);
		newBoard.print();
		std::cout << '\n';
		//Check to see if user wins or if board is filled
		if (p1.getWin()) { std::cout << ">> " << p1.getName() << "wins!\n"; break; }
		if (newBoard.checkBoardFill() == 6) { std::cout << ">> Board is filled. No winners\n"; break; }
	
		// COM's turn
		std::cout << '\n';
		createNodes(listOfNodes, totalNodes, newBoard);
		createAdjList(adjList);
		//the initial depth sent is zero because we want the recursive algoritm to fold backwards
		miniMax(listOfNodes, adjList, listOfNodes[0], 0);
		//We reset the name of COM back to COM cause our minimax algorithm copies the player data from each board, therein overriding the previous name/sym
		//**Must fix this**
		listOfNodes[totalNodes-1].p.setName("COM"); listOfNodes[totalNodes-1].p.setSym("X");
		std::cout << listOfNodes[totalNodes-1].p.getName() << "Turn \n";
		newBoard.addPoint(listOfNodes[totalNodes-1].location, listOfNodes[totalNodes-1].p);
		newBoard.print();
		//Check to see if user wins or if board is filled
		if (listOfNodes[totalNodes-1].p.getWin()) { std::cout << ">> " << listOfNodes[totalNodes-1].p.getName() << "wins!\n"; break; }
		if (newBoard.checkBoardFill()==6) { std::cout << "Board is filled. No winners\n"; break; }
	}
	system("pause");
	return 0;

}