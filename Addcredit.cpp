#include "stdafx.h"
#include "accounts.h"
#include "Delete.h"
#include "Create.h"
#include "Addcredit.h"
#include <iostream>
#include <string>
#include "Accounts.h"

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

	if (checkIfUsernameExist())
	{
		handle.remove(userName)

			cout << "Enter Credit to add:";
		    cin >> Amount;

		while (!cin)
		
		{
			cout << "ERROR: Please enter the initial amount in the format: XX.XX\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> initialAmount;
		}

		acc.update(userName, Amount);
		//GLOBAL VARIABLE ALTERED WITH USER TYPE
		return true;

	}
	else
	{
		cout << "Invalid Username !"
		return false;
	}

}