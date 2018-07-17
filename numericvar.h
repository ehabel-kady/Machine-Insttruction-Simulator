#include "var.h"

class NumericVar: public Var{
    protected:
        long vnumeric = 0; // long variable to hold the value of the numeric varaible
       // string varnname = ""; // A string varialble to hold the name of the numeric variable 
       mutex mu;
    public:
        NumericVar(); // constructor
        long getvalue(bool check_th = 0);
        void setvalue(long x, bool check_th = 0)
        {
            if(check_th == 1) lock_guard<std::mutex> guard(mu);
            vnumeric = x;}
        void initialize(stringstream &ss); // A method that initializes the object from a stringstream
        virtual Var* clone(stringstream &ss); // Factory Clone method
        virtual ~NumericVar(); // Destructor    
};