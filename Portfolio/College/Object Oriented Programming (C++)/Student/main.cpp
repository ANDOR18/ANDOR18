#include <iostream>
#include "student.h"

int main() // Handles the menu
{
	int numOfStudents = 0; // The number of student data loaded into arrays which also corresponds to the first empty entry in each student data array
	
	Student theStudents; // An instance of the student class
	
	bool quit = false; // When set to true the menu loop ends
	
	while (!quit) // Loops the user menu until the user enters 5
	{
		bool validData = false;
		int choice;
		
		cout << "Pick an option from the menu:\n" 
		<< "1. Create Student\n" 
		<< "2. Delete Student\n" 
		<< "3. Display Students\n" 
		<< "4. Search Student by ID\n" 
		<< "5. Quit\n" << flush;
		
		cout << "\n" << ">> " << flush;
		
		while (!validData) // If an invalid data type is entered for the menu index then it loops
		{
			cin >> choice;
			if (cin.fail() || choice < 1 || choice > 5)
			{
				cin.clear();
				cin.ignore(999, '\n');
				cout << "\nIncorrect data type entered!\n\nEnter a valid student menu index ranging from 1 to 5: " << flush;
			}
			else
				validData = true;
		}
		cout << "\n\n" << flush;		
		
		if (choice == 1)
		{
			theStudents.CreateStudent(numOfStudents);
			numOfStudents++;
		}
		else if (choice == 2)
		{
			theStudents.DeleteStudent(numOfStudents);
			numOfStudents--;
		}
		else if (choice == 3)
		{
			theStudents.DisplayStudents(numOfStudents);
		}
		else if (choice == 4)
		{
			theStudents.StudentSearch(numOfStudents);
		}
		else if (choice == 5)
		{
			quit = true;
		}
	} // End of while loop
	return 0;
}
