#ifndef FACEBOOK_STATUS_H
#define FACEBOOK_STATUS_H
#define _CRT_SECURE_NO_WARNINGS
#define IMAGE_VIDEO_LEN 5
#define STATUS_LEN 6
#define IMAGE_ "Image"
#define STATUS_ "Status"
#define VIDEO_ "Video"
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::swap;
using std::getline;
using std::string;
using std::vector;
using std::fstream;

class Status {
	string content;
	string DateAndTime;
public:
	Status(string&& Content, string&& cDateAndTime) : content(std::move(Content)), DateAndTime(std::move(cDateAndTime)) {};
	// this is a class constructor , initializing all the variables of the class with temporary variables.
	Status(const string& Content, const string& cDateAndTime) : content(Content), DateAndTime(cDateAndTime) {};
	// this is a class constructor ,initializing all the variables of the class.
	const string& getContent() const { return content; };
	const string& getDate() const { return DateAndTime; };
	// this function gets the content of the status.
	virtual void printStatus() const;
	// this function prints the status content and the time and date it was published at.
	bool operator == (const Status& other) const { return this->getContent() == other.getContent(); }
	//this function override the "!=" operator in order to compare 2 statuses.
	bool operator != (const Status& other) const { return !(this->getContent() == other.getContent()); }
	//this function override the "!=" operator in order to compare 2 statuses.
	friend std::ostream& operator<<(std::ostream& os, const Status& obj) { return os << obj.content;}

	friend const vector<Status*>& operator+=(vector<Status*>& bulletinBoard, Status*&& obj) { bulletinBoard.push_back(obj); return bulletinBoard; }
	// this function override the "+=" operator in order to add new status to the status list.
	virtual void Serialize(fstream& file) const;
	// this function enter all the obj data to binary file
	virtual ~Status() = default;
	// this is the default destructor of the class "Status".
};
#endif //FACEBOOK_STATUS_H
