#ifndef VAR_H
#define VAR_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
using namespace std;

class Var{
    protected:
        // string svalue = "";
        // long nvalue = 0;
        // double rvalue = 0.0;
        // char cvalue[1];

    public:
        Var();
        // template<typename T> T get() const;
        
        virtual void initialize(stringstream &ss)=0;
        virtual Var* clone(stringstream &ss)=0;
        virtual ~Var();
};
#endif