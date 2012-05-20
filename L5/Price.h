#include <string>

using namespace std;

class Price{
private:
	string name;
	double fee;
public:
	Price(string n = "", double f = 0.0):name(n), fee(f){}
	~Price(){}

	//Set
	void setName(string a){ name = a; }
	void setFee(double a){ fee = a; }

	//Get
	string getName(){ return name; }
	double getFee(){ return fee; }
};