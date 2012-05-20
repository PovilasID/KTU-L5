#pragma once
#include <fstream>
#include "functions.h"
#include "Employee.h"
#include "Workers.h"

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
		Period *e = P;
		struct tm  *timeStruct;
		time_t beginning, end, date;
		string sTemp;
		string source = fn.substr(fn.length()-25, 21);
		if (first){		
			beginning = TimeToSeconds(atoi(source.substr(0,4).c_str()),
				atoi(source.substr(5,2).c_str()),
				atoi(source.substr(8,2).c_str()));
			end = TimeToSeconds(atoi(source.substr(11,4).c_str()),
				atoi(source.substr(16,2).c_str()),
				atoi(source.substr(19,2).c_str()));
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
		fr << "Atsikaitymo periodas nuo: " << TimeToString(beginning) << " iki " << TimeToString(end) << endl; 
		while (branch != NULL)   {                    
			fr << branch->E.getName() << " " << branch->E.getOffice() << " " << branch->E.getDate() << " " << branch->E.getHours() << endl;
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

	//**************************PROTECTION AGAINST DUPLICATES*****************************
	//Add hours and set latest adress
	Workers CompanyToWorkers(){
		Workers *W = new Workers();
		Period *e = P;
		while (e != NULL)   {
			while(e->branch != NULL){
				W->addPerson(Employee(e->branch->E.getName(), e->branch->E.getOffice(), e->branch->E.getSeconds(), e->branch->E.getHours()));
				e->branch = e->branch->next;
			}
			e = e->next;
		}
		return *W;
	}
};
