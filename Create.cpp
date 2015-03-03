#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>
using namespace std;

//Create the user if everthing is correct
//return 1 if the user can be created
//return 0 if the user cannot be created
int createUser(Account currentUser)
{
	//Variables
	string userName;
	int userType = -1, created = -1;
	float initialAmount = -1;

	if (!itIsAdmin(currentUser)){							//Check if the user has privilege
		cout << "Error: Not Authorised to create!";			//If not, tell the user
		created = 0;										//And cancel the transaction
	}
	else{													//If the user has privilege
		cout << "Enter Username:";							//Get the user name
		cin >> userName;

		if (checkIfUsernameExist(userName)){				//If the user does not exist
			cout << "Error: Username Already Exist!";		//Tell the user
			created = 0;									//And cancel the transaction
		}

		else{												//But if the user exist
			if (!checkIfTypeExist(&userType)){				//Check the type, but if do not exist
				cout << "Error: This Type Do Not Exist";	//Tell the user
				created = 0;								//And cancel the transaction
			}

			else{											//If everything is okay
				cout << "Enter Initial Amount:";			//Ask the initial amount

				if (!checkAmount(&initialAmount)){			//And if is not in the right format
					created = 0;							//Cancel the transaction
				}
			}
		}
	}

	if (created == -1){										//If created == -1, let's create the user!
		Accounts acc;
		acc.create(userName, userType, initialAmount);		//Create the user
		cout << "New User Created Successfully!";
		created = 1;
	}

	return created;
}
