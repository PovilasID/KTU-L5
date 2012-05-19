#pragma once
#include <string>
#include <ctime>
#include <time.h>
#include "functions.h"

using namespace std;

class Employee{
private:
	string name;
	string office;
	time_t date;
	int hours;
public:
	Employee():name(""), office(""), date(time(0)), hours(0){}
	Employee(string n, string o, time_t d, int h):name(n), office(o), date(d), hours(h){}
	~Employee(){}

	//Set
	void setName(string a){ name = a; }
	void setOffice(string a){ office = a; }
	void setDate(int &a, int &b, int &c){
		time(&date);
		struct tm  *timeStruct = localtime(&date);
		
		timeStruct->tm_year = a - 1900;
		timeStruct->tm_mon = b;
		timeStruct->tm_mday = c;

		date = mktime(timeStruct);
	}
	void setHours(int a){ hours = a; }

	//Get
	string getName(){ return name; }
	string getOffice() { return office; }
	string getDate(){ 
		time(&date);
		struct tm  *timeStruct = localtime(&date);
		char buffer [80];
		strftime(buffer,80,"%Y-%m-%d",timeStruct);
		return buffer;
	}
	int getHours(){ return hours; }
};
