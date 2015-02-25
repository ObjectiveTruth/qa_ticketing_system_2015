#include "stdafx.h"
#include "Transactions.h"
#include "Handle.h"

Handle::Handle()
{
}


Handle::~Handle()
{
}

int Handle::setCurrentUser(Account newUser){
	currentUser = newUser;
	if (currentUser.type == -1)
	{
		return 0;
	}

	return 1;
}

Account Handle::getCurrentUser()
{
	return currentUser;
}

int Handle::create()
{
	return createUser(currentUser);
}

int Handle::remove()
{
	return removeUser();
}

Handle Handle::login()
{
	return loginUser();
}

int Handle::addcredit()
{
	return addtouser();
	return 1;
}
