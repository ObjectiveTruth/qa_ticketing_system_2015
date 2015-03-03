#include "stdafx.h"
#include "Transactions.h"

//Remove a User
//returns 0 if the user is not found or if you don't have privilege
//returns 1 if the user is found and removed
int removeUser(Account currentUser)
{
	//Variables
	string userName;
	int removed = 0;
	Accounts user;

	if (!itIsAdmin(currentUser)){								//Check if the user has privilege
		cout << "Error: Not Authorised to remove!" << endl;		//If not, tell the user
		removed = 0;											//And cancel the transaction
	}

	else{
		cout << "Enter Username:";								//Get the user
		cin >> userName;

		removed = user.remove(userName);						//Try to remove

		if (removed == 1){										//If removed
			cout << userName + " succesfully deleted";
		}
		else													//If not
			cout << userName + " does not exist";
	}

	return removed;
}