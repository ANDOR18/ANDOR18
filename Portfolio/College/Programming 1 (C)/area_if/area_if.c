#include <iostream>
#include <string>
using namespace std;
int main()
{
double radius,side,base,height,area;
const double PI = 3.14159;
string selection;

cout<<"What do you want to calculate:"<<endl;
cout<<"C for circle"<<endl;
cout<<"S for square"<<endl;
cout<<"T for Right triangle"<<endl;
cout<<"Please enter your selection: ";
cin>>selection;

if(selection=="C")
   {
//Circle calculation
cout<<endl<<endl<<"Circle Area"<<endl;
cout<<"Enter the radius ";
cin>>radius;
area=PI*radius*radius;
cout<<"The area of the circle = "<<area<<endl;
system("pause");
   }
else
	if(selection=="S")
	    {
	//Square calculation
	cout<<endl<<endl<<"Square Area"<<endl;
	cout<<"Enter the side ";
	cin>>side;
	area = side*side;
	cout<<"The area of the square = "<<area<<endl;
	system("pause");
	    }
	else
		    {
		//Right Triangle calculation
		cout<<endl<<endl<<"Right Triangle Area"<<endl;
		cout<<"Enter the base ";
		cin>>base;
		cout<<"Enter the height ";
		cin>>height;
		area=0.5*base*height;
		cout<<"The area of the right triangle = "<<area<<endl;
		system("pause");
		   }
return 0;
}
