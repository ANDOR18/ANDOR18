#include "bag.h"

Bag::Bag()
{
	//makes a new node
	Head = new Node();
	//points to node in front of the head node
	Head->Next = NULL;
	srand(time(NULL));
	NodeCount = 0;
}
void Bag::Insert(const int value)
{
	//makes a new node which is saved under temp
	Node* temp = new Node();
	// inserts value for the new node
	temp->Value = value;
	//makes temp equal to the node after head
	temp->Next = Head->Next;
	//temp mode is now the head
	Head->Next = temp;
	//adds to the number of nodes
	NodeCount++;
}
void Bag::Remove()
{
	//variables we'll use to remove node
	Node* temp1 = Head;
	Node* temp2 = NULL;
	//random number generator selects node
	int ranNum = rand() % NodeCount;
	for (int i = 0; i < ranNum; i++)
	{
		temp1 = temp1->Next;
	}
	//makes the head node null
	temp2 = temp1;
	//declareing the new head
	temp1 = temp1->Next;
	cout << "Removing a node with a " << temp1->Value << " in it" << endl;
	//links the conection between  
	temp2->Next = temp1->Next;
	//removes node
	delete temp1;
	//subtracts from the number of nodes
	NodeCount--;
}
ostream& operator<<(ostream& out, const Bag& bag)
{
	const int itemsPerLine = 5;
	//begins a counter
	int counter = 0;
	//creates a node temp for the item after head
	Node* temp = bag.Head->Next;
	//begins the while loop for counter
	while (temp != NULL)
	{
		out << "	" << temp->Value;
		//node count up 1
		counter++;
		//data check
		if (counter >= itemsPerLine)
		{
			//makes the counter 0 if count is higher then itemsperline
			counter = 0;
			out << endl;
		}
		//moves to next node
		temp = temp->Next;
	}
	out << "\n" << endl;
	return out;
}
Bag::~Bag()
{
	//deletes head
	delete Head;
}
