#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

class Event {
protected:
	char title[60];
	string date;
	char* time;
	int duration;
	char eventLocation[50];
	int basicPrice;
	int VIPprice;
	int specialPrice;

	//const static int max_no_of_tickets;

public:
	//accessors
	char* getTitle() {
		if (this->title != NULL)
		{
			char* copy = new char[strlen(this->title) + 1];
			strcpy(copy, this->title);
			return copy;
		}
	}

	char* getEventLocation() {
		if (this->eventLocation != NULL)
		{
			char* copy = new char[strlen(this->eventLocation) + 1];
			strcpy(copy, this->eventLocation);
			return copy;
		}
	}

	string getDate() {
		return this->date;
	}

	char* getTime() {
		if (this->time != NULL)
		{
			char* copy = new char[strlen(this->time) + 1];
			strcpy(copy, this->time);
			return copy;
		}
	}

	int getDuration() {
		return this->duration;
	}

	int getBasicPrice() {
		return this->basicPrice;
	}

	int getVIPprice() {
		return this->VIPprice;
	}

	int getSpecialPrice() {
		return this->specialPrice;
	}

	//setters
	void setTitle(const char title[]) {

		strcpy(this->title, title);
	}

	//set eventLocation
	void setEventLocation(const char eventLocation[]) {

		strcpy(this->eventLocation, eventLocation);
	}


	bool validateDate(const string date) {

		bool ok = 1;

		string lastFour = date.substr(date.length() - 4);
		if (lastFour != "2023" && lastFour != "2024")
			ok = 0;

		return ok;
	}

	void setDate(const string date) {
		if(validateDate(date) == 0)
			throw exception("Invalid date. Should be the current year or the next year! ");
		else
			this->date = date;
	}

	bool validateTime(const char* time) {
		
		bool ok = 1;
		if (time[2] != ':' || isdigit(time[0]) == 0 || isdigit(time[1]) == 0 || isdigit(time[3]) == 0 || isdigit(time[4]) == 0)
		{
			ok = 0;
		}
		if (time[0] != '0' && time[0] != '1' && time[0] != '2')
			ok = 0;
		if (time[0] == '2')
			if (time[1] != '0' && time[1] != '1' && time[1] != '2' && time[1] != '3' && time[1] != '4')
				ok = 0;
		if (time[3] == '6' || time[3] == '7' || time[3] == '8' || time[3] == '9')
			ok = 0;

		return ok;
	}

	void setTime(const char* time)
	{
		if (validateTime(time) == 1)
		{
			if (this->time != NULL)
				delete[] this->time;

			this->time = new char[strlen(time) + 1];
			strcpy(this->time, time);
		}
		else
			throw exception("Invalid format. You must enter a value like 18:15");

	}

	void setDuration(int minutes)
	{
		if (minutes >= 0 && minutes <= 300)
			this->duration = minutes;
		else
			throw exception("The number of minutes should be greater than 0 and smaller than 300. ");
	}

	void setBasicPrice(int newPrice)
	{
		if (newPrice < 0)
			throw exception("Number is negative");
		else
			this->basicPrice = newPrice;
	}

	void setVIPprice(int newPrice)
	{
		if (newPrice < 0)
			throw exception("Number is negative");
		else
			this->VIPprice = newPrice;
	}

	void setSpecialPrice(int newPrice)
	{
		if (newPrice < 0)
			throw exception("Number is negative");
		else
			this->specialPrice = newPrice;
	}


	//generic method to show the title in Uppercase
	virtual void showUppercase() {

		char copy[60];
		strcpy(copy, this->title);
		for (int i = 0; i<strlen(copy); ++i) {
			if (copy[i] >= 'a' && copy[i] <= 'z') {
				
				copy[i] = copy[i] - 'a' + 'A';
			}
		}
		cout << endl;
		for (int i = 0; i < strlen(copy); ++i) {
			cout << copy[i];
		}
	}

	//default construct
	Event()
	{
		strcpy(this->title, "");
		this->date = "";
		this->time = NULL;
		this->duration = 0;
		strcpy(this->eventLocation, "");
		this->basicPrice = 0;
		this->VIPprice = 0;
		this->specialPrice = 0;
	}

