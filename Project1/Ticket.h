#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class Ticket {
	const int uid;
	int seat_code;
	char* buyerName; //or eventType
	char eventLocation[50];
	int price;

public:
	static int ticket_counter;
	//accessors

	int getUid()
	{
		return this->uid;
	}

	char* getEventLoc()
	{
		if (this->eventLocation != NULL)
		{
			char* copy = new char[strlen(this->eventLocation) + 1];
			strcpy(copy, this->eventLocation);
			return copy;
		}
	}

	int get_seat_code()
	{
		return this->seat_code;
	}

	char* getbuyerName() {
		if (this->buyerName != NULL)
		{
			char* copy = new char[strlen(this->buyerName) + 1];
			strcpy(copy, this->buyerName);
			return copy;
		}
	}

	//setters
	void set_seat_code(int code)
	{
		this->seat_code = code;
	}
	
	void setBuyerName(const char* buyerName) {

		if (this->buyerName != NULL)
			delete[] this->buyerName;

		this->buyerName = new char[strlen(buyerName) + 1];
		strcpy(this->buyerName, buyerName);

	}

	void setEventLoc(const char loc[])
	{
		strcpy(this->eventLocation, loc);
	}

	void set_price(int newPrice)
	{
		if (newPrice <= 0)
			throw exception("Number is negative or null");
		else
			this->price = newPrice;
	}

	//generic method: increase the price
	void increasePrice(int amount)
	{
		this->price += amount;
	}

	//default construct
	Ticket() :uid(++ticket_counter)
	{
		this->seat_code = 0;
		this->buyerName = NULL;
		strcpy(this->eventLocation, "");
		this->price = 0;
	}

	//constructor with parameters
	Ticket(int seat_code, const char* buyerName, const char eventLocation[], int price) :uid(++ticket_counter)
	{
		this->seat_code = seat_code;

		this->buyerName = new char[strlen(buyerName) + 1];
		strcpy(this->buyerName, buyerName);

		strcpy(this->eventLocation, eventLocation);

		if (price <= 0)
			throw exception("Number is negative or null");
		else
			this->price = price;
	}

	//cpy constructor
	Ticket(const Ticket& t) :uid(++ticket_counter)
	{
		this->seat_code = t.seat_code;

		if (t.buyerName != NULL)
		{
			if (this->buyerName != NULL)
			{
				delete[] this->buyerName;
				this->buyerName = nullptr;
			}

			this->buyerName = new char[strlen(t.buyerName) + 1];
			strcpy(this->buyerName, t.buyerName);
		}

		strcpy(this->eventLocation, t.eventLocation);

		this->price = t.price;
	}

	Ticket& operator=(const Ticket& t)
	{
		this->seat_code = t.seat_code;

		if (t.buyerName != NULL)
		{
			if (this->buyerName != NULL)
			{
				delete[] this->buyerName;
				this->buyerName = nullptr;
			}
			this->buyerName = new char[strlen(t.buyerName) + 1];
			strcpy(this->buyerName, t.buyerName);
		}

		strcpy(this->eventLocation, t.eventLocation);

		if (price <= 0)
			throw exception("Number is negative or null");
		else
			this->price = price;

		return*this;
	}

	//overload operator []
	char operator[](int i)
	{
		if (this->buyerName != NULL && i >= 0 && i <= strlen(this->buyerName))
		{
			return this->buyerName[i];
		}
		else
		{
			throw exception("The index is negative or greater the length of the name");
		}
	}

	//overload operator !
	bool operator!() {
		return this->price <= 0;
	}

	//overload operator == 
	bool operator==(const Ticket& ticket)
	{
		//const int UID = ticket.getUid();
		if (this->uid == ticket.uid)
			return 1;
		else
			return 0;
	}

	//overload operator <
	bool operator <(const Ticket& ticket)
	{
		if (this->price < ticket.price)
			return 1;
		else
			return 0;
	}

	//overload operator -
	Ticket operator-(int discount)   //smth
	{
		Ticket copy = *this;
		copy.price = copy.price - discount;
		return copy; 
	}
	
	//preincrementation
	Ticket& operator++() {
		++this->price;
		return *this;
	}

	//postincrementation
	Ticket& operator++(int) {

		Ticket copy = *this;
		copy.price++;
		return copy;          //smth
	}

	friend istream& operator>>(istream& in, Ticket& ticket);
	friend ostream& operator<<(ostream& out, const Ticket& ticket);

	~Ticket() {
		if (this->buyerName != NULL)
		{
			delete[] this->buyerName;
			this->buyerName = nullptr;
		}
	}
};

int Ticket::ticket_counter = 0;

istream& operator>>(istream& in, Ticket& ticket) {

	cout << "Enter Seat Code: ";
	in >> ticket.seat_code;

	cout << "Enter Buyer Name: ";
	char buffer[100];
	in.ignore(); 
	in.getline(buffer, 100);
	ticket.setBuyerName(buffer);
	strcpy(buffer, "");

	cout << "Enter Location Name: ";
	in.ignore(); // Ignore newline left in the buffer
	in.getline(buffer, 100);
	ticket.setEventLoc(buffer);
	strcpy(buffer, "");

	cout << "Enter Price: ";
	in >> ticket.price;

	return in;
}

ostream& operator<<(ostream& out, const Ticket& ticket) {

	cout << endl;
	out << "Ticket Information:" << endl;
	out << "UID: " << ticket.uid << endl;
	out << "Seat Code: " << ticket.seat_code << endl;
	out << "Buyer Name: " << ticket.buyerName << endl;
	out << "Event Location: " << ticket.eventLocation << endl;
	out << "Price: " << ticket.price << endl;

	return out;
}
