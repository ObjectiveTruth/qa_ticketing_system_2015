#include "stdafx.h"
#include "Transactions.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

/*
	TODO
		Check the maximum size for Event Name
		Check the maximum size for Seller Name
*/

int buyTicket(Account currentUser){
	
	//Variables
	Ticket ticket;
	string sellerName, eventName, purchase;
	int nOfTickets = -1, bought = -1;

	if (!itIsAdmin(currentUser) && (currentUser.type != BUYER && currentUser.type != FULL )){			//Check if the user has privilege
		cout << "Error: Not Authorised to buy tickets!";												//If not, tell the user
		bought = 0;																						//And cancel the transaction
	}
	else{																								//If the user has privilege
		cout << "Event Title:";																			//Get the event title
		cin.ignore();													//Ignore the '\n'
		getline(cin, eventName);										//And get the hole line

		cout << "Seller Username:";																		//Get the seller name
		cin.clear();
		getline(cin, sellerName);

		cout << "Number of Tickets to Buy:";															//And the number of tickets
		cin >> nOfTickets;

		if (nOfTickets > 4)																				//If this number is > 4
		{
			cout << "Error: The maximum number of tickets avaiable to buy at one time is 4";			//Print the error
			bought = 0;																					//And cancel it
		}
		else{

			//Get the tickets info
			Tickets tickets = Tickets();
			ticket = tickets.getInfo(eventName, sellerName);

			cout << eventName << endl;
			cout << sellerName << endl;

			if (ticket.eventName.empty()){																//If the eventName after get the info from the file is empty
				cout << "Sorry, we can not find what you are looking for!" << endl;						//Means that we cannot find it
				cout << "The event or seller does not exist";											//Because event or seller does not exist
				bought = 0;
			}
			else if (ticket.ticketsLeft < nOfTickets)													//Also we check if there is enough tickets
			{
				cout << "Sorry, but the seller does not have enought tickets avaiable. The seller has just " << ticket.ticketsLeft << " tickets";
				bought = 0;
			}
			else					//If we are right, everyting is okay, so let's seal the deal
			{
																									//Show all information
				cout << endl << "Event name:\t\t" << ticket.eventName << endl;
				cout << "Seller:\t\t\t" << ticket.sellerName << endl;
				cout << "N. Of Tickets:\t\t" << nOfTickets << endl;
				cout << "Price per Ticket:\t$ " << ticket.price << endl;
				cout << "Total Price:\t\t$ " << nOfTickets*ticket.price << endl;
				cout << endl << "Would you like to confirm the purchase? (yes/no)" << endl;
				cin >> purchase;																	//And ask for confirmation

				if (purchase.compare("yes") == 0)													//If yes
				{	
					if (currentUser.credit < nOfTickets*ticket.price)
					{
						cout << "Ops! Perhaps you don't have enough money. Please refuel yourself first!";
					}
					else
					{
						//Variables to seal the deal
						DailyTransactions DT;
						Handle handler;

						tickets.remove(ticket.eventName, ticket.sellerName, nOfTickets);					//Remove the tickets from the file
						makeTransfer(sellerName, currentUser.username, nOfTickets*ticket.price);			//Transfer the money
						
						DT.logBuy(ticket.eventName, ticket.sellerName, nOfTickets, ticket.price);			//Add buy log into the daily transaction file
						cout << "Transaction successfully complete!";
						bought = 1;
					}
				}
				else{																				//If no
					cout << "Transaction canceled!";													//Cancel transaction
					bought = 0;
				}
			}
		}
	}

	return bought;
}