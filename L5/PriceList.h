#pragma once
#include <fstream>
#include "Price.h"
#include "functions.h"

class PriceList{
private:
	struct Prices{
		Price P;
		Prices * next;
	};

	Prices *PL;
	Prices *x;
public:
	PriceList():PL(NULL),x(NULL){}
	~PriceList(){ destroy(); }

	void destroy(){
		Prices * temp;
		while(PL){
			temp = PL;
			PL = PL->next;
			delete temp;
		}
		x =  NULL;
	}
	void start()		{ x = PL;			}
    bool notLast()		{ return x != NULL;	}
    void next()			{ x = x->next;		}
	Price getFirst()	{ return PL->P;		}
    Price get()			{ return x->P;		} 
	Price &edit()		{ return x->P;		}
	void add(Price & a)	{ 		
		Prices * t = new Prices;
		t->P = a;
		t->next = PL;
		PL = t;
	}

	void read(string fn){
		ifstream fs(fn.c_str());
		string name, fee;
		char line[100];
		bool first = true;
		while (!fs.eof())   { 
			fs.get(line, 25);  
			name = line;
			fs >> ws;
			fs.get(line, 11);
			fee = line;                        
			fs.ignore ();
			add(Price(trim(name), string_to_double(trim(fee))));
		}
		fs.close();	
	}

	void output(string fn){
		ofstream fr(fn.c_str(), ios::app);
		fr << "Valanadu kainininkas " << endl; 
		while (PL != NULL)   {                    
			fr << PL->P.getName() << " " << PL->P.getFee() << endl;
			PL = PL->next;
		}
		fr << endl;
		fr.close();
	}


};

