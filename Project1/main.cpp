#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include "Event.h"
#include "EventLocation.h"
#include "Ticket.h"
#include "Seat.h"
using namespace std;


int main()
{
	//char fileName[50];
	//cout << "Enter file name (with extension): ";
	//cin.getline(fileName, 50);

	ifstream inputFile1("Locations.txt", ios::in);
	ifstream inputFile2("Events.txt", ios::in);

	int no_of_loc;
	if (!inputFile1.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		inputFile1 >> no_of_loc;
	}
	EventLocation** locations;
	locations = new EventLocation* [no_of_loc+1];

	//for (int i = 0; i < no_of_loc; ++i) {
		//locations[i] = new EventLocation;  // Allocate memory for an EventLocation object and make locations[i] point to it
	//}

	if (!inputFile1.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		for(int i = 0; i<no_of_loc; i++)
		{
			if (!inputFile1.is_open())
			{
				cout << "***Error! The file can't be opened or is missing.";
			}
			else
			{
				//EventLocation loc;
				locations[i] = new EventLocation;
				locations[i]->readData(inputFile1);///
				//locations[i] = &loc;
				//cout << locations[0]->getLocName() << endl;
				//locations[i]->printInfo();
				cout << endl;
			}
		}
	}

	for (int i = 0; i < no_of_loc; i++)
	{
		cout << "Location " << i + 1 << " Info: " << endl;
		locations[i]->printInfo();
		cout << endl;
	} //first time it didn't work because of the dangling pointer

	/*
	cout << endl <<  "Event Info: " << show1;
	show1.printInfo();

	Event* events[3];
	events[0] = &movie1;
	events[1] = &concert1;
	events[2] = &show1;

	for (int i = 0; i < 3; i++)
		events[i]->showUppercase(), cout<<endl;
	*/

	int no_of_events;
	if (!inputFile2.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		inputFile2 >> no_of_events;
	}
	Event** events;
	events = new Event * [no_of_events+1];
	
	if (!inputFile2.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		for (int i = 0; i < no_of_events; i++)
		{
			if (!inputFile2.is_open())
			{
				cout << "***Error! The file can't be opened or is missing.";
			}
			else
			{
				int eventType;
				inputFile2 >> eventType;
				cout << "EventType read: " << eventType<<endl;
				if (eventType == 1)
				{
					events[i] = new Movie;
					events[i]->readEventData(inputFile2);
				}
				else if (eventType == 2)
				{
					events[i] = new Concert;
					events[i]->readEventData(inputFile2);
				}
				else if (eventType == 3)
				{
					events[i] = new StandUpShow;
					events[i]->readEventData(inputFile2);
				}
				
			}
		}
	}

	for (int i = 0; i < no_of_events; i++)
	{
		events[i]->showUppercase();
		cout << endl;
	}

	cout << "Hello, dear client! \nSelect one of the options below:\n";
	cout << "1. See the list of events available\n";
	cout << "0. Exit\n";
	int option1;
	cin >> option1;
	switch (option1) {
	case 0:
	{
		exit(0);
	}
	break;
	case 1:
	{
		cout << "Here are the events: ";

		int option2;
		//cin >> option2;

	}
	break;
	//default:

	}

	for (int i = 0; i < no_of_loc; i++)
		delete locations[i];
	delete[] locations;


	for (int i = 0; i < no_of_events; i++)
		delete events[i];
	delete[] events;

	inputFile1.close();
	inputFile2.close();

	/*Ticket tick1(3, 5, "Costi", "Bodega Ursilor", 30);
	cout << endl << "Ticket Info: ";
	cout << endl << tick1;

	Ticket tick2;
	tick1 = tick1-5;
	*/
	/*Event ev1("Concursul cu ursul", "25/03/2023", "18:10", 125);
	cout << endl << "Event info: " << ev1;
	ev1 = ev1 + 20;
	cout << ev1;
	*/
}
