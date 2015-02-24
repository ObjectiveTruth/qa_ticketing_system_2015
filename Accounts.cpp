#include <string.h>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

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

//int main(int argc, char* arg[]){
//
//
 //   Accounts accounts = Accounts(); 
  //  Account foundAccount = accounts.get("jose");
   // cout << "type is :" << foundAccount.type << endl;
    //cout << "cred it :" << foundAccount.credit <<endl;
//    return 0;
//}
