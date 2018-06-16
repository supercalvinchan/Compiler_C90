#include "ast.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
extern FILE *yyout;
extern FILE *yyin;
using namespace std;
extern int yydebug;
using namespace std;
int main(int argc, char* argv[])
{
  yydebug = 1;


  if(argc < 2)
  {
  //  cout << "need prameters" <<endl;
    exit(-1);
  }

  //cout << "step 0 :" << endl;
  string argv_2 = argv[2];
  string argv_4 = argv[4];
  string argv_1 = argv[1];
    string argv_3 = argv[3];
      string argv_0 = argv[0];

  if(argv_1 == "--translate")
  {
    string command;
    command = argv_0;
    const char* p;
    p = strrchr(argv[0], '/');
    if(p != NULL)
    {
      command = command.substr(0,(p+1)-argv[0]);
    }else
    {
      command = "";
    }

    command.append("python_compiler ");
    command.append(argv_1);
    command.append(" ");
    command.append(argv_2);
    command.append(" ");
    command.append(argv_3);
    command.append(" ");
    command.append(argv_4);


    return system(command.c_str());
  }

    yyin = fopen(argv_2.c_str(), "r");

    //cout << "step1" << endl;
    Expression *ast=parseAST();

    fclose(yyout);

    FILE* python_out = fopen(argv_4.c_str(), "w");

    if(python_out == NULL)
  {
    cout << "open file output fail" << endl;
  }

  if(argv_1 == "-S")
   {


    string a;

//print python code
    a =  ast->print_assembly();

  // write python code to the file
  fwrite(a.c_str(), 1, a.size(), python_out);

  //write python tenplate to the file
  //fwrite(tmp.c_str(), 1, tmp.size(), python_out);

  //close the python file
  fclose(python_out);
  }

    //cout << "step2" << endl;
  //  cout <<  ast->print_assembly();


    //cout << "step3" << endl;
    return 0;
}
