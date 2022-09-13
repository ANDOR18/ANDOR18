#include <iostream>
#include <string>
#include "Test_1.h"

using namespace std;

int main()
{
	Test_1 study;
	bool flag = true;
	int inp = 0; 
	 
	while(flag == true)
	{
		cout << "Please enter a value: " << flush;
		cin >> inp;
		study.Insert(inp);
		study.Print_list();
		cout << "\nEnter another value? (1/0): " << flush;
		cin >> inp;
		if (inp == 1)
		{
			inp = 0;
			flag = true;
		}
		
		else
		{
			flag = false;
		}
	 } 
	
	return 0;	
}

