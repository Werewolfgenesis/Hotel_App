#pragma once

#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

using namespace std;

class Room
{
private:
	int roomNumber;
	int nrBeds;
	int nrGuests = 0;
	int fromDate, toDate; //dateFormat: yyyy-mm-dd
	bool isFree;
	char* notes;
public:
	//constructors and operator=
	Room();
	Room(Room& other);
	Room(int roomNumber, int nrBeds, const char* notes);	
	Room& operator=(Room& other);

	//----------------------------------Setter methods

	void SetRoomNumber(int roomNumber);
	void SetNrBeds(int nrBeds);
	void SetNotes(const char* notes);
	void SetIsFreeStatus(bool isFree);
	void SetFromDate(int fromDate);
	void SetToDate(int toDate);
	void SetNrGuests(int nrGuests);
	//-------------------------------Getter methods

	bool GetIsFreeStatus();
	int GetRoomNumber();
	int GetNumberBeds();
	int GetFromDate();
	int GetToDate();

	//----------------------------func which gives us all the info about a room

	void GetInfo();
	
	//--------------------------------operators >> and << 

	friend ostream& operator<<(ostream& output, const Room& r)
	{
		output << r.roomNumber << endl
			<< r.nrBeds << endl
			<< r.isFree << endl
			<< r.fromDate << endl
			<< r.toDate << endl
			<< r.notes << endl;

		return output;
	}

	friend istream& operator>>(istream& input, Room& r)
	{
		char str[64];
		input >> r.roomNumber;
		input >> r.nrBeds;
		input >> r.isFree;
		input >> r.fromDate;
		input >> r.toDate;
		input.get();
		input.getline(str, 64);
		r.SetNotes(str);
		return input;
	}
};