	//constructor with parameters
	Event(const char title[], string date, const char* time, int duration, const char eventLocation[], int basicPrice, int VIPprice, int specialPrice)
	{
		strcpy(this->title, title);

		if (validateDate(date) == 0)
			throw exception("Invalid date. Should be the current year or the next year! ");
		else
			this->date = date;

		if (validateTime(time) == 1)
		{
			if (this->time != NULL)
				delete[] this->time;

			this->time = new char[strlen(time) + 1];
			strcpy(this->time, time);
		}
		else
			throw exception("Invalid format. You must enter a value like 18:15");

		if (duration >= 0 && duration <= 300)
			this->duration = duration;
		else
			throw exception("The number of minutes should be greater than 0 and smaller than 300. ");

		strcpy(this->eventLocation, eventLocation);

		//prices for each type
		if (basicPrice < 0)
			throw exception("Number is negative");
		else
			this->basicPrice = basicPrice;

		if (VIPprice < 0)
			throw exception("Number is negative");
		else
			this->VIPprice = VIPprice;

		if (specialPrice < 0)
			throw exception("Number is negative");
		else
			this->specialPrice = specialPrice;

	}

	//copy construct
	Event(const Event& m)
	{
		if (m.title != NULL)
		{
			strcpy(this->title, m.title);
			
		}

		this->date = m.date;

		if (m.time != NULL)
		{
			this->time = new char[strlen(m.time) + 1];
			strcpy(this->time, m.time);
		}

		this->duration = m.duration;

		if (m.eventLocation != NULL)
		{
			strcpy(this->eventLocation, m.eventLocation);

		}

		this->basicPrice = m.basicPrice;
		this->VIPprice = m.VIPprice;
		this->specialPrice = m.specialPrice;
	}

	//overloading operator =
	Event& operator=(const Event& m) {

		if (m.title != NULL)
		{
			strcpy(this->title, m.title);
		}

		this->date = m.date;

		if (m.time != NULL)
		{
			if (this->time != NULL)
			{
				delete[] this->time;
				this->time = nullptr;
			}
			this->time = new char[strlen(m.time) + 1];
			strcpy(this->time, m.time);
		}

		this->duration = m.duration;

		if (m.eventLocation != NULL)
		{
			strcpy(this->eventLocation, m.eventLocation);

		}

		this->basicPrice = m.basicPrice;
		this->VIPprice = m.VIPprice;
		this->specialPrice = m.specialPrice;

		return *this;
	}

	//first generic method; it returns the duration of the movie expressed in hours
	float durationInHours()
	{
		float hours = this->duration / 60.0;
		return hours;
	}

	//second generic method; it transforms the hour and minutes into integers and then shows a message 
	//saying when will the event start and what is the delay given by the advertisements or arrangements
	void startMoment(int delay) {
		int hour1 = this->time[0] - '0';
		int hour2 = this->time[1] - '0';
		int hh;
		hh = hour1*10 + hour2;

		int min1 = this->time[3] - '0';
		int min2 = this->time[4] - '0';
		int mm;
		mm = min1 * 10 + min2;

		cout <<endl<< "The moment when the event should start is " << hh << ":" << mm << ". But the main event will begin after the " << delay << " minutes of advertisements and preparation.";
	}

	//overload operator []
	char operator[](int i)
	{
		if (this->title != NULL && i >= 0 && i <= strlen(this->title))
		{
			return this->title[i];
		}
		else
		{
			throw exception("the index is negative or greater the length of title");
		}
	}

	//overload operator !
	//to check if the event is set or not
	bool operator!() {
		return (strlen(title) == 0) && (date.empty()) && (time == NULL) && (duration == 0);
	}

	//overload operator <=
	bool operator<=(const Event& e) {
		return this->duration <= e.duration;
	}

	//overload operator +
	//to extend the duration of the event
	Event operator+(int add)
	{
		Event copy = *this;
		copy.duration = copy.duration + add;
		return copy;
	}

