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
bool checkIfUsernameExist(string *userName);
bool checkIfTypeExist(string userType);
bool checkAmount(float *initialAmount);
int createUser(Account currentUser);

// Add credit functions
bool checkIfUsernameExist();
bool addtouser();

//Login functions
Handle loginUser();