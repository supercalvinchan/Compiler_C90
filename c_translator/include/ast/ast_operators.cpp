#include <string>
#include <iostream>
#include "ast_operators.hpp"

BinaryOperator::BinaryOperator(Expression* _left, string& _op, Expression* _right) : left(_left), op(_op), right(_right)
{
}

BinaryOperator::BinaryOperator(){}

string BinaryOperator::print(int no)
 {
    stringstream ss;
    ident(ss, no);
    if(op == "+")
    {
	  ss << "(";
	  if(left != NULL){
		ss << left->print(0);
	  }
      ss << " + ";
	  if(right != NULL){				//nothing in the parser construct operator with right = NULL, just leave here in case of that happens in the future
      ss<< right->print(0);
	  }
	  ss << ")";
    }
    if(op == "-")
    {
	  ss << "(";
	  if(left != NULL){
		ss << left->print(0);
	  }
      ss << " - ";
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "*")
    {
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " * ";
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "/")
    {
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " // ";			//"/" has weired behaviour, only support int now,oh python do you really need different / and // 
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "<")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " < ";
      ss << right->print(0);
	  ss << ")";
    }
	if(op == ">")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " > ";
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "==")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " == ";
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "&&")
    {
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " and ";
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "||")
    {
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " or ";
      ss << right->print(0);
	  ss << ")";
    }
    if(op == "=")
    {
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " = ";
      ss << right->print(0);
    }
    cout << ss.str();
	if(op == "&")
	{	
		ss << "(";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " & ";
		ss << right->print(0);
		ss << ")";
	}
	if(op == "^")
	{
		ss << "(";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " ^ ";
		ss << right->print(0);
		ss << ")";
	}
	if(op == "|")
	{
		ss << "(";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " | ";
		ss << right->print(0);
		ss << ")";
	}
	if(op == "+=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " += ";
		ss << right->print(0);
	}
	if(op == "-=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " -= ";
		ss << right->print(0);
	}
	if(op == "*=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " *= ";
		ss << right->print(0);
	}
	if(op == "/=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " /= ";
		ss << right->print(0);
	}
	if(op == "%=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " %= ";
		ss << right->print(0);
	}
	if(op == ">>=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " = ";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " >> ";
		ss << right->print(0);
	}
	if(op == "<<=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " = ";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " << ";
		ss << right->print(0);
	}
	if(op == "&=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " = ";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " & ";
		ss << right->print(0);
	}
	if(op == "^=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " = ";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " ^ ";
		ss << right->print(0);
	}
	if(op == "|=")
	{
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " = ";
		if(left != NULL){
		ss << left->print(0);
	  }
		ss << " | ";
		ss << right->print(0);
	}
	if(op == ">=")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " >= ";
      ss << right->print(0);
	  ss << ")";
    }
	if(op == "<=")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " <= ";
      ss << right->print(0);
	  ss << ")";
    }
	if(op == "!=")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " != ";
      ss << right->print(0);
	  ss << ")";
    }
	if(op == "%")
    { 
	  ss << "(";
      if(left != NULL){
		ss << left->print(0);
	  }
      ss << " % ";
      ss << right->print(0);
	  ss << ")";
    }
    return ss.str();
 }

 void BinaryOperator::set_type(string &_type)
 {

 }
 string BinaryOperator::get_type()
 {

 }
 void BinaryOperator::add (BinaryOperator* ptr){
	 }
 
 argumentList::argumentList(){}
 
 void argumentList::add(Expression* ptr){
	argument_expression_list.push_back(ptr);
 }
 
 string argumentList::print(int no){
	stringstream ss;
	ident(ss, no);
	list<Expression*>::iterator it;
	for(it = argument_expression_list.begin(); it != argument_expression_list.end(); it++){
		if(it != argument_expression_list.begin()){
			ss << ",";
		}
		ss << (*it)->print(no);
		
	}
	return ss.str();
 }
 
 