	//put friend so that the operators can have access to private attributes
	friend istream& operator>>(istream& in, Event& event);
	friend ostream& operator<<(ostream& out, const Event& event);

	virtual void readEventData(ifstream& file) {
		if (!file.is_open())
		{
			cout << "***Error! The file can't be opened or is missing.";
		}
		else
		{
			//read title
			char buffer[60];
			file.ignore();
			file.getline(buffer, 60);
			this->setTitle(buffer);
			//cout <<endl<< "Title read succesfully! : ";
			//cout << this->getTitle()<<endl;

			//read date
			file.ignore();
			file.getline(buffer, 11);
			this->date = string(buffer);
			//cout << "Date read succesfully! " << this->date<< endl;

			//read time
			//file.ignore();
			file.getline(buffer, 6);
			//cout << "Got line: " << buffer<<endl;
			this->setTime(buffer);
			//cout << "Time read succesfully! " << this->getTime()<<endl;

			file >> this->duration;
			//cout << "Duration read succesfully! " << this->duration<< endl;

			//read eventLocation
			file.ignore();
			file.getline(buffer, 60);
			this->setEventLocation(buffer);

			//file.ignore();
			file >> this->basicPrice;
			file >> this->VIPprice;
			file >> this->specialPrice;
		}
	}

	virtual void printInfo() {
		cout << "Title: " << this->title << endl;
		cout << "Date: " << this->date << endl;
		cout << "Time: " << this->time << endl;
		cout << "Duration: " << this->duration << " minutes" << endl;
		cout << "EventLocation: " << this->eventLocation << endl;

		cout << "Standard Ticket Price: " << this->basicPrice << endl;
		cout << "VIP Ticket Price: " << this->VIPprice << endl;
		cout << "Special Ticket Price: " << this->specialPrice << endl;
	}

	//destructor 
	~Event() {

		if (this->time != NULL)
		{
			delete[] this->time;
			this->time = nullptr;
		}
	}

};

istream& operator>>(istream& in, Event& event) {
	char buffer[100];

	cout << endl;
	// Input for title
	cout << endl << "Enter Title: ";
	in.getline(buffer, 100);
	event.setTitle(buffer);

	cout << "Enter Date (dd/mm/yyyy): ";
	in >> event.date;

	cout << "Enter Time (hh:hh): ";
	in >> buffer;
	event.setTime(buffer);

	cout << "Enter Duration (in minutes): ";
	in >> event.duration;

	cout << endl << "Enter Location Name: ";
	in.getline(buffer, 100);
	event.setEventLocation(buffer);

	cout << "Enter Standard Ticket Price: ";
	in >> event.basicPrice;
	cout << "Enter VIP Ticket Price: ";
	in >> event.VIPprice;
	cout << "Enter Special Ticket Price: ";
	in >> event.specialPrice;

	return in;
}

ostream& operator<<(ostream& out, const Event& event) {
	//out << endl;
	out << "Title: " << event.title << endl;
	out << "Date: " << event.date << endl;
	out << "Time: " << event.time << endl;
	out << "Duration: " << event.duration << " minutes" << endl;
	out << "EventLocation: " << event.eventLocation << endl;

	out << "Standard Ticket Price: " << event.basicPrice << endl;
	out << "VIP Ticket Price: " << event.VIPprice << endl;
	out << "Special Ticket Price: " << event.specialPrice << endl;

	return out;
}



enum Format { Format2D = 0, Format3D = 1, Format4D = 2, IMAX = 3 };

class Movie : public Event {

	string genre;
	Format formatType;

public:

	string getGenre() {
		return this->genre;
	}

	string getCategoryName() const
	{
		if (this->formatType == Format::Format2D)
			return "Format2D";
		else if (this->formatType == Format::Format3D)
			return "Format3D";
		else if (this->formatType == Format::Format4D)
			return "Format4D";
		else if (this->formatType == Format::IMAX)
			return "IMAX";
	}

