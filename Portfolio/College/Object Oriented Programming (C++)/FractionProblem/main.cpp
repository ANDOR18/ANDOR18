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
	
	AddProblem A1;
	SubtractProblem S1;
	MultiplyProblem M1;
	DivideProblem D1;
	
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
		
		int TempNum, TempDen, TempWhole;
		char TempSign;
		
		switch (Choice) // Brings the user to the appropriate menu based on the number entered
		{			
			case 1: // Enter Left Fraction
				cout << "Enter the sign of the fraction (+ or -): " << flush;
				TempSign = SignInputCheck();
				cout << "\nEnter the numerator of the fraction: " << flush;
				TempNum = IntInputCheck();
				cout << "\nEnter the denominator of the fraction: " << flush;
				TempDen = IntInputCheck();
				while (TempDen == 0)
				{
					cout << "Remember the denominator cannot be zero!\n\nEnter the denominator of the fraction: " << flush;
					TempDen = IntInputCheck();
				}
				cout << "\nEnter the whole number: " << flush;
				TempWhole = IntInputCheck();
				cout << endl;
				LeftFraction = Fraction(TempSign, TempNum, TempDen, TempWhole);
				cout << "Left Fraction entered successfully!" << endl;
				system("pause");
				break;
			case 2: // Enter Right Fraction
				cout << "Enter the sign of the fraction (+ or -): " << flush;
				TempSign = SignInputCheck();
				cout << "\nEnter the numerator of the fraction: " << flush;
				TempNum = IntInputCheck();
				cout << "\nEnter the denominator of the fraction: " << flush;
				TempDen = IntInputCheck();
				cout << "\nEnter the whole number: " << flush;
				TempWhole = IntInputCheck();
				cout << endl;
				RightFraction = Fraction(TempSign, TempNum, TempDen, TempWhole);
				cout << "Left Fraction entered successfully!" << endl;
				system("pause");
				break;
			case 3: // Add
				A1.SetLeftFraction(LeftFraction);
				A1.SetRightFraction(RightFraction);
				A1.Calculate();
				A1.Display();
				system("pause");
				break;
			case 4: // Subtract
				S1.SetLeftFraction(LeftFraction);
				S1.SetRightFraction(RightFraction);
				S1.Calculate();
				S1.Display();
				system("pause");
				break;
			case 5: // Multiply
				M1.SetLeftFraction(LeftFraction);
				M1.SetRightFraction(RightFraction);
				M1.Calculate();
				M1.Display();
				system("pause");
				break;
			case 6: // Divide
				D1.SetLeftFraction(LeftFraction);
				D1.SetRightFraction(RightFraction);
				D1.Calculate();
				D1.Display();
				system("pause");
				break;
			case 7: // Quit
				break;
			default: // Other
				cout << "Be sure to enter a number between 1 and 7!" << endl;
				system("pause");
				break;
		}
		system("cls");
	}
	
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
