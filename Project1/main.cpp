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
	fstream idsFile("IDs.txt", ios::in | ios::out | ios::app);
	fstream availableSeats("AvailableSeats.txt", ios::in | ios::out | ios::app);

	ofstream outputBFile("Tickets.bin", ios::binary | ios::out | ios::app);
	ifstream inputBFile("Tickets.bin", ios::binary | ios::in);

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
			}
		}
	}

	/*for (int i = 0; i < no_of_loc; i++)
	{
		cout << "Location " << i + 1 << " Info: " << endl;
		locations[i]->printInfo();
		cout << endl;
	} //first time it didn't work because of the dangling pointer
	*/

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

	/*for (int i = 0; i < no_of_events; i++)
	{
		//cout<< *events[i]<<endl;
		//events[i]->showUppercase();
		events[i]->printInfo();
		cout << endl;
	}*/
	

	

	Ticket* tickets[100];
	int cnt = 0;

	
	cout << "Hello, dear client! \nSelect one of the options below:\n";
	cout << "1. See the list of events available\n";
	cout << "0. Exit\n";
	int option1;
	cin >> option1;
	switch (option1) {
	case 0:
	{
		return 0;
	}
	break;
	case 1:
	{
		cout << "Here are the events: \n";
		for (int i = 0; i < no_of_events; i++)
		{
			cout << i + 1 << '.' << *events[i];
			cout << endl;
		}
		cout<< "0. Exit\n";

		cout << endl << "Choose one of the options and see the seats available. \n";

		int option2;
		cin >> option2;
		//clear();
		if (option2 >= 1 && option2 <= no_of_events)
		{
			cout << endl;
			char locName[50];
			strcpy(locName, events[option2 - 1]->getEventLocation());
			
			int index = 0, i;
			for (i = 0; i < no_of_loc; i++)
			{
				//cout << "i = " << i<<'\n';
				//cout << locName << " = " << locations[i]->getLocName()<<'\n';
				//cout << "strcmp result: " << strcmp(locName, locations[i]->getLocName()) << '\n';
				if (strcmp(locName, locations[i]->getLocName()) == 0)
				{
					index = i;
					break;
				}
			}

			cout <<"The event takes place at " << locName << ".\nBelow you can see all the seats.\n\n";
			locations[index]->printSeatAvailabilityMatrix();

			cout << "\n \n" << "Also take a look at the seat types/categories that can be bought and take this into consideration when choosing a seat.\n\n";
			locations[index]->printSeatCategoryMatrix();

			cout << "\nType 1 if you want to buy a ticket...Then you will choose the seat by typing the number of the row and column you want.";
			int option3;
			cin >> option3;
			if (option3 == 1)
			{
				int row, column;
				cout << "\nInsert row number: ";
				cin >> row;
				cout<< "\nInsert column number: ";
				cin >> column;

				//locations[index]->printSeatAvailabilityMatrix();

				int isBought;
				
				int ticketPrice = 0;
				if (locations[index]->getSeatCategory(row, column) == 0)
				{
					ticketPrice = events[option2 - 1]->getBasicPrice();
				}
				else if (locations[index]->getSeatCategory(row, column) == 1)
				{
					ticketPrice = events[option2 - 1]->getVIPprice();
				}
				else if (locations[index]->getSeatCategory(row, column) == 2)
				{
					ticketPrice = events[option2 - 1]->getSpecialPrice();
				}

				
				cout << "The ticket for the selected seat is: $" << ticketPrice <<endl << "Confirm your place by typing 1...  ";

				//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				//cin.ignore();
				//cout << "Do you want to buy the ticket? \n";

				cin >> isBought;
				if (isBought == 1)
				{
					char buyerName[50];
					cout << "Enter your name (FirstName): ";
					cin>>buyerName;
					locations[index]->reserveSeat(row, column);
					cout << "Hi " << buyerName << ". Your seat is reserved! "<<endl;
					//const char* charArray = buyerName.c_str();
					tickets[cnt] = new Ticket(row, column, buyerName, locName, ticketPrice);
					tickets[cnt]->printIdtoFile(idsFile);
					cnt++;
					cout << "\nTicket printed. Here's the info: " << endl;
					//cout << *tickets[cnt - 1];

					tickets[cnt - 1]->serialize(outputBFile);

					//Ticket copyTicket;
					//cout << "\n New ticket:\n";
					
					//copyTicket.deserialize(inputBFile);
					//copyTicket.deserialize(inputBFile);
					//cout << *tickets[cnt];
					//delete[] charArray;
				}
				else
				{
					cout << "Purchase canceled.";
				}
				
			}
			else return 0;
	
		}
		else if (option2 == 0)
			return 0;
			else
			{
			cout << "Invalid option\n";
			}
			
	}
	break;
	cout << "Invalid option\n";

	}

	

	for (int i = 0; i < no_of_loc; i++)
		delete locations[i];
	delete[] locations;


	for (int i = 0; i < no_of_events; i++)
		delete events[i];
	delete[] events;

	inputFile1.close();
	inputFile2.close();
	outputBFile.close();
	inputBFile.close();
	idsFile.close();

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
