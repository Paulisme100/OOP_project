#include <iostream>
#include <string.h>
#include <cstring>
#include "Event.h"
#include "EventLocation.h"
#include "Ticket.h"
using namespace std;


int main()
{
	Event movie1("Inception", "23/09/2023", "12:30", 150, "sci-fi", "3D");
	//cout << "Title is: "<<movie1.getTitle() <<endl<< "Date: "<< movie1.getDate() <<endl<< "Time: "<< movie1.getTime()<<endl<< "Duration: " << movie1.getDuration()<<endl<<"Genre: " << movie1.getGenre()<<endl << "Format: "<< movie1.getFormat();
	Event movie2(movie1);
	cout <<endl<< "Movie2 Info: " <<endl<<"Title:"<< movie2.getTitle() << endl;

	cout << "How many hours do the movie last: " << movie2.durationInHours();
		//cout<< endl<<"Hour: "<< movie2.rest();
	cout <<endl<<"First letter of movie2 title: "<< movie2[0];

	movie2 + 10;
	cout <<endl<<"New duration: "<< movie2.getDuration();
	movie2.startMoment(20);

	/*Movie movie3;
	cin >> movie3;
	cout << movie3;*/

	int seatsPerRow[] = { 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25, 20, 25 };
	EventLocation loc1("Afi Palace Cotroceni", 20, seatsPerRow, true);
	int rows = loc1.get_no_of_rows();

	//cout <<endl<< loc1;
	loc1.searchforFood("Nachos");

	if (!loc1) {
		cout << endl<< "Unfortunately, there is no concession stand." << endl;
	}
	else {
		cout <<endl<< "Yes. There is a concession stand." << endl;
	}
	
	--loc1;

	EventLocation loc2;
	loc2 = loc1;

	cout << endl << loc2;
	
	Ticket ticket1("Inception", 73, 25);
	Ticket ticket2(ticket1);

	cout << endl << ticket1.getUid() << endl;

	if (ticket1 == ticket2)
		cout << "That's a problem! ";
	else
		cout << "It's ok! ";

	if (ticket1 < ticket2)
		cout << endl<< "Ticket1 is cheaper than ticket2";
	else
		cout<< endl << "Ticket1 is not cheaper than ticket2";
}