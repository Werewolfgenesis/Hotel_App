#include <iostream>
#include "Room.h"

#pragma warning(disable:4996)
using namespace std;

Room::Room()
{
	this->notes = new char[4];
	this->isFree = true;
	this->roomNumber = 0;
	this->nrBeds = 0;
	strcpy(notes, " ");
}
Room::Room(Room& other)
{
	//other.notes = new char[128];
	this->notes = new char[strlen(other.notes) + 1];
	this->SetIsFreeStatus(other.isFree);
	this->SetRoomNumber(other.roomNumber);
	this->SetNrBeds(other.nrBeds);
	strcpy(this->notes, other.notes);
}
Room::Room(int roomNumber, int nrBeds, const char* notes)
{
	this->notes = new char[strlen(notes) + 1];
	this->roomNumber = roomNumber;
	this->nrBeds = nrBeds;
	strcpy(this->notes, notes);
}
Room& Room::operator=(Room& other)
{
	this->notes = new char[strlen(other.notes) + 1];

	if (this != &other)
	{
		this->roomNumber = other.roomNumber;
		this->isFree = other.isFree;
		this->nrBeds = other.nrBeds;
		this->fromDate = other.fromDate;
		this->toDate = other.toDate;
		strcpy(this->notes, other.notes);
	}
	return *this;
}
void Room::SetRoomNumber(int roomNumber)
{
	this->roomNumber = roomNumber;
}
void Room::SetNrBeds(int nrBeds)
{
	this->nrBeds = nrBeds;
}
void Room::SetNotes(const char* notes)
{
	if (notes != nullptr)
	{
		delete[] this->notes;
		this->notes = new char[strlen(notes) + 1];
		strcpy(this->notes, notes);
	}
}
void Room::SetIsFreeStatus(bool isFree)
{
	this->isFree = isFree;
}
void Room::SetFromDate(int fromDate)
{
	this->fromDate = fromDate;
}
void Room::SetToDate(int toDate)
{
	this->toDate = toDate;
}
void Room::SetNrGuests(int nrGuests)
{
	this->nrGuests = nrGuests;
}
int Room::GetRoomNumber()
{
	return this->roomNumber;
}
int Room::GetNumberBeds()
{
	return this->nrBeds;
}
bool Room::GetIsFreeStatus()
{
	return this->isFree;
}
int Room::GetFromDate()
{
	return this->fromDate;
}
int Room::GetToDate()
{
	return this->toDate;
}
void Room::GetInfo()
{
	
	if (this->isFree == false)
	{
		if (nrGuests > 0)
		{
			cout << "Room " << this->roomNumber << " has " << nrBeds << " beds " << " -> " << notes << " - " << nrGuests << " guests. Occupied until " << this->toDate;
		}
		else
		{
			cout << "Room " << this->roomNumber << " has " << nrBeds << " beds " << " -> " << notes << " Occupied until " << this->toDate;
		}
	}
	else
	{
		cout << "Room " << this->roomNumber << " has " << nrBeds << " beds ";
	}
}




