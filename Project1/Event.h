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

	//setters
	void setTitle(const char title[]) {

		strcpy(this->title, title);
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

	//generic method to show the title in Uppercase
	void showUppercase() {

		char copy[60];
		strcpy(copy, this->title);
		for (int i = 0; i<strlen(copy); ++i) {
			if (copy[i] >= 'a' && copy[i] <= 'z') {
				
				copy[i] = copy[i] - 'a' + 'A';
			}
		}
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
		//this->genre = NULL;
		//this->format = "";
	}

	//constructor with parameters
	Event(const char title[], string date, const char* time, int duration)
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

		/*if (m.genre != NULL)
		{
			this->genre = new char[strlen(m.genre) + 1];
			strcpy(this->genre, m.genre);
		}*/

		//this->format = m.format;
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

		/*if (m.genre != NULL)
		{
			if (this->genre != NULL)
			{
				delete[] this->genre;
				this->genre = nullptr;
			}
			this->genre = new char[strlen(m.genre) + 1];
			strcpy(this->genre, m.genre);
		}*/

		//this->format = m.format;
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

	//destructor 
	~Event() {

		if (this->time != NULL)
		{
			delete[] this->time;
			this->time = nullptr;
		}

		/*if (this->genre != NULL)
		{
			delete[] this->genre;
			this->genre = nullptr;
		}*/
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

	/*
	// Input for genre
	cout << "Enter Genre: ";
	in.ignore(); // Ignore newline left in the buffer
	in.getline(buffer, 100);
	movie.setGenre(buffer);
	*/
	/*cout << "Enter Format: ";
	in >> movie.format;
	*/
	return in;
}

ostream& operator<<(ostream& out, const Event& event) {
	out << endl;
	out << "Title: " << event.title << endl;
	out << "Date: " << event.date << endl;
	out << "Time: " << event.time << endl;
	out << "Duration: " << event.duration << " minutes" << endl;
	//out << "Genre: " << movie.genre << endl;
	//out << "Format: " << movie.format << endl;

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
			return "standard";
		else if (this->formatType == Format::Format3D)
			return "VIP";
		else if (this->formatType == Format::Format4D)
			return "disability";
		else if (this->formatType == Format::IMAX)
			return "IMAX";
	}

	Movie()
	{
		this->genre = "";
		this->formatType = Format2D;
	}

	Movie(const char title[], string date, const char* time, int duration, string genre, Format formatType) :Event(title, date, time, duration)
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

	~Movie() {

	}
};


class Concert : public Event {

	char* artistName;
	string musicGenre;

public:

	Concert()
	{
		this->artistName = NULL;
		this->musicGenre = "";
	}

	Concert(const char title[], string date, const char* time, int duration, const char* artistName, string musicGenre) :Event(title, date, time, duration)
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

	StandUpShow() {
		this->no_of_comedians = 0;
		this->comedians = NULL;
		this->specialGuest = NULL;
	}

	StandUpShow(const char title[], string date, const char* time, int duration, int no_of_comedians, const string* comedians, const char * specialGuest):Event(title, date, time, duration) {

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
