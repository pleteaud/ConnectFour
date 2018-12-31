#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Player.h"

/**
* Class Board
* Purpose: Holds member functions and variables that:
*		   1) Keeps track of the empty and filled locations
*		   2) Adds a symbol to a location
*		   3) Checks valid locations,who won, and if the board is filled
*		   4) Prints board out
*/
class Board
{
	std::vector<std::vector<std::string>> loc;

public:
	Board();
	void print();
	bool check(uint16_t x,uint16_t y);
	void checkWinner(uint16_t x, uint16_t y,Player &p);
	void addPoint( uint16_t x_coor,Player &p);
	uint16_t	findMinPoint(uint16_t x);
	uint16_t checkBoardFill();
	~Board();
};

