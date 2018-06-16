#ifndef ast_functions_hpp
#define ast_functions_hpp
#include "ast_expression.hpp"
#include "ast_parameters.hpp"
#include "ast_statements.hpp"

#include <list>
#include <cmath>

class declare;
class Function_Declaration;
class Declare_translate;

//===========================================external==============
class external
     : public Expression
{
public:
  external();
  virtual void add(Function_Declaration* exptr);//useful
  void print(std::ostream &dst) const;
  string get_id();
  void add_List(Expression* exptr);
   string print_assembly(); // pr
  virtual void add(declare* ptr);//useful
   void set_type(deftype* _type);
   deftype* get_type();


private:
  list <Function_Declaration*> FList;
  list<declare*> D_List;
  string id;
  deftype* type;

};

//===========================================argument list======================
class argument_list
    : public Expression
{
private:
  list<Expression*> argumentlist;
public:
uint32_t get_VariableOffset(int no);
argument_list(Expression* exptr);
virtual void add_List(Expression* exptr);
void print(ostream &dst) const override;
string print_assembly();
void set_type(deftype* _type);
deftype* get_type();
string get_id();
void finalize();
};

//============================================function calling=====================
class function_calling
     : public Expression
{
//function_name
//parameter state
//jump
private:
 string name;
 argument_list* argument;
 //Context* parent_ctext;
 string id;
 deftype* type;

public:
function_calling(deftype* _type, const string& _name, argument_list* _argument);
void add_List(Expression* exptr);
void print(ostream &dst) const override;
string print_assembly();
void set_type(deftype* _type);
deftype* get_type();
string get_id();
};

//===========================================function declaration
class Function_Declaration
    : public Expression
{
private:
string id;
deftype* type;
parameter_list* parameter_list_temp;
Compoundstatement* outline;

public:

  Function_Declaration(string _id, parameter_list* _parameter_list, Compoundstatement* _outline);
Variable* find_variable(string variablename);
  void add_List(Expression* exptr);

  void print(ostream &dst) const override;

  string print_assembly();

  void set_type(deftype* _type);
string get_id();
  deftype* get_type();

};

#endif
