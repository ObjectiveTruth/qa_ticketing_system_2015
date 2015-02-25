#include "stdafx.h"
#include "Transactions.h"

//Remove a User
//returns 0 if the entry is not found
//returns 1 if the entry is found
int removeUser()
{
	string userName;
	int removed = 0;

	cout << "Enter Username:";
	cin >> userName;
	Accounts user;

	removed = user.remove(userName);

	if (removed == 1){
		cout << userName + " succesfully deleted";
	}
	else
		cout << userName + " does not exist";

	return removed;
}