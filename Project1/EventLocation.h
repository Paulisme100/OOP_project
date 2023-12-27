#pragma once
#include <exception>

#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
 
class EventLocation {

	char* locationName;
	int no_of_rows;
	int* no_of_seats;
	bool hasConcessionStand;

public:
	//accessors
	char* getLocName() {
		if (this->locationName != NULL)
		{
			char* copy = new char[strlen(this->locationName) + 1];
			strcpy(copy, this->locationName);
			return copy;
		}
	}
	int get_no_of_rows() {
		return this->no_of_rows;
	}
	int* get_no_of_seats() {

		//if (this->no_of_seats == nullptr && this->no_of_rows == 0)
			//return nullptr;

		int* copy = new int[this->no_of_rows + 1];
		for (int i = 0; i < this->no_of_rows; i++)
			copy[i] = this->no_of_seats[i];
		return copy;
	}

	bool get_state_of_existence() {
		return this->hasConcessionStand;
	}

	//setters with validations
	void setLocName(const char* title) {
		if (this->locationName != NULL)
			delete[] this->locationName;

		this->locationName = new char[strlen(title) + 1];
		strcpy(this->locationName, title);

	}

	void set_no_of_rows(int value) {
		if (value <= 10)
			throw exception("Number of rows must be greater than 10. ");
		else
			this->no_of_rows = value;
	}

	void set_no_of_seats(int* seats) {
		if (this->no_of_seats != NULL)
			delete[] this->no_of_seats;

		this->no_of_seats = new int[no_of_rows + 1];

		for (int i = 0; i < this->no_of_rows; i++)
			this->no_of_seats[i] = seats[i];
	}

	void setExistenceofStand(bool is) {
		this->hasConcessionStand = is;
	}

	//first generic method; it calculates the total number of seats
	int max_no_of_seats() {
		int totalSeats = 0;
		for (int i = 0; i < no_of_rows; i++)
			totalSeats += no_of_seats[i];
		return totalSeats;
	}

	//second generic method;
	void searchforFood(const string foodName)
	{
		if (this->hasConcessionStand)
			cout << endl << "We have a Concession Stand. Look there for " << foodName << " and see if there are any portions left.";
		else
			cout << endl << "Sorry we do not have a Concession Stand so we can't offer you any food or drink.";
	}

	//default construct
	EventLocation()
	{
		this->locationName = nullptr;
		this->no_of_rows = 0;
		this->no_of_seats = nullptr;
		this->hasConcessionStand = false;
	}

	//constructor with parameters
	EventLocation(const char* locationName, int no_of_rows, int* no_of_seats, bool hasConcessionStand)
	{
		this->locationName = new char[strlen(locationName) + 1];
		strcpy(this->locationName, locationName);

		this->no_of_rows = no_of_rows;

		if (this->no_of_seats != NULL)
			delete[] this->no_of_seats;
		this->no_of_seats = new int[no_of_rows + 1];
		for (int i = 0; i < this->no_of_rows; i++)
			this->no_of_seats[i] = no_of_seats[i];

		this->hasConcessionStand = hasConcessionStand;
	}

	//copy construct
	EventLocation(const EventLocation& e)
	{
		if (e.locationName != NULL)
		{
		this->locationName = new char[strlen(e.locationName) + 1];
		strcpy(this->locationName, e.locationName);
		}

		this->no_of_rows = e.no_of_rows;

		if (e.no_of_seats != NULL)
		{
			if (this->no_of_seats != NULL)
				delete[] this->no_of_seats;
			this->no_of_seats = new int[e.no_of_rows + 1];
			for (int i = 0; i < e.no_of_rows; i++)
				this->no_of_seats[i] = e.no_of_seats[i];
		}

		this->hasConcessionStand = e.hasConcessionStand;
	}

	//overloading operator =
	EventLocation& operator=(const EventLocation& e) {

		if (e.locationName != NULL)
		{
			if (this->locationName != NULL)
			{
				delete[] this->locationName;
				this->locationName = nullptr;
			}
			this->locationName = new char[strlen(e.locationName) + 1];
			strcpy(this->locationName, e.locationName);
		}

		this->no_of_rows = e.no_of_rows;

		if (e.no_of_seats != NULL)
		{
			if (this->no_of_seats != NULL)
				delete[] this->no_of_seats;
			this->no_of_seats = new int[e.no_of_rows + 1];
			for (int i = 0; i < e.no_of_rows; i++)
				this->no_of_seats[i] = e.no_of_seats[i];
		}

		this->hasConcessionStand = e.hasConcessionStand;
		return *this;
	}

	//overload operator--
	void operator--() {
		for (int i = 0; i < this->no_of_rows; i++)
			if(this->no_of_seats[i] > 0)
				this->no_of_seats[i] = this->no_of_seats[i] - 1;
	}

	//overload operator !
	bool operator!() {
		bool is = !hasConcessionStand;
		return is;
	}

	friend istream& operator>>(istream& in, EventLocation& eventLocation);
	friend ostream& operator<<(ostream& out, const EventLocation& eventLocation);

	//destructor
	~EventLocation() {

		if (this->no_of_seats != nullptr) {
			delete[] this->no_of_seats;
			this->no_of_seats = nullptr;
		}
	}
};

istream& operator>>(istream& in, EventLocation& location) {

	// Input for locationName
	cout << "Enter Location Name: ";
	char buffer[100];
	in.ignore(); // Ignore newline left in the buffer
	in.getline(buffer, 100);
	location.setLocName(buffer);

	// Input for number of rows
	cout << "Enter Number of rows: ";
	in >> location.no_of_rows;

	// Input for number of seats per row
	cout << "Enter Number of seats per row (space-separated): ";
	if (location.no_of_seats != nullptr) {
		delete[] location.no_of_seats;
		location.no_of_seats = nullptr;
	}
	location.no_of_seats = new int[location.no_of_rows];
	for (int i = 0; i < location.no_of_rows; i++) {
		in >> location.no_of_seats[i];
	}

	// Input for concession stand
	cout << "Does it have a Concession Stand?: ";
	in >> location.hasConcessionStand;

	return in;
}

ostream& operator<<(ostream& out, const EventLocation& location) {

	out << "Location Name: " << location.locationName << endl;
	out << "Number of rows: " << location.no_of_rows << endl;
	out << "Number of reats per row: ";
	for (int i = 0; i < location.no_of_rows; i++) {
		out << location.no_of_seats[i] << " ";
	}
	out << endl;
	out << "Concession Stand: ";
	if (location.hasConcessionStand)
		out << "Yes" << endl;
	else
		out << "No" << endl;

	return out;
}