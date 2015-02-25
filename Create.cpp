#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>
using namespace std;

// Check if the user has privilege to create
bool itHasPrivilege(Account currentUser)
{
	if (currentUser.type == 1)
	return true;
	else{
	cout << "Error: Not Authorised to create!";
	return false;
	}
}

// Check if the userName already exists
bool checkIfUsernameExist(string userName)
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
bool checkIfTypeExist(string userType)
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
bool checkAmount(float initialAmount)
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

int createUser(Account currentUser)
{
	string userName;
	string userType;
	float initialAmount = -1;

	if (!itHasPrivilege(currentUser) || checkIfUsernameExist(userName) || !checkIfTypeExist(userType) || !checkAmount(initialAmount)){
		return 0;
	}
	else{
		cout << "New User Created Successfully!";
		return 1;
	}

}
