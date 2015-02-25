using namespace std;
#include <string>
//Account is a case class that holds information about 
//a particular user. See main.cpp for type definitions
//credit is the current credit of that user
class Account{
public:
	int type;
	double credit;
};

//A variable that allows easy access to the Database
//with convenient helper functions shown below
class Accounts{
public:
	Account get(string);
	int update(string, double);
	int create(string, int, double);
	int remove(string);

};

