#include <string.h>
#include <sstream>
#include <iomanip>
#include <streambuf>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"
#include "constants.cpp"


using namespace std;

//Helper Function for all functions in this file
//Reads the database and converts it to a string for easy
//manipulation
string ReadFileAccounts(){
	std::ifstream t("accounts.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return str;
}

//Helper function to convert a userType string to its corresponding Int code
//See Ticket.cpp for constants values
int userTypeStringToIntConverter(string userString){
    if(userString.compare("AA") == 0){
        return 1;
    }else if(userString.compare("BS") == 0){
        return 2;
    }else if(userString.compare("SS") == 0){
        return 3;
    }else if(userString.compare("FS") == 0){
        return 4;
    }else{
        return -1;
    }
}

//Helper function to trim the white space from a string starting from 
//the left and from the right
//Example "    Hello World    "
//output: "Hello World"
string TrimLeftRightWhiteSpaceAccounts(string suspect){
    suspect.erase(suspect.find_last_not_of(" \n\r\t")+1);
    size_t startpos = suspect.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        suspect = suspect.substr( startpos );
    }
    return suspect;
}

//Helper Function that turns ints to the appropriate String representation in the file
string UserTypeIntToStringConverterAccounts(int userType){
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

//Get searches the database for the occurance of a username
//username must be a string. 
//Returns an Account object with the properites of that user if they exist
//If username doens't exist, all values of the Account object will be -1
Account Accounts::get(string search){
	string readFromFile = ReadFileAccounts();
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    //Create the empty Account object to be filled with real data
	Account newAccount = Account();
	newAccount.type = -1;
	newAccount.credit = -1;
    newAccount.username = "";
    //0 is a fail so we initialize
    int returnValue = 0;
    //iterate through file until search matches
    while (getline(fileInputStream, line)) {
        suspect = TrimLeftRightWhiteSpaceAccounts(line.substr(0,USERNAME_SIZE));
        if (search.compare(suspect) == 0){
            //found it, so update return value 
            returnValue = 1;
            newAccount.username = suspect;
            newAccount.type = userTypeStringToIntConverter(line.substr(USERNAME_SIZE + 1, USER_TYPE_SIZE));
            string creditAlphanumeric = line.substr(USERNAME_SIZE + USER_TYPE_SIZE + 2, CREDIT_FLOAT_SIZE);
            //atof converts the substring to float. /100 to normalize 
            newAccount.credit = atof(creditAlphanumeric.c_str())/100;
        }
    }
    return newAccount;
}

//Updates the user's entry in the database with the new
//credit amount
//Returns 0 if user is not found, 
//Returns 1 if user is found.
int Accounts::update(string username, double credit){
    string END = "END";
	string readFromFile = ReadFileAccounts();
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    //0 is a fail so we initialize
    int returnValue = 0;
    //open the outputfile to push each line to
	ofstream myfile;
	myfile.open("accounts.txt");
    //iterate through file until search matches then update
    while (getline(fileInputStream, line)) {
        suspect = TrimLeftRightWhiteSpaceAccounts(line.substr(0,USERNAME_SIZE));
        if (username.compare(suspect) == 0){
            //found it, so update return value
            returnValue = 1;
            stringstream ss;
            ss << line.substr(0, USERNAME_SIZE + USER_TYPE_SIZE + 2);
            ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << credit * 100;
            line = ss.str();
        }
        //if the line doesn't start with END
        if(line.compare(0, 3, END) != 0){
            myfile << line << endl;
        }
    }
    myfile << END;
	
	//Variables for the log
	Accounts acc;
	Account account;

	myfile.close();

	account = acc.get(username);
	//DT.logAddCredit(account.username, account.type, account.credit);		//Log the addcredit in the daily transaction file

	return returnValue;
}

//Creates a new entry in the databse with the values of
//uesrname, type and starting credit
//returns 0 if fails
//returns 1 if succesful
int Accounts::create(string username, int type, double credit){
    string END = "END";
	string readFromFile = ReadFileAccounts();
    istringstream fileInputStream(readFromFile);
    string line;
    //0 is a fail so we initialize
    int returnValue = 1;
    //open the outputfile to push each line to
	ofstream myfile;
	myfile.open("accounts.txt");
    //iterate through file until search matches then update
    while (getline(fileInputStream, line)) {
        //if the line doesn't start with END
        if(line.compare(0, 3, END) != 0){
            myfile << line << endl;
        }
    }
    stringstream ss;
    ss << setw(USERNAME_SIZE) << left << setfill(' ') << username << ' ';
    ss << UserTypeIntToStringConverterAccounts(type) << ' ';
    ss << setw(CREDIT_FLOAT_SIZE) << setfill('0') << right << credit * 100 << endl;
    myfile << ss.str();
    myfile << END;
	myfile.close();
	//DT.logCreate(username, type, credit);							//Log the create in the daily transaction file
    return returnValue;
}

//Removes an entry from the databse with the username specified
//returns 0 if the entry is not found
//returns 1 if the entry is found
int Accounts::remove(string username){
    string END = "END";
	string readFromFile = ReadFileAccounts();
    istringstream fileInputStream(readFromFile);
    string line;    
    string suspect;
    //0 is a fail so we initialize
    int returnValue = 0;
    //open the outputfile to push each line to
	ofstream myfile;
	myfile.open("accounts.txt");
    //iterate through file until search matches then update
    while (getline(fileInputStream, line)) {
        suspect = TrimLeftRightWhiteSpaceAccounts(line.substr(0,USERNAME_SIZE));
        if (username.compare(suspect) == 0){
            //found it, so update return value
            returnValue = 1;
            line =  "";
        }
        //if the line doesn't start with END
        if(line.compare(0, 3, END) != 0){
            if(line.compare("") != 0){
                myfile << line << endl;
            }
        }
    }
    myfile << END;
	
	//Variables for the log
	Accounts acc;
	Account account;
	account = acc.get(username);
	myfile.close();

	//DT.logDelete(account.username,account.type,account.credit);		//Log the delete in the daily transaction file

	return returnValue;
}

int main(){
    Accounts accounts = Accounts();
    accounts.create("objectivetruth", 1, 100.34);
    Account me = accounts.get("me");
    cout << me.username << endl;
    cout << me.credit << endl;
    cout << me.type << endl;
    accounts.update("me", 200);
    return 0;

}
