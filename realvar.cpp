#include "realvar.h"

RealVar::RealVar(){}
void RealVar::initialize(stringstream &ss){
    //varrname = p_name; // assign the given variable name to varrname holder
    string str = ""; // a string to hold the rest of parsed line
    getline(ss,str,','); // parse the line to the first comma to get the value
    vreal = stof(str); // convert the value from string to float
    //cout<<varrname<<' '<<vreal<<endl;
}
Var* RealVar::clone(stringstream &ss){
    RealVar * realvar = new RealVar();
    realvar->initialize(ss);
    return realvar;
}
double RealVar::getvalue(bool check_th)
{
    if(check_th == 1) lock_guard<std::mutex> guard(mu);
    return vreal;
}
void RealVar::setvalue(double x,bool check_th)
{
    if(check_th == 1) lock_guard<std::mutex> guard(mu);
    vreal = x;
}
RealVar::~RealVar(){}