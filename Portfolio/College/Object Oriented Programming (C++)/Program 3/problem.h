/*
CLASSES PROVIDED: Fraction, Problem, AddProblem, SubtractProblem, MultiplyProblem, DivideProblem

Fraction::Fraction()
    Description:	Initializes objects under fraction	
    Precondition:	none
    Postcondition:	Initializes variables under private
    
friend istream& operator>>(istream&, Fraction&)
    Description:	Overloads the >> operator to parse the string entered as a fraction 
    Precondition:	Numbers need to be set in the order of "Sign Whole Numberator/Denominator
    Postcondition:	The data entered as a fraction can now be utilized by other functions
    
friend ostream& operator<<(ostream&, const Fraction&)
	Description:	Overloads the << operator to display values in fraction form 
    Precondition:	none
    Postcondition:	The data is displayed as a fraction
    
void SetFraction(const Fraction&)
	Description:	Sets the fraction


    


void setwhole(const int value)
    Description:	
    Precondition:
    Postcondition:

*/
#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>

using namespace std;

class Fraction
{
	public:
		Fraction(const char, const int, const int, const int);
		Fraction();
		friend istream& operator>>(istream&, Fraction&);
		friend ostream& operator<<(ostream&, const Fraction&);
		void SetFraction(const Fraction&);
		void SetNum(const int);
		void SetDen(const int);
		void SetSign(const char);
		void SetWhole(const int);
		Fraction ConvertToMixed(Fraction);
		Fraction ConvertToImproper(Fraction);
		string ParseFraction();
		Fraction ReduceFraction(Fraction);
		int GetWhole() const;
		int GetNum() const;
		int GetDen() const;
		char GetSign() const;
		
	private:
		int Whole;
		int Num;
		int Den;
		char Sign;
};

class Problem 
{
	public:
		Problem();
		Problem(const Fraction&, const Fraction&);
		void SetLeftFraction(const Fraction);
		void SetRightFraction(const Fraction);
		Fraction GetLeftFraction() const;
		Fraction GetRightFraction() const;
		Fraction GetResult() const;
		void SetResult(const Fraction);
		void MatchDenominators();
		virtual void Calculate() = 0;
		virtual ~Problem();
		
	private:
		Fraction LeftFraction;
		Fraction RightFraction;
		Fraction Result;
};

class AddProblem : virtual public Problem
{
	public:
		AddProblem();
		void Calculate();
		~AddProblem();
};

class SubtractProblem : virtual public Problem
{
	public:
		SubtractProblem();
		void Calculate();
		~SubtractProblem();
};

class MultiplyProblem : virtual public Problem
{
	public:
		MultiplyProblem();
		void Calculate();
		~MultiplyProblem();
};

class DivideProblem : virtual public Problem
{
	public:
		DivideProblem();
		void Calculate();
		~DivideProblem();
};

#endif
