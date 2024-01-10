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
	int seatsPerRow[] = { 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25 };
	EventLocation loc1("Afi Palace Cotroceni", "Bulevardul General Paul Teodorescu 4", 20, seatsPerRow, 2, 1, true);
	/*cout << loc1 << endl;
	loc1.printSeatAvailabilityMatrix();
	cout << endl;
	loc1.printSeatCategoryMatrix();*/

	Movie movie1("Jumanji", "29/03/2024", "20:30", 123, "SF", Format3D);

	Concert concert1("Trap&Punk Madness", "25/04/2024", "21:00", 60, "Hvnds", "Punk/Trap");

	StandUpShow show1("Neispiratie", "25/04/2024", "21:00", 60, 3, new string[3]{"Vio", "Mocanu", "Costel"}, "Micutzu");
	show1.showUppercase();

	char fileName[50];
	//cout << "Enter file name (with extension): ";
	//cin.getline(fileName, 50);

	ifstream inputFile(fileName, ios::in);

	//while (){
	/*	int i, no_of_Objects;
		file >> no_of_Objects;

		for (i = 0; i < no_of_Objects; i++)
		{

		}
	*/
	//read title
	
}
