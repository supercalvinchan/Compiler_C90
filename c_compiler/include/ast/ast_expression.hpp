#ifndef ast_expression_hpp
#define ast_expression_hpp
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>
#include <memory>
#include <stack>
#include <list>
#include "stdint.h"

using namespace std;

class Variable;
class Expression;
class deftype;
/*
|r0        Always 0 |        |r1        Reserved for assembler |
|r2-r3     Stores result |      |r4-r7     Stores arguments |
|r8-r15    Temporaries, not saved |  |r16-r23   Contents saved for later |
|r24-r25   More temporaries not saved | |r26-r27   Reserved by OS |
|r28       Global pointer | |r29        Stack pointer  sp |
|r30       Frame pointer fp | |r31      Return address |
*/
typedef Expression *ExpressionPtr;

class Context
{
public:
  Context();
  void set_startpoint(uint32_t _start);
  ~Context();
  void add_globalitems(deftype* _type_var, const string& _name_var, uint32_t elements = 1);
      //scope inside scope; relase SubScopes

     //After doing operations
  void add_context(Context& ctext);
      //Add variables
  void add_items(deftype* _type_var, const string& _name_var, uint32_t elements= 1);
  int get_Totalsize();
  void addpadding(int pad_size);
  //void add_registersvariable(const string& _type_var, const string& _name_var);
  void IncrementLoopCounter(bool bIncOnly = false); // e.g foe while: L2 L1 label
  //void DecrementLoopCounter(); // e.g foe while: L2 L1 label
  uint32_t get_LoopCounter();
  string makeLabel(string base);
  static uint32_t loopCounter; // for while // global
  void setlabelCounter(int counter);
  Variable* find_variable(string name); //base on name
  Variable* find_variable(int no);  // base on position
  //need to confirm
  uint32_t get_VariableOffset(int no);

  uint32_t get_startpoint();


private:
    uint32_t scope_pointer_start; //pointer location which inherit from the previous scope
    stack<Variable*>vmap;          //Variable stack
       //!! Scope could be inside scope // context is a scope
    vector<Variable*> map1;  // finding variable in the map
    int m_nTotalSize;
    vector<Variable*> Register_variable; // just for parameters greater than 4
    uint32_t labelCounter; //
    map <Context*, uint32_t> SubScopes;

};

extern Context root_ctext;//global context

class Expression
{
protected:
  Expression* parent;
public:
  bool bHas_functioncall;
    Context expression_scope;

    //Expression* parent;
    uint32_t return_label;
Expression(){
  return_label = 0;
  bHas_functioncall = 0;
}

    bool has_functioncall()
    {
      return bHas_functioncall;
    }

    void set_hasfunctioncall(bool has_call)
    {
       bHas_functioncall= has_call;
       if(parent != NULL && bHas_functioncall)
       {
         parent->set_hasfunctioncall(true);
       }
    }

    void set_parent(Expression* _parent)
    {
      parent = _parent;
      if(parent != NULL && bHas_functioncall)
      {
        parent->set_hasfunctioncall(true);
      }
      parent->expression_scope.add_context(expression_scope);
    }


    virtual ~Expression()
    {}

  uint32_t get_returnlabel()
  {
    if(return_label != 0)
    {
      return return_label;
    }
    if(parent != NULL)
    {
      return parent->get_returnlabel();
    }
    return return_label;
  }

    virtual Variable* find_variable(string variablename)
    {
        Variable* ptr;
        ptr = expression_scope.find_variable(variablename);
        if(ptr != NULL)
        {
          return ptr;
        }

      if(parent != NULL)
      {
      return parent->find_variable(variablename);
    }else
      {
      return root_ctext.find_variable(variablename);
    }
  }

  virtual double get_value()
  {
    return 0;
  }

virtual string print_assembly_getaddress()
{
  return "";
}
  virtual Variable* find_variable(int no)
  {
      return expression_scope.find_variable(no);
  }

   virtual void add_items(deftype* _type_var, const string& _name_var, uint32_t elements = 1)
   {
      expression_scope.add_items(_type_var, _name_var, elements);
   }

   virtual uint32_t getSize()
   {
  return 4;
  }
    virtual void add_List(Expression* exptr) = 0;// not useful so far, lazy to change, maybe delete it after
    virtual void print(std::ostream &dst) const =0; // we could use to print PYTHON later
     virtual string print_assembly() = 0; // print mips code
     virtual void set_type(deftype* _type) = 0;   // Setting type
     virtual deftype* get_type() = 0; // Getting type
     virtual string get_id() = 0;   // Getting id
};


class Expressionlist
     : public Expression
{
private:
  list <Expression*> E_List;

public:
  uint32_t getSize();
   Expressionlist();
    void add_List(Expression* exptr);
     void print(std::ostream &dst) const ;
     string print_assembly();
    void set_type(deftype* _type);   // Setting type
    deftype* get_type();// Getting type
    string get_id(); // Getting id


};




/*
In our MIPS code generator, we are going to allocate the registers in following declaration:
$0: zero
$2: holding return value
$4, $5, $6, $7: first four arguments to functions, but move to stack immediately
$3: holding temporary results for binary operations (e.g. “+”, “-”, “*”, “/”)
$8: holding final result of the expression
$9: address where the variables read or write from
$28: global pointer
$29: stack pointer
$30: frame pointer
$31: return address
*/




#endif
