#pragma once
#include "Room.h"

class Hotel
{
private:
	int nrRooms;
	Room rooms[64];
public:
	//---------------------------------------Constructors and some operators
	Hotel();
	Hotel(int numberRooms);
	Hotel(Hotel& other);
	Hotel& operator=(Hotel& other);
	Room& operator[](size_t index);
	
	//------------------------------------Getter and setter methods
	int GetNumberRooms() const;
	void SetNumberRooms(int nrRooms);
	
	//------------------------------------Main functions of the hotel system
	void Report(int fromDate, int toDate);
	void FindRoom(int nrBeds, int fromDate, int toDate);
	void Unavailable(int roomNumber, int fromDate, int toDate,char* notes);
	void CheckIn(int roomNumber, int fromDate, int toDate,const char* notes);
	void CheckIn(int roomNumber, int fromDate, int toDate, const char* notes, int nrGuests);
	void Checkout(int roomNumber);
	void Availability(int date);

	//operator << 
	friend std::ofstream& operator<<(ofstream& output, Hotel& h)
	{
		for (size_t i = 0; i < h.nrRooms; i++)
		{
			output << h[i];
		}
		return output;
	}
};

