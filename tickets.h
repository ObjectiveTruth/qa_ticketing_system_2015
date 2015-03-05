using namespace std;
#include <string>
//Ticket is a case class that holds info about the tickets returned
//contains, ticketsLeft, price, eventName and sellerName

class Ticket{
    public:
        int ticketsLeft;
        double price;
        string eventName;
        string sellerName;
};

//Tickets is a database helper class for vieweing
//adding and removing tickets from tickets.txt
class Tickets{
    public:
        Ticket getInfo(string, string);
        int add(string, string, int, double);
        int remove(string, string, int);
};

