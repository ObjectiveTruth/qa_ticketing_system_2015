#include "stdafx.h"
#include "Transactions.h"
#include "Handle.h"

Handle::Handle()
{
	currentUser.type = -1;		//Always initialize with type -1, so we know that we don't have a current user yet
}


Handle::~Handle()
{
}

//This function set the current user
//returns 1 if the user is set
//returns 0 otherwise
int Handle::setCurrentUser(Account newUser){		
	currentUser = newUser;
	if (currentUser.type == -1)
	{
		return 0;
	}

	return 1;
}

//This function returns the current user
Account Handle::getCurrentUser()
{
	return currentUser;
}

//This function create a new user
//return 1 if the user can be created
//return 0 if the user cannot be created
int Handle::create()
{
	return createUser(currentUser);
}

//This function removes a user
//returns 0 if the user is not found
//returns 1 if the user is found and removed
int Handle::remove()
{
	return removeUser();
}

//This function is for login into the system
//returns the handle with the current user
Handle Handle::login()
{
	return loginUser();
}

//This function is for add credit for the user
//returns 1 if the credit is added
//returns 0 if it can't add credit
int Handle::addcredit()
{
	return addtouser();
}
