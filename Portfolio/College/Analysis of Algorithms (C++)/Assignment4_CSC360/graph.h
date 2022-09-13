// CLASS PROVIDED:  Graph 
//
// CONSTRUCTOR for the Graph class:
//   Graph()
//     Description:		constructor initializes Graph objects
//     Preconditions:	none
//     Postcondition:	sets all graph values equal to -1, then and decides where edges occur in the graph, prints those connections
//
// CONSTANT MEMBER FUNCTIONS for the Graph class
//   bool HasEdge(const int, const int) 
//     Description:		checks to see if there is an edge between two nodes
//     Preconditions:	none
//     Postcondition:	true or false is returned based on whether or not there was an edge
//
//   bool CheckNodesUpTo(int) 
//     Description:		checks all the nodes up to the integer provided
//     Preconditions:	none
//     Postcondition:	true or false is returned based on whether there are any edges or not
//
//   void ClearIndependentSet() 
//     Description:		checks to see if there is an edge between two nodes
//     Preconditions:	none
//     Postcondition:	sets the Checking array to 0
//
//   void PrintMaxIndependent(void) const
//     Description:		prints the maximum independent
//     Preconditions:	none
//     Postcondition:	none
//
//   void FindMaxIndependent(void) const
//     Description:		finds the maximum independent set and weight using a brute-force algorithm
//     Preconditions:	none
//     Postcondition:	sets MaxIndependentSize to the maximum independent weight based off the brute-force algorithm
//
//   void ApproxMaxIndependent(void) const
//     Description:		finds the maximum independent set and weight using a greedy approximation algorithm
//     Preconditions:	none
//     Postcondition:	sets MaxIndependentSize to the approximate maximum independent weight
//
//   void PrintInfo(void) const
//     Description:		prints the edge density and total amount of nodes to the screen
//     Preconditions:	none
//     Postcondition:	none
//
// 	 DESTRUCTOR for the Graph class:
//   ~Graph()
//     Description:		destructor for Graph
//     Preconditions:	none
//     Postcondition:	none


#ifndef GRAPH_H
#define GRAPH_H

#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Graph
{

private:
	static const int NODE_ARRAY_SIZE = 20;
	static const int EDGE_DENSITY_PERCENT = 25;
	int AmountOfEdges;
	int Edges[NODE_ARRAY_SIZE][NODE_ARRAY_SIZE];
	bool IndependentNodes[NODE_ARRAY_SIZE];
	bool Checking[NODE_ARRAY_SIZE];

	bool CheckNodesUpTo(int);

public:
	Graph();
	int MaxIndependentSize;
	bool HasEdge(const int, const int);
	void ClearIndependentSet();
	void PrintTheGraph();
	void PrintMaxIndependent();
	void FindMaxIndependent();
	void ApproxMaxIndependent();
	void PrintInfo();
	~Graph();
};

#endif

