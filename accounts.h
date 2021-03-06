using namespace std;
#include <string>
#include "DailyTransactions.h"
//Account is a case class that holds information about 
//a particular user. See main.cpp for type definitions
//credit is the current credit of that user
class Account{
public:
	int type;
	double credit;
    string username;
};

//A variable that allows easy access to the Database
//with convenient helper functions shown below
class Accounts{
public:
	Account get(string);
	int update(string, double);
	int create(string, int, double);
	int remove(string);

private:
	DailyTransactions DT;
};

