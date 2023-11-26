#pragma once
#include <exception>

#include <iostream>
#include <string.h>
#include <cstring>

class EventLocation {
	
	int no_of_rows;
	int* no_of_seats;
	bool hasConcessionStand;

public:
	//accessors
	int get_no_of_rows() {
		return this->no_of_rows;
	}
	int* get_no_of_seats() {

		//if (this->no_of_seats == nullptr && this->no_of_rows == 0)
			//return nullptr;

		int *copy = new int[this->no_of_rows+1];	
		for(int i = 0; i<this->no_of_rows; i++)
			copy[i] = this->no_of_seats[i];
		return copy;
	}

	bool get_state_of_existence() {
		return this->hasConcessionStand;
	}

	//setters with validations
	void set_no_of_rows(int value) {
		if (value <= 10)
			throw exception("Number of rows must be greater than 10. ");
		else
			this->no_of_rows = value;
	}

	void set_no_of_seats(int* seats) {
		if(this->no_of_seats != NULL)
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

	//default construct
	EventLocation()
	{
		this->no_of_rows = 0;
		this->no_of_seats = nullptr;
		this->hasConcessionStand = false;
	}

	//constructor with parameters
	EventLocation(int no_of_rows, int* no_of_seats, bool hasConcessionStand)
	{
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
};
