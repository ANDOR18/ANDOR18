#include <iostream>
#include <string>
#include "Test_1.h"

using namespace std;
Test_1::Test_1()
{
	Head = new Node();	
	Head->Next = NULL;
}

void Test_1::Insert(const int input)
{
	Node* temp =  new Node();
	temp->Value = input;
	temp->Next = Head->Next;
	Head->Next = temp;
}

void Test_1::Print_list()
{
	Node* temp = Head->Next;
	
	while (temp != NULL)
	{
		cout << " "<< temp->Value;
		temp = temp->Next;
	}

} 

Test_1::~Test_1()
{
	delete Head;
}



