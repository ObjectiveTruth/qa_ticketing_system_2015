#pragma once
#include <iostream>
#include <string>
#include "Accounts.h"
#include "Handle.h"
using namespace std;

//Delete functions
int removeUser();

//Create functions
bool itHasPrivilege(Account currentUser);
bool checkIfUsernameExist(string userName);
bool checkIfTypeExist();
bool checkAmount();
int createUser(Account currentUser);

//Login functions
Handle loginUser();