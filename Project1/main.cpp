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

	ifstream inputFile("Data.txt", ios::in);


	EventLocation locatie;
	if (!inputFile.is_open())
	{
		cout << "***Error! The file can't be opened or is missing.";
	}
	else
	{
		locatie.readData(inputFile);
	}
	cout <<"Location Info: "<< locatie;

	inputFile.close();
	
}
