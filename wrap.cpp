#include "wrap.h"
#include "maps.h"
// map <pair<string,string>, Var*> varmap; //(variable map) map that has two keys to search for the variable and a value pointer to the passed object from cloning
// map<string,operation *> ops;
// map <string, Var *> dtypemap;
// map<string,int> labels;
Wrap::Wrap(vector <string> line)
{
    //parser.parsing(filename, lines);

    dtypemap["STRING"] = new StringVar();
    dtypemap["REAL"] = new RealVar();
    dtypemap["NUMERIC"] = new NumericVar();
    dtypemap["CHAR"] = new CharVar();
    lines = line;
    ops["ADD"] = new ADD();
    ops["SUB"] = new SUB();
    ops["MUL"] = new MULT();
    ops["DIV"] = new DIV();
    ops["ASSIGN"] = new ASSIGN();
    ops["OUT"] = new OUT();
    ops["SLEEP"] = new Sleep();
    ops["SET_STR_CHAR"] = new SET_STR_CHAR();
    erline = parser.parsing(line);
}
void Wrap::action()
{
    check_labels();
    vector<string> myvector;
    for(i = lines.begin(); i != lines.end(); i++)
    {
        string tmp = "";
        string tmp2 = "";
        stringstream is(*i);
        getline(is,tmp,' ');
        for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];} // save the rest of the line to tmp2
        if(*i == "THREAD_BEGIN")
        {
            i = i+1;
            for(;*i!= "THREAD_END";i++)
                myvector.push_back(*i);
            cout<<myvector.size()<<endl;
            threadmanage threadm(myvector, varmap, ops, dtypemap);
            threadm.distribute_threads();
            threadm.execute();

        }
        else if(tmp == "VAR"){Save_var(tmp2);}
        else if(tmp == "JMP"){i = lines.begin()+labels[tmp2];}
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
                if(tmp->getvalue() == 0) i = lines.begin()+labels[lab];
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
            if(x > y) i = lines.begin()+labels[lab];

        }
        else{
            operation* obj = ops[tmp];
            if(obj != NULL){
                obj->perform(varmap,tmp2);
            }else cout<<"Undefined Object Identifier...\n";
        }
    }
    usleep(500*1000);

}
void Wrap::Save_var(string line)
{
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
void Wrap::check_labels()
{
    int count = 0;
    for(i = lines.begin(); i != lines.end(); i++)
    {
        string tmp = "";
        string tmp2 = "";
        stringstream is(*i);
        getline(is,tmp,' ');
        for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];} // save the rest of the line to tmp2
        if(tmp == "LABEL")
        {
            labels[tmp2] = count;
        }
        count++;
    }
}