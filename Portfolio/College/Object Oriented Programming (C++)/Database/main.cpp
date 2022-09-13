#include "db.h"

int main()
{
	const int LEFTAGELIMIT = 18;
	const int RIGHTAGELIMIT = 120;
	const int NAMELENGTHLIMIT = 25;
	
	int choice = 0;
	bool quit = false;
	string fileName;
	Database nameData;
	int idLimit = nameData.GetIDLimit();
	int theAge = 0;
	int theID = -1;
	string theName = "";
	
	while (!quit)
	{
		cout << "Menu\n1. Load records from file\n2. Add record\n3. Remove record\n4. Search for record\n"
		<< "5. Display all record slots\n6. Dump records to a file\n7. Quit\n\n>> ";
		cin >> choice;
		cout << endl;
		switch(choice)
		{
			case 1: // Load records from file
				cout << "Please enter the file name: " << flush;
				cin >> fileName;
				nameData.LoadFileData(fileName);
				break;
			case 2: // Add record
				cout << "Please enter an ID number: " << flush;
				cin >> theID;
				cout << "Please enter the name: " << flush;
				cin >> theName;
				cout << "Please enter the age: " << flush;
				cin >> theAge;
				cout << endl;
				nameData.AddRecord(theName, theAge, theID);
				break;
			case 3: // Remove record
				cout << "Please enter an ID number: " << flush;
				cin >> theID;
				nameData.DeleteRecord(theID);
				cout << endl;
				break;
			case 4: // Search for record
				
				break;
			case 5: // Display all record slots
				nameData.Display();
				break;
			case 6: // Dump records to a file
				cout << "Please enter the file name: " << flush;
				cin >> fileName;
				nameData.DumpToFile(fileName);
				break;
			case 7: // Quit
				quit = true;
				cout << "Quitting" << endl;
				break;
			default: // Invalid menu choice
				cout << "An invalid number was entered please enter a value that corresponds to the menu choices" << endl;
				break;
		}
		system("PAUSE");
		//system("CLS");
		cout << endl;
	}
	return 0;
}

