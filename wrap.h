 #ifndef WRAP_H
 #define WRAP_H
// #pragma once
#include "stringvar.h"
#include "realvar.h"
#include "numericvar.h"
#include "charvar.h"
#include <unistd.h>
#include "parse.h"
#include "operations.h"
#include "Threadmanage.h"
#include "Threadexe.h"
//#include "maps.h"
// #include "Threadmanage.h"
// #include "Threadexe.h"

class Wrap{
    protected:
        map <pair<string,string>, Var*> varmap; //(variable map) map that has two keys to search for the variable and a value pointer to the passed object from cloning
        map<string,operation *> ops;
        map <string, Var *> dtypemap;
        map<string,int> labels;
        typedef  array<pair<string,string>,4> pair_array;
        Parse parser;
        vector <string> lines;
        vector <string> :: iterator i;
        short int erline = 0; // index to the first error line after parsing
    public:
        Wrap(vector <string> line);
        void Save_var(string line);
        void action();
        void check_labels();
        //~Wrap();
};

#endif