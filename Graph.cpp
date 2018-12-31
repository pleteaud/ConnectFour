#include "Graph.h"
#include "Core.h"

/**
*deleteElements(): Deletes all elements of vector
*return: None
*@param: vector of intergers
*/
void deleteElements(std::vector<int> &v)
{
	while (v.size() != 0)
	{
		v.erase(v.begin());
	}
}
/**
*calcTotalNodes(): Calculate the sum of all nodes in tree given brachning factor and depth.
*				   Using the equation for Geometric Progression: S = (1-r^n)/(1-r), where n is the number of terms
*				   The number of terms is equivalent to Depth + 1 because "depth 0" must also counts towards the number of terms.
*return: interger representing the total amount of nodes
*@param: Two intergers representing the bracnhing factor and depth (r and n-1 respectively)
*/
int calcTotalNodes(int branchingFactor, int depth)
{
	int total = (1 - std::pow(branchingFactor, depth + 1)) / (1 - branchingFactor);
	return total;
}

/**
*createNodes(): Create total nodes of tree
*return: None
*@param: Vector of Nodes, interger representing total nodes in tree
*/
void createNodes(std::vector<Node> &listOfNodes, int totalNodes, Board &parentState)
{
	int j = 6; int k = 1;
	for (int i = totalNodes-1; i >= 0; i--)
	{
		
		// Initialize each node position with a number from 0 to totalNodes-1. Will simplify locating desired node using adjacent list.
		Node tempNode; tempNode.index = i;
		//if root node copy the current state of the game
		if (i == totalNodes - 1)
		{
			tempNode.state = parentState;
			tempNode.p.setName("COM");
			tempNode.p.setSym("X");
		}
		//if create nodes at depth 1
		else if (i >= totalNodes - 8 && i < totalNodes - 1)
		{
			tempNode.state = parentState;
			tempNode.p.setName("Dave");
			tempNode.p.setSym("O");
			try
			{
				tempNode.state.addPoint(j, tempNode.p);
			}
			catch (const Exception &e)
			{
				//if illegal move, render branch useless. In the future make a constant variable associated with this value, i.e c1 = -1.
				tempNode.static_Val = -1;
			}
		}
		//depth 2
		else if (i < totalNodes - 8)//57-1-7(to get to everything below 49)
		{
			if (j == 6) k++;
			tempNode.state = listOfNodes[totalNodes - k].state; //k[1,7]
			tempNode.p.setName("COM");
			tempNode.p.setSym("X");
			try
			{
				tempNode.state.addPoint(j, tempNode.p);
			}
			catch (const Exception &e)
			{
				//if illegal move, render branch useless. In the future make a constant variable associated with this value, i.e c1 = -1.
				tempNode.static_Val = -1;
			}
		}
		if ((i % 7 != 0) && (i != listOfNodes.size()-1)) j--;
		else j = 6;
		listOfNodes[i] = tempNode;
	}
}
/**
*printNodes(): Print Nodes Data
*return: None
*@param: Vector of Nodes
*/
void printNodes(std::vector<Node> listOfNodes)
{
	for (int x = 0; x < listOfNodes.size(); x++)
	{
		std::cout << "Node " << listOfNodes[x].index << ", Name: " << listOfNodes[x].p.getName()
			<< listOfNodes[x].p.getSym() << '\n';
		listOfNodes[x].state.print();
	}
}
/**
*calcStaticValues(): Calculate the static values of the nodes (state of the game)
*					 "Description of function"
*return: None
*@param: A node
*/
void calcStaticValues(Node &anode)
{
	anode.static_Val = anode.index * 2;
}

