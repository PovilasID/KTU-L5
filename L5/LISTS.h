#include "Company.h"
#include "Workers.h"
#include "PriceList.h"

Company *C = new Company(); 
Workers *W = new Workers();
PriceList *PL = new PriceList();

//Get
Company getCompany(){ return *C; }
Workers getWorkers(){ return *W; }
PriceList getPriceList(){ return *PL; }

//Edit
Company &editCompany(){ return *C; }
Workers &editWorkers(){ return *W; }
PriceList &editPriceList(){ return *PL; }

//Set
void setWorkers(Workers *a){
	for(a->toStart(); a->notLast(); a->toNext()){
		W->addPerson(Employee(a->getPerson().getName(), a->getPerson().getOffice(), a->getPerson().getSeconds(), a->getPerson().getHours()));
	}
}