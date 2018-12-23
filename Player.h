#pragma once
#include <iostream>
#include <string>

/**
* Class Player
* Purpose: Store customizable features like Name, Symbol, and whether they won or not.
*/
class Player
{
	std::string name;
	std::string symbol;
	bool win = false;
public:
	Player();
	std::string getSym() { return symbol; }
	std::string getName() { return name; }	
	void setWin(bool is_w) { win = is_w; }
	bool getWin() { return win;}

	~Player();
};

