#include "Board.h"
#include "Core.h"

///Constructor: Initialize 2D Vector with all "_" to indicate empty spaces. 
/**
*@Return: None
*@param: None
*/
Board::Board()
{
	for (uint16_t y = 0; y < 6; y++) 
	{
		loc.push_back(std::vector<std::string>());
		for (uint16_t x = 0; x < 7; x++) loc[y].push_back("_");
	}
}

///Print(): Print the board layout.
/**
*@Return: None
*@param: None
*/
void Board::print()
{
	std::cout << '\n';
	for (int x = 0; x < 7; x++) std::cout << x << std::setw(5);
	std::cout << '\n';
	for (uint16_t i = 0; i < 6; i++)
	{
		for (uint16_t j = 0; j < 7; j++)
		{
			std::cout << loc[i][j] << std::setw(5);
		}
		std::cout << '\n';

	}
}

/**
*Check(): Determine whether the desired location is vacant.
*		 
*Return:  If location is filled with either player's piece, throw an Exception indicating filled space and to insert a new piece 
*		  Otherwise, return true.
*@param:  Pair of (X,Y) coordinats (uint16_t x, uint16_t y).
*/
bool Board::check(uint16_t x, uint16_t y)
{
	
	if (loc[x][y] == "_") return true;
	else throw Exception{ "Location already filled. \nPlease choose a new one:\n" };
}

/**
*checkWinner(): Using a given point and a Player symbol, check whether there is 4 consecutive symbols (including newly placed point that was passed in)
*				Eight possible ways to win: 2 ways horizontally and vertically, 4 diagonals.
*				If they win set the player's win variable to true.
*
*@param: pair of (X,Y) coordinate, Player to access the player's win variable)
*/
void Board::checkWinner(uint16_t y, uint16_t x, Player &p)
{
	//horizontal right
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if (x + i >6) break;
			else if (loc[y][x + i] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;
			
	}
	//horizontal left
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if (x - i < 0) break;
			else if (loc[y][x - i] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
	//vertical up
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if (y - i < 0) break;
			else if (loc[y-i][x] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
	//vertical down
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if (y + i >5 ) break;
			else if (loc[y + i][x] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
	//right top diagonal
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if ((y - i < 0) || (x + i)>6) break;
			else if (loc[y - i][x + i] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
	//left top diagonal
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if ((y - i < 0) || (x - i) < 0) break;
			else if (loc[y - i][x - i] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
	//left bottom diagonal
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if ((y + i > 5) || (x - i)<0) break;
			else if (loc[y + i][x - i] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
	//right bottom diagonal
	while (true)
	{
		uint16_t counter = 0;
		for (uint16_t i = 0; i < 4; i++)
		{
			if ((y + i > 5) || (x + i) > 6) break;
			else if (loc[y + i][x + i] == p.getSym()) counter++;
		}
		if (counter == 4) p.setWin(true);
		break;

	}
}


/**
*addPoint(): Given the column (X-coord) that that user chose, add a symbol at the next avalaible spot in that row. Invoke findMinRowPoint() to do so. 
*			 Using the new minimum row determined using findMinRowPoint and the user-inputted column variable, the locations' avaliability is tested using check()
*			 Also checks if player has won
*
*@param: X coordinate, Player.
*/

void Board::addPoint(uint16_t x_coor, Player &p)
{
	while (true)
	{
		uint16_t y_coor = findMinPoint(x_coor);
		try
		{
			if (check(y_coor,x_coor))
			{
				//one should think of the y-ccordinate as the rows, and x-coordinate as the columns. 
				loc[y_coor][x_coor] = p.getSym();
				checkWinner(y_coor, x_coor, p);
				break;
			}
		}
		//catch the error thrown by check()
		catch (const Exception &e)
		{
			
			throw e;
			/*std::cin >> x_coor;
			x_coor -= 1;*/
		}

	}
}

/**
*findMinPoint(): Determine the lowest row (y-coor) to place the symbol at
*				 Return the row index.
*				 Lowest in this case means highest real number value... Y_coor = 5  is lower than Y_coor = 4;
*
*@param: An X-coordinate
*/

uint16_t Board::findMinPoint(uint16_t x)
{
	
	uint16_t min_loc = 0;
	for(uint16_t y = 0; y < 6; y++)
	{
		if (loc[y][x] == "_") min_loc = y;
		else break;
	}
	return min_loc;
}

/**
*checkBoardFill(): Determine whether the board is filled or not by check the vacancy of the highest row ([0,6],0)
*				   Return an interger representing the total filled holes.
*				 
*
*@param: An X-coordinate
*/
uint16_t Board::checkBoardFill()
{
	uint16_t counter = 0;
	for (uint16_t x = 0; x < 7; x++) 
	{
		if (loc[0][x] != "_") counter++;

	}
	return counter;
}

	Board::~Board()
{
}

