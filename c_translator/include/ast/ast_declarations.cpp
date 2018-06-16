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
//======Declarator
Declarator::Declarator(const string& _type, Expression* _exptr) : type(_type), exptr(_exptr){}

void Declarator::add(Declarator* ptr)
{
}

string Declarator::print(int no){
  stringstream ss;
  ss << exptr->print(no) << "\n";
  cout << "Declaration is here :" << ss.str() << "\n";
      return ss.str();
}

void Declarator::set_type(string &_type)
  {
    type = _type;
  }
string Declarator::get_type()
  {
    return type;
  }

Expression* Declarator::get_id(){
	return exptr;
}


//=======declaration list
declaration_list::declaration_list() : Declarator(type, exptr){}

void declaration_list::add(Declarator* ptr)
  {
    D_LIST.push_back(ptr);
  }

void declaration_list::addVar(Expression* id){
	variableName.push_back(id);
}

string declaration_list::print(int no)
{
    stringstream ss;
    list<Declarator*>::iterator it;
    for(it = D_LIST.begin(); it != D_LIST.end(); ++it)
     {
      ss << (*it)->print(no);
     }
     return ss.str();

  }

void declaration_list::set_type(string &_type)
    {
      type = _type;
    }
string declaration_list::get_type()
    {
      return type;
    }
	


//init declare
init_declare::init_declare(Expression* _ptr, Expression* _ptr1) : ptr(_ptr), ptr1(_ptr1){}
string init_declare::print(int no)
{
	stringstream ss;
	ss << ptr->print(no) << " = " ;
	if(ptr1 != NULL){
		ss << ptr1->print(0);
	}else{
		ss << "0";
	}
	ss << "\n";
	return ss.str();
}
void init_declare::set_type(string &_type)
{

}
string init_declare::get_type()
{

}

//==================init_declarelist
string init_declarelist::print(int no){
	stringstream ss;
	list<init_declare*>::iterator it;
	 for(it = declarationlist.begin(); it != declarationlist.end(); ++it)
     {
		if(it != declarationlist.begin()){
			//ident(ss,no);
		}
		ss << (*it)->print(no);
     }
     return ss.str();
}


 init_declarelist::init_declarelist(){

 }
 void init_declarelist::add(Expression* exptr)
 {
    declarationlist.push_back((init_declare*)exptr);
 }

