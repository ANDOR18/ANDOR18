#include "db.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
Database::Database()
{}

int Database::LoadFileData(string fileName)
{
	int i = 0;
	int slot = 0;
	int ID = 0;
	string Name;
	int Age = 0;
	ifstream file_in;
	file_in.open(fileName.c_str(), ios::in);
  	if (file_in.is_open())
  	{
    	while (getline(file_in, textData))
    	{
//			cout << "i = " << i << endl;
//			cout << "Current line: " << textData << endl;
			if(i == 0)
			{
//				cout << "Title hit " << slot << endl;
				i++;
			}

			
      		else if(i == 1)
			{
				if(!textData.compare("Empty"))
				{
					Name = "";
					ID = -1;
					Age = 0;
					i = 4;
//					cout << "Empty hit " << slot << endl;
				}
				else
				{
					ID = atoi(textData.c_str());
					i++;
//					cout << "ID hit " << slot << endl;
				}
			}
				
			else if(i == 2)
			{
				Name = textData;
				i++;
//				cout << "Name hit " << slot << endl;
			}
				
      		else if(i == 3)
      		{
				Age = atoi(textData.c_str());
      			i++;
 //     			cout << "Age hit " << slot << endl;
			}
			
			else if(i==4)
			{
				AddRecord(Name, Age, ID);
				i = 0;
//				cout << "Recorded hit " << slot << endl;
				slot++;
			}

					
		}
			
		file_in.close();
    }
   	 		
  else 
  	cout << "Unable to open " << fileName << endl;
	return 0;
}

int Database::DumpToFile(string fileName)
{
	int i = 0;
	int ID = 0;
	string Name;
	int Age = 0;
	ofstream file_out;
	file_out.open(fileName.c_str(), ios::out);
  	if (file_out.is_open())
  	{
		for(int i = 0; i < 19; i++)
		{
			file_out << "Slot " << i << ":" << endl;
			if(Records[i].ID != -1&&Records[i].Name.compare("")&&Records[i].Age != 0)
			{	file_out << Records[i].ID << endl;
				file_out << Records[i].Name << endl;
				file_out << Records[i].Age << endl;

			}
			else
				file_out << "Empty" << endl;
				file_out << endl;
		}
			
		file_out.close();
    }
   	 		
  else 
  	cout << "Unable to open " << fileName << endl;
	return 0;
}
int Database::SearchRecord(int theID)
{
	int index = Hash(theID);
	if (Records[index].ID > -1)
	{
		cout << "ID: " << Records[index].ID << "\nName: " << Records[index].Name << "\nAge: " << Records[index].Age << endl;
		return 0;
	}
	return -1;
}
int Database::DeleteRecord(int theID)
{
	int index = Hash(theID);
	if (Records[index].ID > -1 && Records[index].ID == theID)
	{
		Records[index].Name = "";
		Records[index].Age = 0;
		Records[index].ID = -2;
		return 0;
	}
	return -1;
}
int Database::AddRecord(string theName, int theAge, int theID)
{
	int index = 0, startIndex = 0;
	bool findingOpen = true;
	startIndex = Hash(theID);
	index = startIndex;
	
	while (findingOpen)
	{
		if (Records[index].ID == -1)
		{
			findingOpen = false;
			Records[index].ID = theID;
			Records[index].Name = theName;
			Records[index].Age = theAge;
			findingOpen = false;
			index = 0; // Return value
		}
		else
		{
			if (theID < IDLIMIT)
				theID++;
			else
				theID = 0;
			index = Hash(theID);
			if (index == startIndex)
			{
				findingOpen = false;
				index = -1; // Return value (No open slots found)
			}
		}
	}
	return index; // Reused as a return value
}
int Database::Hash(int theID)
{
	int address = theID % RECORDNUM;
	return address;
}
void Database::Display()
{
	cout << left << setw(10) << "Index" << setw(10) << "ID" << setw(10) << "Age" << setw(10) << "Name\n" << endl;
	for (int i = 0; i < RECORDNUM; i++)
	{
		cout << setw(10) << i << setw(10) << Records[i].ID << setw(10) << Records[i].Age << Records[i].Name << endl;
	}
	cout << endl;
}
int Database::GetIDLimit()
{
	return IDLIMIT;
}
Database::~Database()
{
	
}
