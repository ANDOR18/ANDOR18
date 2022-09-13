#ifndef TEST_1_H
#define TEST_1_H

struct Node
{
	Node() {Value=0;}
	int Value;
	Node* Next;
};

class Test_1
{
	public:
		Test_1();
		
		void Insert(const int);
		
//		void Remove();
		
		void Print_list();
		
		~Test_1();
		
	private:
		Node* Head;
		int Nodecount = 0;
	
};

#endif
