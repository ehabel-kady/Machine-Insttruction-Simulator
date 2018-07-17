#include "charvar.h"

CharVar::CharVar(){}
void CharVar::initialize(stringstream &ss){
    //varcname = p_name;
    string str = "";
    getline(ss, str, ',');
    vchar = str[3];
    //cout<<"variable name: "<<varcname<<' '<<vchar<<endl;
}
Var* CharVar::clone(stringstream &ss){
    CharVar* charvar = new CharVar();
    charvar ->initialize(ss);
    return charvar;
}
char CharVar::getvalue(bool check_th)//getter
{
    if(check_th == 1) lock_guard<std::mutex> guard(mu);//locking the mutex in case of executing a thread
    return vchar;
}
CharVar::~CharVar(){}