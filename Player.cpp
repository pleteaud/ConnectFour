#include "Player.h"

/**
*Constructor: Initializes the symbol and the name of a player
*
*@param: Str1 Str2 represents symbol and name respectively
*/
Player::Player()
{
	std::cout << ">> What's your Name: ";
	std::getline(std::cin, name);
	std::cout << "\n>> What would you like your symbol to be: ";
	std::getline(std::cin, symbol);
}

Player::~Player()
{
}
