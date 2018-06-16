#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>
#include <memory>
#include <stack>
#include <list>
#include "ast_variable.hpp"
#include "ast_declarations.hpp"
using namespace std;

extern list<deftype*> G_typeList;


//==================================================DEFTYPE===============================================


deftype* find_type(string type, string id)
{
  list<deftype*>::iterator it;
  for(it = G_typeList.begin(); it != G_typeList.end(); ++it)
  {
     if((*it)->get_id() == id && (*it)->get_typename() == type)
     {
       return (*it);
     }
  }
  if(type != "struct")
  {
    deftype* Pd = new deftype(type, id, NULL);
    G_typeList.push_back(Pd);
    return Pd;
  }
  return NULL;
}

string deftype::get_typename()
{
  return type;
}


uint32_t deftype::get_memberoffset(string member_id)
{
  if(structdeclarelist != NULL)
  {
     Variable* v_P;
     v_P = expression_scope.find_variable(member_id);
      assert(v_P != NULL);
      return (v_P->get_memOffset() - expression_scope.get_startpoint());
  }else if(type == "struct"){
    deftype* d_P;
    d_P = find_type(type, id);
    assert(d_P != NULL);
    return d_P->get_memberoffset(member_id);
  }else
  {
    return 0;
  }
}


deftype::deftype(string _type, string _id, declaration_list* _structdeclarelist) : type(_type), id(_id), structdeclarelist(_structdeclarelist)
{
  parent = NULL;

  if(structdeclarelist != NULL)
  {
    structdeclarelist->set_parent(this);
    list<declare*>::iterator it;
    for(it = structdeclarelist->declarationlist.begin(); it !=  structdeclarelist->declarationlist.end(); ++it)
    {
       (*it)->add_VariableToContext(expression_scope);
    }
    G_typeList.push_back(this);
  }
}
void deftype::add_List(Expression* exptr)
{

}
void deftype::print(std::ostream &dst) const
{

}
string deftype::print_assembly()
{
  stringstream ss;

  return ss.str();
}
void deftype::set_type(deftype* _type)
{

}
deftype* deftype::get_type()
{
  if(type == "struct" && structdeclarelist == NULL)
  {
    return find_type(type, id);
  }
   return this;
}
string deftype::get_id()
{
  return id;
}

uint32_t deftype::getSize()
{
  if ( (type.compare("char")==0) || (type.compare("unsigned char")==0)
      || (type.compare("signed char")==0)){
       return 1;
  }
  if (   (type.compare("int")==0)  || (type.compare("unsigned int")==0)
      || (type.compare("long")==0) || (type.compare("unsigned long")==0)){
       return 4;
  }
  if ((type.compare("short")==0) || (type.compare("unsigned short")==0)){
       return 2;
  }
  if (type.compare("float")==0){
       return 4;
  }
  if (type.compare("double")==0){
       return 8;
  }
  if (type.compare("long double")==0){
       return 10;
  }
  if(type.compare("struct")==0){
   if(structdeclarelist != NULL)
   {
     return expression_scope.get_Totalsize();
   }else{
    deftype* ptype;
    ptype = find_type(type,id);
    assert(ptype != NULL);
    return ptype->getSize();
   }

  }
  return 4;
}

//=====================================================VARIABLE======================================================

Variable::Variable(deftype* _type, const string& _name, uint32_t elements) : type(_type), name(_name){
  parent = NULL;
  var_offset = 0;
  reg = NO_REG;
  global = false;
  array_size = elements;
  if(array_size < 1)
  {
    array_size = 1;
  }
}

uint32_t Variable::get_arraysize()
{
  return array_size;
}


string Variable::print_assembly_getaddress()
  {
    stringstream ss;
    if(global)
    {
      ss << "#get address print assembly 1:" << "\n";
      ss << "lw	$2,%got(" << name << ")($28)" << "\n";

    }
    else{
    ss << "#get address print assembly 2:" << "\n";
      ss << "addiu $2, $fp, " <<get_memOffset()<< "\n";

   }
    return ss.str();
  }

string Variable::print_assembly()
{
  stringstream ss;
  ss << print_assembly_getaddress();
  ss << "lw	$2,0($2)"<<"\n";
  return ss.str();
}

void Variable::set_global(bool _global)
{
    global = _global;
}

bool Variable::is_global()
{
  return global;
}


int Variable::getSize() const{
  if(type != NULL)
  {
    return type->getSize();
  }else
  {
    return 4;
  }

}

deftype* Variable::get_Type()  {
  return type;
}

string Variable::get_name() const {
  return name;
}

void Variable::set_framePointer()
{
}

void Variable::set_scopePointer(){}


int Variable::get_register(){
  return reg;
}

void Variable::set_register(int _reg){
  reg = _reg;
}

int Variable::get_memOffset(){

  return var_offset;
}

void Variable::set_memOffset(int _var_offset){

  var_offset = _var_offset;
}

void Variable::set_Type(deftype* _type){}

void Variable::add_List(Expression* exptr){}
void Variable::print(std::ostream &dst) const{}

 void Variable::set_type(deftype* _type){
   type = _type;
 }
 deftype* Variable::get_type(){
   return type;
 }
 string Variable::get_id(){
   return get_name();
 }

 uint32_t Variable::get_Totalsize()
 {

   return getSize()*array_size;
 }
