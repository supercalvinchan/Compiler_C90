#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include "ast_declarations.hpp"
extern deftype* find_type(string type, string id);
using namespace std;


initializerlist::initializerlist()
{
parent = NULL;
}
void initializerlist::add_List(Expression* exptr)
{
  exptr->set_parent(this);
  explist.push_back(exptr);
}
void initializerlist::print(ostream &dst) const{}
string initializerlist::print_assembly()
{
  stringstream ss;
  return ss.str();
}
void initializerlist::set_type(deftype* _type)
{

}
deftype* initializerlist::get_type()
{

}
string initializerlist::get_id()
{

}
double initializerlist::get_value()
{
  if(!explist.empty())
  {
    return (*explist.begin())->get_value();
  }else
   {
     return 0;
   }
}
string initializerlist::print_assembly_getaddress()
{

}


//===========================================init declare =============================
init_declare::init_declare(Expression* _left_exp, Expression* _right_exp):left_exp(_left_exp), right_exp(_right_exp){
parent = NULL;
if(left_exp != NULL)
{
left_exp->set_parent(this);
}
if(right_exp != NULL)
{
right_exp->set_parent(this);
}


}

void init_declare::add_List(Expression* exptr)
{

}
  string init_declare::get_id()
  {
     return left_exp->get_id();
  }
//  void add_list(declare* d_ptr);
  void init_declare::print(ostream &dst) const
  {

  }

string init_declare::print_globalvariableassembly()
{
  stringstream ss;
  string globalvariablename = left_exp->get_id();
  if(right_exp != NULL)
  {
    ss << "#init declare print_assembly global 1:" << "\n";
    ss << ".globl " << globalvariablename << "\n";
    ss << ".data" << "\n";
    ss << ".align	2" << "\n";
    ss << ".type	" <<globalvariablename<<", @object" << "\n";
    ss <<" .size	" <<globalvariablename<<", "<< ((Variable*)left_exp)->get_Totalsize() << "\n";
   ss << globalvariablename << ":" << "\n";
   Variable* v = find_variable(left_exp->get_id());
   assert(v != NULL);
   if(v->get_arraysize() > 1)
   {
     int counter = 0;
     list<Expression*>::iterator it;
     initializerlist* initP = dynamic_cast<initializerlist*>(right_exp);
     assert(initP != NULL);
     uint32_t array_size = v->get_arraysize();

     for(it = initP->explist.begin(); it != initP->explist.end(); ++it)
     {
       int value = ((primaryexpression*)(*it))->get_value();
       if(v->get_type()->get_typename() == "char")
       {
         ss << ".byte " << value << "\n";
       }else{
       ss << ".word	" << value << "\n";
     }
       counter++;
     }
      if(array_size > counter)
      {
      ss << ".space " << (array_size - counter)*v->getSize() << "\n";
      }
    }else
    {
      int value = ((primaryexpression*)right_exp)->get_value();
      if(v->get_type()->get_typename() == "char")
      {
        ss << ".byte " << value << "\n";
      }else {
      ss << ".word	" << value << "\n";
    }
    }
  }else
  {
    ss << ".comm "<<globalvariablename<<","<< ((Variable*)left_exp)->get_Totalsize() <<",4" << "\n";
  }
  return ss.str();
}


  string init_declare::print_assembly()
  {
   stringstream ss;

   if(right_exp != NULL)
   {
     assert(left_exp != NULL);
     //int array[10] = {1,2,3,4,5};
      Variable* v = find_variable(left_exp->get_id());
      assert(v != NULL);
      if(v->get_arraysize() > 1)
      {
        int counter = 0;
        list<Expression*>::iterator it;
        initializerlist* initP = dynamic_cast<initializerlist*>(right_exp);
        assert(initP != NULL);

        for(it = initP->explist.begin(); it != initP->explist.end(); ++it)
        {
          ss << (*it)->print_assembly();
          ss << "addu  $3, $2, $0\n";
          ss << v->print_assembly_getaddress();
          ss << "addi $2,$2," << counter*(v->getSize()) << "\n";
          if(v->get_type()->get_typename() == "char")
          {
            ss << "sb $3,0($2)" << "\n";
          }else
          {
          ss << "sw $3,0($2)" << "\n";
        }
          counter++;
        }
      /*    while(counter < array_size)
          {
            ss << v->print_assembly_getaddress();
            ss << "addi $2,$2," << counter*(v->getSize()) << "\n";
            ss << "add $3,$0,$0\n";
            ss << "sw $3,0($2)" << "\n";
          }
          */
      }else
      {
      ss << "#init declare print_assembly 1:" << "\n";
      ss << right_exp->print_assembly();
       ss << "#init declare print_assembly 2:" << "\n";
       ss << "addu  $3, $2, $0\n";
       ss << v->print_assembly_getaddress();
       if(v->get_type()->get_typename() == "char")
       {
         ss << "sb $3,0($2)" << "\n";
       }else
       {
       ss << "sw $3, 0($2)" << "\n";
     }
       ss << "addu $2, $3, $0" << "\n";
     }
  }
   return ss.str();
  }

  void init_declare::set_type(deftype* _type)
  {
       type = _type;
  }

