#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>

using namespace std;

class Ticket {
	const int uid;
	const char* purchaseDate;
	//int seat_code;
	int row;
	int column; 
	char* buyerName; 
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

	/*int get_seat_code()
	{
		return this->seat_code;
	}*/

	int getRow()
	{
		return this->row;
	}

	int getColumn()
	{
		return this->column;
	}

	char* getbuyerName() {
		if (this->buyerName != NULL)
		{
			char* copy = new char[strlen(this->buyerName) + 1];
			strcpy(copy, this->buyerName);
			return copy;
		}
	}

	const char* getCurrentTime() const {
		auto currentTime = chrono::system_clock::now();
		auto timePoint = chrono::system_clock::to_time_t(currentTime);
		return ctime(&timePoint);
	}

	//setters
	/*void set_seat_code(int code)
	{
		this->seat_code = code;
	}*/

	int generateRandomUid()
	{
		fstream idsFile("IDs.txt", ios::in | ios::out | ios::app);
		int ok;
		srand(static_cast<unsigned int>(time(nullptr)));
		int random = rand() % 3;
		if (!idsFile.is_open())
		{
			throw exception("Couldn't open the file!");
		}
		else
		{
			ok = 0;
			while (ok == 0)
			{
				ok = 1;
				while (!idsFile.eof() && ok == 1)
				{
					int ID;
					idsFile >> ID;
					//cout << "ID = " << ID << "; random = " << random<<endl;
					if (ID == random)
					{
						ok = 0;
					}

				}
				if (ok == 0)
				{
					//srand(static_cast<unsigned int>(time(nullptr)));
					random = rand() % 3;
					cout << "New random var: "<<random<<endl;
				}
			}
			/*if (ok == 1)
				cout << "Generated number: " << random;
			else cout << "No number :/";*/
			return random;
		}

		idsFile.close();
	}

	void setRow(int value)
	{
		this->row = value;
	}

	void setColumn(int value)
	{
		this->column = value;
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
		if (newPrice < 0)
			throw exception("Number is negative! ");
		else
			this->price = newPrice;
	}

	//generic method: increase the price
	void increasePrice(int amount)
	{
		this->price += amount;
	}

	//2nd method: compute the code of the seat 
	int seatCode()
	{
		int c = this->row + this->column + 1;
		return c;
	}

	//default construct
	Ticket() :uid(this->generateRandomUid()), purchaseDate(getCurrentTime())
	{
		//this->seat_code = 0;
		this->row= 0;
		this->column = 0;
		this->buyerName = NULL;
		strcpy(this->eventLocation, "");
		this->price = 0;
		++ticket_counter;
	}

	//constructor with parameters
	Ticket(int row, int column, const char* buyerName, const char eventLocation[], int price) :uid(this->generateRandomUid()), purchaseDate(getCurrentTime())
	{
		this->row = row;
		this->column = column;

		this->buyerName = new char[strlen(buyerName) + 1];
		strcpy(this->buyerName, buyerName);

		strcpy(this->eventLocation, eventLocation);

		if (price <= 0)
			throw exception("Number is negative or null");
		else
			this->price = price;

		++ticket_counter;
	}

	//cpy constructor
	Ticket(const Ticket& t) :uid(this->generateRandomUid()), purchaseDate(getCurrentTime())
	{
		this->row = t.row;
		this->column = t.column;

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

		this->eventLocation[0] = '\0';
		if (t.eventLocation != NULL)
			strcpy(this->eventLocation, t.eventLocation);

		this->price = t.price;
		++ticket_counter;
	}

	Ticket& operator=(const Ticket& t)
	{
		this->row = t.row;
		cout << "Row copied";
		this->column = t.column;
		cout << "Column copied";
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
		cout << "BuyerName copied";

		this->eventLocation[0] = '\0';
		if(t.eventLocation != NULL)
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
		cout << "Ticket copy made!" << endl;
		if (this->price > discount)
		{
			cout << "It's ok. Price is bigger than the discount. " << endl;
			copy.price = copy.price - discount;
			cout << "Discount substracted!" << endl;
		}
		return copy;
	}
	
	//preincrementation
	Ticket& operator++() {
		++this->price;
		return *this;
	}

