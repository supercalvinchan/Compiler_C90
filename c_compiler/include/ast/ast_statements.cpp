#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include "ast_statements.hpp"
//===========================================STATEMENT==========
statement::statement(){
  parent = NULL;
}

string statement::get_id()
{
  return id;
}

void statement::add_list(statement* exptr)
{

}
void statement::add_List(Expression* exptr)
{

}
void statement::print(ostream &dst) const
{

}
string statement::print_assembly()
{

}
 void statement::set_type(deftype* _type)
 {

 }
deftype* statement::get_type()
{

}


//============================================Compound statement===========================
Compoundstatement::Compoundstatement(declaration_list* _dlist_ptr, statementlist* _slist_ptr) : dlist_ptr(_dlist_ptr), slist_ptr(_slist_ptr){
parent = NULL;
  if(dlist_ptr != NULL)
  {
    dlist_ptr->set_parent(this);
    list<declare*>::iterator it;
    list<declare*>& dlist = dlist_ptr->declarationlist;
    for(it = dlist.begin(); it != dlist.end(); ++it)
    {
         (*it)->add_VariableToContext(expression_scope);
    }
  }
  if(slist_ptr != NULL)
  {

    slist_ptr->set_parent(this);
  //  slist_ptr->add_subscope(expression_scope);

  }
}

void Compoundstatement::add_List(Expression* exptr){}
void Compoundstatement::add_list(statement* exptr){}
void Compoundstatement::print(ostream &dst) const{}
string Compoundstatement::print_assembly()
{
  stringstream ss;
  if(dlist_ptr!= NULL)
  {
    ss << "#Compound statement print assembly 1:" << "\n";
    ss << dlist_ptr->print_assembly();
  }
  if(slist_ptr!= NULL)
  {
      ss << "#Compound statement print assembly 2:" << "\n";
    ss << slist_ptr ->print_assembly();
  }

  return ss.str();
}

string Compoundstatement::get_id()
{
  return id;
}

void Compoundstatement::set_type(deftype* _type)
 {
   type = _type;
 }
deftype* Compoundstatement::get_type()
 {
   return type;
 }

 /*==================================================== STATEMENT LIST==========*/

 statementlist::statementlist(){
   parent = NULL;

 }

/*void statementlist::add_subscope(Context& ctext)
{
  list<statement*>::iterator it;
  for(it = statement_list.begin(); it != statement_list.end(); ++it)
  {
    ctext.add_context((*it)->expression_scope);
  }
}*/
 void statementlist::add_list(statement* exptr)
 {
   exptr->set_parent(this);
   statement_list.push_back(exptr);

 }

 void statementlist::add_List(Expression* exptr)
 {

 }

 string statementlist::print_assembly()
 {
   stringstream ss;
   list<statement*>::iterator it;
   for(it = statement_list.begin(); it != statement_list.end(); ++it)
   {
       ss << "#statement list print assembly 1:" << "\n";
     ss << (*it) -> print_assembly();
   }
   return ss.str();

 }

 void statementlist::print(ostream &dst) const{}

 void statementlist::set_type(deftype* _type){}

 deftype* statementlist::get_type(){}
 void statementlist::set_contextpoint(uint32_t _point)
 { //start of the address

  expression_scope.set_startpoint(_point);
 }

 string statementlist::get_id()
 {
   return id;
 }

//==============================================jump statement=======================================

jump_statement::jump_statement(Expression* _ptr) : ptr(_ptr), statement()
{
parent = NULL;
ptr->set_parent(this);
}
void jump_statement::add_List(Expression* exptr){}
void jump_statement::add_list(statement* exptr){}
void jump_statement::print(ostream &dst) const
{
  dst << "jump id: " << type;
}


string jump_statement::print_assembly()
{
  stringstream ss;
  if(ptr != NULL)
  {
      ss << "#jump statement print assembly 1:" << "\n";
  ss << ptr->print_assembly()<<"\n";

  ss << "b	$L" << get_returnlabel() << "\n";

  }
  return ss.str();
}

void jump_statement::set_type(deftype* _type)
{
  type = _type;
}

