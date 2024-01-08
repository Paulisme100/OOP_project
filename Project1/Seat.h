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
	
	~Seat() {

	}

};