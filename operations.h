#include <map>
#include "var.h"
#include <time.h>
#include <unistd.h>
#include <mutex>
//#include "Connection.h"
// vector <string> output;
// vector <string> errors;

using namespace std;

class operation
{
    private:
    bool thread_check=0;
    public:
        NumericVar* setv1 = 0;
        RealVar* setv2 = 0;
        StringVar* setv3 = 0;
        CharVar* setv4 = 0;
        operation(){} // Constructor
        //virtual void perform(int* a, string x) = 0;
        //virtual void initialize(stringstream & ss)=0;
        //virtual operation * clone(stringstream & ss)=0;
        typedef  array<pair<string,string>,4> pair_array;

        pair_array Pair1(string v){
            pair_array keys = {make_pair(v,"NUMERIC"), make_pair(v,"REAL"),make_pair(v,"STRING"),make_pair(v,"CHAR") };
            return keys;
        }

        virtual void perform(map <pair<string,string>, Var*>& getmap, string opline, bool check_th = 0) = 0; // a virtual function that takes variable map to get the value of the variable and a line string of variables and constants
        virtual ~operation(){} // Destructor
};

class ADD: public operation
{
    private:
    bool thread_check=0;
    public:
        ADD(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline, bool check_th)
        {
            thread_check = check_th;
            string str = "";
            string var="";
            double new_var=0; // a variable to store the sum of the numbers
            string newvar;
            string new_var_name=""; // the variable name that will store the numbers ( the first parameter)
            stringstream iss(opline);
            getline(iss,new_var_name,','); // parse the given line to the first comma which is the storing variable
            // getline(iss,newvar,',');
            pair_array p1 = Pair1(new_var_name);

            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                new_var = tmp->getvalue(thread_check); // add the value to new_var
                setv1 = tmp;
            }
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                new_var = tmp->getvalue(thread_check);
                setv2 = tmp;
            }
            else
            {
                ofstream outfile;
                outfile.open("error.err", ios_base::app);
                outfile<<"There are no variable with that name "<<new_var_name<<"\n";
                outfile.close();
                return;
            }

            while(getline(iss,str,','))
            {
                if(str[0] == '$'){
                    pair_array p3 = Pair1(str);
                    if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                        NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                        new_var += tmp->getvalue(thread_check); // add the value to new_var
                    }
                    else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                        RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                        new_var += tmp->getvalue(thread_check);
                    }
                    else{
                        ofstream outfile;
                        outfile.open("error.err", ios_base::app);
                        outfile<<"There are no variable named "<<str<<"\n";
                        outfile.close();
                    }
                }
                else{
                    new_var += stof(str);
                    str = "";}
            }
            if(setv1 != 0) {setv1->setvalue(new_var,thread_check); setv1 = 0;}
            else if(setv2 !=0 ){setv2 ->setvalue(new_var,thread_check); setv2 = 0;}
            str = "";
            //cout<<new_var<<endl;
            // the new_var is the variable that hold the result after the add operation
        }
        ~ADD(){}
};


class SUB: public operation
{
    private:
    bool thread_check=0;
    public:
        SUB(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline, bool check_th)
        {
            thread_check = check_th;
            double new_var=0; // a variable to store the divid of the numbers

            string second_p="";
            string first_p=""; // the variable name that will store the numbers ( the first parameter)
            string third_p="";

            stringstream iss(opline);
            getline(iss,first_p,','); // parse the given line to the first comma which is the storing variable
            getline(iss,second_p,',');
            getline(iss,third_p,',');
             // create an object from struct pair

            pair_array p2 = Pair1(second_p);
            // save the second value to new_var variable to subtract the third parameter from it
            if(second_p[0] == '$')
            {
                if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    new_var = tmp->getvalue(thread_check); // add the value to new_var
                }
                else if(getmap.find(p2[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    new_var = tmp->getvalue(thread_check);
                }
                else{
                    ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<second_p<<"\n";
                    outfile.close();
                    return;}
            }else
                new_var = stof(second_p);

            // get the value of the third parameter and subtract it from the second one
            pair_array p3 = Pair1(third_p);
            if(third_p[0] == '$')
            {
                if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                    new_var -= tmp->getvalue(thread_check); // add the value to new_var
                }
                else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                    new_var -= tmp->getvalue(thread_check);
                }
                else{ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<third_p<<"\n";
                    outfile.close();return;}
            }else
                new_var -= stof(third_p);

