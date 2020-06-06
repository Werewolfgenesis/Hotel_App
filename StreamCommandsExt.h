#pragma once
#include <iostream>
#include <fstream>
#include "Hotel.h"
using std::cout;
using std::endl;
class StreamCommandsExt 
{
public:
	void Help()
	{
		cout << "The program provides the following options:  " << endl;
		cout << "--------------------------------------------------------------- " << endl;
		cout << "CheckIn <roomNr> <from> <to> ->               will check in a room in the given period" << endl;
		cout << "Unavailable <roomNr> <from> <to> <reason> ->  marks room as unavailable in the period due to reason" << endl;
		cout << "CheckOut <roomNr>->                           marks the room as free" << endl;
		cout << "FindRoom <nrBeds> <from> <to> ->              finds a room in the given period with the given amount of beds." << endl;
		cout << "Close ->                                      closes currently opened file." << endl;
		cout << "Save ->									   saves the currently opened file." << endl;
		cout << "Saveas <file> ->                              saves the currently opened file as <file>." << endl;
		cout << "Help ->									   shows the functionality of the program." << endl;
		cout << "Exit ->                                       exits the currently opened program." << endl;
		cout << "Open <file> ->                                opens file <file>" << endl;
	}
	Hotel& Open(Hotel& myH, const char* file)
	{
		char rowInFile[32];
		int index = 0;
		ifstream myFile;
		Room room;

		myFile.open(file);

		while (myFile >> room)
		{
			cout << 5;
			myH[index] = room; 
			index += 1;
		}

		myFile.close();
		myH.SetNumberRooms(index);

		return myH;
	}
	void Close(Hotel& myH)
	{
		myH.SetNumberRooms(0);
	}
	void Save(Hotel h, const char* file)
	{
		ofstream output;
		output.open(file);

		for (size_t i = 0; i < h.GetNumberRooms(); i++)
		{
			output << h[i];
		}

		output.close();
	}
	
};

