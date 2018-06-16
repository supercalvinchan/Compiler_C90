#include "ast.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;
extern FILE *yyout;
extern FILE *yyin;
extern int yydebug;

//ident: helps us to put space in each scope
// in python, scope is representing by different lengths of white spaces
// This is the THINGS we need to test in out testcase!!!!!
void ident(stringstream& ss, int no)
{

  for(int i = 0; i < no; i++)
  {
    ss << "\t";
  }
}


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
    //  cout << "need prameters" <<endl;
      exit(-1);
    }
    //cout << "step 0 :" << endl;
    string argv_2 = argv[2];
    string argv_4 = argv[4];
    string argv_1 = argv[1];

//yydebug: a function includes in bison to check the parsing
// not useful at the end
// just for debugging
//ALL the cout is not useful, just for debugging
    yydebug = 0;

    yyin = fopen(argv_2.c_str(), "r");
    //yyout = fopen("tmp/formative/yyout.txt", "w");


    Expression *ast=parseAST();
    fclose(yyout);

    cout << "step 1 :" << endl;

    FILE* python_out = fopen(argv_4.c_str(), "w");
    cout << "argv 4" << argv_4<<endl;
    if(python_out == NULL)
	{
		cout << "open python file output fail" << endl;
	}

    //print the python template to run python code
        if(argv_1 == "--translate"){
      string tmp = "if __name__ == \"__main__\":\n"
      "    import sys\n"
      "    ret=main()\n"
      "    sys.exit(ret)\n";
          cout << "step 2 :" << endl;

          string a;

    //print python code
          a = ast->print(0);

          cout << "a:" << a << endl;

        // write python code to the file
        fwrite(a.c_str(), 1, a.size(), python_out);

        //write python tenplate to the file
        fwrite(tmp.c_str(), 1, tmp.size(), python_out);

        //close the python file
        fclose(python_out);
    }

        cout << "step 3 :" << endl;






    return 0;
}
