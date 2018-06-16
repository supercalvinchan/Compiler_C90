#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include "ast_primitives.hpp"


using namespace std;
//===================================================Pointer===
Pointer::Pointer(const string &_ptr, Expression* _exptr)
    : ptr(_ptr), exptr(_exptr)
{
  parent = NULL;
  exptr->set_parent(this);
}

string Pointer::get_id()
{
  return id;
}

void Pointer::add_List(Expression* exptr){}
string Pointer::getId() const
{ return ptr; }

void Pointer::print(ostream &dst) const
{
    dst<<ptr;
}
string Pointer::print_assembly()
{
}
void Pointer::set_type(deftype* _type){}
deftype* Pointer::get_type(){}

//==============================================Numbers===========================

Number::Number(double _value)
    : value(_value)
{
  parent = NULL;
}

double Number::getValue() const
{ return value; }


void Number::add_List(Expression* exptr){}
void Number::print(ostream &dst) const
{
    dst<<value;
}

string Number::print_assembly()
{
  stringstream ss;
  ss << "#Number print assembly:" << "\n";
  ss << "li $2," << value << "\n";
  return ss.str();
}

void Number::set_type(deftype* _type){}

deftype* Number::get_type(){}

string Number::get_id()
{
  return id;
}

//==============================================Array===================================
