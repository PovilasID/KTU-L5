#include <string>

using namespace std;

class PriceList{
private:
	string name;
	double fee;
public:
	PriceList(string n = "", double f = 0.0):name(n), fee(f){}
	~Employee(){}

	//Set
	void setName(string a){ name = a; }
	void setFee(double a){ fee = a; }

	//Get
	string getNeme(){ return name; }
	double getFee(){ return fee; }
};