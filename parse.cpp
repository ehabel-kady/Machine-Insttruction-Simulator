#include "parse.h"
//#include <map>
Parse::Parse(){
        instructions.push_back("VAR");instructions.push_back("ASSIGN");
        instructions.push_back("GET_STR_CHAR");instructions.push_back("SLEEP");
        instructions.push_back("LABEL");instructions.push_back("ADD");
        instructions.push_back("JMP");instructions.push_back("MUL");
        instructions.push_back("JMPNZ");instructions.push_back("SUB");
        instructions.push_back("JMPZ");instructions.push_back("DIV");
        instructions.push_back("JMPGT");instructions.push_back("OUT");
        instructions.push_back("JMPGTE");instructions.push_back("SET_STR_CHAR");
        instructions.push_back("JMPLT");instructions.push_back("JMPLTE");
        instructions.push_back("THREAD_BEGIN");instructions.push_back("THREAD_END");
}
int Parse::parsing(vector <string>& vec){
    Parse();
    vector <string> :: iterator i;
    vector <string> :: iterator j;
    int errline =0;
    //string line1 = ""; // a string to hold each line to then push back to the vector
    //ifstream readFile1(filename); // read mis file
        for(i = vec.begin(); i != vec.end(); i++){
            string x = "";
            stringstream iss(*i);
            getline(iss,x,' ');
            for(j = instructions.begin(); j != instructions.end(); j++){
                if(x == *j){
                    errline++;break;}
            }
            if(j == instructions.end()){
                ofstream outfile;
                outfile.open("error.err", ios_base::app);
                outfile<<x<<" synatx error!!\n";
                outfile.close();
            }
        }
        return errline;
}
Parse::~Parse(){}