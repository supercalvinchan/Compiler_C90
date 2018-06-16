#include <cmath>
#include <stdint.h>
#include <iostream>
#include <list>
#include "ast_functions.hpp"
extern deftype* find_type(string type, string id);
Context root_ctext;
//=================================================Argument List

argument_list::argument_list(Expression* exptr)
{
  expression_scope.add_items(find_type("int", ""), "");
    expression_scope.add_items(find_type("int", ""), "");
    parent= NULL;
    add_List(exptr);
}

void argument_list::add_List(Expression* exptr)
{
  argumentlist.push_back(exptr);
  if(argumentlist.size() > 4)
  {
    expression_scope.add_items(exptr->get_type(), exptr->get_id());
    //add 8 offsets

  }
  exptr->set_parent(this);
}


uint32_t argument_list::get_VariableOffset(int no)
{
return expression_scope.get_VariableOffset(no);
}


void argument_list::print(ostream &dst) const{}
string argument_list::print_assembly(){
  stringstream ss;
  list<Expression*>::iterator it;
  int counter = 0;
  for(it = argumentlist.begin(); it != argumentlist.end(); ++it)
  {
  counter ++;
  (*it)->print_assembly();
  ss << (*it)->print_assembly();
  if(counter <= 4)
    {
        ss << "#argument list print assembly 1:" << "\n";
        ss << "addu $"<<counter + 3<<", $2, $0" << "\n";
    }else
    {
      ss << "#argument list print assembly 2:" << "\n";
      ss << "sw	$2,"<< 4*(counter - 1) <<"($sp)" << "\n";

    }
  }
  return ss.str();
}



void argument_list::set_type(deftype* _type){}
deftype* argument_list::get_type(){}
string argument_list::get_id(){}
void argument_list::finalize()
{
    uint32_t a = expression_scope.get_Totalsize();
    if(a > 0 && (a % 8) != 0)
    {
      expression_scope.addpadding(8-a%8);
    }
}
//===================================================Function Call========
function_calling::function_calling(deftype* _type, const string& _name, argument_list* _argument) :type(_type), name(_name), argument(_argument)
{
 if(argument != NULL)
 {
  argument->set_parent(this);
   argument->finalize();
 }
 parent = NULL;
 bHas_functioncall = true;
}

string function_calling::get_id()
{
  return id;
}

void function_calling::add_List(Expression* exptr){}

void function_calling::print(ostream &dst) const{}

string function_calling::print_assembly(){
  stringstream ss;
  if(argument != NULL)
  {
  ss << argument->print_assembly();
}
	ss << "lw	$2, %got(" << name<< ")($28)" << "\n";
  ss << "nop" << "\n";
  ss << "move	$25,$2" << "\n";
  ss << "jalr $25" << "\n";

  ss << "nop" << "\n";
  return ss.str();
}

void function_calling::set_type(deftype* _type){}

deftype* function_calling::get_type(){
  
}

//====================================================Function Declaration
Function_Declaration::Function_Declaration(string _id, parameter_list* _parameter_list, Compoundstatement* _outline) : id(_id), parameter_list_temp(_parameter_list), outline(_outline)
{
   parent = NULL;
   expression_scope.IncrementLoopCounter();
   return_label = expression_scope.get_LoopCounter();

  if(outline != NULL)
  {

    uint32_t statescope_size;
    statescope_size = outline->expression_scope.get_Totalsize();
    if(statescope_size != 0)
    {
      expression_scope.add_items(find_type("int", ""), "");
      expression_scope.add_items(find_type("int", ""), "");// add offset 8
      //expression_scope.add_context(outline->expression_scope);

      if(statescope_size % 8)//beginning
      {
        expression_scope.addpadding(8-statescope_size%8);
      }
    }
     outline->set_parent(this);
  }

  if(parameter_list_temp != NULL)
  {
  parameter_list_temp->set_parent(this);


  }

  expression_scope.add_items(find_type("int", ""), "");
  expression_scope.add_items(find_type("int", ""), "");


  root_ctext.add_context(expression_scope);

}

