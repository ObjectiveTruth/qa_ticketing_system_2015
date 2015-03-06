#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/*
	TODO
		Constrains
*/


int sellTicket(Account currentUser){

	//Variables
	string sellerName, eventName;
	int nOfTickets = -1, putToSell = -1;
	float pricePerTicket = -1;

	if (!itIsAdmin(currentUser) && (currentUser.type != SELLER && currentUser.type != FULL)){			//Check if the user has privilege
		cout << "Error: Not Authorised to buy tickets!";												//If not, tell the user
		putToSell = 0;																					//And cancel the transaction
	}
	else{																								//If the user has privilege
		cout << "Event Title:";																			//Get the event title
		cin.ignore();													//Ignore the '\n'
		getline(cin, eventName);										//And get the hole line
		
		sellerName = currentUser.username;

		cout << "Number of Tickets to Sell:";
		cin >> nOfTickets;

		cout << "Price per Ticket:";
		cin >> pricePerTicket;

		//Add tickets
		Tickets ticket = Tickets();
		ticket.add(eventName, sellerName, nOfTickets, pricePerTicket);

		//Add sell log in the daily transaction file
		DailyTransactions DT;
		DT.logSell(eventName, sellerName, nOfTickets, pricePerTicket);

		/*
			Need to add the constrains here
		*/
		

		cout << endl << "The tickets now has been posted to sell!" << endl;
		cout << "Please note that the tickets will just appear to sell when you logout";
		putToSell = 1;
	}

	return putToSell;
}