#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>

using namespace std;

//Check if the userName exists
//returns 1 with successfully logged in
//0 otherwise
int loginUser(Handle *currentHandle)
{
	//Variables
	string userName;
	int logged = -1;
	Accounts acc;
	Handle handle = *currentHandle;

	if (handle.getCurrentUser().type != -1){									//First check if you are already logged in
		cout << "Error: You are already logged in. Please logout first!";		//If yes, print it
		return 0;																//And return 0
	}
		
	cout << "Enter Username:";													//Get the user name
	cin.ignore();								//Ignore the '\n'
	getline(cin, userName);						//And get the hole line

	if (checkIfUsernameExist(userName)){										//Check if the user exists, if yes
		handle.setCurrentUser(acc.get(userName));								//Set as the current user
		logged = 1;
		cout << "User Logged in Successfully !";								//And tell the user
	}

	else{																		//If no
		logged = 0;																//Set 0 to return
		cout << "User does not exist !";										//Tell the error to the user
	}
	
	*currentHandle = handle;													//Update the currentHandle

	return logged;
}