#ifndef ast_expression_hpp
#define ast_expression_hpp
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>
#include <memory>
#include <stack>
using namespace std;
class Expression;

typedef Expression *ExpressionPtr;
extern void ident(stringstream& ss, int no);
//Expression is a base class with lots of virtual functions
//Expression_DO is a class which actual implement things in parser
class Expression
{
public:
    virtual ~Expression()
    {}



    virtual string print(int no) =0; // we could use to print PYTHON later

     virtual void set_type(string &_type) = 0;   // Setting type for debugging
     virtual string get_type() = 0; // Getting type fopr debugging
	virtual void add(Expression* ptr){}
};


#endif
