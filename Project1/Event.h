#include <iostream>
#include <string.h>
#include <cstring>
//#include "Movie.h"
using namespace std;

class Event {
	char* title;
	string date;
	char* time;
	int duration;
	//char* genre;
	string format;

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

	/*char* getGenre() {
		if (this->genre != NULL)
		{
			char* copy = new char[strlen(this->genre) + 1];
			strcpy(copy, this->genre);
			return copy;
		}
	}*/

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

	string getFormat() {
		return this->format;
	}

	//setters
	void setTitle(const char* title) {
		if (this->title != NULL)
			delete[] this->title;

		this->title = new char[strlen(title) + 1];
		strcpy(this->title, title);

	}

	/*void setGenre(const char* genre) {
		if (this->genre != NULL)
			delete[] this->title;

		this->genre = new char[strlen(genre) + 1];
		strcpy(this->genre, genre);

	}*/

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

	void setFormat(string format)
	{
		if (format != "4D" && format != "3D" && format != "4XD" && format != "IMAX")
			throw exception("Wrong format. Try again or write the word in capital letters");
		else
		{
			this->format = format;
		}
	}

	//default construct
	Event()
	{
		this->title = NULL;
		this->date = "";
		this->time = NULL;
		this->duration = 0;
		//this->genre = NULL;
		this->format = "";
	}

	//constructor with parameters
	Event(const char* title, string date, const char * time, int duration, const char* genre, string format)
	{
		this->title = new char[strlen(title) + 1];
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

		/*this->genre = new char[strlen(genre) + 1];
		strcpy(this->genre, genre);*/

		if (format != "4D" && format != "3D" && format != "4XD" && format != "IMAX")
			throw exception("Wrong format. Try again or write the word in capital letters");
		else
		{
			this->format = format;
		}
	}

	//copy construct
	Event(const Event& m)
	{
		if (m.title != NULL)
		{
			this->title = new char[strlen(m.title) + 1];
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

		this->format = m.format;
	}

	//overloading operator =
	Event& operator=(const Event& m) {

		if (m.title != NULL)
		{
			if (this->title != NULL)
			{
				delete[] this->title;
				this->title = nullptr;
			}
			this->title = new char[strlen(m.title) + 1];
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

		this->format = m.format;
		return *this;
	}

	//first generic method; it returns the duration of the movie expressed in hours
	float durationInHours()
	{
		float hours = this->duration / 60.0;
		return hours;
	}

	//second generic method; it transforms the hour and minutes into integers and then shows a message 
	//saying when will the movie start and what is the delay given by the advertisements
	void startMoment(int delay) {
		int hour1 = this->time[0] - '0';
		int hour2 = this->time[1] - '0';
		int hh;
		hh = hour1*10 + hour2;

		int min1 = this->time[3] - '0';
		int min2 = this->time[4] - '0';
		int mm;
		mm = min1 * 10 + min2;

		cout <<endl<< "The start date is " << hh << ":" << mm << ". But the movie will begin after the " << delay << " minutes of advertisement.";
	}

	//overload operator []
	char operator[](int i)
	{
		if (i >= 0 && i <= strlen(this->title))
		{
			return this->title[i];
		}
		else
		{
			throw exception("the index is negative or greater the length of title");
		}
	}

	//overload operator +
	char operator+(int add)
	{
		if (duration <= 0)
			throw exception("the number is negative or null");
		else
		{
			this->duration += add;
		}
	}

	//put friend so that the operators can have access to private attributes
	friend istream& operator>>(istream& in, Event& movie);
	friend ostream& operator<<(ostream& out, const Event& movie);

	//destructor 
	~Event() {
		if (this->title != NULL)
		{
			delete[] this->title;
			this->title = nullptr;
		}

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

istream& operator>>(istream& in, Event& movie) {
	char buffer[100];

	cout << endl;
	// Input for title
	cout << endl << "Enter Title: ";
	in.getline(buffer, 100);
	movie.setTitle(buffer);

	cout << "Enter Date (dd/mm/yyyy): ";
	in >> movie.date;

	cout << "Enter Time (hh:hh): ";
	in >> buffer;
	movie.setTime(buffer);

	cout << "Enter Duration (in minutes): ";
	in >> movie.duration;

	/*
	// Input for genre
	cout << "Enter Genre: ";
	in.ignore(); // Ignore newline left in the buffer
	in.getline(buffer, 100);
	movie.setGenre(buffer);
	*/
	cout << "Enter Format: ";
	in >> movie.format;

	return in;
}

ostream& operator<<(ostream& out, const Event& movie) {
	out << endl;
	out << "Title: " << movie.title << endl;
	out << "Date: " << movie.date << endl;
	out << "Time: " << movie.time << endl;
	out << "Duration: " << movie.duration << " minutes" << endl;
	//out << "Genre: " << movie.genre << endl;
	out << "Format: " << movie.format << endl;

	return out;
}
