#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class Ticket {
	const int uid;
	int seat_code;
	char* movieTitle;
	int price;

public:
	static int ticket_counter;
	//accessors

	int getUid()
	{
		return this->uid;
	}

	int get_seat_code()
	{
		return this->seat_code;
	}

	char* getMovieTitle() {
		if (this->movieTitle != NULL)
		{
			char* copy = new char[strlen(this->movieTitle) + 1];
			strcpy(copy, this->movieTitle);
			return copy;
		}
	}

	//setters
	void set_seat_code(int code)
	{
		this->seat_code = code;
	}
	
	void setMovieTitle(const char* movieTitle) {
		if (this->movieTitle != NULL)
			delete[] this->movieTitle;

		this->movieTitle = new char[strlen(movieTitle) + 1];
		strcpy(this->movieTitle, movieTitle);

	}

	void set_price(int newPrice)
	{
		if (newPrice <= 0)
			throw exception("Number is negative or null");
		else
			this->price = newPrice;
	}

	//default construct
	Ticket() :uid(++ticket_counter)
	{
		this->seat_code = 0;
		this->movieTitle = NULL;
		price = 0;
	}

	//constructor with parameters
	Ticket(const char* movieTitle, int seat_code,int price) :uid(++ticket_counter)
	{
		this->seat_code = seat_code;

		this->movieTitle = new char[strlen(movieTitle) + 1];
		strcpy(this->movieTitle, movieTitle);

		if (price <= 0)
			throw exception("Number is negative or null");
		else
			this->price = price;
	}

	//cpy constructor
	Ticket(const Ticket& t) :uid(++ticket_counter)
	{
		if (t.movieTitle != NULL)
		{
			if (this->movieTitle != NULL)
			{
				delete[] this->movieTitle;
				this->movieTitle = nullptr;
			}

			this->movieTitle = new char[strlen(t.movieTitle) + 1];
			strcpy(this->movieTitle, t.movieTitle);
		}

		this->seat_code = t.seat_code;

		//if (price <= 0)
			//throw exception("Number is negative or null");
		//else
			this->price = t.price;
	}

	Ticket& operator=(const Ticket& t)
	{
		if (t.movieTitle != NULL)
		{
			if (this->movieTitle != NULL)
			{
				delete[] this->movieTitle;
				this->movieTitle = nullptr;
			}
			this->movieTitle = new char[strlen(t.movieTitle) + 1];
			strcpy(this->movieTitle, t.movieTitle);
		}

		this->seat_code = t.seat_code;

		if (price <= 0)
			throw exception("Number is negative or null");
		else
			this->price = price;

		return*this;
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

	bool operator <(const Ticket& ticket)
	{
		if (this->price < ticket.price)
			return 1;
		else
			return 0;
	}

	friend istream& operator>>(istream& in, Ticket& ticket);
	friend ostream& operator<<(ostream& out, const Ticket& ticket);

	~Ticket() {
		if (this->movieTitle != NULL)
		{
			delete[] this->movieTitle;
			this->movieTitle = nullptr;
		}
	}
};

int Ticket::ticket_counter = 0;

istream& operator>>(istream& in, Ticket& ticket) {
	
	cout << "Enter Seat Code: ";
	in >> ticket.seat_code;

	cout << "Enter Movie Title: ";
	char buffer[100];
	in.ignore(); 
	in.getline(buffer, 100);
	ticket.setMovieTitle(buffer);

	cout << "Enter Price: ";
	in >> ticket.price;

	return in;
}

ostream& operator<<(ostream& out, const Ticket& ticket) {

	cout << endl;
	out << "Ticket Information:" << endl;
	out << "UID: " << ticket.uid << endl;
	out << "Seat Code: " << ticket.seat_code << endl;
	out << "Movie Title: " << ticket.movieTitle << endl;
	out << "Price: " << ticket.price << endl;

	return out;
}
