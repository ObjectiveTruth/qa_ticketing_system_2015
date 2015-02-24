#include "stdafx.h"
#include "Create.h"
#include "accounts.h"
#include <iostream>
#include <string>
using namespace std;

Create::Create(void)
{
}

// Check if the user has privilege to create
bool Create::ItHasPrivilege(void)
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
bool Create::CheckIfUsernameExist()
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
bool Create::CheckIfTypeExist()
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
bool Create::CheckAmount()
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

bool Create::TryToCreate(void)
{
	
	if (!ItHasPrivilege() || CheckIfUsernameExist() || !CheckIfTypeExist() || !CheckAmount()){
		return false;
	}
	else{
		cout << "New User Created Successfully!";
		return true;
	}
	
}
