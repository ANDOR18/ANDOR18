#include "problem.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int IntInputCheck();
char SignInputCheck();

/// <summary>Loops a menu that allows the user to input two separate mixed numbers and display calculations performed on the fractions</summary>
int main()
{
	int Choice = 0;

	Fraction LeftFraction;
	Fraction RightFraction;

	Problem** ProbPtr = new Problem * [4]{ new AddProblem(), new SubtractProblem(), new MultiplyProblem(), new DivideProblem() };
	char ArithmeticSign[4] = { '+', '-', '*', '/' };
	
	cout << "WELCOME TO THE FRACTION CALCULATOR\n\n" << flush;
	
	while(Choice != 7)
	{
		cout << "	MENU\n\n"
		"	1. Enter Left Fraction\n" << 
		"	2. Enter Right Fraction\n" <<
		"	3. Add\n" <<
		"	4. Subtract\n" <<
		"	5. Multiply\n" <<
		"	6. Divide\n" <<
		"	7. Quit\n\n>> " << flush;
		Choice = IntInputCheck();
		cout << endl;
		
		/// <precondition>Checks if the user selected a calculate function</precondition>
		if (Choice > 2 && Choice < 7)
		{
			/// <precondition>Checks if the user entered fractions not equal to zero</precondition>
			/// <postcondition>Sets the user's choice to set a new left fraction or right fraction</postcondition>
			if (LeftFraction.GetNum() == 0 && LeftFraction.GetWhole() == 0)
			{
				cout << "Please give the Left Fraction a value other than zero before doing any calculations\n\n" << flush;
				Choice = 1;
			}
			else if (RightFraction.GetNum() == 0 && RightFraction.GetWhole() == 0)
			{
				cout << "Please give the Right Fraction a value other than zero before doing any calculations\n\n" << flush;
				Choice = 2;
			}
		}

		if (Choice == 1) // Enter Left Fraction
		{
			cin >> LeftFraction;

			cout << "Left Fraction entered successfully!" << endl;
			system("pause");
		}
		else if (Choice == 2) // Enter Right Fraction
		{
			cin >> RightFraction;

			cout << "Right Fraction entered successfully!" << endl;
			system("pause");
		}
		else if (Choice > 2 && Choice < 7)
		{
			int TempIndex = Choice - 3;
			ProbPtr[TempIndex]->SetLeftFraction(LeftFraction);
			ProbPtr[TempIndex]->SetRightFraction(RightFraction);
			ProbPtr[TempIndex]->Calculate();
			cout << "(" << ProbPtr[TempIndex]->GetLeftFraction() << ") ";
			cout << ArithmeticSign[TempIndex] << " (" << ProbPtr[TempIndex]->GetRightFraction() << ") = ";
			cout << ProbPtr[TempIndex]->GetResult() << "\n" << endl;
			system("pause");
		}
		else if (Choice == 7)
			; // Let the while loop exit
		else
		{
			cout << "Be sure to enter a number between 1 and 7!" << endl;
			system("pause");
		}
		system("cls");
	}
	

	ProbPtr[0] = 0;
	ProbPtr[1] = 0;
	ProbPtr[2] = 0;
	ProbPtr[3] = 0;

	delete[] ProbPtr;
	
	cout << "Quit Was Successful\n" << endl;
	
	system("pause");
	
	return 0;
}

/// <summary>Continues to loop until the user enters an integer then returns the int<\summary>
/// <return>Returns the int, Value</return>
int IntInputCheck()
{
	int Value;
	
	cin >> Value;
	
	while (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Enter a valid number: " << flush;
		cin >> Value;
	}
	
	return Value;
}

/// <summary>Continues to loop until the user enters a character that is either '+' or '-' then returns the char<\summary>
/// <return>Returns the char, Sign</return>
char SignInputCheck()
{
	char Sign;
	
	cin >> Sign;
	
	while (Sign != '+' && Sign != '-')
	{
		cout << "Enter a valid sign (+ or -): " << flush;
		cin >> Sign;
	}
	
	return Sign;
}
