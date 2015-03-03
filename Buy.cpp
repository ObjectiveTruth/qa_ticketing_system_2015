#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int buyTicket(Account currentUser){
	
	//Variables
	string sellerName, eventName, purchase;
	int nOfTickets = -1, bought = -1;
	float pricePerTicket = -1;

	if (!itIsAdmin(currentUser) && (currentUser.type != BUYER && currentUser.type != FULL )){			//Check if the user has privilege
		cout << "Error: Not Authorised to buy tickets!";												//If not, tell the user
		bought = 0;																						//And cancel the transaction
	}
	else{																								//If the user has privilege
		cout << "Event Title:";																			//Get the event title
		cin >> eventName;

		cout << "Seller Username:";
		cin >> sellerName;

		cout << "Number of Tickets to Buy:";
		cin >> nOfTickets;

		//Get the tickets info

		cout << endl << "Event name:\t\t" << eventName << endl; 
		cout << "Seller:\t\t\t" << sellerName << endl;
		cout << "N. Of Tickets:\t\t" << nOfTickets << endl; 
		cout << "Price per Ticket:\t$ " << pricePerTicket << endl;
		cout << "Total Price:\t\t$ " << nOfTickets*pricePerTicket << endl;
		cout << endl << "Would you like to confirm the purchase? (yes/no)" << endl;
		cin >> purchase;

		if (purchase.compare("yes") == 0)
		{
			//Do the magic here
			cout << "Transaction successfully complete!";
			bought = 1;
		}
		else{
			cout << "Transaction canceled!";
			bought = 0;
		}
	}

	return bought;
}