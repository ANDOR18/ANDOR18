#ifndef BAG_H
#define BAG_H

#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

struct Node
{
	// Default Node constructor
	Node() { Value = 0;  }
	int Value;
	Node* Next;
};

class Bag
{
	public:
		// Default Constructor
		Bag();
		// Inserts a value into the Node right after the data member, Head
		void Insert(const int);
		// Removes a random item from the bag
		void Remove();
		// Overloads the output operator for outputting the the entire bag except for the Head Node
		friend ostream& operator<<(ostream&, const Bag&);
		// Default Destructor
		~Bag();
	private:
		Node* Head;
		int NodeCount;
};

#endif
