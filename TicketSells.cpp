#include <iostream>
#include <string>
#include <cstdlib>
#include "Transactions.h" 

Handle handle = Handle();
using namespace std;

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
		}

		else if (command.compare("create") == 0)
		{
			handle.create();
		}

		else if (command.compare("delete") == 0)
		{
			handle.remove();
		}

		else if (command.compare("help") == 0)
		{
			cout << "Here is the commands that you can use:" << endl << endl;
			cout << "login \t\tFor login into the system" << endl;
			cout << "buy \t\tCommand to buy tickets" << endl;
			cout << "sell \t\tCommand to sell tickets" << endl;
			cout << "addcredit \tCommand to add credit to the user" << endl;
			cout << "create \t\tCommand to create a new user" << endl;
			cout << "delete \t\tCommand to delete a new user" << endl;
		}

		else
		{
			cout << "Unrecogonized command. Please try again" << endl;
		}

	}
}
