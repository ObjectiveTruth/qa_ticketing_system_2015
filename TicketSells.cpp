#include <iostream>
#include <string>
#include <cstdlib>
#include "Transactions.h" 
#define GUEST 0
#define ADMIN 1
#define BUYER 2
#define SELLER 3
#define FULL 4

Handle handle = Handle();
int userType;
using namespace std;
string USER = "miguel";

int main()
{
	
	Accounts accountsDB = Accounts();

	Account user = Account();

	cout << "*****************************************************" << endl;
	cout << "Welcome to the Ticket Selling Service" << endl;
	cout << "*****************************************************" << endl;

	string command;

	while (command.compare("exit") != 0)
	{

		cout << "\n" << endl;
		cout << "Enter your command:-> ";
		cin >> command;

		if (command.compare("login") == 0)
		{
			handle = handle.login();
		}


		else if (command.compare("buy") == 0)
		{
			//buy()
			cout << "Successfully purchased tickets" << endl;
		}

		else if (command.compare("sell") == 0)
		{
			//sell()
			cout << "Successfully sold tickets" << endl;
		}

		else if (command.compare("addcredit") == 0)
		{
			handle.addcredit();
			cout << "Successfully added credit" << endl;
		}

		else if (command.compare("create") == 0)
		{
			handle.create();
			//cout << "Successfully created new user !" << endl;
		}

		else if (command.compare("delete") == 0)
		{
			handle.remove();
			//cout << "Successfully added credit" << endl;
		}

		else
		{
			cout << "Unrecogonized command. Please try again" << endl;
		}

	}
}
