#pragma once
#include "Employee.h"

class Workers{
private:
	struct Person{
		Employee E;
		double salary;
		Person * next;
	};

	Person * P;
	Person * x;
public:
	Workers():P(NULL){}
	~Workers(){ Destroy(); }

	void toStart() { x = P; }
	void toNext() { if(x) x = x->next; }
	bool notLast() { return x != NULL; }

	void Destroy(){
		while(P){
			x = P;
			P = P->next;
			delete x;
		}
	}

	void addPerson(Employee e){
		Person * t = new Person;
		t->E = e;
		t->next = P;
		P = t;
	}

	Employee getPerson(){ return x->E; }

	//**************************CHECK IF USING MAIN POINTER DOES ALOW TO REUSE IT************************************
	void output(string fn){
		ofstream fr(fn.c_str(), ios::app);
		fr << "Darbuotoju sarasas " << endl; 
		while (P != NULL)   {                    
			fr << P->E.getName() << " " << P->E.getOffice() << " " << P->E.getDate() << " " << P->E.getHours() << endl;
			P = P->next;
		}
		fr << endl;
		fr.close();
	}


};
