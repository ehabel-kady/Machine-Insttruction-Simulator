
// #include "stringvar.h"
// #include "realvar.h"
// #include "numericvar.h"
// #include "charvar.h"
// //#include "maps.h"
// #include <unistd.h>
// #include <vector>
// #include "parse.h"
#include "wrap.h"

// map<string,int> labels;
// void Save_var(string line);
// void check_labels();
// vector <string> lines; // vector to store lines of the mis file
// vector <string> :: iterator i;
// vector <string> :: reverse_iterator ir;

int main()
{
    // typedef  array<pair<string,string>,4> pair_array;

    // dtypemap["STRING"] = new StringVar();
    // dtypemap["REAL"] = new RealVar();
    // dtypemap["NUMERIC"] = new NumericVar();
    // dtypemap["CHAR"] = new CharVar();

    // ops["ADD"] = new ADD();
    // ops["SUB"] = new SUB();
    // ops["MUL"] = new MULT();
    // ops["DIV"] = new DIV();
    // ops["ASSIGN"] = new ASSIGN();
    // ops["OUT"] = new OUT();
    // ops["SLEEP"] = new Sleep();

    // // string line1 = ""; // a string to hold each line to then push back to the vector
    // // ifstream readFile1("test1.mis"); // read mis file
    // // if(readFile1.good()){
    // //     while(getline(readFile1,line1)){
    // //         lines.push_back(line1);
    // //     }
    // //     readFile1.close();
    // // }
    // // else{cout<<"Error! Cannot open the file \n"; return -1;}
    
    // check_labels();
    // for(i = lines.begin(); i != lines.end(); i++)
    // {
    //     string tmp = "";
    //     string tmp2 = "";
    //     stringstream is(*i);
    //     getline(is,tmp,' ');
    //     for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];} // save the rest of the line to tmp2
    //     if(tmp == "VAR"){Save_var(tmp2);}
    //     else if(tmp == "JMP"){i = lines.begin()+labels[tmp2];}
    //     else if(tmp == "JMPZ")
    //     {
    //         string lab = "";
    //         string vars = "";
    //         string t = tmp2;
    //         stringstream iss(t);
    //         getline(iss,lab,',');
    //         getline(iss,vars,',');
    //         operation* bf;
    //         pair_array p = bf->Pair1(vars);
    //         if(varmap.find(p[0]) != varmap.end()){ // to get numeric value
    //             NumericVar* tmp = dynamic_cast<NumericVar*>(varmap[p[0]]);
    //             if(tmp->getvalue() == 0) i = lines.begin()+labels[lab];
    //         }

    //     }
    //     else if(tmp == "JMPGE")
    //     {
    //         string t = tmp2;
    //         string lab = "";
    //         string vars = "";
    //         string vars2 = "";
    //         long x = 0;
    //         long y = 0;
    //         stringstream iss(t);
    //         getline(iss,lab,',');
    //         getline(iss,vars,',');
    //         getline(iss,vars2,',');
    //         operation* bf;
    //         pair_array p = bf->Pair1(vars);
    //         if(varmap.find(p[0]) != varmap.end()){ // to get numeric value
    //             NumericVar* tmp = dynamic_cast<NumericVar*>(varmap[p[0]]);
    //             x = tmp->getvalue();
    //         }
    //         delete bf;
    //         //operation* bf;
    //         p = bf->Pair1(vars2);
    //         if(varmap.find(p[0]) != varmap.end()){ // to get numeric value
    //             NumericVar* tmp = dynamic_cast<NumericVar*>(varmap[p[0]]);
    //             y = tmp->getvalue();
    //         }
    //         if(x > y) i = lines.begin()+labels[lab];

    //     }
    //     else{
    //         operation* obj = ops[tmp];
    //         if(obj != NULL){
    //             obj->perform(varmap,tmp2);
    //         }else cout<<"Undefined Object Identifier...\n";
    //     }
    // }
    Wrap wraper("test1.mis");
    wraper.action();   
    return 0;
}
// void Save_var(string line)
// {
//     stringstream iss(line);
//     string name = "";// The string to hold the name of the object
//     string type = "";// The string to hold the type of the object
//     getline(iss, name, ',');// parse until the first comma
//     getline(iss,type,',');
//     Var *obj = dtypemap[type];
//     //static_cast<NumericVar*>(obj)
//     if(obj != NULL){
//         obj = obj->clone(iss);
//         varmap[make_pair(name,type)] = obj;
//     }else cout<<"Undefined Object Identifier\n";
// }
// void check_labels(){
//     int count = 0;
//     for(i = lines.begin(); i != lines.end(); i++)
//     {
//         string tmp = "";
//         string tmp2 = "";
//         stringstream is(*i);
//         getline(is,tmp,' ');
//         for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];} // save the rest of the line to tmp2
//         if(tmp == "LABEL")
//         {
//             labels[tmp2] = count;
//         }
//         count++;
//     }
// }