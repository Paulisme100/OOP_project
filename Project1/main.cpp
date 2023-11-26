#include <iostream>
#include <string.h>
#include <cstring>
#include "Movie.h"
#include "EventLocation.h"
using namespace std;

class Ticket {
	const int code_num;
	int room;
	char* movieTitle;
	string date;
	int price;
public:

	int getPrice()
	{
		int price;
		price = this->price;
		return price;
	}

	string getDate()
	{
		string date;
		date = this->date;
		return date;
	}

};


int main()
{
	Movie movie1("Inception", "23/09/2023", "12:30", 150, "sci-fi", "3D");
	cout << "Title is: "<<movie1.getTitle() <<endl<< "Date: "<< movie1.getDate() <<endl<< "Time: "<< movie1.getTime()<<endl<< "Duration: " << movie1.getDuration()<<endl<<"Genre: " << movie1.getGenre()<<endl << "Format: "<< movie1.getFormat();
	Movie movie2(movie1);
	cout <<endl<< "Movie2 Info: " <<endl<<"Title:"<< movie2.getTitle() << endl;

	cout << "How many hours do the movie last: " << movie2.durationInHours();
		//cout<< endl<<"Hour: "<< movie2.rest();
	cout <<endl<<"First letter of movie2 title: "<< movie2[0];

	movie2 + 10;
	cout <<endl<<"New duration: "<< movie2.getDuration();
	movie2.startMoment(20);

	Movie movie3;
	cin >> movie3;
	cout << movie3;

	EventLocation loc1;
}