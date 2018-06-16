#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include <stdlib.h>
#include "ast_parameters.hpp"
#include "ast_declarations.hpp"
//=======================================PARAMETERS=======================
Parameters::Parameters(deftype* _type, string& _id, uint32_t _index) : type(_type), id(_id), index(_index)
{
  parent = NULL;

}

void Parameters::add_List(Expression* exptr)
{
}

uint32_t Parameters::get_index()
{
  return index;
}

void Parameters::print(ostream &dst) const
{
  dst << "Parameters id: " << id;
}

string Parameters::print_assembly()
{
  stringstream ss;

  //do nothing
  return ss.str();
}

void Parameters::set_type(deftype* _type)
{
  type = _type;
}

deftype* Parameters::get_type()
{
  return type;
}

string Parameters::get_id()
{
  return id;
}

void Parameters::add_list(Parameters* exptr)
{

}

//============================================================================
/*  PARAMETERS LIST           */
parameter_list::parameter_list()
{
parent = NULL;

}

Variable* parameter_list::find_variable(string variablename)
{
    return expression_scope.find_variable(variablename);
}

void parameter_list::print(ostream &dst) const
{

}

string parameter_list::print_assembly()
{
  stringstream ss;
  list<Parameters*>::iterator it;
  int counter = 0;

  for(it = parameterlist.begin(); it != parameterlist.end(); ++it)
  {
    counter++;
    if(counter <= 4)
    {
    //  sw	$2,8($fp)
      Parameters* p = *it;
      string varianblename = p->get_id();
      Variable* ptr = expression_scope.find_variable(varianblename);
      ss << "#parameter list print assembly 1:" << "\n";
      if(ptr->get_type()->get_typename() == "char")
      {
        ss << "sb $" << counter + 3 << "," << ptr->get_memOffset() <<"($fp)" << "\n";
      }else
      {
      ss << "sw $" << counter + 3 << "," << ptr->get_memOffset() <<"($fp)" << "\n";
      }
    }else{
        ss << "#parameter list print assembly 2:" << "\n";

        ss << (*it) -> print_assembly();
  }

  }

  return ss.str();
}

void parameter_list::add_List(Expression*){}

void parameter_list::set_type(deftype* _type)
 {
   type = _type;
 }
deftype* parameter_list::get_type()
  {
    return type;
  }

void parameter_list::add_list(Parameters* exptr)
{
    exptr->set_parent(this);
    parameterlist.push_back(exptr);
    expression_scope.add_items(exptr->get_type(), exptr->get_id(), exptr->get_index());

}

string parameter_list::get_id()
{
  return id;
}

void parameter_list::set_contextpoint(uint32_t _point)
{//start of the address
 expression_scope.set_startpoint(_point);
}
