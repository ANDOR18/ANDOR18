#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>

using namespace std;

class Fraction
{
	public:
		Fraction(const char, const int, const int, const int);
		Fraction();
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
		void SetLeftFraction(const Fraction);
		void SetRightFraction(const Fraction);
		Fraction GetLeftFraction() const;
		Fraction GetRightFraction() const;
		Fraction GetResult() const;
		void SetResult(const Fraction);
		void MatchDenominators();
		void Calculate() const;
		void Display();
		
	private:
		Fraction LeftFraction;
		Fraction RightFraction;
		Fraction Result;
};

class AddProblem : public Problem
{
	public:
		void Calculate();
		void Display();
};

class SubtractProblem : public Problem
{
	public:
		void Calculate();
		void Display();
};

class MultiplyProblem : public Problem
{
	public:
		void Calculate();
		void Display();
};

class DivideProblem : public Problem
{
	public:
		void Calculate();
		void Display();
};

#endif
