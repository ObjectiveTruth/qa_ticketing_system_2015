#include "stdafx.h"
#include "Transactions.h"

//Remove a User
//returns 0 if the user is not found
//returns 1 if the user is found and removed
int removeUser()
{
	//Variables
	string userName;
	int removed = 0;
	Accounts user;

	//Get the user
	cout << "Enter Username:";
	cin >> userName;

	//Try to remove
	removed = user.remove(userName);

	//If removed
	if (removed == 1){
		cout << userName + " succesfully deleted";
	}
	else //If not
		cout << userName + " does not exist";

	return removed;
}