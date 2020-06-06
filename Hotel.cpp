#include "Hotel.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
using std::cout;
using std::endl;
Hotel::Hotel()
{
	this->nrRooms = 16;
	srand(time(NULL));
	for (size_t i = 0; i < this->nrRooms; i++)
	{
		rooms[i].SetRoomNumber(100 + i); 
		int nrBeds = rand() % 3 + 1;
		rooms[i].SetNrBeds(nrBeds);
	}
}
Hotel::Hotel(int numberRooms)
{
	this->nrRooms = numberRooms;
	srand(time(NULL));


	for (size_t i = 0; i < this->nrRooms; i++)
	{
		rooms[i].SetRoomNumber(100 + i);
		int nrBeds = rand() % 3 + 1;
		rooms[i].SetNrBeds(nrBeds);
	}
}
Hotel::Hotel(Hotel& other)
{
	this->nrRooms = other.nrRooms;

	for (size_t i = 0; i < other.nrRooms; i++)
	{
		this->rooms[i] = other.rooms[i];
	}
}
Hotel& Hotel::operator=(Hotel& other)
{
	if (this != &other)
	{
		this->nrRooms = other.nrRooms;

		for (size_t i = 0; i < other.nrRooms; i++)
		{
			this->rooms[i] = other.rooms[i];
		}
	}
	return *this;
}
Room& Hotel::operator[](size_t index)
{
	return rooms[index];	
}
int Hotel::GetNumberRooms() const
{
	return this->nrRooms;
}
void Hotel::SetNumberRooms(int nrRooms)
{
	this->nrRooms = nrRooms;
}
void Hotel::Report(int fromDate, int toDate)
{
	if (fromDate < toDate)
	{
		int monthsFromDate;
		int monthsToDate; 
		int daysFromDate; 
		int daysToDate; 
		int daysOccupied = 0;

		for (size_t i = 0; i < nrRooms; i++)
		{
			rooms[i].GetInfo();
			cout << endl;
			if (rooms[i].GetIsFreeStatus() == false && rooms[i].GetToDate() >= toDate)
			{
				monthsFromDate = (rooms[i].GetFromDate() % 10000) / 100;
				monthsToDate = (rooms[i].GetToDate() % 10000) / 100;
				daysFromDate = rooms[i].GetFromDate() % 100;
				daysToDate = rooms[i].GetToDate() % 100;

				if (monthsFromDate == monthsToDate)
				{

					daysOccupied = rooms[i].GetToDate() - rooms[i].GetFromDate();
				}
				else
				{
					switch (monthsToDate - monthsFromDate)
					{
					case 1: if ((monthsFromDate == 1) || (monthsFromDate == 3) || (monthsFromDate == 5) || (monthsFromDate == 7) ||
						(monthsFromDate == 8) || (monthsFromDate == 10) || (monthsFromDate == 12)) {daysOccupied = 31 + (daysToDate - daysFromDate);}
						  else { daysOccupied = 30 + (daysToDate - daysFromDate); }break;
					case 2: daysOccupied = 61 + (daysToDate - daysFromDate);
						break;
					case 3: if ((monthsFromDate == 1) || (monthsFromDate == 3) || (monthsFromDate == 5) || (monthsFromDate == 7) ||
						(monthsFromDate == 8) || (monthsFromDate == 10) || (monthsFromDate == 12)) {daysOccupied = 92 + (daysToDate - daysFromDate);}
						  else { daysOccupied = 91 + (daysToDate - daysFromDate); }break;
					default: cout << "The apartment is taken from long ago." << endl; break;
					}
				}
				cout << " and has been occupied for " << daysOccupied << " days! " << endl;
			}
		}
	}
	else
	{
		cout << "Invalid date" << endl;
	}
	
}
void Hotel::FindRoom(int nrBeds, int fromDate, int toDate)
{
	if (fromDate < toDate)
	{
		Room freeRooms[32];
		int index = 0;
		for (size_t i = 0; i < this->nrRooms; i++)
		{
			if (rooms[i].GetIsFreeStatus() == true && rooms[i].GetNumberBeds() >= nrBeds)
			{
				freeRooms[index] = rooms[i];
				index += 1;
			}
		}
		for (size_t i = 0; i < index; i++)
		{
			if (freeRooms[i].GetNumberBeds() == nrBeds)
			{
				freeRooms[i].GetInfo();
				return;
			}
		}
		rooms[0].GetInfo();
	}
	else
	{
		cout << "Invalid date " << endl;
	}

}
void Hotel::Unavailable(int roomNumber, int fromDate, int toDate, char* notes)
{
	if (fromDate < toDate)
	{
		int yearsFromDate = fromDate / 10000;
		int yearsToDate = toDate / 10000;
		int monthsFromDate = (fromDate % 10000) / 100;
		int monthsToDate = (toDate % 10000) / 100;
		int daysFromDate = fromDate % 100;
		int daysToDate = toDate % 100;

		for (size_t i = 0; i < this->nrRooms; i++)
		{
			if (this->rooms[i].GetRoomNumber() == roomNumber)
			{
				this->rooms[i].SetIsFreeStatus(false);
				this->rooms[i].SetFromDate(fromDate);
				this->rooms[i].SetToDate(toDate);

				cout << "Unavailable from " << yearsFromDate << "-" << monthsFromDate << "-" << daysFromDate
					<< " to " << yearsToDate << "-" << monthsToDate << "-" << daysToDate
					<< " " << notes << endl;
				break;
			}
		}
	}
	else
	{
		cout << "Invalid date" << endl;
	}
}
void Hotel::CheckIn(int roomNumber, int fromDate, int toDate, const char* notes)
{
	if (fromDate < toDate)
	{
		for (size_t i = 0; i < this->nrRooms; i++)
		{
			if (rooms[i].GetRoomNumber() == roomNumber)
			{
				if (rooms[i].GetIsFreeStatus() == true || rooms[i].GetToDate() <= fromDate)
				{

					this->rooms[i].SetIsFreeStatus(false);
					this->rooms[i].SetFromDate(fromDate);
					this->rooms[i].SetToDate(toDate);
					this->rooms[i].SetNotes(notes);

					break;
				}
				else
				{
					cout << "The room is already taken. Feel free to choose another one.";
					break;
				}
			}
		}
	}
	else
	{
		cout << "Invalid date" << endl;
	}
}
void Hotel::CheckIn(int roomNumber, int fromDate, int toDate, const char* notes, int nrGuests)
{
	if (fromDate < toDate)
	{
		for (size_t i = 0; i < this->nrRooms; i++)
		{
			if (rooms[i].GetRoomNumber() == roomNumber)
			{
				if (rooms[i].GetIsFreeStatus() == true || rooms[i].GetToDate() <= fromDate)
				{
					this->rooms[i].SetNrGuests(nrGuests);
					this->rooms[i].SetIsFreeStatus(false);
					this->rooms[i].SetFromDate(fromDate);
					this->rooms[i].SetToDate(toDate);
					this->rooms[i].SetNotes(notes);
					break;
				}
				else
				{
					cout << "The room is already taken. Feel free to choose another one.";
					break;
				}
			}
		}
	}
	else
	{
		cout << "Invalid date" << endl;
	}
}
void Hotel::Checkout(int roomNumber)
{
	for (size_t i = 0; i < this->nrRooms; i++)
	{
		if (this->rooms[i].GetRoomNumber() == roomNumber)
		{
			this->rooms[i].SetIsFreeStatus(true);
			break;
		}
	}
}

void Hotel::Availability(int date)
{
	cout << "Currently available rooms:" << endl;
	for (size_t i = 0; i < this->nrRooms; i++)
	{
		if (rooms[i].GetIsFreeStatus() == true || rooms[i].GetToDate() < date || rooms[i].GetFromDate() > date)
		{
			rooms[i].GetInfo();
		}
	}
}