	void setGenre(string g) {
		this->genre = g;
	}

	
	void setFormat(const string formatString) {
		//cout << formatString << endl;
		if (formatString == "0") {
			cout << "WRONG 0 NOT OK;";
		}
		if (formatString == "Format2D") {
			this->formatType = Format2D;
		}
		else if (formatString == "Format3D") {
			this->formatType = Format3D;
		}
		else if (formatString == "Format4D") {
			this->formatType = Format4D;
		}
		else if (formatString == "IMAX") {
			this->formatType = IMAX;
		}
		else throw exception("Wrong type! Enter a valid type! ");
	}
	


	Movie()
	{
		this->genre = "";
		this->formatType = Format2D;
	}

	Movie(const char title[], string date, const char* time, int duration, const char eventLocation[], int basicPrice, int VIPprice, int SpecialPrice, string genre, Format formatType) :Event(title, date, time, duration, eventLocation, basicPrice, VIPprice, specialPrice)
	{
		this->genre = genre;
		this->formatType = formatType;
	}

	Movie(const Movie& m) :Event(m)
	{
		this->genre = m.genre;
		this->formatType = m.formatType;
	}

	void showUppercase() {
		this->Event::showUppercase();
		cout << endl;

		const char* copy1 = this->genre.c_str();
		char* copy2 = new char[strlen(copy1) + 1];
		strcpy(copy2, copy1);

		for (int i = 0; i < strlen(copy2); ++i) {
			if (copy2[i] >= 'a' && copy2[i] <= 'z') {

				copy2[i] = copy2[i] - 'a' + 'A';
			}
		}
		for (int i = 0; i < strlen(copy2); ++i) {
			cout << copy2[i];
		}
	}

	void readEventData(ifstream& file) {
		this->Event::readEventData(file);
		
		//read genre
		char buffer[30];
		file.ignore();
		file.getline(buffer, 30);
		this->genre = string(buffer);
		//cout << "\nGenre has been read: "<<this->genre<<endl;

		//read Format
		//file.ignore();
		file.getline(buffer, 30);
		string formatRead = string(buffer);
		this->setFormat(formatRead);
		//cout << "\nFormat has been read: " << buffer << endl;
	}

	void printInfo() {

		this->Event::printInfo();

		cout << "Genre: "<<this->genre << endl;
		cout << "Format: ";
		if (this->formatType == Format::Format2D)
			cout << "Format2D"<<endl;
		else if (this->formatType == Format::Format3D)
			cout << "Format3D" << endl;
		else if (this->formatType == Format::Format4D)
			cout << "Format4D" << endl;
		else if (this->formatType == Format::IMAX)
			cout << "IMAX" << endl;
	}

	~Movie() {

	}
};


class Concert : public Event {

	char* artistName;
	string musicGenre;

public:

	void setArtistName(const char* name)
	{
		if (this->artistName != NULL)
			delete[] this-> artistName;

		this->artistName = new char[strlen(name) + 1];
		strcpy(this->artistName, name);
	}

	Concert()
	{
		this->artistName = NULL;
		this->musicGenre = "";
	}

	Concert(const char title[], string date, const char* time, int duration, const char eventLocation[], int basicPrice, int VIPprice, int SpecialPrice, const char* artistName, string musicGenre) :Event(title, date, time, duration, eventLocation, basicPrice, VIPprice, specialPrice)
	{
		this->artistName = new char[strlen(artistName) + 1];
		strcpy(this->artistName, artistName);

		this->musicGenre = musicGenre;
	}

	Concert(const Concert& m) :Event(m)
	{
		if (m.artistName != NULL)
		{
			if (this->artistName != NULL)
			{
				delete[] this->artistName;
				this->artistName = nullptr;
			}

			this->artistName = new char[strlen(m.artistName) + 1];
			strcpy(this->artistName, m.artistName);
		}
		this->musicGenre = m.musicGenre;
	}

	void showUppercase() {
		this->Event::showUppercase();
		cout << endl;

		char copy1[60];
		strcpy(copy1, this->artistName);
		for (int i = 0; i < strlen(copy1); ++i) {
			if (copy1[i] >= 'a' && copy1[i] <= 'z') {

				copy1[i] = copy1[i] - 'a' + 'A';
			}
		}
		for (int i = 0; i < strlen(copy1); ++i) {
			cout << copy1[i];
		}
	}

