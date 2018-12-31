#pragma once
#include <vector>
#include <cmath>
#include "Board.h"


struct Node
{
	int index;
	int location;
	Board state;
	Player p; // Can be either User or COM
	int static_Val = 0;
};
int calcTotalNodes(int branchingFactor, int depth);
void createAdjList(std::vector<std::vector<int>> &adjList);
void deleteElements(std::vector<int> &v);
void printNodes(std::vector<Node> listOfNodes);
void createNodes(std::vector<Node> &v, int totalNodes, Board &parentState);
void calcStaticValues(Node &anode);
void miniMax(std::vector<Node> &listOfNodes, std::vector<std::vector<int>> &adjList, Node &anode, int depth);

