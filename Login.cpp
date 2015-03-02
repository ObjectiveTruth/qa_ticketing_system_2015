#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>

using namespace std;

//Check if the userName exists
//returns the handle with the current user
Handle loginUser()
{
	//Variables
	string userName;
	bool exist = false;
	Accounts acc;
	Handle handle;

	//Get the user
	cout << "Enter Username:";
	cin >> userName;

	if (checkIfUsernameExist(userName)){			//Check if the user exists, if yes
		handle.setCurrentUser(acc.get(userName));		//Set as the current user
		cout << "User Logged in Successfully !";		//And tell the user
	}

	else{											//If no
		cout << "User does not exist !";				//Tell the user too
	}
		
	return handle;
}