	void readEventData(ifstream& file) {
		this->Event::readEventData(file);

		//read artistName
		char buffer[30];
		file.ignore();
		file.getline(buffer, 30);
		this->setArtistName(buffer);

		//read musicGenre
		//file.ignore();
		file.getline(buffer, 30);
		this->musicGenre = string(buffer);
	}

	void printInfo() {

		this->Event::printInfo();

		cout << "Artist's name: " << this->artistName <<endl;
		cout << "Music genre: " << this->musicGenre << endl;
	}

	~Concert() {

		if (this->artistName != NULL)
		{
			delete[] this->artistName;
			this->artistName = nullptr;
		}
	}
};

class StandUpShow : public Event {

	int no_of_comedians;
	string* comedians;
	char * specialGuest;

public:

	void setSpecialGuest(const char* name)
	{
		if (this->specialGuest != NULL)
			delete[] this->specialGuest;

		this->specialGuest = new char[strlen(name) + 1];
		strcpy(this->specialGuest, name);
	}

	StandUpShow() {
		this->no_of_comedians = 0;
		this->comedians = NULL;
		this->specialGuest = NULL;
	}

	StandUpShow(const char title[], string date, const char* time, int duration, const char eventLocation[], int basicPrice, int VIPprice, int SpecialPrice, int no_of_comedians, const string* comedians, const char * specialGuest):Event(title, date, time, duration, eventLocation, basicPrice, VIPprice, specialPrice) {

		this->no_of_comedians = no_of_comedians;

		this->comedians = new string[no_of_comedians];
		for (int i = 0; i < no_of_comedians; ++i) {
			this->comedians[i] = comedians[i];
		}

		this->specialGuest = new char[strlen(specialGuest) + 1];
		strcpy(this->specialGuest, specialGuest);

	}

	StandUpShow(const StandUpShow& s) :Event(s) {

		this->no_of_comedians = s.no_of_comedians;

		this->comedians = new string[s.no_of_comedians];
		for (int i = 0; i < s.no_of_comedians; ++i) {
			this->comedians[i] = s.comedians[i];
		}

		this->specialGuest = new char[strlen(s.specialGuest) + 1];
		strcpy(this->specialGuest, s.specialGuest);
	}

	void showUppercase() {
		this->Event::showUppercase();
		cout << endl;

		char copy1[60];
		strcpy(copy1, this->specialGuest);
		for (int i = 0; i < strlen(copy1); ++i) {
			if (copy1[i] >= 'a' && copy1[i] <= 'z') {

				copy1[i] = copy1[i] - 'a' + 'A';
			}
		}
		for (int i = 0; i < strlen(copy1); ++i) {
			cout << copy1[i];
		}
	}

	void readEventData(ifstream& file) {
		this->Event::readEventData(file);

		//read no of comedians
		file >> this->no_of_comedians;
		//cout << "No of comedians read = "<< this->no_of_comedians<<endl;
		char buffer[30];

		this->comedians = new string[this->no_of_comedians];

		for (int i = 0; i < this->no_of_comedians; i++)
		{
			if(i == 0)
				file.ignore();
			file.getline(buffer, 30);
			//cout << endl << i<<endl;
			this->comedians[i] = string(buffer);
			//cout << "Name: " << this->comedians[i] << endl;
		}

		//read specialGuest
		//file.ignore();
		file.getline(buffer, 30);
		this->setSpecialGuest(buffer);

	}

	void printInfo() {

		this->Event::printInfo();

		cout << "No. of comedians: " << this->no_of_comedians << endl;
		for (int i = 0; i < this->no_of_comedians; i++)
			cout << "Comedian " << i + 1 << ": " << this->comedians[i]<<endl;
		cout << "Tonight's Special Guest: "<<this->specialGuest;
		
	}


	~StandUpShow() {

		if (this->specialGuest != NULL)
		{
			delete[] this->specialGuest;
			this->specialGuest = nullptr;
		}

		if (this->comedians != NULL)
		{
			delete[] this->comedians;
			this->comedians = nullptr;
		}
	}
};
