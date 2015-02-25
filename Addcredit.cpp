#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>

using namespace std;

// Variables
string userName;
int Amount;
// Check if the userName already exists


bool checkIfUsernameExist()
{
	bool exist = false;

	cout << "Enter Username:";
	cin >> userName;

	Accounts acc;
	if (acc.get(userName).type != -1)
	
	{
		exist = true;
	}

	return exist;
}


bool addtouser()
{
	Accounts test;
	if (checkIfUsernameExist())
	{
		test.remove(userName);

			cout << "Enter Credit to add:";
		    cin >> Amount;

		while (!cin)
		
		{
			cout << "ERROR: Please enter the initial amount in the format: XX.XX\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> Amount;
		}

		test.update(userName, Amount);
		//GLOBAL VARIABLE ALTERED WITH USER TYPE
		return true;

	}
	else
	{
		cout << "Invalid Username !";
		return false;
	}

}