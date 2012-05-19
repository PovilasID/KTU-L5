#include "Company.h"
#include "Workers.h"

Company *C = new Company(); 
Workers *W = new Workers();

//Get
Company getCompany(){ return *C; }
Workers getWorkers(){ return *W; }

//Edit
Company &editCompany(){ return *C; }
Workers &editWorkers(){ return *W; }