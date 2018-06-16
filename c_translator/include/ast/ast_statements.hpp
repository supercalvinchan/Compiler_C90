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
#include "ast_declarations.hpp"

using namespace std;
class statement
     : public Expression
{
public:
  statement();

  virtual void add(statement* ptr);
  string print(int no) override;
  void set_type(string &_type);
  string get_type();
};

class statementlist
    : public statement
{
private:
  list<statement*> statement_list;
public:
  statementlist();

  void add(statement* ptr);

  string print(int no) override;

  void set_type(string &_type);

   string get_type();
};

//==========================================COMPOUND STATEMENT=================================
class Compoundstatement
    : public statement
{
private:
  statement* left;
  Expression* right;
  string type;
	list<Expression*> variableName;
public:
  Compoundstatement(statement* _left, Declarator* _right);

  string print(int no) override;

   void set_type(string &_type);

    string get_type();
	void add(Expression*);
	void set_variable(list<Expression*> variableName);
};

//==========================================JUMP STATEMENT=================================
class jump_statement
    : public statement
{
private:
  string type;
  Expression* ptr;
public:
  jump_statement(Expression* _ptr, string& _type);

  string print(int no) override;

  void set_type(string &_type);

  string get_type();
};


//==========================================IF STATEMENT=================================
//SELECTION_STATEMENT : IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT
//                    | IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT ELSE STATEMENT
class if_statement
     : public statement
{
public:
 if_statement(Expression* _exptr, statement * _ptr, statement * _ptr1);
 void add(statement* ptr);
 string print(int no) override;
 void set_type(string &_type);
 string get_type();

private:
  Expression* exptr;
  statement * ptr;
  statement * ptr1;

};

//=========================================Just for connecting statement and expression in parser
class Expression_DO
     : public statement
{
public:
  Expression_DO(Expression* _exptr);

  string print(int no);

   void set_type(string &_type); // Setting type for debugging
   string get_type();// Getting type fopr debugging
private:
  Expression* exptr;


};

//=========================================IF
class ifstatement
    : public statement
{
private:
  statement* s_ptr1;
  statement *s_ptr2;
  Expression* s_ptr3;
  string type;

public:
  ifstatement(statement* _s_ptr1, statement* _s_ptr2, Expression* _s_ptr3);

  void add(statement* exptr);    //not useful
  string print(int no);

  void set_type(string &_type);

  string get_type();

};

//=====================================While
class whilestatement
    : public statement
{
private:
  string type;
  Expression *exptr;
  statement* s_ptr;

public:
  whilestatement(string& _type, Expression* _exptr, statement* _s_ptr);

  void add(statement* exptr);
   string print(int no);

  void set_type(string &_type);

  string get_type();

};


//===============For
//wait do we really need to implement this
class forstatement
	:public statement
{
private:
	statement *initPtr;
	statement *conditionPtr;
	Expression *increment;
	statement *s_ptr;
	
public:
	forstatement(statement* _initPtr, statement* _conditionPtr, Expression* _increment, statement* _s_ptr);
	string print(int no);
};


