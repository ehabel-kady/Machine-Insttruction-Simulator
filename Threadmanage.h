#ifndef TMAN_H
#define TMAN_H
#include "Threadexe.h"
//#include "maps.h"
class threadexe;
class threadmanage
{
    protected:
    //threadmanage* nextthread;
    int num;
    vector <string> operationlines;
    map <string,int>label;
    vector <threadexe> threads;
    typedef  array<pair<string,string>,4> pair_array;
    pair_array Pair1(string v){
        pair_array keys = {make_pair(v,"NUMERIC"), make_pair(v,"REAL"),make_pair(v,"STRING"),make_pair(v,"CHAR") };
        return keys;
    }
    map <pair<string,string>, Var*> varmap; //(variable map) map that has two keys to search for the variable and a value pointer to the passed object from cloning
    map<string,operation *> ops;
    map <string, Var *> dtypemap;
    map<string,int> labels;
    //std::mutex mu;
    public:
    threadmanage( vector <string> x, map <pair<string,string>, Var*> vars, map<string,operation *> op, map <string, Var *> dtype);
    void distribute_threads();
    void execute();
    void check_labels();
    ~threadmanage();
};
#endif