            // save the result to the first parameter
            pair_array p1 = Pair1(first_p);
            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                tmp->setvalue(new_var,thread_check);
            }
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                tmp->setvalue(new_var,thread_check);
            }
            else{
                ofstream outfile;
                outfile.open("error.err", ios_base::app);
                outfile<<"There are no variable with that name !"<<first_p<<"\n";
                outfile.close();
            }

        }
        ~SUB(){}
};

class MULT: public operation
{
    private:
    bool thread_check=0;
    public:
        MULT(){}
         void perform(map <pair<string,string>, Var*>& getmap, string opline, bool check_th)
        {
            thread_check = check_th;
            string str = "";
            string var="";
            double new_var=0; // a variable to store the sum of the numbers
            string newvar;
            string new_var_name=""; // the variable name that will store the numbers ( the first parameter)
            stringstream iss(opline);
            getline(iss,new_var_name,','); // parse the given line to the first comma which is the storing variable
            pair_array p1 = Pair1(new_var_name);

            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                new_var = tmp->getvalue(thread_check); // add the value to new_var
                setv1 = tmp;
            }
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                new_var = tmp->getvalue(thread_check);
                setv2 = tmp;
            }
            else{
                ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name "<<new_var_name<<"\n";
                    outfile.close();
                return;
            }

            while(getline(iss,str,','))
            {
                if(str[0] == '$'){
                    pair_array p3 = Pair1(str);
                    if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                        NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                        new_var *= tmp->getvalue(thread_check); // add the value to new_var
                    }
                    else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                        RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                        new_var *= tmp->getvalue(thread_check);
                    }
                    else{ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name "<<str<<"\n";
                    outfile.close();}
                }
                else{
                    new_var *= stof(str);
                    str = "";}
            }
            if(setv1 != 0) {setv1->setvalue(new_var,thread_check); setv1 = 0;}
            else if(setv2 !=0 ){setv2 ->setvalue(new_var,thread_check); setv2 = 0;}
            str = "";
            //cout<<new_var<<endl;
            // the new_var is the variable that hold the result after the add operation
        }
        ~MULT(){}
};

class DIV: public operation
{
    private:
    bool thread_check=0;
    public:
        DIV(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline, bool check_th)
        {
            thread_check = check_th;
            cout<<"this is DIV op\n";
            double new_var=0; // a variable to store the divid of the numbers

            string second_p="";
            string first_p=""; // the variable name that will store the numbers ( the first parameter)
            string third_p="";

            stringstream iss(opline);
            getline(iss,first_p,','); // parse the given line to the first comma which is the storing variable
            getline(iss,second_p,',');
            getline(iss,third_p,',');
             // create an object from struct pair
            pair_array p2 = Pair1(second_p);
            if(second_p[0] == '$')
            {
                if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    if(tmp->getvalue() != 0)
                        new_var = tmp->getvalue(thread_check); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;}
                }
                else if(getmap.find(p2[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    if(tmp->getvalue() != 0)
                        new_var = tmp->getvalue(thread_check); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;}
                }
                else{ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<second_p<<"\n";
                    outfile.close();
                    return;}
            }else
                new_var = stof(second_p);