Variable* Function_Declaration::find_variable(string variablename)
{
    Variable* ptr;
    ptr = expression_scope.find_variable(variablename);
    if(ptr != NULL)
    {
      return ptr;
    }
  if(parameter_list_temp != NULL)
  {
    ptr = parameter_list_temp->find_variable(variablename);
    if(ptr != NULL)
    {
      return ptr;
    }
  }
  if(parent != NULL)
  {

  return parent->find_variable(variablename);
}else
  {
  return root_ctext.find_variable(variablename);
}
}

string Function_Declaration::get_id()
{
  return id;
}
void Function_Declaration::add_List(Expression* exptr){}

void Function_Declaration::print(ostream &dst) const
{
  dst << "Function id: " << id;
}

string Function_Declaration::print_assembly()
{
uint32_t offset = expression_scope.get_startpoint();
uint32_t Totalsize = expression_scope.get_Totalsize();
uint32_t endpoint = Totalsize+ offset;
if(parameter_list_temp != NULL)
{
  parameter_list_temp->expression_scope.set_startpoint(endpoint);
}
 stringstream ss;

 ss << "\t.align    	2\n";
 ss <<"\t.globl	"<<id<<"\n";
 ss <<"\t.set	nomips16\n";
 ss <<"\t.set	nomicromips\n";
 ss <<"\t.ent	"<<id << "\n";
 ss <<"\t.type\t"<<id<<", @function\n";
 ss <<id<<":\n";

 ss << "addiu	$sp,$sp,-" << endpoint << "\n";
 if(has_functioncall())
 {
 ss << "sw	$31,"<<endpoint - 4<<"($sp)\n";
 ss << "sw $fp,"<< endpoint- 8 << "($sp)"<< "\n";
}else
{
   ss << "sw $fp,"<< endpoint- 4 << "($sp)"<< "\n";
}
 ss << "move $fp,$sp" << "\n";
 if(parameter_list_temp!=NULL)
 {
   ss << "#function declaration print assembly 1:" << "\n";
 ss << parameter_list_temp->print_assembly();
}
if(outline != NULL)
{
  ss << "#function declaration print assembly 2:" << "\n";
 ss << outline->print_assembly();
}
ss << "$L" << return_label << ":\n";
if(has_functioncall()){
ss << "lw	$28,16($fp)" << "\n";

ss << "move	$sp,$fp" << "\n";
ss << "lw	$31,"<<endpoint - 4<<"($sp)\n";
ss <<	"lw	$fp,"<<endpoint- 8<< "($sp)" << "\n";
}else{
  ss << "move	$sp,$fp" << "\n";
  ss <<	"lw	$fp,"<<endpoint- 4<< "($sp)" << "\n";
}
ss << "addiu $sp,$sp," << endpoint << "\n";
ss << "j $31" << "\n";
ss << "nop" << "\n";
ss<<"\n"<<"\t.set	macro"<<"\n";
ss<<"\t.set	reorder"<<"\n";
ss<<"\t.end	"<<id<<"\n";
ss<<"\t.size	"<<id<<", .-"<<id<<"\n";
 //cout << ss.str();
 return ss.str();
}

void Function_Declaration::set_type(deftype* _type)
{
  type = _type;
}

deftype* Function_Declaration::get_type()
{
  return type;
}


//==========================================================external
external::external(){
  parent = NULL;

}
void external::print(std::ostream &dst) const{}

void external::add_List(Expression* exptr){}

string external::print_assembly()
{
  stringstream ss;

  list<declare*>::iterator itt;

  for(itt = D_List.begin(); itt != D_List.end(); ++itt)
  {
    ss << "#external print assembly 1:" << "\n";
  ss << (*itt)->print_globalvariableassembly();
  }

  list <Function_Declaration*>::iterator it;
  for(it = FList.begin(); it != FList.end(); ++it)
  {
      ss << "#external print assembly 2:" << "\n";
  ss << (*it)->print_assembly();
  }

  return ss.str();
}

void external::add(Function_Declaration* exptr){

    FList.push_back(exptr);
    exptr->set_parent(this);

}

void external::add(declare* ptr){
   D_List.push_back(ptr);
   ptr->set_parent(this);
   ptr->add_globalvariableToContext(root_ctext);

}


void external::set_type(deftype* _type)
 {
   type = _type;
 }

deftype* external::get_type()
 {
   return type;
 }

string external::get_id()
{
   return id;
}
