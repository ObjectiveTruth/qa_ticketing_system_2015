#include <string.h>
#include <sstream>
#include <streambuf>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "DailyTransactions.h"
#include "constants.cpp"

using namespace std;


string ReadDailyTransactionsFile(){
	std::ifstream t("DailyTransactions.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return str;
}

//Adds the number of tickets specified for a particular event being sold by 
//sellerName. Returns 1 if successful, 0 if unsuccessful
int addToEndOfDailyTransactions(string lastLine){
	ofstream myfile;
    string oldFile = ReadDailyTransactionsFile();
	myfile.open("DailyTransactions.txt");
    cout << ReadDailyTransactionsFile();
	myfile << oldFile << lastLine;
	myfile.close();
    return 1;
}

string userTypeIntToStringConverter(int userType){
    switch(userType){
        case 1 : 
            return "AA";
        case 2 :
            return "BS";
        case 3 :
            return "SS";
        case 4 :
            return "FS";
    }
}

int DailyTransactions::logCreate(string buyerName, int userType, double availableCredit){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_CREATE_TRANSACTIONCODE << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << buyerName << ' ';
    ss << userTypeIntToStringConverter(userType) << ' ';
    ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << availableCredit * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

int DailyTransactions::logDelete(string buyerName, int userType, double availableCredit){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_DELETE_TRANSACTIONCODE << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << buyerName << ' ';
    ss << userTypeIntToStringConverter(userType) << ' ';
    ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << availableCredit * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

int DailyTransactions::logAddCredit(string buyerName, int userType, double availableCredit){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_ADD_CREDIT_TRANSACTIONCODE << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << buyerName << ' ';
    ss << userTypeIntToStringConverter(userType) << ' ';
    ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << availableCredit * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

int DailyTransactions::logEndOfSession(string buyerName, int userType, double availableCredit){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_END_OF_SESSION_TRANSACTIONCODE << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << buyerName << ' ';
    ss << userTypeIntToStringConverter(userType) << ' ';
    ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << availableCredit * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

int DailyTransactions::logRefund(string buyerName, string sellerName, double availableCredit){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_REFUND_TRANSACTIONCODE << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << buyerName << ' ';
    ss << setw(BUYERNAME_SIZE) << left << setfill(' ') << sellerName << ' ';
    ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << availableCredit * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

int DailyTransactions::logSell(string eventName, string sellerName,int tickets, double ticketPrice){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_SELL_TRANSACTIONCODE << ' ';
    ss << setw(EVENT_NAME_SIZE) << left << setfill(' ') << eventName << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << sellerName << ' ';
    ss << setw(TICKETS_LOG_SIZE) << setfill('0') << right << tickets << ' ';
    ss << setw(TICKETS_PRICE_SIZE) << setfill('0') << right << ticketPrice * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

int DailyTransactions::logBuy(string eventName, string sellerName,int tickets, double ticketPrice){
    int returnValue = 1;
    stringstream ss;
    ss << LOG_BUY_TRANSACTIONCODE << ' ';
    ss << setw(EVENT_NAME_SIZE) << left << setfill(' ') << eventName << ' ';
    ss << setw(SELLER_NAME_SIZE) << left << setfill(' ') << sellerName << ' ';
    ss << setw(TICKETS_LOG_SIZE) << setfill('0') << right << tickets << ' ';
    ss << setw(TICKETS_PRICE_SIZE) << setfill('0') << right << ticketPrice * 100 << endl;
    addToEndOfDailyTransactions(ss.str());
    return returnValue;
}

//int main(){
//    DailyTransactions dailyTransactions = DailyTransactions();
//    dailyTransactions.logCreate("username", 2, 29.73);
//    dailyTransactions.logDelete("username", 4, 30.53);
//    dailyTransactions.logAddCredit("username", 3, 100.00);
//    dailyTransactions.logRefund("buyer", "seller", 28.38);
//    dailyTransactions.logSell("EVENT_NAME", "seller", 18, 60.13);
//    dailyTransactions.logBuy("EVENT_NAME", "seller", 82, 134);
//
//    return 0;
//}
