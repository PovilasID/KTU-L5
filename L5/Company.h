#pragma once
#include <fstream>
#include "functions.h"
#include "Employee.h"

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
	
	void _AddEmployee(string fn, string name, string office, string year, string month, string day, string hours, bool first){
		bool notNull = false;
		Period *e = P;
		struct tm  *timeStruct;
		time_t beginning, end, date;
		string sTemp;
		sTemp = fn.substr(-25,4);
		if (first){		
			beginning = TimeToSeconds(atoi(fn.substr(-25,4).c_str()),
				atoi(fn.substr(-20,2).c_str()),
				atoi(fn.substr(-17,2).c_str()));
			end = TimeToSeconds(atoi(fn.substr(-14,4).c_str()),
				atoi(fn.substr(-9,2).c_str()),
				atoi(fn.substr(-6,2).c_str()));
			e = e->next;
			e = new Period; 
			e->branch = NULL;
			e->begining = beginning;
			e->end = end;
			e->next = P;
			P = e;
		}

		date = TimeToSeconds(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str()));
			mktime(timeStruct);
		Department *d = new Department;
		d->E = Employee(name, office, date, atoi(hours.c_str()));
		d->next = e->branch;
		e->branch = d;
	}
	void _BranchOutput(ofstream & fr, time_t beginning, time_t end, Department *branch){
		fr << TimeToString(beginning) << " " << TimeToString(end) << endl; 
		while (branch != NULL)   {                    
			fr << branch->E.getName() << " " << branch->E.getOffice() << " " << branch->E.getDate() << branch->E.getHours() << endl;
			branch = branch->next;
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
		string name, office, year, month, day, hours;
		char line[100];
		bool first = true;
		while (!fs.eof())   { 
			fs.get(line, 25);  
			name = line;
			fs >> ws;                       
			fs.get(line, 20);  
			office = line;
			fs >> ws;
			fs.get(line, 5);
			year = line;
			fs >> ws;
			fs.get(line, 3);
			month = line;
			fs >> ws;
			fs.get(line, 3);
			day = line;
			fs >> ws;
			fs.get(line, 11);
			hours = line;                        
			fs.ignore ();
			_AddEmployee(fn, trim(name), trim(office), year, month, day, trim(hours), first);
			first = false;
		}
		fs.close();
	}

	void Otput(string fn){
		ofstream fr(fn.c_str(), ios::app);
		Period *e = P;
		while (e != NULL)   {
			_BranchOutput(fr, e->begining, e->end, e->branch);
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
