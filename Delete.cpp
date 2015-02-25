#include "stdafx.h"
#include "Transactions.h"

string userName;

int removeUser()
{
	int removed = 0;

	cout << "Enter Username:";
	cin >> userName;
	//Accounts user;

	//removed = user.remove(userName);

	if (removed == 1){
		cout << userName + "succesfully deleted";
	}
	else
		cout << userName + "does not exist";

	return removed;
}