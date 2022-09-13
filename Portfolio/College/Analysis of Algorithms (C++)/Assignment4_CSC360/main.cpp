#include <iostream>
#include "graph.h"
/*
Assignment 4 - CSC 360

Program by: Kevin Andor Scutaru, Nathaniel DeHart, Cole Stewart

NOTE: In DevC++, make sure to press 'Rebuild All'(F12) then 'Run'(F10) instead of just 'Compile & Run'(F11).

We found issues in DevC++ when using Compile & Run.
*/

int main()
{
    clock_t t;
    Graph myGraph;

    int choice = -1;
 //   cout << "\nGenerated a graph (0s stand for no edge, 1s stand for an edge)\n" << endl;
//    myGraph.PrintTheGraph();

    //Print the amount of verticies, edges, and edge density of the graph
    myGraph.PrintInfo();
    
    t = clock();
    myGraph.FindMaxIndependent();
    t = clock() - t;
    myGraph.PrintMaxIndependent();
    cout << "It took: " << (((float)t)/CLOCKS_PER_SEC) << " seconds to find the Max Independent Set using Brute Force.\n" << endl;

    myGraph.ClearIndependentSet();

    t = clock();
    myGraph.ApproxMaxIndependent();
    t = clock() - t;
    myGraph.PrintMaxIndependent();
    cout << "It took: " << (((float)t)/CLOCKS_PER_SEC) << " seconds to approximate the Max Independent Set." << endl;
	
	return 0;

}


