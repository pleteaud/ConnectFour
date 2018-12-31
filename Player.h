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
	Player(std::string str, std::string sym);
	void setSym(std::string sym) { symbol = sym; }
	std::string getSym() { return symbol; }
	void setName(std::string str) { name = str; }
	std::string getName() { return name; }	
	void setWin(bool is_w) { win = is_w; }
	bool getWin() { return win;}

	~Player();
};

