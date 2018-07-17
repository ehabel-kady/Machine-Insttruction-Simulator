#include <vector>
#include <string>
#include "var.h"
#include <map>
using namespace std;
//#include "operations.h"

class Parse{
    protected:
        vector <string> instructions;

    public:
        Parse();
        int parsing( vector <string>& vec);
        ~Parse();
};
