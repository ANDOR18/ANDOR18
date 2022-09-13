#include "problem.h"
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;


// Start of Fraction function definitions

/// <summary>Fraction constructor allowing for custom default private member values</summary>
/// <param name="sign">Is the sign to be assigned to the component, Sign</param>
/// <param name="num">Is the numerator to be assigned to the component, Num</param>
/// <param name="den">Is the denominator to be assigned to the component, Den</param>
/// <param name="whole">Is the whole number to be assigned to the component, Whole</param>
Fraction::Fraction(const char sign, const int num, const int den, const int whole)
{
	Num = num;
	Den = den;
	Sign = sign;
	Whole = whole;
}

/// <summary>Fraction constructor used when no custom parameters are present</summary
Fraction::Fraction()
{
	Num = 0;
	Den = 1;
	Sign = '+';
	Whole = 0;
}

void Fraction::SetFraction(const Fraction& F1)
{
	Num = F1.GetNum();
	Den = F1.GetDen();
	Whole = F1.GetWhole();
	Sign = F1.GetSign();
}

/// <summary>Sets Num to an int parameter</summary>
/// <param name="num">Int to be assigned to Num</param>
void Fraction::SetNum(const int num)
{
	Num = num;
}

/// <summary>Sets Den to an int parameter</summary>
/// <param name="den">Int to be assigned to Den</param>
void Fraction::SetDen(const int den)
{
	Den = den;
}

/// <summary>Sets Sign to a char parameter</summary>
/// <param name="sign">Char to be assigned to Sign</param>
void Fraction::SetSign(const char sign)
{
	Sign = sign;
}

/// <summary>Sets Whole to an int parameter</summary>
/// <param name="whole">Int to be assigned to Whole</param>
void Fraction::SetWhole(const int whole)
{
	Whole = whole;
}

/// <summary>Converts a Fraction parameter to a mixed number (if possible) and returns it</summary>
/// <param name="fraction>Gets turned into a mixed number then returned</param>
/// <return>Returns the Fraction, fraction</return>
Fraction Fraction::ConvertToMixed(Fraction fraction)
{
	fraction.SetWhole(fraction.GetNum() / fraction.GetDen());
	fraction.SetNum(fraction.GetNum() % fraction.GetDen());
	
	
	return fraction;
}

/// <summary>Converts a Fraction parameter to an improper fraction (if possible) and returns it</summary>
/// <param name="fraction">Gets turned into an improper fraction then returned</param>
/// <return>Returns the Fraction, fraction</return>
Fraction Fraction::ConvertToImproper(Fraction fraction)
{
	fraction.SetNum(fraction.GetNum() + fraction.GetWhole() * fraction.GetDen());
	fraction.SetWhole(0);
	
	return fraction;
}



/// <summary>Finds the Greatest Common Factor of the numerator and denominator then proceeds to reduce to lowest terms</summary>
/// <param name="fraction">Is reduced to its lowest terms<param>
/// <return>Returns the Fraction, fraction</return>
Fraction Fraction::ReduceFraction(Fraction fraction)
{
	bool StillReducing = true;
	int GCF = fraction.GetDen();
	int Remainder = fraction.GetNum();
	
	if (Remainder != 0)
	{
		while (StillReducing) // (Euclid's Algorithm from https://en.wikipedia.org/wiki/Greatest_common_divisor#Euclid's_algorithm)
		{
			int Temp = Remainder;
			Remainder = GCF % Remainder;
			GCF = Temp;
			if (Remainder == 0)
				StillReducing = false;
		}

		fraction.SetNum(fraction.GetNum() / GCF);
		fraction.SetDen(fraction.GetDen() / GCF);
	}
	
	return fraction;
}

/// <summary>Gets Whole component from Fraction class</summary>
/// <return>Returns the int, Whole</return>
int Fraction::GetWhole() const
{
	return Whole;
}

/// <summary>Gets Num (numerator) component from Fraction class</summary>
/// <return>Returns the int, Num</return>
int Fraction::GetNum() const
{
	return Num;
}

/// <summary>Gets Den (denominator) component from Fraction class</summary>
/// <return>Returns the int, Den</return>
int Fraction::GetDen() const
{
	return Den;
}

/// <summary>Gets Sign component from Fraction class</summary>
/// <return>Returns the char, Sign</return>
char Fraction::GetSign() const
{
	return Sign;
}

// End of Fraction function definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of Problem function definitions

/// <summary>Empty</summary>
Problem::Problem()
{
	
}

Problem::~Problem()
{

}

Problem::Problem(const Fraction& leftFraction, const Fraction& rightFraction)
{
	LeftFraction = leftFraction;
	RightFraction = rightFraction;
}

