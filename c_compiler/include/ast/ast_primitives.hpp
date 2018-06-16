#ifndef ast_primitives_hpp
#define ast_primitives_hpp
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <sstream>
#include <list>
#include "ast_expression.hpp"
#include "ast_variable.hpp"

using namespace std;

class Pointer
    : public Expression
{
private:
    string ptr;
    Expression* exptr;
    string id;
public:
    Pointer(const string &_ptr, Expression* _exptr);
     void add_List(Expression* exptr);
    string getId() const;
    void print(ostream &dst) const override;
    string print_assembly();
    void set_type(deftype* _type);
    deftype* get_type();
    string get_id();

};


class Number
    : public Expression
{
private:
    double value;
    string id;
public:
    Number(double _value);
    double getValue() const;
    void add_List(Expression* exptr);
    void print(ostream &dst) const override;
    string print_assembly();
    void set_type(deftype* _type);
    deftype* get_type();
    string get_id();
};







#endif
