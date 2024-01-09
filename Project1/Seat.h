#pragma once
#include <iostream>
#include <string.h>

using namespace std;

enum Category { standard = 0, VIP = 1, disability = 2 };

class Seat {
	int seat_code;
	bool availability;
	Category category;
public:
	Seat()
	{
		this->seat_code = 0;
		this->availability = 0;
		this->category = Category::standard;
	}

	Seat(int seat_code, bool availability, Category newcategory)
	{
		this->seat_code = seat_code;
		this->availability = availability;

		if (newcategory >= 0 && newcategory <= 2) {  
			this->category = newcategory;
		}
		else {
			// Default to standard category if the provided value is invalid
			cout << "Invalid category value. Defaulting to standard category." <<endl;
			this->category = Category::standard;
		}
	}

	Seat(const Seat& s)
	{
		this->seat_code = s.seat_code;
		this->availability = s.availability;

		if (s.category >= 0 && s.category <= 2)
			this->category = s.category;
		
	}

	Seat& operator=(const Seat& s)
	{
		this->seat_code = s.seat_code;
		this->availability = s.availability;

		if (s.category >= 0 && s.category <= 2)
			this->category = s.category;
		return *this;
	}

	friend istream& operator>>(istream& in, Seat& seat);
	friend ostream& operator<<(ostream& out, const Seat& seat);
	
	~Seat() {

	}

};

istream& operator>>(istream& in, Seat& seat) {

	cout << endl << "Enter the code of the seat: ";
	in >> seat.seat_code;

	cout << endl << "Is the seat available? Write 1 for yes and 0 for no. ";
	in >> seat.availability;

	cout << endl << "Specify category (0 for standard, 1 for VIP, 2 for disability): ";
	int categoryInput;
	in >> categoryInput;

	if (categoryInput >= 0 && categoryInput <= 2) {
		seat.category = static_cast<Category>(categoryInput);
	}
	else {
		// Default to standard category if the provided value is invalid
		cout << "Invalid category value. Defaulting to standard category." << endl;
		seat.category = Category::standard;
	}
	return in;
}

ostream& operator<<(ostream& out, const Seat& seat) {
	out << endl << "Seat Information: "<< endl;
	out << "Seat_code: " << seat.seat_code << endl;
	out << "Availability: " << seat.availability << endl;

	if(seat.category == Category::standard)
		out << "Category: Standard" << endl;
	else if (seat.category == Category::VIP)
		out << "Category: VIP" << endl;
	else if (seat.category == Category::disability)
		out << "Category: Disability" << endl;
	//out << "Category: " << seat.category << endl;

	return out;
}
