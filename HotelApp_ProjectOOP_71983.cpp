// HotelApp_ProjectOOP_71983.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string> 
#include "Room.h"
#include "Hotel.h"
#include "StreamCommandsExt.h"

using namespace std;

int DateToInt(const char * date)
{
	char * newDate = new char [strlen(date) - 2 + 1];
	size_t c = 0;
	for (size_t i = 0; date[i]; i++)
	{
		if (date[i] != '-')
		{
			newDate[c] = date[i];
			c++;
		}
		else
		{
			continue;
		}
	}
	newDate[strlen(date) - 2] = 0;
	return stoi(newDate);
}
bool CheckDate(const char* date) //--------------func to check if a given date is valid
{
	int convertedDate= DateToInt(date);
	int monthsDate = (convertedDate % 10000) / 100;
	int daysDate = convertedDate % 100;

	if (monthsDate > 12 || monthsDate <= 0)
	{
		return 0;
	}
	else if (daysDate > 31 || daysDate <= 0)
	{
		return 0;
	}
	else if (date[0] > '2' || date[1] > '0' || date[2] > '2')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

char currentFile[64];


int main()
{

	//----------------------------variable declarations

	// uncomment if u want to create hotel with custom number of rooms and in the check in section change the validation to < nrRooms

	/*int nrRooms;
	cout << "Enter number of rooms: "; 
	cin >> nrRooms;
	Hotel* hotel = new Hotel(nrRooms);*/ 

	StreamCommandsExt scext;
    Hotel*  hotel = new Hotel();// 16 rooms
	ifstream myFile;
	char date[30];
	char date2[30];
	bool Using = 1;
	int roomNumber;
	bool isOpened = false;

	std::cout << "\tHello to our hotel system :D" << endl;
	//----------------------------------system dialog
	do
	{
		char command[20];
		cout << "How can I help you now?" << endl;
		cin.getline(command, 30);

		if (strcmp(command, "CheckIn") == 0 || strcmp(command, "check in") == 0 || strcmp(command, "Check in") == 0)
		{
			char name[30];
			char answer;
			cout << "Enter family name, please: " << endl;
			cin.getline(name, 30);
			cout << "Enter date from: ";
			cin.getline(date, 30);
			cout << "Enter end date: ";
			cin.getline(date2, 30);
			cout << "Select a room:" << endl;

			hotel->Report(DateToInt(date), DateToInt(date2));

			cout << "Enter room number: " << endl;
			cin >> roomNumber;
			cout << "Do you want to tell us the number of guests? y(yes) or n(no)" << endl;
			cin >> answer;
			if (answer == 'y')
			{
				int nrGuests;
				cout << "Enter number of guests: ";
				cin >> nrGuests;

				if (roomNumber >= 100 && roomNumber <= 115)
				{
					if (DateToInt(date) <= DateToInt(date2) && CheckDate(date) && CheckDate(date2))
					{
						cout << "Checking in..." << endl;
						hotel->CheckIn(roomNumber, DateToInt(date), DateToInt(date2), name, nrGuests);
						cout << "You have successfully checked in room " << roomNumber << endl;
					}
					else
					{
						cout << "Wrong date(s)" << endl;
					}
				}
				else
				{
					cout << "Wrong room number. Please try again!";
				}
			}
			else
			{
				if (roomNumber >= 100 && roomNumber <= 115)
				{
					if (DateToInt(date) <= DateToInt(date2) && CheckDate(date) && CheckDate(date2))
					{
						cout << "Checking in..." << endl;
						hotel->CheckIn(roomNumber, DateToInt(date), DateToInt(date2), name);
						cout << "You have successfully checked in room " << roomNumber << endl;
					}
					else
					{
						cout << "Wrong date(s)" << endl;
					}
				}
				else
				{
					cout << "Wrong room number. Please try again!";
				}
			}
		}
		else if (strcmp(command, "Report") == 0 || strcmp(command, "report") == 0)
		{
			cout << "Enter date from: ";
			cin.getline(date, 30);
			cout << "Enter end date: ";
			cin.getline(date2, 30);

			if (CheckDate(date) && CheckDate(date2))
			{
				cout << "Extracting report..." << endl;
				hotel->Report(DateToInt(date), DateToInt(date2));
			}
			else
			{
				cout << "Wrong date" << endl;
			}
		}
		else if (strcmp(command, "FindRoom") == 0 || strcmp(command, "Find room") == 0 || strcmp(command, "find room") == 0)
		{
			int nrBeds;

			cout << "Enter number of beds" << endl;
			cin >> nrBeds;
			cout << "Enter date from: ";
			cin.ignore();
			cin.getline(date, 30);
			cout << "Enter end date: ";
			cin.ignore();
			cin.getline(date2, 30);

			if (CheckDate(date) && CheckDate(date2))
			{
				if (nrBeds > 3)
				{
					cout << "Too many beds!";
				}
				else
				{
					cout << "Finding your room..." << endl;
					hotel->FindRoom(nrBeds, DateToInt(date), DateToInt(date2));
					cout << "and is perfect for you!" << endl;
				}
			}
			else
			{
				cout << "Invalid date(s)" << endl;
			}
		}
		else if (strcmp(command, "Checkout") == 0 || strcmp(command, "checkout") == 0 || strcmp(command, "check out") == 0)
		{
			cout << "Which is your room number?";
			cin >> roomNumber; 
			if (roomNumber >= 100 && roomNumber <= 115)
			{
				cout << "Checking out..." << endl;
				hotel->Checkout(roomNumber);
				cout << "You have successfully checked out!" << endl;
			}
			else
			{
				cout << "Wrong room number!" << endl;
			}
		}
		else if (strcmp(command, "Unavailable") == 0 || strcmp(command, "unavailable") == 0)
		{
			char reason[30];

			cout << "Select a room to be made unavailable: ";
			cin >> roomNumber;
			cout << "Select a from date: ";
			cin.ignore();
			cin.getline(date,30);
			cout << "Select a to date: ";
			cin.ignore();
			cin.getline(date2,30);
			cout << "Why do you mark the room as unavailable?" << endl;
			cout << "Select from: (repair, cleaning, painting, <any reason>)" << endl;
			cin.ignore();
			cin.getline(reason, 30);

			if (CheckDate(date) && CheckDate(date2))
			{
				hotel->Unavailable(roomNumber, DateToInt(date), DateToInt(date2), reason);
			}
			else
			{
				cout << "Invalid date" << endl;
			}
		}
		else if (strcmp(command, "Availability") == 0)
		{
			cout << "Enter date: ";
			cin.getline(date, 30);
			if (CheckDate(date) == true)
			{
				cout << "Generating availibility report..." << endl;
				cout << "Available rooms: " << endl;
				hotel->Availability(DateToInt(date));
			}
			else
			{
				cout << "Invalid date" << endl;
			}
		}
		else if (strcmp(command, "Help") == 0 || strcmp(command, "help") == 0)
		{
			cout << "Generating help message..." << endl;
			scext.Help();
		}
		else if (strcmp(command, "Save") == 0 || strcmp(command, "save") == 0)
		{ 
			if (isOpened == true)
			{
				cout << "Saving file..." << endl;
				scext.Save(*hotel,currentFile);
				cout << "File successfully saved" << endl;
			}
			else
			{
				cout << "No file ready to be saved" << endl;
			}
		}
		else if (strcmp(command, "SaveAs") == 0 || strcmp(command, "Save As") == 0 || strcmp(command, "save as") == 0)
		{
			if (isOpened == true)
			{
				char file[32];
				cout << "Please enter desired name: " << endl;
				cin.getline(file, 32);
				cout << "Saving file as " << file << "..." << endl;
				scext.Save(*hotel,file);
				cout << "File successfully save as " << file << endl;
			}
			else
			{
				cout << "No file ready to be saved" << endl;
			}
		}
		else if (strcmp(command, "Open") == 0 || strcmp(command, "open") == 0)
		{
			if (isOpened == false)
			{
				isOpened = true;
				cout << "Which file do you want to be opened? " << endl;
				cin.getline(currentFile, 64);
				scext.Open(*hotel, currentFile);
				cout << "You have successfully opened file " << currentFile << endl;
			}
			else
			{
				cout << "Another file in use. Please close the first one." << endl;
			}
		}
		else if (strcmp(command, "Close") == 0 || strcmp(command, "close") == 0)
		{
			if (isOpened == true)
			{
				isOpened = false;
				cout << "You have suuccessfully closed the file" << endl;
			}
			else
			{
				cout << "There is no file opened. You should have an opened file in order to close it." << endl;
			}
		}
		else if (strcmp(command, "Exit") == 0 || strcmp(command, "exit") == 0)
		{
			Using = 0;
			cout << "Thank you for using our program. Bye!" << endl;
		}
		else
		{
			cout << "You have entered an invalid command!" << endl;
			cout << "Write Help to see which are the supported commands." << endl;
			cout << endl;
		}
		cout << "Press enter to continue, please!" << endl;
		cin.ignore();
	}while (Using != 0);	
	
	delete[] hotel;
}

