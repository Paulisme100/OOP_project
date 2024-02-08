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

	/*switch () {
	case 0:
	{

	}
	break;
	case 1:
	{
		// code block
	}
	break;
	case 2:
	{
		// code block
	}
	break;
	default:

	}*/

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


	/*Movie movie1;
	if (!inputFile2.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		movie1.readEventData(inputFile2);
	}

	cout << endl << "Event Info: " << movie1;
	movie1.printInfo();
	*/

	/*StandUpShow show1;

	if (!inputFile2.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		show1.readEventData(inputFile2);
	}

	cout << endl <<  "Event Info: " << show1;
	show1.printInfo();
	*/
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
