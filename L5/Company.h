#pragma once

class Company{
private:
	struct Worker{
		Employee E;
		Worker * next;
	};
	struct Department{
		Worker E;
		Department * next;
		Worker * branch;
	};

	Department * D;
	
	void _AddEmployee(string name, string office, int year,int month int day, int hours){
		
	}
	void _BranchuOutput(){
	
	}

	void _BranchDestroy(){
	}

public:	
	Company():D(NULL){}
	~Company(){ Destroy(); }

	void Read(string fn){
		ifstream fd(fn.c_str());
		string   gr,  vrd;    double vid;   char eil[30];
		while (!fd.eof())   { 
			fd.get(eil, 8);  gr = eil;      // skaito grupës pavadinimà
			fd  >> ws;                       // praleidþiami tarpai
			fd.get(eil, 15);  vrd = eil;   // skaito vardà 
			fd >> vid;                        // skaito vidurká
			fd.ignore ();
			Papildyti (gr, vrd, vid);
		}
		fd.close();
	}

	void Print(string fn){
	}

	void Destroy(){
	}
};
