#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <list>
#include "ast_expression.hpp"
#include "ast_variable.hpp"

class BinaryOperator
    : public Expression
{
private:
  Expression* left;
  Expression* right;
  string op;
  string id;
  deftype* type;
public:
  uint32_t getSize();
  BinaryOperator(Expression* _left, string& _op, Expression* _right);
  void add_List(Expression* exptr);
  void print(std::ostream &dst) const override;
   string print_assembly();
   string print_assembly_getaddress();
   void set_type(deftype* _type);
   deftype* get_type();
   string get_id();

};




#endif