deftype* init_declare::get_type()
{
    return type;
   }


//==================
void init_declarelist::print(ostream &dst) const{}
string init_declarelist::print_assembly()
{
  stringstream ss;
list<init_declare*>::iterator it;
for(it = declarationlist.begin(); it != declarationlist.end(); ++it)
{
ss << (*it)->print_assembly();
}
return ss.str();
}

void init_declarelist::set_type(deftype* _type)
{
  type = _type;

}

 deftype* init_declarelist::get_type()
 {

      return type;
 }

 init_declarelist::init_declarelist(){
   parent = NULL;

 }
 void init_declarelist::add_List(Expression* exptr)
 {
    declarationlist.push_back((init_declare*)exptr);
    exptr->set_parent(this);
    exptr->set_type(type);
 }

 string init_declarelist::get_id()
 {
   return "";
 }



string init_declarelist::print_globalvariableassembly()
{
  stringstream ss;
list<init_declare*>::iterator it;
for(it = declarationlist.begin(); it != declarationlist.end(); ++it)
{
ss << (*it)->print_globalvariableassembly();
}
return ss.str();
}


//==================
primaryexpression::primaryexpression(string _id, double _value, Expression* _index)
{
  id = _id;
  value = _value;
  parent = NULL;
  index = _index;
  type = NULL;



  expression_scope.add_items(find_type("int", ""), "");
  if(index != NULL)
  {
     index->set_parent(this);
  }
}

double primaryexpression::get_value()
{
  return value;
}

string primaryexpression::print_assembly_getaddress()
{
  stringstream ss;
  if(id != "")
  {

    Variable* v;

    v = this->find_variable(id);
    assert(v != NULL);
    ss << "#primaryexpression find variable and load it 1:"<<"\n";
      ss << v->print_assembly_getaddress()<<"\n";

      if(index != NULL)
      {
          Variable* tempVariable = NULL;
          tempVariable = find_variable(0);
          assert(tempVariable != NULL);
           ss << "sw	$2," << tempVariable->get_memOffset() <<"($fp)" << "\n";
          ss << index->print_assembly();
          ss << "li $3," << v->getSize() << "\n";
          ss << "mul $2,$3,$2\n";
          ss << "lw	$3,"<<tempVariable->get_memOffset()<<"($fp)"<<"\n";
          ss << "add $2, $3, $2\n";
      }
   }
  return ss.str();
}


uint32_t primaryexpression::getSize()
{
  if(id != "")
  {
    Variable* v;
    v = this->find_variable(id);
    if(index != NULL)
    {
      return v->getSize();
    }else
    {
      return v->get_Totalsize();
    }
  }else
  {
    return 4;
  }

}

