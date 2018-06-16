#ifndef ast_functions_hpp
#define ast_functions_hpp
#include "ast_expression.hpp"
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include "ast_statements.hpp"
#include "ast_parameters.hpp"

class Declarator;

class Function_Declaration;

class Declare_translate;

class Variables;

class external
     : public Expression
{
public:
	external();
	string print(int no);
	virtual void add(Function_Declaration* exptr);

	virtual void add(Declarator* ptr);
	void set_type(string &_type);
	string get_type();
	
	virtual void add(Expression*);
	

private:
  list <Function_Declaration*> FList;
  list<Declarator*> D_List;
  list<Expression*> variableName;
};

//===============================================Function Definition
class Function_Declaration
    : public external
{
protected:
string id;
string type;
Expression* parameters;
statement* outline;
parameter_list* p_ptr;
list<Variables*> v_ptr;
Expression* parent;
list<Expression*> variableName;

public:
  Function_Declaration(const string &_type, const string &_id, statement* _outline, parameter_list* _p_ptr);

  void add_variable(Variables* _v_ptr);

   Variables* find_variable(string name);

  string print(int no) override;

  void set_type(string &_type);

  string get_type();

	void set_variable(list<Expression*> variableName);
};






#endif
