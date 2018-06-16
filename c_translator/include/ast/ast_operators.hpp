#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <list>
#include "ast_expression.hpp"

class BinaryOperator
    : public Expression
{
private:
  Expression* left;
  Expression* right;
  string op;

public:
  BinaryOperator(Expression* _left, string& _op, Expression* _right);
  BinaryOperator();
  string print(int no) override;

   void set_type(string &_type);
   string get_type();
   virtual void add (BinaryOperator* ptr);
};

class argumentList
	: public BinaryOperator
{
private:
	list<Expression*> argument_expression_list;
public:
	argumentList();
	void add(Expression* ptr);
	string print(int no) override;
};



#endif
