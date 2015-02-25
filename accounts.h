using namespace std;
#include <string>

class Account{
    public:
        int type;
        double credit;
};

class Accounts{
    public:
        Account get(string);
        int update(string, double);
        int create(string, int, double);
        int remove(string);

};

