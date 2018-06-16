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
#include "ast_variable.hpp"
#include "ast_primitives.hpp"

using namespace std;

class initializerlist
     : public Expression
{
public:
  initializerlist();
  void add_List(Expression* exptr);
  void print(ostream &dst) const override;
  string print_assembly();
  void set_type(deftype* _type);
  deftype* get_type();
  string get_id();
  double get_value();
  string print_assembly_getaddress();
  list<Expression*> explist;



};




class primaryexpression
    : public Expression
{
public:
primaryexpression(string _id, double _value, Expression* _index = NULL);
void add_List(Expression* exptr);
void print(ostream &dst) const override;
string print_assembly();
void set_type(deftype* _type);
deftype* get_type();
string get_id();
double get_value();
string print_assembly_getaddress();
uint32_t getSize();

private:
  deftype* type;
  string id;
  double value;
  Expression* index;


};
class init_declare
    : public Expression
{
private:
  deftype* type;
  string id;

public:
  Expression* left_exp;
  Expression* right_exp;
init_declare(Expression* _left_exp, Expression* _right_exp);

string print_globalvariableassembly();


  void add_List(Expression* exptr);
  string get_id();
//  void add_list(declare* d_ptr);
  void print(ostream &dst) const override;
  string print_assembly();
  void set_type(deftype* _type);
deftype* get_type();
};

//init declare===========================================
class init_declarelist
    : public Expression
{

public:
  string print_globalvariableassembly();
  deftype* type;
  string id;
  list<init_declare*> declarationlist;
  init_declarelist();
  void add_List(Expression* exptr);
  string get_id();
//  void add_list(declare* d_ptr);
  void print(ostream &dst) const override;
  string print_assembly();
  void set_type(deftype* _type);
   deftype* get_type();
};

//================================================Declarator=================
//init declare
//DECLARATOR { $$ = $1; }
//               | DECLARATOR EQUAL INITIALIZER
class declare
    : public Expression
{
protected:

  deftype* type;
  string id;
  init_declarelist* exptr;

public:
string print_globalvariableassembly();
  declare(deftype* _type, init_declarelist* _exptr);
  void add_List(Expression* exptr);
  virtual void add_list(declare* d_ptr);
  void print(ostream &dst) const override;
  string print_assembly();
  void set_type(deftype* _type);
  deftype* get_type();
  string get_id();
  void add_VariableToContext(Context& ctext);
  void add_globalvariableToContext(Context& ctext);
};
//===init declare


//================================================declaration_list=================
class declaration_list
    : public Expression
{
private:
    //list<declare*> declarationlist;
    string id;
public:
  list<declare*> declarationlist;
void add_globalvariableToContext(Context& ctext);
  declaration_list();
  void add_List(Expression* exptr);
  string get_id();
//  void add_list(declare* d_ptr);
  void print(ostream &dst) const override;
  string print_assembly();
  void set_type(deftype* _type);
  deftype* get_type();
};
