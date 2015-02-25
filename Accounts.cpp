#include <string.h>
#include <sstream>
#include <streambuf>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"

using namespace std;

//Get searches the database for the occurance of a username
//username must be a string. 
//Returns an Account object with the properites of that user if they exist
//If username doens't exist, all values of the Account object will be -1
Account Accounts::get(string search){
    string line;
    ifstream myfile ("accounts.txt");

    Account newAccount = Account();
    newAccount.type = -1;
    newAccount.credit = -1;

    if (myfile.is_open()){
        while ( getline (myfile,line) ){
          char str[1024];
          strcpy(str, line.c_str());
          char * pch;
          pch = strtok (str,",");
          std::string pchConvert(pch);
          if(search.compare(pchConvert) == 0){
                //cout << "found it!" << endl;
                newAccount = Account();

              pch = strtok (NULL,",");
              newAccount.type = atoi(pch);

              pch = strtok (NULL,",");
              newAccount.credit = atof(pch);
              return newAccount;
          }
        }
        myfile.close();
    }
    return newAccount;
}

//Helper Function for all functions in this file
//Reads the database and converts it to a string for easy
//manipulation
string readFile(){
    std::ifstream t("accounts.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}

//Updates the user's entry in the database with the new
//credit amount
//Returns 0 if user is not found, 
//Returns 1 if user is found.
int Accounts::update(string username, double credit){
    string readFromFile = readFile();
    std::size_t found = readFromFile.find(username);
    stringstream ss;
    ss << credit;

    if(found!=std::string::npos){
        std::size_t firstFound = readFromFile.find(',', found);
        std::size_t secondFound = readFromFile.find(',', firstFound+1);
        std::size_t foundEnd = readFromFile.find('\n', found+1);
        readFromFile.replace(secondFound+1,foundEnd-secondFound-1 ,ss.str() );
    }  
    else{
        return 0;
    }
    ofstream myfile;
    myfile.open ("accounts.txt");
    myfile << readFromFile;
    myfile.close();

    return 1;
}

//Creates a new entry in the databse with the values of
//uesrname, type and starting credit
//returns 0 if fails
//returns 1 if succesful
int Accounts::create(string username, int type, double credit){
    std::ofstream out;
    out.open("accounts.txt", std::ios::app); 
    out << username << "," << type << ","<< credit << endl; 
    return 1;
}

//Removes an entry from the databse with the username specified
//returns 0 if the entry is not found
//returns 1 if the entry is found
int Accounts::remove(string username){
    string readFromFile = readFile();
    std::size_t found = readFromFile.find(username);
    if(found!=std::string::npos){
        std::size_t foundEnd = readFromFile.find('\n', found);
        readFromFile.replace(found, foundEnd+1, "");
    }  
    else{
        return 0;
    }
    ofstream myfile;
    myfile.open ("accounts.txt");
    myfile << readFromFile;
    myfile.close();

    return 1;
}
