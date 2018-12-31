#include "Player.h"

/**
*Constructor: Initializes the symbol and the name of a player
*
*@param: Str1 Str2 represents symbol and name respectively
*/
Player::Player()
	:name{"Unknown"}, symbol{"Unknown"}
{
}

Player::Player(std::string str, std::string sym)
	:name{ str }, symbol{ sym }
{
}

Player::~Player()
{
}
