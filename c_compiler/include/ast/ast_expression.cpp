#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>
#include <memory>
#include <stack>
#include <stdint.h>
#include <list>
#include "ast_expression.hpp"
#include "ast_variable.hpp"

uint32_t Context::loopCounter = 1;
list<deftype*> G_typeList;

Context::Context(){
   m_nTotalSize = 0;
   scope_pointer_start = 0;
   labelCounter = loopCounter;
 }

 Context::~Context()
{
    while(!vmap.empty())
  {
    Variable* p_var = vmap.top();//needs to be confirmed about top
    vmap.pop();
    delete p_var;
  }

}
  int Context::get_Totalsize()
  {
     if((m_nTotalSize % 4))
      {
      m_nTotalSize  += 4 - m_nTotalSize % 4;
    }
       return m_nTotalSize;
    }

  void Context::set_startpoint(uint32_t _start){

    uint32_t old_startpoint = scope_pointer_start;

    scope_pointer_start = _start;

    for(int i = 0; i < map1.size(); ++i)
    {
      uint32_t offset = map1[i]->get_memOffset();
      map1[i]->set_memOffset((offset + scope_pointer_start)-old_startpoint);
    }
    map <Context*, uint32_t>::iterator it;
    for (it = SubScopes.begin(); it != SubScopes.end(); ++it)
    {
      uint32_t old_subscopestartpoint = (it->first)->get_startpoint();
      it->second = (old_subscopestartpoint+scope_pointer_start)-old_startpoint;
      (it->first)->set_startpoint(it->second);
    }

  }

  uint32_t Context::get_startpoint()
  {
    return scope_pointer_start;
  }

  void Context::add_context(Context& ctext){
SubScopes[&ctext] = get_Totalsize() + scope_pointer_start;
    ctext.set_startpoint(get_Totalsize()+ scope_pointer_start);

   m_nTotalSize += ctext.get_Totalsize();
 }

void Context::add_globalitems(deftype* _type_var, const string& _name_var, uint32_t elements)
{
  Variable* p_var = new Variable(_type_var, _name_var, elements);
  p_var->set_global(true);
   vmap.push(p_var);
   map1.push_back(p_var);
   //m_nTotalSize += p_var->getSize();
}

  void Context::add_items(deftype* _type_var, const string& _name_var, uint32_t elements){
    Variable* p_var = new Variable(_type_var, _name_var, elements);
    p_var->set_memOffset(m_nTotalSize + scope_pointer_start);
     vmap.push(p_var);
     map1.push_back(p_var);
     uint32_t variablesize =  p_var->get_Totalsize();
     if((variablesize % 4 == 0)&&(m_nTotalSize % 4 != 0))
     {
       m_nTotalSize += 4 - m_nTotalSize%4;
     }
     m_nTotalSize += variablesize;
  }

  // just for parameters greater than 4
  /*void Context::add_registersvariable(const string& _type_var, const string& _name_var)
  {
      Variable* p_var = new Variable(_type_var, _name_var);
      Register_variable.push_back(p_var);
  }*/

//Findindg variable by name
  Variable* Context::find_variable(string name)
  {
    for(int i = 0; i < map1.size(); i++)
    {
      if(map1[i]->get_id() == name)
      {
        return map1[i];
      }
    }
    return NULL;
  }

//Finding variable by position
  Variable* Context::find_variable(int no)
  {
    if(no < 0 || no >= map1.size())
    {
      return NULL;
    }else
    {
      return map1[no];
    }
  }

void Context::setlabelCounter(int counter)
{
  labelCounter = counter;
}
     //add no. offset
  void Context::addpadding(int pad_size){
     m_nTotalSize += pad_size;
  }

  void Context::IncrementLoopCounter(bool bIncOnly)
  {
    loopCounter++;
    if(!bIncOnly)
    {


    labelCounter = loopCounter;
  }
  }

  uint32_t Context::get_LoopCounter()
  {
    return labelCounter;
  }

//implements in argument list
  uint32_t Context::get_VariableOffset(int no)
  {
  }

//============================================================================
  uint32_t Expressionlist::getSize()
  {
    if(!E_List.empty())
    {
      (*E_List.begin())->getSize();
    }else
    {
      return 4;
    }
  }


 Expressionlist::Expressionlist()
 {
parent = NULL;
 }
  void Expressionlist::add_List(Expression* exptr)
  {
      E_List.push_back(exptr);
      exptr->set_parent(this);
      expression_scope.add_context(exptr->expression_scope);
  }
   void Expressionlist::print(std::ostream &dst) const{

   }
   string Expressionlist::print_assembly()
   {
   stringstream ss;
   list <Expression*>::iterator it;
   for(it = E_List.begin(); it != E_List.end(); ++it)
   {
     ss <<(*it)->print_assembly();
   }
   return ss.str();
   }
  void Expressionlist::set_type(deftype* _type){}  // Setting type
  deftype* Expressionlist::get_type(){}// Getting type
  string Expressionlist::get_id(){} // Getting id
