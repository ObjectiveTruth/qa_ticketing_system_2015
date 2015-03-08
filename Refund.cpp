#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>

using namespace std;

//Return the type of the user
int getType(string userName){
	Accounts acc;
	return acc.get(userName).type;
}

//This function make the refund
//returns false if not work
//true otherwise
bool makeTransfer(string to, string from, float amount){
	Accounts acc;
	DailyTransactions DT;
	Account buyerAccount = acc.get(to);
	Account sellerAccount = acc.get(from);

	if (sellerAccount.credit < amount)
		return false;

	if (to != from)		//If the user is not the same, update ======> If user is the same, don't need to update, because the value will be the same
	{
		//Update the users
		acc.update(sellerAccount.username, sellerAccount.credit - amount);
		acc.update(buyerAccount.username, buyerAccount.credit + amount);
	}

	//And log it into the daily transaction file
	DT.logRefund(to, from, amount);

	return true;
}

int refundUser(Account currentUser){

	//Variables
	string buyerName, sellerName;
	float totalAmount;
	int userType, refunded = -1;

	if (!itIsAdmin(currentUser)){																					//If is not admin
		cout << "Error: You do not have privilege to use this command!";											//Print error to user
		return 0;																									//Return 0
	}

	cout << "Enter the buyer username:";																			//Get the buyer name
	cin.ignore();								//Ignore the '\n'
	getline(cin, buyerName);						//And get the hole line

	userType = getType(buyerName);																					//Get the buyer type

	if (!checkIfUsernameExist(buyerName) || (userType != BUYER && userType != FULL && userType != ADMIN)){			//If the buyer does not exist or it is not a BUYER or FULL or ADMIN
		cout << "Error: User does not exist or does not has the privilege to execute this transaction!";			//Print error message
		refunded = 0;																								//And return 0
	}
	else{																											//If buyer is okay
		cout << "Enter the seller username:";																		//Ask for the seller name
		cin.clear();									//Ignore the '\n'
		getline(cin, sellerName);						//And get the hole line

		userType = getType(sellerName);																				//Get the seller type

		if (!checkIfUsernameExist(sellerName) || (userType != SELLER && userType != FULL && userType != ADMIN)){	//If the seller does not exist or it is not a SELLER or FULL or ADMIN
			cout << "Error: User does not exist or does not has the privilege to execute this transaction!";		//Print error message
			refunded = 0;																							//And return 0
		}
		else{																										//If seller is okay
			cout << "Enter the total amount:";																		//Ask for the total amount
			while (!checkAmount(&totalAmount)){																		//While is not in the right format
				cout << "Enter the total amount:";																	//Keep asking
			}
		
			if (!makeTransfer(buyerName, sellerName, totalAmount)){													//If can't refund
				cout << "Error: The seller does not have credit to refund";											//Show error
				refunded = 0;																						//Return 0
			}
			else{																									//If the refund was made
				cout << "Refund Successfully made!";																//Print it to the user
				refunded = 1;																						//Return 1
			}
		}
	}

	return refunded;
}