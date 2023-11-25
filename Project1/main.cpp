#include <iostream>
#include <string>
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

/*class EventLocation {
	//1int max_no_of_seats;
	int no_of_rows;
	int* no_of_seats;

};*/

class Movie {
	char* title;
	string date;
	string time;
	int duration;
	char* genre;
	string format;

	//accessors
	//char* getTitle() {
		//if(this->title)
	//}
	//string lastFour = myString.substr(myString.length() - 4);
};

int main()
{

}