istream& operator>>(istream& inp, Fraction& f1)
{
	int NumIndexRange[2] = { -1, -1 }; {}; //  setting to -1 later sets the fraction to (0/1)
	int WholeIndexRange[2] = { -1, -1 }; {}; // setting to -1 later sets whole to (0)
	int SignIndex = 0;
	string Temp;
	bool Invalid = true;

	while(Invalid)
	{
		Invalid = false; // stays false until an error is found

		cout << endl << "Please enter a fraction using the following format: sign whole numerator/denominator (Example: +3 4/5)\n" << endl;

		cin.clear();
		cin.ignore();

		getline(inp, Temp);

		cout << "\n" << endl;

		if (Temp[0] != '+' && Temp[0] != '-')
		{
			cout << "Sign Not Found!\n" << endl;
			Invalid = true;
		}
		if (Temp.find('/') == -1) // A fraction doesn't exist
		{
			WholeIndexRange[0] = 1;
			WholeIndexRange[1] = Temp.length() - 1;
		}
		else if (isdigit(Temp[Temp.find('/') + 1]) && isdigit(Temp[Temp.find('/') - 1]))  // A fraction exists
		{
			if (Temp.find(' ') != -1) // A whole number exists
			{
				NumIndexRange[0] = Temp.find(' ') + 1;
				NumIndexRange[1] = Temp.find('/') - 1;
				WholeIndexRange[0] = 1;
				WholeIndexRange[1] = Temp.find(' ') - 1;
				long TempDenIndex = NumIndexRange[1] + 2;
				if (stoi(Temp.substr(TempDenIndex, Temp.length() - 1)) == 0)
				{
					cout << "The denominator cannot be 0\n" << endl;
					Invalid = true;
				}
			}
			else // A whole number does not exists
			{
				cout << "FART" << endl;
				NumIndexRange[0] = 1;
				NumIndexRange[1] = Temp.find('/') - 1;
			}
		}
		else
		{
			cout << "The fraction was not found\n" << Temp << endl;
			Invalid = true;
		}
	}

	f1.Sign = Temp[0];
	if (WholeIndexRange[0] == -1)
		f1.Whole = 0;
	else
		f1.Whole = stoi(Temp.substr(WholeIndexRange[0], WholeIndexRange[1]));
	if (NumIndexRange[0] == -1)
	{
		f1.Num = 0;
		f1.Den = 1;
	}
	else
	{
		long TempDenIndex = NumIndexRange[1] + 2;
		f1.Num = stoi(Temp.substr(NumIndexRange[0], NumIndexRange[1]));
		f1.Den = stoi(Temp.substr(TempDenIndex, Temp.length() - 1));
	}

	return inp;
}

ostream& operator<<(ostream& out, const Fraction& f1)
{
	if (f1.Whole == 0)
	{
		if (f1.Num != 0)
			out << f1.Sign << f1.Num << "/" << f1.Den << flush;
		else
			out << f1.Sign << "0" << flush;
	}
	else if (f1.Num != 0)
		out << f1.Sign << f1.Whole << " " << f1.Num << "/" << f1.Den << flush;
	else
		out << f1.Sign << f1.Whole << flush;

	return out;

}

/// <summary>Sets LeftFraction from Problem class to a Fraction parameter</summary>
/// <param name="fraction">Fraction to be assigned to LeftFraction</param>
void Problem::SetLeftFraction(const Fraction fraction)
{
	LeftFraction = fraction;
}

/// <summary>Sets RightFraction from Problem class to a Fraction parameter</summary>
/// <param name="fraction">Fraction to be assigned to RightFraction</param>
void Problem::SetRightFraction(const Fraction fraction)
{
	RightFraction = fraction;
}

/// <summary>Gets LeftFraction from Problem class</summary>
/// <return>Returns the Fraction, LeftFraction</return>
Fraction Problem::GetLeftFraction() const
{
	return LeftFraction;
}

/// <summary>Gets RightFraction from Problem class</summary>
/// <return>Returns the Fraction, RightFraction</return>
Fraction Problem::GetRightFraction() const
{
	return RightFraction;
}

/// <summary>Gets Result from Problem class</summary>
/// <return>Returns the Fraction, Result</return>
Fraction Problem::GetResult() const
{
	return Result;
}

/// <summary>Sets Result to passed a Fraction</summary>
/// <param name="result">Fraction to be assigned to Result</param>
void Problem::SetResult(const Fraction result)
{
	Result = result;
} 

/// <summary>Sets Problem's Fraction components LeftFrac and RightFrac to have a common denominator while keeping the ratios constant</summary>
void Problem::MatchDenominators()
{
	LeftFraction.SetNum(LeftFraction.GetNum() * RightFraction.GetDen());
	RightFraction.SetNum(RightFraction.GetNum() * LeftFraction.GetDen());
	LeftFraction.SetDen(LeftFraction.GetDen() * RightFraction.GetDen());
	RightFraction.SetDen(LeftFraction.GetDen());
}

// End of Problem function definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of AddProblem function definitions

/// <summary>
AddProblem::AddProblem() {}

AddProblem::~AddProblem()
{

}

