#include <iostream>
#include <string>
#include "Problem.h"

using namespace std;

//Fraction Functions
Fraction::Fraction()
{
	sign = '+';
  	whole = 0;
  	num = 0;
  	den = 1;
}

void Fraction::setnum(void)
{
	cout << "Enter the numerator:" << endl;
	cin >> num;
	
}

/*Fraction::setden()
{
}

Fraction::setwhole()
{
}

Fraction::setsign()
{
}

Fraction::getnum()
{
}

Fraction::getden()
{
}

Fraction::getwhole()
{
}

Fraction::getsign()
{
}

void Fraction::display(void) const;
{
	cout << num;
}

Fraction::reduce()
{
}



//Problem Functions
Problem::Problem()
{
	Fraction f1;
	Fraction f2;
	lefttop = 0;
	righttop = 0;
	answer = 0;
}

Problem::setleft()
{
}

Problem::setright()
{
}

Problem::getleft()
{
}

Problem::getright()
{
}

Problem::display()
{
}

Problem::calculate()
{
}


//Add Problem
AddProblem::calculate()
{
}

AddProblem::display()
{
}


//Sub Problem
SubProblem::calculate()
{
}

SubProblem::display()
{
}


//Mult Problem
MultProblem::calculate()
{
}

MultProblem::display()
{
}


//Div Probem
DivProblem::calculate()
{
}

DivProblem::display()
{
}*/
