#include "Threadexe.h"


threadexe::threadexe(string op, map <pair<string,string>, Var*> vars, map<string,operation *> opa, map <string, Var *> dtype)
{
    line = op;
    varmap = vars;
    ops = opa;
    dtypemap = dtype;
}
//the main body of the thread to be executed
void * threadexe::threadMainBody(void* arg)
{
    //declaring two strings to hold the line parts 
    string tmp = "";
    string tmp2 = "";
    stringstream is(line);
    getline(is,tmp,' ');
    //storing the rest of the operaion line in tmp2
    for(int j = tmp.length()+1; j<(line).length();j++){tmp2 += line[j];} // save the rest of the line to tmp2
    //checking the type of the operation to be executed
    if(tmp == "VAR"){Save_var(tmp2);}
    else
    {
        operation* obj = ops[tmp];//putting the operation object in a generic operation object
        if(obj != NULL){
            obj->perform(varmap,tmp2,1);//performing the operaion
        }
        else
        {
            //writing the error to the error file in case of errors
            ofstream outfile;
            outfile.open("error.err", ios_base::app);
            outfile<<"Undefined Object Identifier...\n";
            outfile.close();
        }
    }
    //waiting for a few seconds to make sure that the thread executed
    usleep(500*1000);
}
//method for storing the variable
void threadexe::Save_var(string line)
{
    //putting the line in string stringstream
    stringstream iss(line);
    string name = "";// The string to hold the name of the object
    string type = "";// The string to hold the type of the object
    getline(iss, name, ',');// parse until the first comma
    getline(iss,type,',');
    Var *obj = dtypemap[type];
    //static_cast<NumericVar*>(obj)
    if(obj != NULL){
        obj = obj->clone(iss);
        varmap[make_pair(name,type)] = obj;
    }else cout<<"Undefined Object Identifier\n";
}

threadexe::~threadexe(){}