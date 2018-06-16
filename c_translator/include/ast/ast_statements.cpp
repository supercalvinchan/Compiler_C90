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

//statement
statement::statement(){}

void statement::add(statement* ptr)
{
}
string statement::print(int no){
  return "";
}
void statement::set_type(string &_type){}
string statement::get_type(){
  return "";
}

//statementlist
statementlist::statementlist(){}

void statementlist::add(statement* ptr)
{
    statement_list.push_back(ptr);
}

string statementlist::print(int no){
	stringstream ss;
	list<statement*>::iterator it;
	for(it = statement_list.begin(); it != statement_list.end(); it++){
		ss << (*it)->print(no);
		ss << "\n";
  }
  return ss.str();
}

void statementlist::set_type(string &_type){}

 string statementlist::get_type(){
   return "";
 }

//Compoundstatement
 Compoundstatement::Compoundstatement(statement* _left, Declarator* _right) : left(_left), right(_right){}

 string Compoundstatement::print(int no)
 {
   cout << "call Compoundstatement print" << endl;
   stringstream ss;
 //  ss << ":" << "\n";
 if(right != NULL)
 {
 ss << right->print(no);
 }
 if(left != NULL)
   {
     ss << left->print(no);
 }
  cout << "Compoundstatement output:" << ss.str() << endl;
   return ss.str();
  }

void Compoundstatement::set_type(string &_type)
   {
     type = _type;
   }

string Compoundstatement::get_type()
   {
     return type;
   }
   
void Compoundstatement::add(Expression* id){
	variableName.push_back(id);
}

void Compoundstatement::set_variable(list<Expression*> input){
	variableName = input;
}
//jump statement
jump_statement::jump_statement(Expression* _ptr, string& _type) : ptr(_ptr), type(_type){}

string jump_statement::print(int no)
{
   cout << "jump" << endl;
   stringstream ss;
   ident(ss, no);
  if(ptr != NULL)
  {

    ss << "return ";
    ss << ptr -> print(0) << "\n";

  }else
  {
    ss << "return" << endl;
  }
  cout <<"jump output:" <<ss.str();
  return ss.str();
}

void jump_statement::set_type(string &_type)
{
  type = _type;
}

string jump_statement::get_type()
{
  return type;
}



//if statement
if_statement::if_statement(Expression* _exptr, statement * _ptr, statement * _ptr1) : exptr(_exptr), ptr(_ptr), ptr1(_ptr1){
}
void if_statement::add(statement* ptr){}
string if_statement::print(int no){
  return "";
}
void if_statement::set_type(string &_type){}
string if_statement::get_type(){
  return "";
}


//Expression Do
Expression_DO::Expression_DO(Expression* _exptr) : exptr(_exptr){}

string Expression_DO::print(int no)
{
  stringstream ss;
  ss<<exptr->print(no);
  return ss.str();
}

void Expression_DO::set_type(string &_type){}   // Setting type for debugging
string Expression_DO::get_type(){}

//IF
ifstatement::ifstatement(statement* _s_ptr1, statement* _s_ptr2, Expression* _s_ptr3) : s_ptr1(_s_ptr1), s_ptr2(_s_ptr2), s_ptr3(_s_ptr3){}

void ifstatement::add(statement* exptr)
{

}
string ifstatement::print(int no)
{
  stringstream ss;
  ident(ss, no);
  ss << "if";
  ss << "(" << s_ptr3->print(0) << ")" << ":" << "\n";
  if(s_ptr2 != NULL)
  {
    ss <<  s_ptr2->print(no+1);
  }
  if(s_ptr1 != NULL)
  {	
	ident(ss,no);
    ss << "else" << ":" << "\n";
    ss << s_ptr1->print(no+1) << "\n";
  }

  return ss.str();
}

void ifstatement::set_type(string &_type)
{
   type = _type;
}

string ifstatement::get_type()
{
return type;
}

//======while=====
whilestatement::whilestatement(string& _type, Expression* _exptr, statement* _s_ptr) : type(_type), exptr(_exptr), s_ptr(_s_ptr){}

void whilestatement::add(statement* exptr)
{

}

string whilestatement::print(int no){
  stringstream ss;
  ident(ss, no);
  ss << "while "<< exptr->print(0) << ": \n";
  ss << s_ptr->print(no+1);
  return ss.str();
}

void whilestatement::set_type(string &_type){
  type = _type;
}

string whilestatement::get_type(){
  return type;
}

//==for
forstatement::forstatement(statement* _initPtr, statement* _conditionPtr, Expression* _increment, statement* _s_ptr)
	:initPtr(_initPtr),conditionPtr(_conditionPtr),increment(_increment),s_ptr(_s_ptr){}
	
string forstatement::print(int no){
	stringstream ss;
	ss << initPtr->print(no) << endl;
	ident(ss,no);
	ss << "while " << conditionPtr->print(0) << ": \n";
	ss << s_ptr->print(no + 1);
	if(increment != NULL){
		ss << "\n" << increment->print(no+1) << "\n";
	}
	return ss.str();
}