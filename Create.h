#pragma once
#include <string>
#include "Accounts.h"

using namespace std;

// functions

bool itHasPrivilege(Account currentUser);
bool checkIfUsernameExist();
bool checkIfTypeExist();
bool checkAmount();
int createUser(Account currentUser);