/// Create adjacency list for all the nodes of the tree.
/**
*createAdjList(): For each node, the function initializes/creates a vector that holds an int that represents the node that is adjacent to it.
*				  vect[i][j]--> index i represents the desired node, and j represents all the nodes which are reachable by that node
*
*return: None
*@param: An empty vector of int vectors. 
*/
void createAdjList(std::vector<std::vector<int>> &adjList)
{//depth 0
	std::vector<int> v;

	//index i must go from the first to the last node of depth 1, 
	//i.e if BF is 7, then adjacent nodes to  are 36-41.
	for (int i = adjList.size() - 8; i < adjList.size() - 1; i++)
	{
		v.push_back(i);
	}
	//assign the root node (the last node created in "createNodes()" this vector
	adjList[adjList.size() - 1] = v;
	//clear vector to be used for depth 1 and depth 2
	deleteElements(v);

	//depth 1
	//accumulator to be used in the equation to keep track of which nodes are adjacent to a specific node: (6*k)-j, where k = [1,6], j=[1,6]
	// i.e if we are at node 37, then all the nodes adjacent to it will be 42 and (6*k)-j, where k is 2, and j ranges from [1,6].
	int k = 1;
	for (int i = (adjList.size() - 8); i < (adjList.size() - 1); i++)
	{
		for (int j = 7; j > 0; j--)
		{
			int connectedNode{ (7 * k) - j };
			v.push_back(connectedNode);
		}
		//every node in depth 1 is also connected to the root node
		v.push_back(adjList.size() - 1);
		adjList[i] = v;
		deleteElements(v);
		k++;
	}
	//depth 2
	//accumulators to be used in the equation to keep track of which nodes are adjacent to a specific node: (6*k)+j, where k =[6], j[0,5]
	//i.e if we are at node 30, then the only node adjacent to it will be (6*k)-j, where k is 6, and j is 5.
	int j = 0;
	k--;
	for (int i = 0; i < adjList.size() - 8; i++)
	{
		if ((i % 7 == 0) && (i != 0)) j++;
		int connectedNode{ (7 * k) + j };
		v.push_back(connectedNode);
		adjList[i] = v;
		deleteElements(v);
		//we only want to increment the j if we are on the next set of 6 nodes. that is: 0-5 (j=0), 6-11(j=1)...30-35(j=5).

	}

}

/**
*miniMax(): Minimax algorithm to determine which move to take based of static function.
*
*return: None
*@param: Vector of all the nodes, Vectors of adjacent nodes, Node to inspect, interger representing depth
*/
void miniMax(std::vector<Node> &listOfNodes, std::vector<std::vector<int>> &adjList,Node &anode, int depth)
{
	int parentRootIndex = adjList.size() - 1; // clarifies what the terminating case of the for-loops is.
	if (depth == 2)
	{
		//base case, that is we've reached the last node
		//calculate static value for node
		calcStaticValues(anode);

	}
	else if (depth%2 == 0)
	{
		//Maximizer 
		//determine which of the 7 vertices are bigger
		depth++;
		int max; Board maxBoard; int xCoord;
		for (int j = 0; j < 7; j++)
		{
			miniMax(listOfNodes, adjList, listOfNodes[adjList[parentRootIndex][j]], depth);
			int possibleStaticVal = listOfNodes[adjList[parentRootIndex][j]].static_Val;
			int possibleLoc = j;
			Board possibleBoard = listOfNodes[adjList[parentRootIndex][j]].state;
			if ((j == 0) || (max < possibleStaticVal))
			{
				max = possibleStaticVal;
				xCoord = possibleLoc;
				maxBoard = possibleBoard;
			}
		}
		//copy that board and the location to place COM's symbol
		listOfNodes[parentRootIndex].state = maxBoard;
		listOfNodes[parentRootIndex].location = xCoord;
		listOfNodes[parentRootIndex].static_Val = max;
	}
	else if (depth % 2 != 0)
	{
		//Minimizer
		//determine which of the 7 vertices is smallest
		depth++;
		for (int i = 49; i < parentRootIndex; i++)
		{
			int min; Board minBoard; int xCoord;
			for (int j = 0; j < 7; j++)
			{
				miniMax(listOfNodes, adjList, listOfNodes[adjList[i][j]], depth);
				int possibleStaticVal = listOfNodes[adjList[i][j]].static_Val;
				int possibleLoc = j;
				Board possibleBoard = listOfNodes[adjList[i][j]].state;
				if ((j == 0) || (min > possibleStaticVal))
				{
					min = possibleStaticVal;
					xCoord = possibleLoc;
					minBoard = possibleBoard;
				}
			}
			//copy that board and the location to place COM's symbol
			listOfNodes[i].state = minBoard;
			listOfNodes[i].location = xCoord;
			listOfNodes[i].static_Val = min;
		}
	}
	
} 