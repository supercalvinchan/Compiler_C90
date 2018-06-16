#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include "ast_expression.hpp"

using namespace std;

class Pointer
    : public Expression
{
private:
    string ptr;
    Expression* exptr;
public:
    Pointer(const string &_ptr, Expression* _exptr);

    const string getId() const;

    virtual string print(int no) override;

    void set_type(string &_type);

    string get_type();
};

class Variables
    : public Expression {
public:
  Variables(const string &_id);

  virtual string print(int no) override;
  string get_id();

   virtual void set_type(string &_type);
   virtual string get_type();
private:
  string type;
  string id;
};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value);
    double getValue() const;

    virtual string print(int no) override;

    void set_type(string &_type);

    string get_type();

};

//================================================================POSTFIX EXPRESSION
class postfix
     : public Expression
{
public:
postfix(Expression *_exptr1 , Expression *_exptr2);

string print(int no) override;

 virtual void set_type(string &_type);
 virtual string get_type();

private:
  Expression *exptr1;
  Expression *exptr2;
  string type;
};

//================================================================Argument EXPRESSION
class argumentexpression
     : public Expression
{
public:
argumentexpression();

string print(int no) override;

 virtual void set_type(string &_type);
 virtual string get_type();
private:

  string type;
};

//======================Array
class Array
	:public Expression
{
public:
	Array(Expression* _id, double _size);
	string print(int no) override;
	virtual void set_type(string &_type);
	virtual string get_type();
private:
	Expression *id;
	double size;
	string type;
};





#endif
