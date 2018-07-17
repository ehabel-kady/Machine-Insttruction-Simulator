#include "var.h"

class RealVar: public Var{
    protected:
        double vreal = 0.0; // double to hold the decimal value
        //string varrname = ""; // A string to hold the real varialble name 
        mutex mu;
    public:
        RealVar(); // constructor
        double getvalue(bool check_th = 0);
        void setvalue(double x, bool check_th = 0);
        void initialize(stringstream &ss); // A method that initializes the object from a stringstream
        virtual Var* clone(stringstream &ss); // Factory Clone method
        virtual ~RealVar(); // Destructor
};