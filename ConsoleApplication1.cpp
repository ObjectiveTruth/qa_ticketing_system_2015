#include <iostream>
#include <string>
#include <cstdlib>
#include "accounts.h"
#define GUEST 0
#define ADMIN 1
#define BUYER 2
#define SELLER 3
#define FULL 4

	int userType;
	using namespace std;

	int main()
	{
		
        Accounts accountsDB = Accounts();

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
				//login()
				cout << "Successfully Logged in !" << endl;
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
				//addcredit()
				cout << "Successfully added credit" << endl;
			}

			else if (command.compare("create") == 0)
			{
				//login()
				cout << "Successfully created new user !" << endl;
			}

			else
			{
				cout << "Unrecogonized command. Please try again" << endl;
			}

		}
	}
