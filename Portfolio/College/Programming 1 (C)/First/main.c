#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	double Area, pi, Radius;
	double Side;
	double Base, Height;
	
	pi = 3.14159;
	Radius = 10;
	
	Side = 6.5;
	
	Base = 8;
	Height = 10;
	
	
	Area = pi * (Radius * Radius);
	printf("The area of the circle is %lf\n", Area);
	
	
	Area = Side * Side;
	printf("The area of the square is %lf\n", Area);
	
	
	Area = (Base * Height)/2;
	printf("The area of the right triangle is %lf", Area);

	
	 
	return 0;
}
