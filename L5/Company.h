#pragma once
#include <fstream>
#include "functions.h"

class Company{
private:
	struct Department{
		Employee E;
		Department * next;
	};
	struct Period{
		time_t begining, end;
		Period * next;
		Department * branch;
	};

	Period * P;
	
	void _AddEmployee(string fn, string name, string office, int year,int month, int day, int hours, bool first){
		bool notNull = false;
		Period *e = P;
		struct tm  *timeStruct;
		time_t beginning, end, date;
		if (first){		
			timeStruct->tm_year = atoi(fn.substr(0,4).c_str()) - 1900;
			timeStruct->tm_mon = atoi(fn.substr(5,2).c_str()) -1;
			timeStruct->tm_mon = atoi(fn.substr(8,2).c_str());
			beginning = mktime(timeStruct);
			timeStruct->tm_year = atoi(fn.substr(11,4).c_str()) - 1900;
			timeStruct->tm_mon = atoi(fn.substr(16,2).c_str()) - 1;
			timeStruct->tm_mon = atoi(fn.substr(19,2).c_str());
			end = mktime(timeStruct);
			e = e->next;
			e = new Period; 
			e->branch = NULL;
			e->begining = beginning;
			e->end = end;
			e->next = P;
			P = e;
		}

		timeStruct->tm_year = year - 1900;
		timeStruct->tm_mon = month -1;
		timeStruct->tm_mon = day;
		date = mktime(timeStruct);
		Department *d = new Department;
		d->E = Employee(name, office, date, hours);
		d->next = e->branch;
		e->branch = d;
	}
	void _BranchuOutput(ofstream & fr, time_t beginning, time_t end, Department *branch){
		Department *t;
		time(&beginning);
		struct tm  *timeStruct = localtime(&beginning);
		char buffer1 [80];
		strftime(buffer1,80,"%Y-%m-%d",timeStruct);
		time(&end);
		timeStruct = localtime(&end);
		char buffer2 [80];
		strftime(buffer2,80,"%Y-%m-%d",timeStruct);
		fr << buffer1 << " " << buffer2 << endl; //Write a function for this mess
		while (t != NULL)   {                    
			fr << t->E.getName() << " " << t->E.getOffice() << " " << t->E.getDate() << t->E.getHours() << endl;
			t = t->next;
		}
	}

	void _BranchDestroy(Department *branch){
		Department *d;
		while (branch != NULL)   {       
			d = branch;
			branch = d->next;
			delete d;
		}
	}

public:	
	Company():P(NULL){}
	~Company(){ Destroy(); }

	void Read(string fn){
		ifstream fs(fn.c_str());
		string name, office;
		int  year, month, day, hours;
		char line[100];
		bool first = true;
		while (!fs.eof())   { 
			fs.get(line, 25);  
			name = line;
			fs >> ws;                       
			fs.get(line, 40);  
			office = line;   
			fs >> year >> month >> day >> hours;                        
			fs.ignore ();
			_AddEmployee(fn, name, office, year, month, day, hours, first);
			first = false;
		}
		fs.close();
	}

	void Otput(string fn){
		ofstream fr(fn.c_str(), ios::app);
		Period *e = P;
		while (e != NULL)   {
			_BranchuOutput(fr, e->begining, e->end, e->branch);
			//Add line
			fr << endl;
			e = e->next;
		}
		fr.close ();
	}

	void Destroy(){
		Period *e;
		while (e != NULL)   {
			e = P;
			P = P->next;
			_BranchDestroy(e->branch);
			delete e;
		}
	}
};