/// <summary>Calculates LeftFraction plus RightFraction and stores the sum in Result</summary>
void AddProblem::Calculate()
{
	Fraction OriginalLFraction = GetLeftFraction();
	Fraction OriginalRFraction = GetRightFraction();
	
	SetLeftFraction(GetLeftFraction().ConvertToImproper(GetLeftFraction()));
	SetRightFraction(GetRightFraction().ConvertToImproper(GetRightFraction()));
	
	MatchDenominators();
	
	int Temp1 = GetLeftFraction().GetNum();
	int Temp2 = GetRightFraction().GetNum();
	Fraction TempResult;
	
	if (GetLeftFraction().GetSign() == '-')
	{
		Temp1 *= -1;
	}
	if (GetRightFraction().GetSign() == '-')
	{
		Temp2 *= -1;
	}
	
	TempResult.SetNum(abs(Temp1+Temp2));
	TempResult.SetDen(GetLeftFraction().GetDen());
	
	if (Temp1 + Temp2 < 0)
		TempResult.SetSign('-');
	else
		TempResult.SetSign('+');
		
	TempResult = TempResult.ConvertToMixed(TempResult);
	TempResult = TempResult.ReduceFraction(TempResult);
	
	SetLeftFraction(OriginalLFraction);
	SetRightFraction(OriginalRFraction);
		
	SetResult(TempResult);
}

// End of AddProblem function definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of SubtractProblem function definitions

SubtractProblem::SubtractProblem() {}

SubtractProblem::~SubtractProblem()
{

}

/// <summary>Calculates LeftFraction minus RightFraction and stores the difference in Result</summary>
void SubtractProblem::Calculate()
{
	Fraction OriginalLFraction = GetLeftFraction();
	Fraction OriginalRFraction = GetRightFraction();
	
	SetLeftFraction(GetLeftFraction().ConvertToImproper(GetLeftFraction()));
	SetRightFraction(GetRightFraction().ConvertToImproper(GetRightFraction()));
	
	MatchDenominators();
	
	int Temp1 = GetLeftFraction().GetNum();
	int Temp2 = GetRightFraction().GetNum();
	Fraction TempResult;
	
	if (GetLeftFraction().GetSign() == '-')
	{
		Temp1 *= -1;
	}
	if (GetRightFraction().GetSign() == '-')
	{
		Temp2 *= -1;
	}
	
	TempResult.SetNum(abs(Temp1-Temp2));
	TempResult.SetDen(GetLeftFraction().GetDen());
	
	if (Temp1 - Temp2 < 0)
		TempResult.SetSign('-');
	else
		TempResult.SetSign('+');
		
	TempResult = TempResult.ConvertToMixed(TempResult);
	TempResult = TempResult.ReduceFraction(TempResult);
	
	SetLeftFraction(OriginalLFraction);
	SetRightFraction(OriginalRFraction);
		
	SetResult(TempResult);
}

// End of SubtractProblem function definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of MultiplyProblem function definitions

MultiplyProblem::MultiplyProblem() {}

MultiplyProblem::~MultiplyProblem()
{

}

/// <summary>Calculates FirstFraction times SecondFraction and stores the product in Result</summary>
void MultiplyProblem::Calculate()
{
	Fraction TempLeftFraction = GetLeftFraction();
	Fraction TempRightFraction = GetRightFraction();
	Fraction TempResult;
	
	TempLeftFraction = TempLeftFraction.ConvertToImproper(TempLeftFraction);
	TempRightFraction = TempRightFraction.ConvertToImproper(TempRightFraction);
	
	TempResult.SetNum(TempLeftFraction.GetNum() * TempRightFraction.GetNum());
	TempResult.SetDen(TempLeftFraction.GetDen() * TempRightFraction.GetDen());
	
	if (TempLeftFraction.GetSign() == TempRightFraction.GetSign())
		TempResult.SetSign('+');
	else
		TempResult.SetSign('-');
		
	TempResult = TempResult.ConvertToMixed(TempResult);
	TempResult = TempResult.ReduceFraction(TempResult);
		
	SetResult(TempResult);
}

// End of MultiplyProblem function definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of DivideProblem function definitions

DivideProblem::DivideProblem() {}

DivideProblem::~DivideProblem()
{

}

/// <summary>Calculates FirstFraction divided by SecondFraction and stores the quotient in Result</summary>
void DivideProblem::Calculate()
{
	Fraction TempLeftFraction = GetLeftFraction();
	Fraction TempRightFraction = GetRightFraction();
	Fraction TempResult;
	
	TempLeftFraction = TempLeftFraction.ConvertToImproper(TempLeftFraction);
	TempRightFraction = TempRightFraction.ConvertToImproper(TempRightFraction);
	
	TempResult.SetNum(TempLeftFraction.GetNum() * TempRightFraction.GetDen());
	TempResult.SetDen(TempLeftFraction.GetDen() * TempRightFraction.GetNum());
	
	if (TempLeftFraction.GetSign() == TempRightFraction.GetSign())
		TempResult.SetSign('+');
	else 
		TempResult.SetSign('-');
	
	TempResult = TempResult.ConvertToMixed(TempResult);
	TempResult = TempResult.ReduceFraction(TempResult);
	
	SetResult(TempResult);
}

// End of DivideProblem function definitions

