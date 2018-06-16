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

//=================================================Declarator
class Declarator
    : public Expression
{
protected:
  string type;
  Expression* exptr;
public:
  Declarator(const string& _type, Expression* _exptr);
  virtual void add(Declarator* ptr);
  string print(int no) override;
  void set_type(string &_type);
  string get_type();
  Expression* get_id();
  void addVar(Expression* id){};
};

//===================================================DECLARATION LIST
class declaration_list
     : public Declarator
{
public:
	declaration_list();

	void add(Declarator* ptr);
	void addVar(Expression* id);
	string print(int no) override;
	void set_type(string &_type);
	string get_type();
	
private:
	string type;
	list<Declarator*> D_LIST;
	list<Expression*> variableName;

};

//===================================================INIT DECLARATOR
class init_declare
     : public Expression
{
public:
  init_declare(Expression* _ptr, Expression* _ptr1);
  string print(int no) override;
  void set_type(string &_type);
  string get_type();
private:
  string type;
  Expression* ptr;
  Expression* ptr1;


};

//init declarelist===========================================
class init_declarelist
    : public Expression
{

private:
  list<init_declare*> declarationlist;

public:
  init_declarelist();
  void add(Expression* exptr);
  string print(int no) override;
  
  void set_type(string &_type){}
  string get_type(){}
};