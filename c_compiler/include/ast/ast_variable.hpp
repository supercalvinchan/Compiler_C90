#ifndef DEFINE_VARIABLE_11111
#define DEFINE_VARIABLE_11111

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>
#include <memory>
#include <stack>
#include <list>
#include "ast_expression.hpp"
using namespace std;

#define NO_REG -1
class declaration_list;

class deftype
     : public Expression
{
public:
  deftype(string _type, string _id, declaration_list* _structdeclarelist);
  void add_List(Expression* exptr);
  void print(std::ostream &dst) const;
  string print_assembly();
  void set_type(deftype* _type);
  deftype* get_type();
  string get_id();
  uint32_t getSize();
  string get_typename();
  uint32_t get_memberoffset(string member_id);

private:
string type;
string id;
declaration_list* structdeclarelist;

};



class Variable
     : public Expression
{
private:
  deftype* type;
  string name;
  int var_offset;
  int reg;//0-31 // -1-31
  bool global;

  uint32_t array_size;
public:
  Variable(deftype* _type, const string& _name, uint32_t elements);
  bool is_global();
  uint32_t get_arraysize();
  //Calculating the offset of each types of variable
  int getSize() const;
  void set_global(bool _global);
  string get_name() const;
  deftype* get_Type();
  void set_framePointer();
  void add_List(Expression* exptr);
  void print(std::ostream &dst) const;
  string print_assembly();
  void set_type(deftype* _type);
  deftype* get_type();
  string get_id();
  void set_scopePointer();
  int get_register();
  void set_register(int _reg);
  int get_memOffset();
  void set_memOffset(int _var_offset);
  void set_Type(deftype* _type);
  string print_assembly_getaddress();
  uint32_t get_Totalsize();

};



#endif
