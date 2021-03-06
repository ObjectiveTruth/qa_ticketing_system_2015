#pragma once
#include <iostream>
#include <string>
#include "Accounts.h"
#include "Handle.h"
#include "tickets.h"
using namespace std;

//DEFINES

#define GUEST 0
#define ADMIN 1
#define BUYER 2
#define SELLER 3
#define FULL 4

//Check functions
bool itIsAdmin(Account currentUser);
bool checkIfUsernameExist(string userName);
bool checkIfTypeExist(int *userType);
bool checkAmount(float *initialAmount);

//Delete functions
int removeUser(Account currentUser);

//Create functions
int createUser(Account currentUser);

//Add credit functions
bool addtouser();

//Refund functions
int refundUser(Account currentUser);
bool makeTransfer(string to, string from, float amount);

//Login functions
int loginUser(Handle *currentHandle);

//Buy functions
int buyTicket(Account currentUser);

//Sell function
int sellTicket(Account currentUser);