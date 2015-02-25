#include "stdafx.h"
#include "Login.h"
#include "accounts.h"
#include <iostream>
#include <string>

using namespace std;

// Variables
string userName;
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


bool loginUser()
{

	if (checkIfUsernameExist())
	{
		cout << "User Logged in Successfully !";
		//GLOBAL VARIABLE ALTERED WITH USER TYPE
		return true;
	}
	else
	{
		return false;
	}

}