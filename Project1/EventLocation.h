#pragma once
#include <exception>

#include <iostream>
#include <string.h>
#include <cstring>
#include "Seat.h"
using namespace std;
 
class EventLocation {

	char locationName[50];
	char* address;
	int no_of_rows;
	int* no_of_seats;
	bool hasConcessionStand;

	Seat** seatMatrix;
	//Seat specialSeat = Seat(2365286, 1, standard);

public:
	//accessors

	char* getLocName()
	{
		if (this->locationName != NULL)
		{
			char* copy = new char[strlen(this->locationName) + 1];
			strcpy(copy, this->locationName);
			return copy;
		}
	}

	char* getAddress() {
		if (this->address != NULL)
		{
			char* copy = new char[strlen(this->address) + 1];
			strcpy(copy, this->address);
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
	void setLocName(const char loc[])
	{
		strcpy(this->locationName, loc);
	}

	void setAddress(const char* title) {
		if (this->address != NULL)
			delete[] this->address;

		this->address = new char[strlen(title) + 1];
		strcpy(this->address, title);

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
		strcpy(this->locationName, "");
		this->address = NULL;
		this->no_of_rows = 0;
		this->no_of_seats = NULL;
		this->hasConcessionStand = false;
	}

	//constructor with parameters
	EventLocation(const char locationName[], const char* address, int no_of_rows, int* no_of_seats, bool hasConcessionStand)
	{
		strcpy(this->locationName, "");

		this->address = new char[strlen(address) + 1];
		strcpy(this->address, address);

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
		strcpy(this->locationName, e.locationName);

		if (e.address != NULL)
		{
			if (this->address != NULL)
			{
				delete[] this->address;
				this->address = nullptr;
			}
			this->address = new char[strlen(e.address) + 1];
			strcpy(this->address, e.address);
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

		strcpy(this->locationName, e.locationName);

		if (e.address != NULL)
		{
			if (this->address != NULL)
			{
				delete[] this->address;
				this->address = nullptr;
			}
			this->address = new char[strlen(e.address) + 1];
			strcpy(this->address, e.address);
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

	//overload operator []
	char operator[](int i)
	{
		if (this->locationName != NULL && i >= 0 && i <= strlen(this->locationName))
		{
			return this->locationName[i];
		}
		else
		{
			throw exception("The index is negative or greater the length of the name");
		}
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

	//overload operator >
	bool operator>(const EventLocation& e) {
		return this->no_of_rows > e.no_of_rows;
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
	
	// Input for Location Name
	cout << "Enter Location Name: ";
	char buffer[100];
	in.ignore(); // Ignore newline left in the buffer
	in.getline(buffer, 100);
	location.setLocName(buffer);
	strcpy(buffer, "");

	// Input for Address
	cout << "Enter Address: ";
	in.ignore(); 
	in.getline(buffer, 100);
	location.setAddress(buffer);

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

	out << "Location: " << location.locationName << endl;
	out << "Address: " << location.address << endl;
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