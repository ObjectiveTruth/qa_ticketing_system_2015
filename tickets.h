using namespace std;
#include <string>
//Tickets is a database helper class for vieweing
//adding and removing tickets from tickets.txt

class Tickets{
    public:
        int getInfo(string, string);
        int add(string, string, int, double);
        int remove(string, string, int, double);
};