deftype* jump_statement::get_type()
{
  return type;
}

string jump_statement::get_id()
{
  return id;
}

//==============================================expressionstatement===========================
//EXPRESSION SEMICOLUMN
expressionstatement::expressionstatement(Expression* _ptr) : statement(),ptr(_ptr)
{
  parent = NULL;

  if(ptr != NULL)
  {
    ptr->set_parent(this);

  }
}

void expressionstatement::add_list(statement* exptr){}
void expressionstatement::add_List(Expression* exptr){}
void expressionstatement::print(ostream &dst) const{}
string expressionstatement::print_assembly(){
  stringstream ss;
  if(ptr != NULL)
  {
      ss << "#expression statement print assembly 1:" << "\n";
  ss << ptr->print_assembly();
  }
  return ss.str();
}
void expressionstatement::set_type(deftype* _type){}
deftype* expressionstatement::get_type(){}
string expressionstatement::get_id()
{
  return id;
}


//========================================================selectionstatement
//while
////WHILE T_LBRACKET EXPRESSION T_RBRACKET STATEMENT
//DO STATEMENT WHILE T_LBRACKET EXPRESSION T_RBRACKET SEMICOLUMN

whilestatement::whilestatement(string& _type, Expression* _exptr, statement* _s_ptr) : type(_type), exptr(_exptr), s_ptr(_s_ptr),statement()
{
  parent = NULL;
  if(exptr != NULL)
  {

    exptr->set_parent(this);
  }
  expression_scope.IncrementLoopCounter();
  if(s_ptr != NULL)
  {
      s_ptr->set_parent(this);
    //increment loop counter
    s_ptr->expression_scope.IncrementLoopCounter(true);


  }
}

void whilestatement::add_list(statement* exptr){}   //not useful
void whilestatement::add_List(Expression* exptr){} // notuseful
void whilestatement::print(ostream &dst) const{}

string whilestatement::print_assembly()
{
 stringstream ss;

 ss << "#while statement print assembly 1:" << "\n";

 if(type.compare("while") == 0)
 {
 ss << "b" << "        $L" << expression_scope.get_LoopCounter()<< "\n";
 ss << "nop" << "\n";
}
 ss << "$L" << expression_scope.get_LoopCounter() + 1<<":"<< "\n";
 if(s_ptr != NULL)
 {
   ss << "#while statement print assembly 2:" << "\n";
   ss << s_ptr->print_assembly();

 }
 ss << "#while statement print assembly 3:" << "\n";
 if(type.compare("while") == 0)
 {
 ss << "$L" << expression_scope.get_LoopCounter() <<":" <<"\n";
}
 assert(exptr != NULL);

   ss << "#while statement print assembly 4:" << "\n";
 ss << exptr->print_assembly();
 ss << "bne	$2,$0,$L" << expression_scope.get_LoopCounter() + 1 << "\n";
	ss << "nop" << "\n";

 return ss.str();
}

void whilestatement::set_type(deftype* _type)
{

}

deftype* whilestatement::get_type()
{
  return NULL;
}

string whilestatement::get_id()
{
  return id;
}

//For
//FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION T_RBRACKET STATEMENT
//{ $$ = new forstatement($3, $4, $7, $5); }
//FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION T_RBRACKET STATEMENT
//s_ptr:INITIALIZER
//s_ptr1:condition
//s_ptr2:statement
//s_ptr3:incremental
forstatement::forstatement(statement* p_Initializer, statement* p_Condtion, statement* p_Statement, Expression* p_Increment) : mp_Initializer(p_Initializer), mp_Condtion(p_Condtion), mp_Statement(p_Statement), mp_Increment
(p_Increment),statement()
{
  parent = NULL;
//1st expression statement
  if(mp_Initializer != NULL)
  {
    mp_Initializer ->set_parent(this);
  }
  expression_scope.IncrementLoopCounter();
//2nd expression statement
  if(mp_Condtion != NULL)
  {
    mp_Condtion->set_parent(this);
  }

//3rd expression

  if(mp_Increment != NULL)
  {
    mp_Increment->set_parent(this);
  }

//4th expression statement
  if( mp_Statement != NULL)
  {
    mp_Statement->set_parent(this);
    mp_Statement->expression_scope.IncrementLoopCounter(true);

  }
}

