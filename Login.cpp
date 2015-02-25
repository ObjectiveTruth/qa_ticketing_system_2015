#include "stdafx.h"
#include "Transactions.h"
#include "TicketSells.h"
#include <iostream>
#include <string>

using namespace std;

// Check if the userName exists

Handle loginUser()
{
	string userName;
	bool exist = false;

	cout << "Enter Username:";
	cin >> userName;

	Accounts acc;
	Handle handle;

	handle.setCurrentUser(acc.get(userName));
	if (handle.getCurrentUser().type != -1){
		exist = true;
	}

	if (exist)
	{
		cout << "User Logged in Successfully !";
	}
	else
		cout << "User does not exist !";
	return handle;
}