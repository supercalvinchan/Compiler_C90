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

//==============================================statement
class statement
     : public Expression
{
private:
  string id;
  statement* s_ptr;
public:
//  Context statement_scope;
  statement();
  virtual void add_list(statement* exptr) = 0;
  virtual void add_List(Expression* exptr);
  virtual void print(ostream &dst) const override;
  virtual string print_assembly();
  virtual void set_type(deftype* _type);
  virtual deftype* get_type();
  virtual string get_id();

};

//=====================================================statementlist
class statementlist
    : public Expression
{
private:
  list<statement*> statement_list;
  string id;
  statement* s_ptr;
public:
  statementlist();
  void add_list(statement* exptr);
  void add_List(Expression* exptr);

  //void add_subscope(Context& ctext);

  string print_assembly();

  void print(ostream &dst) const override;

  void set_type(deftype* _type);
string get_id();
   deftype* get_type();
   void set_contextpoint(uint32_t _point);

};

//==============================================compoundstatement
class Compoundstatement
    : public statement
{
private:
  declaration_list* dlist_ptr;
  statementlist* slist_ptr;;
  declare* d_left;
  statement* s_right;
  deftype* type;
  string id;
  statement* s_ptr;
public:

  Compoundstatement(declaration_list* _dlist_ptr, statementlist* _slist_ptr);
  void add_list(statement* exptr);
  void add_List(Expression* exptr);
  void print(ostream &dst) const override;
  string print_assembly();
   void set_type(deftype* _type);
  deftype* get_type();
    string get_id();
  //  Variable* find_variable(string variablename);
};



//======================================================jump_statement
class jump_statement
    : public statement
{
private:
  deftype* type;
  Expression* ptr;
  string id;
  statement* s_ptr;
public:
//  Context jump_scope;
  jump_statement(Expression* _ptr);
  void add_list(statement* exptr);
  virtual void add_List(Expression* exptr);
  void print(ostream &dst) const override;
//Variable* find_variable(string variablename);
  string print_assembly();
  string get_id();
  void set_type(deftype* _type);

  deftype* get_type();
};

//=============================================================expressionstatement
class expressionstatement
    : public statement
{
private:
Expression* ptr;
string id;
statement* s_ptr;

public:

//Context expression_statement_scope;
expressionstatement(Expression* _ptr);
void add_list(statement* exptr);
virtual void add_List(Expression* exptr);
void print(ostream &dst) const override;
//Variable* find_variable(string variablename);
string print_assembly();

void set_type(deftype* _type);
string get_id();
deftype* get_type();

};


//============================================================iterationstatement
//while
//WHILE T_LBRACKET EXPRESSION T_RBRACKET STATEMENT
class whilestatement
    : public statement
{
private:
  string type;
  Expression *exptr;
  statement* s_ptr;
  string id;

public:
  //Context while_scope;
  whilestatement(string& _type, Expression* _exptr, statement* _s_ptr);

  void add_list(statement* exptr);    //not useful
  virtual void add_List(Expression* exptr); // notuseful
  void print(ostream &dst) const override;
  //Variable* find_variable(string variablename);
  string print_assembly();

  void set_type(deftype* _type);
  string get_id();
  deftype* get_type();

};

//For
//FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION T_RBRACKET STATEMENT
class forstatement
    : public statement
{
private:
  //s_ptr:INITIALIZER
  //s_ptr1:condition
  //s_ptr2:statement
  //s_ptr3:incremental
  statement* mp_Initializer;
  statement* mp_Condtion;
  statement *mp_Statement;
  Expression* mp_Increment;
  string id;

public:


  forstatement(statement* p_Initializer, statement* p_Condtion, statement* p_Statement, Expression* p_Increment);
  void add_list(statement* exptr);    //not useful
  virtual void add_List(Expression* exptr); // notuseful
  void print(ostream &dst) const override;
  string print_assembly();
  string get_id();
  void set_type(deftype* _type);
//Variable* find_variable(string variablename);
  deftype* get_type();

};

//=================================================================SELECTION STATEMENT
//IF
//IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT
// | IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT ELSE STATEMENT
class ifstatement
    : public statement
{
private:
  statement* s_ptr1;
  statement *s_ptr2;
  Expression* s_ptr3;
  string id;

public:

  ifstatement(statement* _s_ptr1, statement* _s_ptr2, Expression* _s_ptr3);
string get_id();
  void add_list(statement* exptr);    //not useful
  virtual void add_List(Expression* exptr); // notuseful
  void print(ostream &dst) const override;
//Variable* find_variable(string variablename);
  string print_assembly();

  void set_type(deftype* _type);

  deftype* get_type();

};

//==============LABEL STATEMENT
//CASE CONDITIONAL_EXPRESSION COLON STATEMENT
//| DEFAULT COLON STATEMENT

class labelstatement
    : public statement
{
private:
  statement* s_ptr1;
  Expression* s_ptr3;
  deftype* type;

public:
  //Context if_scope;
  labelstatement(Expression* _s_ptr3, statement* _s_ptr1);
string get_id();
  void add_list(statement* exptr);    //not useful

  void print(ostream &dst) const override;
//Variable* find_variable(string variablename);
  string print_assembly();

  void set_type(deftype* _type);

  deftype* get_type();

};
