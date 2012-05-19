#pragma once
#include "Employee.h"

class Workers{
private:
	struct Person{
		Employee E;
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
};
