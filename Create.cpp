#include "stdafx.h"
#include "Create.h"
#include "accounts.h"
#include <iostream>
#include <string>
using namespace std;

// Variables
string userName;
string userType;
float initialAmount;

// Check if the user has privilege to create
bool itHasPrivilege()
{
	/*if (currentAccount.type == ADMIN)
	return true;
	else{
	cout << "Error: Not Authorised to create!";
	return false;
	}*/
	return true;
}

// Check if the userName already exists
bool checkIfUsernameExist()
{
	bool exist = false;

	cout << "Enter Username:";
	cin >> userName;

	Accounts acc;
	if (acc.get(userName).type != -1){
		cout << "Error: Username Already Exist!";
		exist = true;
	}

	return exist;
}

// Check if the type exists
bool checkIfTypeExist()
{
	bool isAType = false;

	cout << "Enter User Type:";
	cin >> userType;

	//if (userType == (ADMIN || BUYER || SELLER || FULL)){
	isAType = true;
	//}

	return isAType;
}

// Check if the amount of money is in the right format
bool checkAmount()
{
	cout << "Enter Initial Amount:";
	cin >> initialAmount;

	while (!cin){
		cout << "ERROR: Please enter the initial amount in the format: XX.XX\n";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> initialAmount;
	}

	return true;
}

bool createUser()
{

	if (!itHasPrivilege() || checkIfUsernameExist() || !checkIfTypeExist() || !checkAmount()){
		return false;
	}
	else{
		cout << "New User Created Successfully!";
		return true;
	}

}
