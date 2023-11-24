#include <iostream>
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

}