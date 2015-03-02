#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>

using namespace std;

//Function that add credit to the user
//returns 1 if the credit is added
//returns 0 if it can't add credit
bool addtouser()
{
	//Variables
	Accounts test;
	Account aux;
	string userName;
	float amount;

	//Get the user
	cout << "Enter Username:";
	cin >> userName;

	if (checkIfUsernameExist(userName))					//If the user exist
	{
		cout << "Enter Credit to add:";					//Ask for the credit
		while (!checkAmount(&amount)){					//If not in the right format
			cout << "Enter Credit to add:";					//Keep asking
		}

		//If it's here, everything is okay
		test.update(userName, test.get(userName).credit + amount);	//Update the credit
		cout << "Successfully added credit" << endl;				//And tell it to the user
		return true;

	}
	else
	{
		cout << "Invalid Username !";	//Ops, invalid user!
		return false;
	}

}