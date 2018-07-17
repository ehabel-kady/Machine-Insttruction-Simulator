#include "Threadmanage.h"

threadmanage::threadmanage (vector <string> x, map <pair<string,string>, Var*> vars, map<string,operation *> op, map <string, Var *> dtype)
{
        operationlines = x;
        varmap = vars;
        ops = op;
        dtypemap = dtype;
}

void threadmanage::distribute_threads()
{
    check_labels();
    vector <string> :: iterator i;
    int count = 0;
    for(i = operationlines.begin(); i < operationlines.end(); i++)
    {
        string tmp = "";
        string tmp2 = "";
        stringstream is(*i);
        getline(is,tmp,' ');
        for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];}
        if(tmp != "JMP" || tmp != "JMPZ" || tmp != "JMPGE")
        {
            threadexe th(*i,varmap, ops, dtypemap);
            threads.push_back(th);
        }
        //delete(th);
        count++;
    }
    // vector <threadexe> :: iterator m;
    // for(m = threads.begin(); m < threads.end(); m++) (m)->start();
    // usleep(500*1000);
}

void threadmanage::execute()
{
    vector <threadexe> :: iterator m;
    vector <string> :: iterator n;
    for(m = threads.begin(),n = operationlines.begin(); m < threads.end() && n < operationlines.end(); m++, n++)
    {
        string tmp = "";
        string tmp2 = "";
        stringstream is(*n);
        getline(is,tmp,' ');
        for(int j = tmp.length()+1; j<(*n).length();j++){tmp2 += (*n)[j];} // save the rest of the line to tmp2
        if(tmp == "JMP")
        {
            n = operationlines.begin()+label[tmp2];
            m = threads.begin()+label[tmp2];
        }
        else if(tmp == "JMPZ")
        {
            string lab = "";
            string vars = "";
            string t = tmp2;
            stringstream iss(t);
            getline(iss,lab,',');
            getline(iss,vars,',');
            operation* bf;
            pair_array p = bf->Pair1(vars);
            if(varmap.find(p[0]) != varmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(varmap[p[0]]);
                if(tmp->getvalue() == 0)
                {
                    n = operationlines.begin()+label[lab];
                    m = threads.begin()+label[lab];
                }
            }
        }
        else if(tmp == "JMPGE")
        {
            string t = tmp2;
            string lab = "";
            string vars = "";
            string vars2 = "";
            long x = 0;
            long y = 0;
            stringstream iss(t);
            getline(iss,lab,',');
            getline(iss,vars,',');
            getline(iss,vars2,',');
            operation* bf;
            pair_array p = bf->Pair1(vars);
            if(varmap.find(p[0]) != varmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(varmap[p[0]]);
                x = tmp->getvalue();
            }
            delete bf;
            //operation* bf;
            p = bf->Pair1(vars2);
            if(varmap.find(p[0]) != varmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(varmap[p[0]]);
                y = tmp->getvalue();
            }
            if(x > y)
            {
                n = operationlines.begin()+label[lab];
                m = threads.begin()+label[lab]+1;
            }
        }
        else
        {
            // operation* obj = ops[tmp];
            // if(obj != NULL){
            //     obj->perform(varmap,tmp2);
            // }
            // else
            // cout<<"Undefined Object Identifier...\n";
            (m)->start();
        }
    }
    usleep(500*1000);
    usleep(500*1000);
}
void threadmanage::check_labels()
{
    vector <string> ::iterator i;
    int count = 0;
    for(i = operationlines.begin(); i != operationlines.end(); i++)
    {
        string tmp = "";
        string tmp2 = "";
        stringstream is(*i);
        getline(is,tmp,' ');
        for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];} // save the rest of the line to tmp2
        if(tmp == "LABEL")
        {
            label[tmp2] = count;
        }
        count++;
    }
}
threadmanage::~threadmanage()
{

}