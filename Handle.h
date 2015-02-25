#pragma once

#include "Transactions.h"

class Handle
{
private:
	Account currentUser;
public:
	Handle();
	~Handle();
	int setCurrentUser(Account newUser);
	int create();
	int remove();
	Handle login();
	Account getCurrentUser();
	int addcredit();
};

