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
//Pointer
Pointer::Pointer(const string &_ptr, Expression* _exptr)
    : ptr(_ptr), exptr(_exptr)
{}

const string Pointer::getId() const
{ return ptr; }

string Pointer::print(int no)
{
}

void Pointer::set_type(string &_type){}

string Pointer::get_type(){
  return "";
}
//Variables

Variables::Variables(const string &_id) : id(_id){}


string Variables::get_id()
{
  return id;
}

string Variables::print(int no){
  stringstream ss;
  ident(ss, no);
  ss << id;
  cout << ss.str();
  return ss.str();
}

void Variables::set_type(string &_type){
   type = _type;
 }
string Variables::get_type()
 {
   return type;
 }

 //Number
 Number::Number(double _value)
     : value(_value)
 {}

 double Number::getValue() const
 { return value; }

 string Number::print(int no)
 {
   stringstream ss;
   ss << value;
   cout << ss.str();
   return ss.str();
 }

 void Number::set_type(string &_type){}

 string Number::get_type(){
   return "";
 }

 //postfix
 postfix::postfix(Expression *_exptr1 , Expression *_exptr2) : exptr1(_exptr1), exptr2(_exptr2)
 {

 }

 string postfix::print(int no){
   stringstream ss;
   ident(ss, no);
   ss << exptr1->print(0);
   if(type == "("){
		ss << "(";
   }
   else if(type == "["){
		ss << "[";
   }
   if(exptr2 != NULL)
   {
     ss << exptr2->print(0);
   }
   if(type == "("){
		ss << ")";
   }
   else if(type == "["){
		ss << "]";
   }
   return ss.str();
 }

void postfix::set_type(string &_type){
    type = _type;
  }

string postfix::get_type()
  {
    return type;
  }

//argumentexpression
argumentexpression::argumentexpression()
  {

  }

string argumentexpression::print(int no) {
    stringstream ss;

    return ss.str();
  }

void  argumentexpression::set_type(string &_type){
     type = _type;
   }

string argumentexpression::get_type()
   {
     return type;
   }


//=============array
Array::Array(Expression* _id, double _size): id(_id), size(_size) {}

string Array::print(int no){
	stringstream ss;
	//ident(ss, no);         //looks like above the AST structure somewhere it has already ident it
	ss << id->print(no);
	ss << " = [";
	for(int i = 0; i < size - 1; i++){
		ss << "0,";
	}
	ss << "0 ]  #";			//evil trick:since it's declaration, to avoid =0 automatically added after this, use # to treat that as comment
	return ss.str();
}

void Array::set_type(string &_type){
     type = _type;
   }

string Array::get_type()
   {
     return type;
   }