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
	int login();
	Account getCurrentUser();
	int addcredit();
	int refund();
	int logout();
	int buy();
	int sell();
};