            pair_array p3 = Pair1(third_p);
            if(third_p[0] == '$')
            {
                if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                    if(tmp->getvalue(thread_check) != 0)
                        new_var /= tmp->getvalue(thread_check); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;} // add the value to new_var
                }
                else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                    if(tmp->getvalue(thread_check) != 0)
                        new_var /= tmp->getvalue(thread_check); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;}
                }
                else{ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<third_p<<"\n";
                    outfile.close();return;}
            }else
                new_var /= stof(third_p);

            pair_array p1 = Pair1(first_p);
            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                tmp->setvalue(new_var,thread_check);
            }
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                tmp->setvalue(new_var,thread_check);
            }
            else{ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<first_p<<"\n";
                    outfile.close();return;}

            cout<<new_var<<endl;

        }
        ~DIV(){}
};
class ASSIGN: public DIV
{
    private:
    bool thread_check=0;
    public:
        ASSIGN(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline,bool check_th)
        {
            thread_check=check_th;
            string newvar="";
            //double new_var=0;

            string new_var_name=""; // the variable name that will store the numbers ( the first parameter)
            stringstream iss(opline);
            getline(iss,new_var_name,','); // parse the given line to the first comma which is the storing variable
            getline(iss,newvar,',');
            //cout<<newvar<<endl;
             // create an object from struct pair
            pair_array p1 = Pair1(new_var_name);
            if(newvar[0] == '$')
            {
                pair_array p2 = Pair1(newvar);
                if((getmap.find(p1[0]) != getmap.end()) && (getmap.find(p2[0]) != getmap.end()) ){ // to check if the two variables are numeric value
                    NumericVar* tmp1 = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                    NumericVar* tmp2 = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    tmp1->setvalue(tmp2->getvalue(thread_check),thread_check); // Assign the value of second variable to the first one
                }
                else if((getmap.find(p1[1]) != getmap.end()) && (getmap.find(p2[1]) != getmap.end()) ){ // to check if the two variables are real value
                    RealVar* tmp1 = dynamic_cast<RealVar*>(getmap[p1[1]]);
                    RealVar* tmp2 = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    tmp1->setvalue(tmp2->getvalue(thread_check),thread_check);
                }
                else if((getmap.find(p1[2]) != getmap.end()) && (getmap.find(p2[2]) != getmap.end()) ){ // to check if the two variables are string value
                    StringVar* tmp1 = dynamic_cast<StringVar*>(getmap[p1[2]]);
                    StringVar* tmp2 = dynamic_cast<StringVar*>(getmap[p2[2]]);
                    tmp1->setvalue(tmp2->getvalue(thread_check),thread_check);
                }
                else if((getmap.find(p1[3]) != getmap.end()) && (getmap.find(p2[3]) != getmap.end()) ){ // to check if the two variables are char value
                    CharVar* tmp1 = dynamic_cast<CharVar*>(getmap[p1[3]]);
                    CharVar* tmp2 = dynamic_cast<CharVar*>(getmap[p2[3]]);
                    tmp1->setvalue(tmp2->getvalue(thread_check),thread_check);
                }
                    else{
                        ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"Error cannot find a variable or cannot assign different data type of values\n";
                    outfile.close();}
            }
            else if(newvar[0] == '"'){
                if((getmap.find(p1[2]) != getmap.end())){ // to check if the two variables are string value
                    StringVar* tmp1 = dynamic_cast<StringVar*>(getmap[p1[2]]);
                    tmp1->setvalue(newvar,thread_check);
                }else{
                    ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"Cannot find the variable "<<new_var_name<<"\n";
                    outfile.close();
                    }
            }
            else if(newvar[0] == '\''){
                if((getmap.find(p1[3]) != getmap.end())){ // to check if the two variables are string value
                    CharVar* tmp1 = dynamic_cast<CharVar*>(getmap[p1[3]]);
                    tmp1->setvalue(newvar[1]);
                }else{ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"Cannot find the variable "<<new_var_name<<"\n";
                    outfile.close();}
            }
            else{
                 if((getmap.find(p1[0]) != getmap.end()) ){ // to check if the two variables are numeric value
                    NumericVar* tmp1 = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                    tmp1->setvalue(stol(newvar),thread_check); // Assign the value of second variable to the first one
                }
                else if((getmap.find(p1[1]) != getmap.end())){ // to check if the two variables are real value
                    RealVar* tmp1 = dynamic_cast<RealVar*>(getmap[p1[1]]);
                    tmp1->setvalue(stod(newvar),thread_check);
                }
            }
        }
        ~ASSIGN(){}
};
class OUT: public operation
{
    private:
    mutex mu;
    bool thread_check=0;
    public:
        OUT(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline, bool check_th)
        {
            thread_check=check_th;
            if(thread_check == 1) lock_guard<std::mutex> guard(mu);
            string var="";
            stringstream iss(opline);
            while (getline(iss,var,','))
            {
                if(var[0] == '$'){
                      pair_array p1 = Pair1(var);
                    if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                        NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                        //output.push_back(to_string(tmp->getvalue()));
                        ofstream outfile;
                        outfile.open("output.out", ios_base::app);
                        outfile<<tmp->getvalue(thread_check)<<endl;// add the value to new_var
                        outfile.close();
                    }
                    else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                        RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                        //output.push_back(to_string(tmp->getvalue()));
                        ofstream outfile;
                        outfile.open("output.out", ios_base::app);
                        outfile<<tmp->getvalue(thread_check)<<endl;// add the value to new_var
                        outfile.close();
                    }
                    else if(getmap.find(p1[2]) != getmap.end()){// to get string value
                        StringVar* tmp = dynamic_cast<StringVar*>(getmap[p1[2]]);
                        //output.push_back(tmp->getvalue());
                        ofstream outfile;
                        outfile.open("output.out", ios_base::app);
                        outfile<<tmp->getvalue(thread_check)<<endl;// add the value to new_var
                        outfile.close();
                    }
                    else if(getmap.find(p1[3]) != getmap.end()){// to get char value
                        CharVar* tmp = dynamic_cast<CharVar*>(getmap[p1[3]]);
                        //output.push_back(to_string(tmp->getvalue()));
                        ofstream outfile;
                        outfile.open("output.out", ios_base::app);
                        outfile<<tmp->getvalue(thread_check)<<endl;// add the value to new_var
                        outfile.close();
                    }
                    else{
                        //errors.push_back("There are no variable with that name !");
                        ofstream outfile;
                        outfile.open("error.err", ios_base::app);
                        outfile<<"There are no variable with that name !\n";
                        outfile.close();
                        }
                    var = "";
                }
                else
                {
                    //output.push_back(to_string(var));
                    ofstream outfile;
                        outfile.open("output.out", ios_base::app);
                        outfile<<var <<" \n";
                        outfile.close();
                }
            }
        }
};
class Sleep: public operation
{
    private:
    bool thread_check=0;
    public:
    Sleep(){}
    void perform(map <pair<string,string>, Var*>& getmap, string opline, bool thread_check)
    {
        if(opline[0] == '$')
        {
            pair_array p2 = Pair1(opline);
            if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    usleep((tmp->getvalue(thread_check))*10000); // add the value to new_var
                }
                else if(getmap.find(p2[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    usleep((tmp->getvalue(thread_check))*10000);
                }
                else{
                    ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<opline<<"\n";
                    outfile.close();
                    return;}
        }
        else
        usleep(stof(opline)*10000);
    }
    ~Sleep(){}

};
class SET_STR_CHAR: public operation
{
    private:
    bool thread_check=0;
    public:
    SET_STR_CHAR(){}
    void perform(map <pair<string,string>, Var*>& getmap, string opline, bool thread_check)
    {
        int index = 0;
        char swap;
        string tmpint = "";
        string tmpchr = "";
        string varx ="";
        stringstream iss(opline);

        getline(iss, varx, ',');
        getline(iss, tmpint, ',');
        getline(iss, tmpchr, ',');
        index = stoi(tmpint);
        swap = tmpchr[1];

        if(varx[0] == '$')
        {
            pair_array p2 = Pair1(varx);
            if(getmap.find(p2[2]) != getmap.end()){// to get string value
                StringVar* tmp = dynamic_cast<StringVar*>(getmap[p2[2]]);
                varx = tmp->getvalue(thread_check);
                if(index > varx.length())
                {
                    ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"Index error! out of range\n";
                    outfile.close();
                }
                else
                {
                    varx[index] = swap;
                    tmp->setvalue(varx,thread_check);
                }
            }
                else
                {
                    ofstream outfile;
                    outfile.open("error.err", ios_base::app);
                    outfile<<"There are no variable with that name !"<<opline<<"\n";
                    outfile.close();
                }
        }
        else
        {
            ofstream outfile;
            outfile.open("error.err", ios_base::app);
            outfile<<"Syntax error!\n";
            outfile.close();
        }
    }
};