void forstatement::add_list(statement* exptr){}
void forstatement::add_List(Expression* exptr){}
void forstatement::print(ostream &dst) const{}

string forstatement::print_assembly()
{
  stringstream ss;
  ss << "#for statement print assembly 1:" << "\n";
  ss << mp_Initializer->print_assembly();
  ss << "b" << "        $L" << expression_scope.get_LoopCounter()<< "\n";
  ss << "nop" << "\n";
  ss << "$L" << expression_scope.get_LoopCounter()+1<< ":"<<"\n";
  if(mp_Statement != NULL)
  {
ss << mp_Statement->print_assembly();
}
ss << mp_Increment->print_assembly();
ss << "$L" << expression_scope.get_LoopCounter()<< ":"<<"\n";
ss << mp_Condtion->print_assembly();
ss << "nop" << "\n";

ss << "bne $2,$0,$L" << expression_scope.get_LoopCounter()+1 << "\n";
ss << "nop" << "\n";
  return ss.str();

}

void forstatement::set_type(deftype* _type){}


deftype* forstatement::get_type(){}

string forstatement::get_id()
{
  return id;
}

//========================================SELECTION STATEMENT
//IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT { $$ = new ifstatement($5, NULL, $3); }
// | IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT ELSE STATEMENT { $$ = new ifstatement($5, $7, $3); }
ifstatement::ifstatement(statement* _s_ptr1, statement* _s_ptr2, Expression* _s_ptr3) : s_ptr1(_s_ptr1), s_ptr2(_s_ptr2), s_ptr3(_s_ptr3)
{
  parent = NULL;
  //1st expression
  if(s_ptr3 != NULL)
  {
    s_ptr3->set_parent(this);
  }
   //2nd statement
   if(s_ptr1 != NULL)
   {
      s_ptr1->set_parent(this);
       expression_scope.IncrementLoopCounter();

   }
   //3rd statement
   if(s_ptr2 != NULL)
   {
      s_ptr2->set_parent(this);
       expression_scope.IncrementLoopCounter(true);

   }

}


void ifstatement::add_list(statement* exptr){}
void ifstatement::add_List(Expression* exptr){}
void ifstatement::print(ostream &dst) const{}
string ifstatement::print_assembly()
{
  stringstream ss;
  ss << "#if statement print assembly 1:" << "\n";
  ss << "nop" << "\n";
  ss << s_ptr3->print_assembly() << "\n";
  ss << "beq $2,$0,$L" << expression_scope.get_LoopCounter() << "\n";
    ss << "nop" << "\n";
    ss << s_ptr1->print_assembly() << "\n";
    ss << "nop" << "\n";
    ss << "$L" << expression_scope.get_LoopCounter()<< ":"<<"\n";
    if(s_ptr2 != NULL)
    {
    ss << s_ptr2->print_assembly() << "\n";
      ss << "$L" << expression_scope.get_LoopCounter()+1<< ":"<<"\n";
   }


  return ss.str();
}

void ifstatement::set_type(deftype* _type){}
deftype* ifstatement::get_type(){}
string ifstatement::get_id()
{
  return id;
}


//labelstatement==================================

labelstatement::labelstatement(Expression* _s_ptr3, statement* _s_ptr1) : s_ptr3(_s_ptr3), s_ptr1(_s_ptr1){
  parent = NULL;
  //1st expression
  if(s_ptr3 != NULL)
  {
    s_ptr3->set_parent(this);
  }

   //2nd statement
   if(s_ptr1 != NULL)
   {
      s_ptr1->set_parent(this);


       expression_scope.IncrementLoopCounter();

   }
}
string labelstatement::get_id()
{
  return "";
}
void labelstatement::add_list(statement* exptr)
{
}

void labelstatement::print(ostream &dst) const{}

string labelstatement::print_assembly()
{
  stringstream ss;
  return ss.str();

}

void labelstatement::set_type(deftype* _type){
  type = _type;
}

deftype* labelstatement::get_type()
{
  return type;
}
