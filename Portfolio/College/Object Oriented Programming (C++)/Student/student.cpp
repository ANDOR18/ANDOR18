#include <iostream>
#include <iomanip>
#include "student.h"

Student::Student()
{
	
}

void Student::CreateStudent(const int numOfStudents) // Adds a new student's name, gpa, and id (defined by the user) to arrays
{
	if (numOfStudents >= 30)
	{
		cout << "There are no students to display!\n\n" << flush;
		return;
	}
	
	bool validData = false;
	
	cout << "\nEnter the first name: " << flush;
	cin >> firstName[numOfStudents];
	cout << "Enter the last name: " << flush;
	cin >> lastName[numOfStudents];
	cout << "Enter the ID: " << flush;
	
	while (!validData) // If an invalid data type is entered for id then it loops
	{
		cin >> id[numOfStudents];
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "\nIncorrect data type entered!\n\nEnter a valid student ID: " << flush;
		}
		else
			validData = true;
	}
	cout << "Enter the student's GPA: " << flush;
	
	validData = false; // Sets the bool validData back to false for reuse in the same function
	
	while (!validData) // If an invalid data type is entered for gpa then it loops
	{
		cin >> gpa[numOfStudents];
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "\nIncorrect data type entered!\n\nEnter a valid student GPA: " << flush;
		}
		else
			validData = true;
	}
	cout << "\n";
	cout << "The data has been entered successfully!\n\n" << flush;
}
void Student::DeleteStudent(const int numOfStudents) // Deletes student data based on id and moves subsequent student data to take the place of deleted data
{
	if (numOfStudents == 0)
	{
		cout << "There are no students to delete!\n\n" << flush;
		return;
	}
	
	int _id;
	bool deleted;
	bool validData = false;
	
	cout << "\nWhat ID you would like to remove? " << flush;
	
	while (!validData) // If an invalid data type is entered for id then it loops
	{
		cin >> _id;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "\nIncorrect data type entered!\n\nEnter a valid student ID: " << flush;
		}
		else
			validData = true;
	}
	
	for (int i = 0; i < numOfStudents; i++)
	{
		if (id[i] == _id)
		{
			id[i] = 0;
			gpa[i] = 0;
			firstName[i] = "";
			lastName[i] = "";
			deleted = true;
			cout << "The data has been removed successfully!\n\n" << flush;
		}
		else if (deleted)
		{
			id[i - 1] = id[i];
			gpa[i - 1] = gpa[i];
			firstName[i - 1] = firstName[i];
			lastName[i - 1] = lastName[i];
		}
	}
}
void Student::DisplayStudents(const int numOfStudents) // Prints out a list of every students data
{
	//"Full Name:" is set to a variable in order to calculate the spacing between the last name and gpa
	string fullname = "Full Name:";
	
	if (numOfStudents == 0)
	{
		cout << "There are no students to display!\n\n" << flush;
		return;
	}
	
	cout << "ID:" << setw(20) << fullname << setw(16) << "GPA:\n\n";
	for (int i = 0; i < numOfStudents; i++)
	{
		int nwidth = firstName[i].size() + 5;
		int gwidth = 13 - ((firstName[i].size() + lastName[i].size() + 1)-fullname.size());
		
		
		cout << id[i] << setw(nwidth) << firstName[i] << " " << lastName[i] << setw(gwidth) << gpa[i] << "\n";
	}
	cout << "\n\n" << flush;
}
void Student::StudentSearch(const int numOfStudents) // Prints out the data of a student that matches the user entered id
{
	if (numOfStudents == 0)
	{
		cout << "There are no students to display!\n\n" << flush;
		return;
	}
	
	int _id;
	bool validData = false;
	cout << "\nEnter the student's ID: " << flush;
	
	while (!validData) // If an invalid data type is entered for id then it loops
	{
		cin >> _id;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(999, '\n');
			cout << "\nIncorrect data type entered!\n\nEnter a valid student ID: " << flush;
		}
		else
			validData = true;
	}	
	
	for (int i = 0; i < numOfStudents; i++)
	{
		if (id[i] == _id)
		{
			cout << "\nID: " << id[i];
			cout << "\nFull Name: " << firstName[i] << " " << lastName[i];
			cout << "\nGPA: " << gpa[i] << "\n\n";
			
			return;
		}
	}
	cout << "\nThe ID you entered did not match any saved student IDs\n\n";
}
