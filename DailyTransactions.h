using namespace std;
#include <string>
//DailyTransactions is a helper class for the DB
//Gives helper functions for writing logs
class DailyTransactions{
    public:
        int logCreate(string, int, double);
        int logDelete(string, int, double);
        int logAddCredit(string, int, double);
        int logEndOfSession(string, int, double);
        int logRefund(string, string, double);
        int logSell(string, string, int, double); 
        int logBuy(string, string, int, double); 
};

