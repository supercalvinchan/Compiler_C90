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

class Parameters
    : public Expression
{
protected:
  string id;
  deftype* type;
  uint32_t index;

public:
  uint32_t get_index();
  Parameters(deftype* _type, string& _id, uint32_t index);
  void add_list(Parameters* exptr);
  virtual void add_List(Expression* exptr);
  void print(ostream &dst) const override;
  string print_assembly();
  void set_type(deftype* _type);
  deftype* get_type();
  string get_id();
};


class parameter_list
    : public Expression
{
private:
  list<Parameters*> parameterlist;
  string id;
  deftype* type;
public:
Variable* find_variable(string variablename);
void add_List(Expression*);
  parameter_list();
  void add_list(Parameters* exptr);
  void set_contextpoint(uint32_t _point);
  void print(ostream &dst) const override;
  string print_assembly();
   void set_type(deftype* _type);
    deftype* get_type();
string get_id();
};
