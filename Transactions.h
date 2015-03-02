#pragma once
#include <iostream>
#include <string>
#include "Accounts.h"
#include "Handle.h"
using namespace std;

//DEFINES

#define GUEST 0
#define ADMIN 1
#define BUYER 2
#define SELLER 3
#define FULL 4

//Check functions
bool itHasPrivilege(Account currentUser);
bool checkIfUsernameExist(string userName);
bool checkIfTypeExist(int *userType);
bool checkAmount(float *initialAmount);

//Delete functions
int removeUser();

//Create functions
int createUser(Account currentUser);

// Add credit functions
bool addtouser();

//Login functions
Handle loginUser();