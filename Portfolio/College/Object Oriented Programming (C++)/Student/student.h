#include <string>

#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

class Student
{
	public:
		Student(void);
		void CreateStudent(const int); // Adds a new student's name, gpa, and id (defined by the user) to arrays
		void DeleteStudent(const int); // Deletes student data based on id and moves subsequent student data to take the place of deleted data
		void DisplayStudents(const int); // Prints out a list of every students data
		void StudentSearch(const int); // Prints out the data of a student that matches the user entered id
		
	private:
		string firstName[30];
		string lastName[30];
		int id[30];
		float gpa[30];
};

#endif
