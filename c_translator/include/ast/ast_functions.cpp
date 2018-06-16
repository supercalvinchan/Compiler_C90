#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include "ast_functions.hpp"
//=Function Declaration
Function_Declaration::Function_Declaration(const string &_type, const string &_id, statement* _outline, parameter_list* _p_ptr) : type(_type), id(_id), outline(_outline), p_ptr(
_p_ptr){

}

void Function_Declaration::add_variable(Variables* _v_ptr)
{
  v_ptr.push_back(_v_ptr);
}

Variables* Function_Declaration::find_variable(string name)
{
  list<Variables*>::iterator it;

  //finding variable
  for(it = v_ptr.begin(); it != v_ptr.end(); ++it)
  {
  //  if(name == (*it)->get_id())
    {
  //    return *it;
    }
  }

  //find in parameter list
    Variables* v = p_ptr->find_variable(name);
    if(v != NULL)
    {
      return v;
    }else
    {
//      return parent->find_variable(name);//function definition parent find ;
    }


}
string Function_Declaration::print(int no)
{

	stringstream ss;


	if((type.compare("int") == 0) || (type.compare("void") == 0) )
	{
		ident(ss, no);
		ss << "def ";
	}
	ss << id;
	ss << "(";
	if(p_ptr != NULL)
	{
		ss << p_ptr->print(no);
	}
	ss << ")";
	ss << ":" << "\n";
	//ss << p_ptr->print(no);
	if(!variableName.empty()){
	list<Expression*>::iterator it;
	for(it = variableName.begin(); it != variableName.end(); it++){
		ident(ss,no+1);
		string vName = (*it)->print(0);
		string::size_type pos = vName.find('=');
		ss << "global " << vName.substr(0,pos)<< "\n";  //TODO: check if case of there isn't = happens
	}
  }
	if(outline != NULL){
		ss << outline->print((no+1));
	}else{
		ident(ss, no+1);
		ss << "pass \n"; 
	}
//  ss << p_ptr->print(no);
	cout << ss.str();
	return ss.str();
}

void Function_Declaration::set_type(string &_type)
{
  type = _type;
}

string Function_Declaration::get_type()
{
  return type;
}
void Function_Declaration::set_variable(list<Expression*> input){
	variableName = input;
}


//external
external::external(){}


string external::print(int no)
{
  stringstream ss;
  list<Declarator*>::iterator it;
 for(it = D_List.begin(); it != D_List.end(); ++it)
 {	
	
   ss << (*it)->print(no) << "\n";

 }
	

  list<Function_Declaration*>::iterator itt;
  for(itt = FList.begin(); itt != FList.end(); itt++)
  {	
    ss << (*itt)->print(no);
  }
  return ss.str();
}

void external::add(Function_Declaration* exptr){
	exptr->set_variable(variableName);
    FList.push_back(exptr);

}

void external::add(Declarator* ptr){
   D_List.push_back(ptr);
}

void external::add(Expression* id){
   variableName.push_back(id);
}
 void external::set_type(string &_type)
 {

 }
 string external::get_type()
 {

 }