string primaryexpression::print_assembly(){
  stringstream ss;
  if(id != "")
  {
    Variable* v;

    v = this->find_variable(id);

    assert(v != NULL);
    ss << "#primaryexpression find variable and load it 1:"<<"\n";
      ss << v->print_assembly_getaddress()<<"\n";
      if(index != NULL)
      {  Variable* tempVariable = NULL;
        tempVariable = find_variable(0);
        assert(tempVariable != NULL);
        ss << "sw	$2," << tempVariable->get_memOffset() <<"($fp)" << "\n";
        ss << index->print_assembly();
        ss << "li $3," << v->getSize() << "\n";
        ss << "mul $2,$3,$2\n";
        ss << "lw	$3,"<<tempVariable->get_memOffset()<<"($fp)"<<"\n";
        ss << "add $2, $3, $2\n";
      }
      if(v->get_type()->get_typename() == "char")
      {
        ss << "lb $2,0($2)" << "\n";
      }else
      {
      ss << "lw $2,0($2)" << "\n";
    }
   }else
   { //li	$2,3
     int int_value = value;
     ss << "#primaryexpression find value and load it 2:"<<"\n";
      ss << "li	$2," << int_value << "\n";
   }

  return ss.str();
}

void primaryexpression::add_List(Expression* exptr)
{
}

void primaryexpression::print(ostream &dst) const{}

void primaryexpression::set_type(deftype* _type)
{
  type = _type;
}

deftype* primaryexpression::get_type()
{
  if(type == NULL)
  {
      if(id != "")
    {

    Variable* v;
    v = this->find_variable(id);
    assert(v != NULL);
    type = v->get_type();

     }else
      {
       type = find_type("", "");
      }
  }
  return type;
}
string primaryexpression::get_id()
{
  return id;
}


//=================================================declare=================
//int a =2;
declare::declare(deftype* _type, init_declarelist* _exptr) : type(_type), exptr(_exptr){
     parent = NULL;
     if(exptr != NULL)
     {
     exptr->set_parent(this);
     exptr->set_type(type);
   }
}

void declare::add_globalvariableToContext(Context& ctext)
{
  if(exptr!=NULL)
  {
    list<init_declare*>::iterator it;
     for(it = exptr->declarationlist.begin(); it != exptr->declarationlist.end(); ++it)
      {
        Variable* v_ptr = dynamic_cast<Variable*>((*it)->left_exp);
        assert(v_ptr!= NULL);
        ctext.add_globalitems(type, (*it)->get_id(), v_ptr->get_arraysize() );

       }
  }


}


string declare::print_globalvariableassembly(){
  stringstream ss;

    if(exptr != NULL)
    {
  ss << "#declare print assembly global:"<<"\n";
    ss<<  exptr->print_globalvariableassembly();

    }
    return ss.str();
}

void declare::add_VariableToContext(Context& ctext)
{

if(exptr!=NULL)
{

  list<init_declare*>::iterator it;
   for(it = exptr->declarationlist.begin(); it != exptr->declarationlist.end(); ++it)
    {
      Variable* v_ptr = dynamic_cast<Variable*>((*it)->left_exp);
      assert(v_ptr!= NULL);
      ctext.add_items(type, (*it)->get_id(), v_ptr->get_arraysize() );
     }

}
}

void declare::add_List(Expression* exptr){}
string declare::get_id()
{
  return id;
}

void declare::print(ostream &dst) const{}


string declare::print_assembly()
{
  stringstream ss;

    if(exptr != NULL)
    {
  ss << "#declare print assembly:"<<"\n";
    ss<<  exptr->print_assembly();

    }
    return ss.str();
}

void declare::add_list(declare* d_ptr)
{

}
void declare::set_type(deftype* _type)
{
    type = _type;
}

deftype* declare::get_type()
{
    return type;
}

/*===========================declaration list====================================*/
declaration_list::declaration_list()
{
  parent = NULL;
}

void declaration_list::add_List(Expression* exptr){
declarationlist.push_back((declare*)exptr);

exptr->set_parent(this);

}

void declaration_list::print(ostream &dst) const {}

string declaration_list::print_assembly()
{
  list<declare*>::iterator it;
  stringstream ss;
  for(it = declarationlist.begin(); it != declarationlist.end(); ++it)
  {
    ss << "#declaration list print assembly:"<<"\n";
  ss << (*it)->print_assembly();
  }
  return ss.str();
}

string declaration_list::get_id()
{
  return id;
}

void declaration_list::set_type(deftype* _type){}

deftype* declaration_list::get_type(){}
