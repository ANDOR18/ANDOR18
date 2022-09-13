#ifndef DB_H
#define DB_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Record
{
	int ID;
	string Name;
	int Age;
	Record() {
		ID = -1;
		Name = "";
		Age = 0;
	}
};

class Database
{
	const static int IDLIMIT = 9999;
	const static int RECORDNUM = 19;
	Record Records[RECORDNUM];
	public:
		// Default constructor
		Database();
		// Loads in records from a file
		// Forgos loading a record if it already exists or has invalid data and prints an error message
		// Returns -1 if there was an error reading from a file
		int LoadFileData(string);
		// Dumps all the records into a file with a name matching theName
		// Returns -1 if there are no records to dump
		int DumpToFile(string);
		// Uses linear probing to find a record with the ID that matches theID
		// Prints the record data if it a match was found
		// Returns -1 if no record was found
		int SearchRecord(int);
		// Deletes a record whose ID matches theID
		// Returns -1 if theID doesn't match any of the records
		int DeleteRecord(int);
		// Places a new record with Name set to theName, and Age set to theAge into an address generated using theID
		int AddRecord(string, int, int);
		// Calculates the index of theID and returns the index
		int Hash(int);
		// Displays each entry of the data
		void Display();
		// Returns IDLIMIT
		int GetIDLimit();
		// Default destructor
		~Database();
		
	private:
		string textData;
};


#endif
