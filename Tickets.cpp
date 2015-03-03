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

using namespace std;

//getInfo searches the database for the numeber of tickets a seller
//has for an event.
//add - adds the numeber of tickets to the seller's account
//remove - removes the tickets from a seller's account

#define EVENTNAME_SIZE 19
#define SELLERNAME_SIZE 13
#define TICKET_NUM_SIZE 3

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
string readFile1(){
	std::ifstream t("tickets.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return str;
}

//Adds the number of tickets specified for a particular event being sold by 
//sellerName. Returns 1 if successful, 0 if unsuccessful

int Tickets::add(string eventName, string sellerName, int addTickets, double price){
	string readFromFile = readFile1();
	stringstream outputStream;
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    string previousLine;
    int returnValue = 0;
    while (getline(fileInputStream, line)) {
        previousLine = line;
        suspect = trimLeftRightWhiteSpace(line.substr(0,EVENTNAME_SIZE));
        if (eventName.compare(suspect) == 0){
            string sellerNameSuspect = line.substr(EVENTNAME_SIZE + 1, SELLERNAME_SIZE);
            if (sellerName.compare(sellerNameSuspect) == 0){
                returnValue = 1;
                //extracts the number of tickets portion
                string ticketsAlpha =line.substr(EVENTNAME_SIZE + SELLERNAME_SIZE + 2, 
                        TICKET_NUM_SIZE); 
                int oldTicketsNumber = atoi(ticketsAlpha.c_str());
                //adds the old value with the new value
                int finalTicketsNumber = oldTicketsNumber + addTickets;
                //formats it nicely with leading 0s to fill 3 spaces
                stringstream ss;
                ss << setw(3) << setfill('0') << finalTicketsNumber;
                //replaces the line with new value
                line.replace(EVENTNAME_SIZE + SELLERNAME_SIZE +2, TICKET_NUM_SIZE , 
                        ss.str());

                //ADD LOGIC HERE TO UPDAET THE FIELDS
            }
        }
        outputStream << line;
        if(line.compare("END") != 0){
            outputStream << endl;
        }
    }
    if(previousLine.compare("END") != 0){
        outputStream << "END";
    }
	ofstream myfile;
	myfile.open("tickets.txt");
	myfile << outputStream.str();
	myfile.close();
    return returnValue;
}

//Removes the number of tickets sold for a sellerName and eventName
//Returns 1 if successful, 0 if unsuccesful
int Tickets::remove(string eventName, string sellerName, int removeTickets, double price){
	string readFromFile = readFile1();
	stringstream outputStream;
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    string previousLine;
    int returnValue = 0;
    while (getline(fileInputStream, line)) {
        previousLine = line;
        suspect = trimLeftRightWhiteSpace(line.substr(0,EVENTNAME_SIZE));
        if (eventName.compare(suspect) == 0){
            string sellerNameSuspect = line.substr(EVENTNAME_SIZE + 1, SELLERNAME_SIZE);
            if (sellerName.compare(sellerNameSuspect) == 0){
                returnValue = 1;
                //extracts the number of tickets portion
                string ticketsAlpha =line.substr(EVENTNAME_SIZE + SELLERNAME_SIZE + 2, 
                        TICKET_NUM_SIZE); 
                int oldTicketsNumber = atoi(ticketsAlpha.c_str());
                //adds the old value with the new value
                int finalTicketsNumber = oldTicketsNumber - removeTickets;
                //formats it nicely with leading 0s to fill 3 spaces
                stringstream ss;
                ss << setw(3) << setfill('0') << finalTicketsNumber;
                //replaces the line with new value
                line.replace(EVENTNAME_SIZE + SELLERNAME_SIZE +2, TICKET_NUM_SIZE , 
                        ss.str());

                //ADD LOGIC HERE TO UPDAET THE FIELDS
            }
        }
        outputStream << line;
        if(line.compare("END") != 0){
            outputStream << endl;
        }
    }
    if(previousLine.compare("END") != 0){
        outputStream << "END";
    }
	ofstream myfile;
	myfile.open("tickets.txt");
	myfile << outputStream.str();
	myfile.close();
    return returnValue;
}

//Returns the number of tickets left for a particular event and seller
//Returns 1 if successful, 0 if unsuccesful
int Tickets::getInfo(string eventName, string sellerName){
	string line;
	ifstream myfile("tickets.txt");
    int returnTickets = -1;
    string suspect;

	if (myfile.is_open()){
		while (getline(myfile, line)){
            suspect = trimLeftRightWhiteSpace(line.substr(0,EVENTNAME_SIZE));
            

			if (eventName.compare(suspect) == 0){
                string sellerNameSuspect = line.substr(EVENTNAME_SIZE + 1, SELLERNAME_SIZE);
                if (sellerName.compare(sellerNameSuspect) == 0){
                    string ticketsAlpha =line.substr(EVENTNAME_SIZE + SELLERNAME_SIZE + 2, 
                            TICKET_NUM_SIZE); 
                    returnTickets = atoi(ticketsAlpha.c_str());
                }
                return returnTickets;
			}
		}
		myfile.close();
	}
	return returnTickets;


}

//int main(){
//
//    Tickets tickets = Tickets();
//    cout << "return : " << tickets.getInfo("Reebok one", "Peter Griffin") << endl;
//    tickets.add("Reebok one", "Peter Griffin", 1, 2.0);
//    tickets.remove("Reebok one", "Peter Griffin", 1, 2.0);
//
//    return 0;
//}
