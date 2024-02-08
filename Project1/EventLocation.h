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
	int rows_for_VIP;
	int rows_for_DisabledPeople;
	bool hasConcessionStand;

	Seat** seatMatrix;

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

	void initializeMatrix()
	{
		if (this->no_of_rows != 0 && this->no_of_seats != NULL)
		{
			this->seatMatrix = new Seat*[this->no_of_rows];
			for (int i = 0; i < this->no_of_rows; i++)
				seatMatrix[i] = new Seat[this->no_of_seats[i]];
		}

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
		Seat** seatMatrix = nullptr;
		this->address = NULL;
		this->no_of_rows = 0;
		this->no_of_seats = NULL;
		this->rows_for_DisabledPeople = 0;
		this->rows_for_VIP = 0;
		this->hasConcessionStand = false;
	}

	//constructor with parameters
	EventLocation(const char locationName[], const char* address, int no_of_rows, int* no_of_seats, int rows_for_VIP, int rows_for_DisabledPeople, bool hasConcessionStand)
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

		this->rows_for_VIP = rows_for_VIP;
		this->rows_for_DisabledPeople = rows_for_DisabledPeople;

		this->hasConcessionStand = hasConcessionStand;

		this->initializeMatrix();

		//set the seatMatrix according the values received for rows, seats per row, seats for disabled and vip
		if (this->no_of_rows != 0 && this->no_of_seats != NULL)
		{
			for (int i = 0; i < this->rows_for_DisabledPeople; i++)
				for (int j = 0; j < this->no_of_seats[i]; j++)
					seatMatrix[i][j] = Seat(0, Category::disability);

			int vipStartRow = this->rows_for_DisabledPeople;
			int vipEndRow = this->rows_for_DisabledPeople + this->rows_for_VIP;
			for(int i = vipStartRow; i < vipEndRow; i++)
				for (int j = 0; j < this->no_of_seats[i]; j++)
					seatMatrix[i][j] = Seat(0, Category::VIP);
			
			for (int i = vipEndRow; i < this->no_of_rows; i++)
				for (int j = 0; j < this->no_of_seats[i]; j++)
					seatMatrix[i][j] = Seat(0, Category::standard);
		}

	}

	void printSeatAvailabilityMatrix()
	{
		if (this->no_of_rows == 0 || this->no_of_seats == nullptr || this->seatMatrix == nullptr)
		{
			cout << "Seat matrix is not initialized or has invalid dimensions." << endl;
			return;
		}

		cout << "Seat Availability Matrix:" << endl;

		for (int i = 0; i < this->no_of_rows; i++)
		{
			cout << "Row " << i + 1 << ": ";
			for (int j = 0; j < this->no_of_seats[i]; j++)
			{
				cout << this->seatMatrix[i][j].getAvailability() << " ";
			}
			cout << endl;
		}
	}

	void printSeatCategoryMatrix()
	{
		if (this->no_of_rows == 0 || this->no_of_seats == nullptr || this->seatMatrix == nullptr)
		{
			cout << "Seat matrix is not initialized or has invalid dimensions." << endl;
			return;
		}

		cout << "Seat Category Matrix:" << endl;

		for (int i = 0; i < this->no_of_rows; i++)
		{
			cout << "Row " << i + 1 << ": ";
			for (int j = 0; j < this->no_of_seats[i]; j++)
			{
				cout << this->seatMatrix[i][j].getCategory() << " ";
			}
			cout << endl;
		}
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

		this->rows_for_VIP = e.rows_for_VIP;
		this->rows_for_DisabledPeople = e.rows_for_DisabledPeople;

		this->initializeMatrix();

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

	//overload operator !
	bool operator!() {
		bool is = !hasConcessionStand;
		return is;
	}

	//overload operator >
	bool operator>(const EventLocation& e) {
		return this->no_of_rows > e.no_of_rows;
	}

	EventLocation operator-(int removeSeats)
	{
		EventLocation copy = *this;
		for (int i = 0; i < copy.no_of_rows; i++)
			if (copy.no_of_seats[i] > 0)
				copy.no_of_seats[i] = copy.no_of_seats[i] - removeSeats;
		return copy;
	}
	
	//overload operator--
	void operator--() {
		for (int i = 0; i < this->no_of_rows; i++)
			if(this->no_of_seats[i] > 0)
				this->no_of_seats[i] = this->no_of_seats[i] - 1;
	}

	friend istream& operator>>(istream& in, EventLocation& eventLocation);
	friend ostream& operator<<(ostream& out, const EventLocation& eventLocation);

	void readData(ifstream& file) {
		if (!file.is_open())
		{
			cout << "***Error! The file can't be opened or is missing.";
		}
		else
		{
			// Read Location Name
			char buffer[70];
			file.ignore();
			file.getline(buffer, 70);
			//cout << "Location read succesfully: " << buffer << endl;
			setLocName(buffer);

			// Read Address
			//file.ignore();
			file.getline(buffer, 100);
			setAddress(buffer);

			file >> this->no_of_rows;

			if (this->no_of_seats != nullptr) {
				delete[] this->no_of_seats;
				this->no_of_seats = nullptr;
			}
			no_of_seats = new int[this->no_of_rows];
			for (int i = 0; i < this->no_of_rows; i++) {
				file >> this->no_of_seats[i];
			}

			file >> this->rows_for_VIP;
			file >> this->rows_for_DisabledPeople;

			// Initialize Seat matrix
			initializeMatrix();
			
			// Put values in the matrix

			if (this->no_of_rows != 0 && this->no_of_seats != NULL)
			{
				for (int i = 0; i < this->rows_for_DisabledPeople; i++)
					for (int j = 0; j < this->no_of_seats[i]; j++)
						seatMatrix[i][j] = Seat(0, Category::disability);

				int vipStartRow = this->rows_for_DisabledPeople;
				int vipEndRow = this->rows_for_DisabledPeople + this->rows_for_VIP;
				for (int i = vipStartRow; i < vipEndRow; i++)
					for (int j = 0; j < this->no_of_seats[i]; j++)
						seatMatrix[i][j] = Seat(0, Category::VIP);

				for (int i = vipEndRow; i < this->no_of_rows; i++)
					for (int j = 0; j < this->no_of_seats[i]; j++)
						seatMatrix[i][j] = Seat(0, Category::standard);
			}
			
			file >> this->hasConcessionStand;
		}

	}

	void printInfo() {
		cout << "Location Name: " << this->locationName << endl;
		cout << "Address: " << this->address << endl;
		cout << "Number of rows: " << this->no_of_rows << endl;
		cout << "Number of seats per row: ";
		for (int i = 0; i < this->no_of_rows; i++) {
			cout << this->no_of_seats[i] << " ";
		}
		cout << endl << "Number of rows for VIP: " << this->rows_for_VIP;
		cout << endl << "Number of rows for people with disabilities: " << this->rows_for_DisabledPeople;

		cout << endl << "Concession Stand: ";
		if (this->hasConcessionStand)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	//destructor
	~EventLocation() {

		if (this->no_of_seats != nullptr) {
			delete[] this->no_of_seats;
			this->no_of_seats = nullptr;
		}

		if (this->address != NULL)
		{
			delete[] this->address;
			this->address = nullptr;
		}

		if (this->seatMatrix != nullptr) {
			for (int i = 0; i < this->no_of_rows; i++) {
				delete[] this->seatMatrix[i];
			}
			delete[] this->seatMatrix;
			this->seatMatrix = nullptr;
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

	cout << "Enter Number of rows for VIP: ";
	in >> location.rows_for_VIP;
	cout << "Enter Number of rows for people with disabilities: ";
	in >> location.rows_for_DisabledPeople;

	// Input for concession stand
	cout << "Does it have a Concession Stand?: ";
	in >> location.hasConcessionStand;

	return in;
}

ostream& operator<<(ostream& out, const EventLocation& location) {

	out << "Location Name: " << location.locationName << endl;
	out << "Address: " << location.address << endl;
	out << "Number of rows: " << location.no_of_rows << endl;
	out << "Number of seats per row: ";
	for (int i = 0; i < location.no_of_rows; i++) {
		out << location.no_of_seats[i] << " ";
	}
	out << endl<< "Number of rows for VIP: "<<location.rows_for_VIP;
	out << endl << "Number of rows for people with disabilities: " << location.rows_for_DisabledPeople;

	out << endl << "Concession Stand: ";
	if (location.hasConcessionStand)
		out << "Yes" << endl;
	else
		out << "No" << endl;

	return out;
}