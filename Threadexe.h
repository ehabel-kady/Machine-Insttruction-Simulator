#ifndef TEXE_H
#define TEXE_H
#include "Thread.h"
#include <mutex>
#include "wrap.h"
#include <iostream>
#include <unistd.h>

//#include "maps.h"
class Wrap;
class threadexe: public Thread
{
    protected:
    string line;
    Wrap * wraper;
    typedef  array<pair<string,string>,4> pair_array;
    pair_array Pair1(string v){
        pair_array keys = {make_pair(v,"NUMERIC"), make_pair(v,"REAL"),make_pair(v,"STRING"),make_pair(v,"CHAR") };
        return keys;
    }
    map <pair<string,string>, Var*> varmap; //(variable map) map that has two keys to search for the variable and a value pointer to the passed object from cloning
    map<string,operation *> ops;
    map <string, Var *> dtypemap;
    map<string,int> labels;
    public:
    threadexe(string op, map <pair<string,string>, Var*> vars, map<string,operation *> opa, map <string, Var *> dtype);
    void * threadMainBody(void * arg);
    void Save_var(string line);
    ~threadexe();
};
#endif