	//postincrementation
	Ticket& operator++(int) {    //smth

		Ticket copy = *this;
		copy.price++;
		return copy;          
	}

	void serialize(ofstream& outputBFile)
	{
		if (!outputBFile.is_open())
		{
			cout << "Couldn't open or create the output file!";
		}
		else {

			outputBFile.write((char*)&this->uid, sizeof(int));
			int length = strlen(purchaseDate);
			outputBFile.write((char*) & length, sizeof(int));
			//cout << "\nLength of date: " << length;
			char date[30] = "";
			strcpy(date, this->purchaseDate);
			outputBFile.write((char*)&date, sizeof(char) * (length + 1));
			//cout << "\nPurchase date: " << this->purchaseDate;
			outputBFile.write((char*)&this->row, sizeof(int));
			outputBFile.write((char*)&this->column, sizeof(int));
			int clientNameLength = strlen(this->buyerName);
			outputBFile.write((char*) & clientNameLength, sizeof(int));
			char clientN[50] = "";
			strcpy(clientN, this->buyerName);
			outputBFile.write((char*)&clientN, sizeof(char) * (clientNameLength + 1));
			int locNameLength = strlen(this->eventLocation);
			outputBFile.write((char*) & locNameLength, sizeof(int));
			outputBFile.write((char*)&this->eventLocation, sizeof(char) * (locNameLength + 1));
			outputBFile.write((char*)&this->price, sizeof(int));
		}
	}

	void deserialize(ifstream& inputBFile)
	{
		if (!inputBFile.is_open())
		{
			cout << "Couldn't open the file!";
		}
		else
		{
			int locUid;
			inputBFile.read((char*)&locUid, sizeof(int));
			cout << endl << "Uid: " << locUid;

			int length;
			inputBFile.read((char*)&length, sizeof(int));
			cout << endl << "Length: " << length;
			//char* localPurchaseDate = new char[length + 1];
			char localPurchaseDate[30];
			inputBFile.read((char*)&localPurchaseDate, sizeof(char) * (length + 1));
			cout << endl << "PurchaseDate: " << localPurchaseDate;

			int row;
			int column;
			inputBFile.read((char*)&row, sizeof(int));
			inputBFile.read((char*) &column, sizeof(int));
			cout << "\nRow: "<<row;
			cout << "Column: " <<column;

			int clientNameLen;
			inputBFile.read((char*) & clientNameLen, sizeof(int));
			cout << "\nName length: " << clientNameLen;

			/*if (this->buyerName != NULL)
			{
				delete[] this->buyerName;
				this->buyerName = nullptr;
			}*/
			char clientN[50] = "";
			//this->buyerName = new char[clientNameLen + 1];
			inputBFile.read((char*) & clientN, sizeof(char) * (clientNameLen + 1));
			cout << "\nclientName: " << clientN;

			int locNameLen;
			inputBFile.read((char*) & locNameLen, sizeof(int));
			cout << "\n Length of locName: " << locNameLen;
			char nameOfLoc[60];
			inputBFile.read((char*) & nameOfLoc, sizeof(char) * (locNameLen + 1));
			cout << "\n location: " << nameOfLoc;

			int pprice;
			inputBFile.read((char*)&pprice, sizeof(int));
			cout << "\nPrice: " << pprice;
		}
	}

	void printIdtoFile(fstream& outputFile)
	{
		if (this->uid > 0)
		{
			outputFile << this->uid<<endl;
		}
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

	cout << "Enter Row: ";
	in >> ticket.row;
	cout << "Enter Column: ";
	in >> ticket.column;

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

	out << endl;
	out << "Ticket Information:" << endl;
	out << "UID: " << ticket.uid << endl;
	out << "Purchase Date: " << ticket.purchaseDate;
	out << "Seat row: " << ticket.row << endl;
	out << "Seat column: " << ticket.column << endl;
	out << "Seat Code: " << (ticket.row + ticket.column + 1) << endl;
	//out << "Seat Code: " << ticket.seat_code << endl;
	out << "Buyer Name: " << ticket.buyerName << endl;
	out << "Event Location: " << ticket.eventLocation << endl;
	out << "Price: " << ticket.price << endl;

	return out;
}
