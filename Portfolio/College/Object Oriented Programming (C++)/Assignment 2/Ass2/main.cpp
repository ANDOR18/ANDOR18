#include <iostream>
#include <string>
#include "Problem.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

int main(void) 
{
	Problem p;
	AddProblem ap;
	SubProblem sp;
	MultProblem mp;
	DivProblem dp;
	Fraction f;
	bool flag = false;
	int selection;
	
	cout << "Select an option from the menu" << endl;
	cout << 
	"1. Enter Left Fraction\n" <<
	"2. Enter Right Fraction\n" <<
	"3. Add\n" <<
	"4. Subtract\n" <<
	"5. Multiply\n" <<
	"6. Divide\n" <<
	"7. Quit\n" << flush;
	
	
	while (flag != true)
	{
	cout << ">> " << flush;
	cin >> selection;
	if (selection == 1)
	{
		f.setnum();
		f.display();
		//p.getleft();
	}
	
	if (selection == 2)
	{
		//p.getright();
	}
	
	if (selection == 3)
	{
		//ap.calculate();
		//ap.display();
	}
	
	if (selection == 4)
	{
		//sp.calculate();
		//sp.display();
	}
	
	if (selection == 5)
	{
		//mp.calculate();
		//mp.display();
	}
	
	if (selection == 6)
	{
		//dp.calculate();
		//dp.display();
	}
	
	if (selection == 7)
	{
		cout << "\nGoodbye" << endl;
		flag = true;
	}
	
	else 
	{
		cout << "Please enter a valid selection" << endl;
	}
	
	}
	
	return 0;
}
