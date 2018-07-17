#include "var.h"
class CharVar: public Var{
    protected:
        char vchar; // A variable of type char to hold the value char
       // string varcname = ""; // A string to hold the name of the char variable
       mutex mu;
    public:
        CharVar(); // Constructor
        char getvalue(bool check_th = 0);
        void setvalue(char x, bool check_th = 0)
        {
            if(check_th == 1) lock_guard<std::mutex> guard(mu);
            vchar = x;
        }
        void initialize(stringstream &ss); // A method that initializes the object from a stringstream
        virtual Var* clone(stringstream &ss); // Factory Clone method
        virtual ~CharVar(); // Destructor
};