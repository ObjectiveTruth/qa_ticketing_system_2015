#include <string.h>
#include <sstream>
#include <streambuf>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "Tickets.h"
#include "constants.cpp"

using namespace std;

//getInfo searches the database for the numeber of tickets a seller
//has for an event.
//add - adds the numeber of tickets to the seller's account
//remove - removes the tickets from a seller's account


//Helper function to trim the white space from a string starting from 
//the left and from the right
//Example "    Hello World    "
//output: "Hello World"
string trimLeftRightWhiteSpace(string suspect){
    suspect.erase(suspect.find_last_not_of(" \n\r\t")+1);
    size_t startpos = suspect.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        suspect = suspect.substr( startpos );
    }
    return suspect;
}

//Helper Function for all functions in this file
//Reads the database and converts it to a string for easy
//manipulation
string ReadFileTickets(){
	std::ifstream t("tickets.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return str;
}

//Adds the number of tickets specified for a particular event being sold by 
//If the record exists, the price argument is ignored
//sellerName. Returns 1 if successful, 0 if unsuccessful
int Tickets::add(string eventName, string sellerName, int addTickets, double price){
	string readFromFile = ReadFileTickets();
	stringstream outputStream;
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    string previousLine;
    int returnValue = 0;
    while (getline(fileInputStream, line)) {
        previousLine = line;
        suspect = trimLeftRightWhiteSpace(line.substr(0,EVENT_NAME_SIZE));
        if (eventName.compare(suspect) == 0){
            string sellerNameSuspect = 
                trimLeftRightWhiteSpace(line.substr(EVENT_NAME_SIZE, SELLER_NAME_SIZE));
            if (sellerName.compare(sellerNameSuspect) == 0){
                cout << "found here" << endl;

                returnValue = 1;
                //extracts the number of tickets portion
                //2 is the total spaces so far
                string ticketsAlpha =line.substr(EVENT_NAME_SIZE + SELLER_NAME_SIZE + 2, 
                        TICKET_NUM_SIZE); 
                int oldTicketsNumber = atoi(ticketsAlpha.c_str());
                //adds the old value with the new value
                int finalTicketsNumber = oldTicketsNumber + addTickets;
                //formats it nicely with leading 0s to fill 3 spaces
                stringstream ss;
                ss << setw(3) << setfill('0') << finalTicketsNumber;
                //replaces the line with new value
                line.replace(EVENT_NAME_SIZE + SELLER_NAME_SIZE +2, TICKET_NUM_SIZE , 
                        ss.str());
            }
        }
        if(line.compare("END") != 0){
            outputStream << line << endl;
        }
    }
    //If the inputted entry doesn't exist in the db, create it
    if(returnValue == 0){
        stringstream ss;
        ss << setw(EVENT_NAME_SIZE) << setfill(' ') << left << eventName << ' ';
		ss << setw(SELLER_NAME_SIZE) << setfill(' ') << left << sellerName << ' ';
        ss << setw(TICKET_NUM_SIZE) << setfill('0') << right << addTickets << ' ';
        ss << setw(TICKETS_PRICE_SIZE) << setfill('0') << right << price * 100 << endl;
        outputStream << ss.str();
    }
    outputStream << "END";
	ofstream myfile;
	myfile.open("tickets.txt");
	myfile << outputStream.str();
	myfile.close();
    return returnValue;
}

//Removes the number of tickets sold for a sellerName and eventName
//Returns 1 if successful, 0 if unsuccesful
int Tickets::remove(string eventName, string sellerName, int removeTickets){
	string readFromFile = ReadFileTickets();
	stringstream outputStream;
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    string previousLine;
    int finalTicketsNumber = 0;
    int returnValue = 0;
    while (getline(fileInputStream, line)) {
        previousLine = line;
        suspect = trimLeftRightWhiteSpace(line.substr(0,EVENT_NAME_SIZE));
        if (eventName.compare(suspect) == 0){
            string sellerNameSuspect = 
                trimLeftRightWhiteSpace(line.substr(EVENT_NAME_SIZE, SELLER_NAME_SIZE));
            if (sellerName.compare(sellerNameSuspect) == 0){
                returnValue = 1;
                //extracts the number of tickets portion
                //2 is the total spaces so far
                string ticketsAlpha =line.substr(EVENT_NAME_SIZE + SELLER_NAME_SIZE + 2, 
                        TICKET_NUM_SIZE); 
                int oldTicketsNumber = atoi(ticketsAlpha.c_str());
                //adds the old value with the new value
                finalTicketsNumber = oldTicketsNumber - removeTickets;
                //formats it nicely with leading 0s to fill 3 spaces
                stringstream ss;
                ss << setw(3) << setfill('0') << finalTicketsNumber;
                //replaces the line with new value
                line.replace(EVENT_NAME_SIZE + SELLER_NAME_SIZE +2, TICKET_NUM_SIZE , 
                        ss.str());
            }
        }
        if(line.compare("END") != 0 && finalTicketsNumber > 0){
            outputStream << line << endl;
        }
    }
    outputStream << "END";
	ofstream myfile;
	myfile.open("tickets.txt");
	myfile << outputStream.str();
	myfile.close();
    return returnValue;
}

//Returns a Ticket Object which contains the information needed
//If record doesn't exist, a ticket object will be returned with 
//.ticketsleft = -1, .price = -1, and eventName and sellerName
//set to an empty string
Ticket Tickets::getInfo(string eventName, string sellerName){
	string line;
	ifstream myfile("tickets.txt");
    Ticket returnTicket = Ticket();
    returnTicket.ticketsLeft = -1;
    returnTicket.price = -1.0;
    returnTicket.eventName = "";
    returnTicket.sellerName = "";
    string suspect;

	if (myfile.is_open()){
		while (getline(myfile, line)){
            suspect = trimLeftRightWhiteSpace(line.substr(0,EVENT_NAME_SIZE));
            

			if (eventName.compare(suspect) == 0){
				string sellerNameSuspect = trimLeftRightWhiteSpace(line.substr(EVENT_NAME_SIZE + 1, SELLER_NAME_SIZE));
                if (sellerName.compare(sellerNameSuspect) == 0){
                    string ticketsAlpha =line.substr(EVENT_NAME_SIZE + SELLER_NAME_SIZE + 2, 
                            TICKET_NUM_SIZE); 
                    string priceAlpha = line.substr(EVENT_NAME_SIZE + SELLER_NAME_SIZE
                            + TICKET_NUM_SIZE + 3, TICKETS_PRICE_SIZE);

                    returnTicket.ticketsLeft = atoi(ticketsAlpha.c_str());
                    returnTicket.eventName = suspect;
                    returnTicket.sellerName = sellerNameSuspect;
                    returnTicket.price = atof(priceAlpha.c_str())/100;
                    //cout << "TicketsLeft:" << returnTicket.ticketsLeft << endl;
                    //cout << "EventName:" << returnTicket.eventName << endl;
                    //cout << "SellerName:" << returnTicket.sellerName << endl;
                    //cout << "Price:" << returnTicket.price << endl;
                    return returnTicket;
                }
			}
		}
		myfile.close();
	}
	return returnTicket;


}

//int main(){
//
//    Tickets tickets = Tickets();
//    //tickets.add("Game of Thrones", "Peter Griffin", 1, 2.48);
//    tickets.remove("Game of Thrones", "Peter Griffin", 1);
//
//    return 0;
//}
