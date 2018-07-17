#include "var.h"
#include <cstring>
class StringVar: public Var{
    protected:
        short int length=0; // size of the array
        char* vstring; // a pointer to the array
        //string varsname; // string to hold the string variable name
        mutex mu;
    public:
        StringVar(); // Defualt Constructor
        char* getvalue(bool check_th = 0);
        void setvalue(string x, bool check_th=0);
        void initialize(stringstream &ss); // A method that initializes the object from a stringstream
        virtual Var* clone(stringstream &ss); // Factory Clone method
        virtual ~StringVar(); // Destructor
};