#include "Transactions.h"

// Check if the user has privilege to create
bool itIsAdmin(Account currentUser)
{
	if (currentUser.type == 1)
		return true;

	else
		return false;
}

// Check if the userName already exists
bool checkIfUsernameExist(string userName)
{
	bool exist = false;

	Accounts acc;
	if (acc.get(userName).type != -1){
		exist = true;
	}

	return exist;
}

// Check if the type exists
// Return true if is corret
// False otherwise
bool checkIfTypeExist(int *type)
{
	bool isAType = false;
	string userType;

	cout << "Enter User Type:";
	cin >> userType;

	if (userType == "admin"){
		*type = ADMIN;
		isAType = true;
	}
	else if (userType == "buyer"){
		*type = BUYER;
		isAType = true;
	}
	else if (userType == "seller"){
		*type = SELLER;
		isAType = true;
	}
	else if (userType == "full"){
		*type = FULL;
		isAType = true;
	}
	else{
		isAType = false;
	}

	return isAType;
}

// Check if the amount of money is in the right format
// keep in a loop until the right format is put
//return true
bool checkAmount(float *amount)
{
	cin >> *amount;

	if (!cin){
		cout << "ERROR: Please enter the value in the format: XX.XX\n";
		cin.clear();
		cin.ignore(256, '\n');
	}
	else{
		//Check constrains
		if (*amount <= 0)
		{
			cout << "The amount need to be positive and greater than 0" << endl;
		}
		else
		{
			return true;
		}
	}

	return false;
		
}