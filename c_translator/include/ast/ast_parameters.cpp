#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include "ast_parameters.hpp"
//Parameters
Parameters::Parameters(string& _specifier, string& _id) : specifier(_specifier), id(_id){}

void Parameters::add(Parameters* ptr)
{}
string Parameters::print(int no)
{
  stringstream ss;
  ss << id;
   cout << "Parameter output:" << ss.str() << endl;
  return ss.str();
}
 void Parameters::set_type(string &_type)
  {
    type = _type;
  }

string Parameters::get_type()
  {
    return type;
  }

//parameter list
parameter_list::parameter_list() : Parameters(specifier, id){}

void parameter_list::add(Parameters* ptr)
  {
    parameterlist.push_back(ptr);
  }

void parameter_list::add_variable(Variables* _v_ptr)
{
   v_ptr.push_back(_v_ptr);
}


Variables* parameter_list::find_variable(string name)
{
  list<Variables*>::iterator it;
  for(it = v_ptr.begin(); it != v_ptr.end(); ++it)
  {
  //  if(name == (*it)->get_id())
    {
//      return *it;
    }
  }



}

string parameter_list::print(int no){
       stringstream ss;
       list<Parameters*>::iterator it;
     for(it = parameterlist.begin(); it != parameterlist.end(); ++it)
     {
		if(it != parameterlist.begin()){
			ss << ",";
		}
		ss <<(*it)->print(0);
     }
  //   cout << "Parameter output:" << ss.str() << endl;
     return ss.str();
   }

void parameter_list::set_type(string &_type)
    {
      type = _type;
    }

string parameter_list::get_type()
    {
      return type;
    }
