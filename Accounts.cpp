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

string readFile(){
    std::ifstream t("accounts.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}

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
        //cout <<  "found it! at pos: "<< found << " and position: " <<foundEnd<<  " credit " <<credit <<endl;
    }  
    else{
        //cout << "not found!" << endl;
        return 0;
    }
    //cout << readFromFile << endl;
    ofstream myfile;
    myfile.open ("accounts.txt");
    myfile << readFromFile;
    myfile.close();

    return 1;
}

int Accounts::create(string username, int type, double credit){
    std::ofstream out;
    out.open("accounts.txt", std::ios::app); 
    out << username << "," << type << ","<< credit << endl; 
    return 1;
}

int Accounts::remove(string username){
    string readFromFile = readFile();
    std::size_t found = readFromFile.find(username);
    if(found!=std::string::npos){
        std::size_t foundEnd = readFromFile.find('\n', found);
        readFromFile.replace(found, foundEnd+1, "");
        //cout <<  "found it! at pos: "<< found << " and position: " <<foundEnd<<endl;
    }  
    else{
        //cout << "not found!" << endl;
        return 0;
    }
    ofstream myfile;
    myfile.open ("accounts.txt");
    myfile << readFromFile;
    myfile.close();

    return 1;
}

//int main(int argc, char* arg[]){
 //   Accounts accounts = Accounts(); 
  //  Account foundAccount = accounts.get("jose");
    //accounts.create("yes", 2, 52.12);
    //accounts.create("shaine", 3, 50.25);
    //accounts.remove("Arun");
   // accounts.update("jose", 12.25);
//    cout << "type is :" << foundAccount.type << endl;
//    cout << "cred it :" << foundAccount.credit <<endl;
//    return 0;
//}
