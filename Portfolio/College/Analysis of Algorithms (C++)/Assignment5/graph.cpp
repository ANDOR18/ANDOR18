#include "graph.h"

Graph::Graph()
{
	MaxIndependentSize = 0;
	srand(time(NULL));
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		Checking[i] = false;
		IndependentNodes[i] = false;
	}
	int randomNum = 0;
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		for (int j = 0; j < NODE_ARRAY_SIZE; j++)
		{
			Edges[i][j] = -1;
		}
	}
	
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		for (int j = 0; j < NODE_ARRAY_SIZE; j++)
		{
			randomNum = rand() % 100;
		//	cout << "\n" << EDGE_DENSITY_PERCENT << "\%" << endl;
		//	cout << "rnd: " << randomNum << endl;
			if(Edges[i][j] == -1)
			{
				if(i == j) //If both indexes match, make the value 0 since a node shouldnt connect to itself
				{
			//		cout << i + 1 << " " << j+1 << " Same Node" << endl;
					Edges[i][j] = 0;
				}
				
				else if(randomNum < EDGE_DENSITY_PERCENT) //If EDGE_DENSITY_PERCENT chance is hit, the verticies have an edge to eachother
				{
					Edges[i][j] = 1;
					Edges[j][i] = 1;
					cout << "Vertex" << i + 1 << " <-> Vertex" << j + 1 << endl; // = " << Edges[i][j] << "\n"; //Specify the connections
	
				}
				
				else //The verticies do not have an edge to eachother
				{
			//		cout << i + 1 << " x " << j+1 << endl;
					Edges[i][j] = 0;
					Edges[j][i] = 0;
				}

			}
			
			/*else
			{
				cout << i + 1 << " " << j+1 << " Already filled" << endl;
			}*/
		}
	}
	cout << "\n" << endl;
}
bool Graph::HasEdge(const int rowIndex, const int colIndex)
{
	if (Edges[rowIndex][colIndex] == 1)
		return true;
	else
		return false;
}
void Graph::ClearIndependentSet()
{
	MaxIndependentSize = 0;
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		Checking[i] = false;
		IndependentNodes[i] = false;
	}
}
void Graph::PrintTheGraph()
{
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		for (int j = 0; j < NODE_ARRAY_SIZE; j++)
		{
			cout << Edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::PrintInfo()
{
	cout << "Amount of verticies: " << NODE_ARRAY_SIZE << endl;
	//	cout << "Amount of edges: " << AmountOfEdges << endl;
	cout << "Edge density percent: " << EDGE_DENSITY_PERCENT << "\%" << endl;
}

void Graph::PrintMaxIndependent()
{
	cout << MaxIndependentSize << " nodes make up the max independent set." << endl;
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		if (IndependentNodes[i])
		{
			cout << i + 1 << " ";
		}
	}
	cout << "are all part of the maximum independent set" << endl;
}
void Graph::FindMaxIndependent()
{
	bool foundEmpty = true;
	int currentIndependentSize = 0;
	while (foundEmpty) // Loops until every possible combination has been checked
	{
		foundEmpty = false;
		for (int i = 0; i < NODE_ARRAY_SIZE; i++) // Updates which nodes will be checked
		{
			if (!Checking[i])
			{
				Checking[i] = true;
				foundEmpty = true;
				break;
			}
			else
				Checking[i] = false;
		}
		for (int i = NODE_ARRAY_SIZE - 1; i >= 0; i--)
		{
			if (Checking[i])
			{
				if (CheckNodesUpTo(i))
				{
					currentIndependentSize = 0;
					for (int j = i; j >= 0; j--)
					{
						if (Checking[j])
						{
							currentIndependentSize++;
						}
					}
					if (currentIndependentSize > MaxIndependentSize)
					{
						for (int j = i; j >= 0; j--)
						{
							IndependentNodes[j] = Checking[j];
						}
						for (int j = NODE_ARRAY_SIZE; j > i; j--)
						{
							IndependentNodes[j] = false;
						}
						MaxIndependentSize = currentIndependentSize;
						break;
					}
				}
			}		
		}
	}
}
bool Graph::CheckNodesUpTo(int endNode)
{
	bool areIndependent = true;
	for (int i = 0; i < endNode; i++)
	{
		if (Checking[i])
		{
			if (HasEdge(i, endNode))
			{
				return false;
			}
		}
	}
	for (int i = endNode - 1; i > 0; i--)
	{
		if (Checking[i])
		{
			areIndependent = CheckNodesUpTo(i);
			break;
		}
	}
	return areIndependent;
}

/*UPDATE: An if-statement was added to the function ApproxMaxIndependent at line 199. Without the statement, the function would include connections that were
 already knocked out and would choose an independent set further from the max indpendent set.*/

void Graph::ApproxMaxIndependent()
{
	// Get the available vertex with the least connections
	int connections = 0;
	int leastConnections = NODE_ARRAY_SIZE;
	int nodeSelection = -1;
	for (int i = 0; i < NODE_ARRAY_SIZE; i++)
	{
		if (!Checking[i]) // If the vertex is still available
		{
			connections = 0;
			for (int j = 0; j < NODE_ARRAY_SIZE; j++)
			{
				if (!Checking[j])
				{
					if (HasEdge(i, j))
						connections++;
				}
			}
			if (connections < leastConnections) // A vertex was found with less connections
			{
				nodeSelection = i;
				leastConnections = connections;
			}
		}
	}

	if (nodeSelection != -1)
	{
		// Save vertex selection in IndependentNodes and increment MaxIndependentSize
		IndependentNodes[nodeSelection] = true;
		MaxIndependentSize++;
		Checking[nodeSelection] = true;

		// Mark the vertex selection's connections as unavailable
		for (int i = 0; i < NODE_ARRAY_SIZE; i++)
		{
			if (HasEdge(nodeSelection, i))
			{
				Checking[i] = true;
			}
		}
		ApproxMaxIndependent();
	}
}

Graph::~Graph()
{	
}

