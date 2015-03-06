using namespace std;
#include <string>

//For writing to the DailyTransactions.txt files
const string LOG_CREATE_TRANSACTIONCODE = "01";
const string LOG_DELETE_TRANSACTIONCODE = "02";
const string LOG_ADD_CREDIT_TRANSACTIONCODE = "06";
const string LOG_END_OF_SESSION_TRANSACTIONCODE = "00";
const string LOG_REFUND_TRANSACTIONCODE = "05";
const string LOG_SELL_TRANSACTIONCODE = "03";
const string LOG_BUY_TRANSACTIONCODE = "04";
const int TICKETS_LOG_SIZE = 3;
const int TICKETS_PRICE_SIZE = 6;
const int CREDIT_FLOAT_SIZE = 9;
const int BUYERNAME_SIZE = 15;
const int SELLERNAME_SIZE = 15;
const int EVENT_NAME_SIZE = 19;
