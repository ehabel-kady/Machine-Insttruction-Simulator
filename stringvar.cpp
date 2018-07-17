#include "stringvar.h"

StringVar::StringVar(){}
//StringVar::StringVar(char* p_vname, short int len): vname(p_vname),length(len),Var(){}
void StringVar::initialize(stringstream &ss)
{
   // varsname = n; // assign the given variable name to varname
    string str = ""; // a string to hold the rest of parsed line
    getline(ss,str,','); // parse the line to the first comma to get the size of the array
    length = stoi(str); // convert the size of array from string to integer
    getline(ss,str,','); // parse the line to the second comma to get the string
    vstring = new char[length]; // initialize the array dynamacilly with the given size
    str = str.substr(3,str.size()-6); // remove the double quote from the string
    strcpy(vstring,str.c_str()); // assign the string to the array of char
    // test cases
    // for(int i = 0; i<strlen(vstring); i++){
    //     cout<<vstring[i];
    // }
    // cout<<endl;
}

Var * StringVar::clone(stringstream & ss){
    StringVar * stringvar = new StringVar();
    stringvar->initialize(ss);
    return stringvar;
}

void StringVar::setvalue(string x, bool check_th)
{
    if(check_th == 1) lock_guard<std::mutex> guard(mu);
    strcpy(vstring,x.c_str());
}

char* StringVar::getvalue(bool check_th)
{
    if(check_th == 1) lock_guard<std::mutex> guard(mu);
    return vstring;
}
StringVar::~StringVar(){}
