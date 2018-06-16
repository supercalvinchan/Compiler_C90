#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include <iterator>
#include "ast_expression.hpp"


class Variables;


class Parameters
    : public Expression
{
protected:
  string specifier;
  string id;
  string type;

public:
  Parameters(string& _specifier, string& _id);

  virtual void add(Parameters* ptr);
  string print(int no) override;
   void set_type(string &_type);

    string get_type();

};


class parameter_list
    : public Parameters
{
private:
  list<Parameters*> parameterlist;
  string type;
  list<Variables*> v_ptr;
  Expression* parent;
public:
  parameter_list();

  void add(Parameters* ptr);

 void add_variable(Variables* _v_ptr);

  Variables* find_variable(string name);

   string print(int no) override;

   void set_type(string &_type);

    string get_type();

};
