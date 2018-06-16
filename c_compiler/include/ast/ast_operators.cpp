#include <string>
#include <iostream>
#include <list>
#include "ast_operators.hpp"
extern deftype* find_type(string type, string id);

BinaryOperator::BinaryOperator(Expression* _left, string& _op, Expression* _right) : left(_left), op(_op), right(_right){
  parent = NULL;

  type = NULL;
  if(left != NULL)
  {
  deftype* Pdef = find_type("int", "");
  expression_scope.add_items(Pdef, "");
  left->set_parent(this);
   }


if(right != NULL)
{
  right->set_parent(this);

}


}

void BinaryOperator::add_List(Expression* exptr){}

void BinaryOperator::print(std::ostream &dst) const{}

string BinaryOperator::get_id()
{
  return id;
}

 string BinaryOperator::print_assembly_getaddress()
 {
   stringstream ss;
   ss << "#operator print assembly :" << "\n";
   if(op == "*" && left == NULL)
   {
     assert(right != NULL && left == NULL);
     ss << right->print_assembly();
     return ss.str();
   }

   if(op == ".")
   {
        assert(right != NULL && left != NULL);
        deftype* d_P;
        d_P = left->get_type();
        ss << left->print_assembly_getaddress();
        ss << "addi $2,$2," << d_P->get_memberoffset(right->get_id()) << "\n";
       return ss.str();
   }

    return ss.str();
 }



string BinaryOperator::print_assembly()
 {

   stringstream ss;
   ss << "#operator print assembly :" << "\n";
  Variable* leftVariable = NULL;
  if(left != NULL)
  {
    leftVariable = find_variable(0);
  }

//=============DOT==============================================================
   if(op == ".")
   {
     assert(left != NULL && right != NULL);
     deftype* d_P;
     d_P = left->get_type();
     ss << left->print_assembly_getaddress();
     ss << "addi $2,$2," << d_P->get_memberoffset(right->get_id()) << "\n";
     ss << "lw $2,0($2)" << "\n";
     return ss.str();
   }



  //==============================unary Operator = ===============================
   if(op == "+" && left == NULL)
   {
     assert(right != NULL && left == NULL);
     ss << right->print_assembly();
     return ss.str();
   }
   if(op == "-" && left == NULL)
   {
     assert(right != NULL && left == NULL);
     ss << right->print_assembly();
     ss << "sub $2,$0,$2\n";
     return ss.str();
   }
   if(op == "&" && left == NULL)
   {
     assert(right != NULL && left == NULL);
     ss << right->print_assembly_getaddress();
     return ss.str();
   }
   if(op == "*" && left == NULL)
   {
     assert(right != NULL && left == NULL);
     ss << right->print_assembly();
     if(right->get_type()->get_typename()== "char")
     {
       ss << "lb $2,0($2)\n";
     }else
     {
     ss << "lw $2,0($2)\n";
   }
     return ss.str();
   }

   if(op == "sizeof" && right != NULL)
   {

     assert(right != NULL && left == NULL);
     ss << "#size of print" << "\n";
     ss << "li $2," << right->getSize()<<"\n";
     return ss.str();
   }

//==============================Operator = ===============================

   if(op == "=") //a=b
   {//sw	$2,8($fp)\  v_ptr = this->find_variable(left->get_id()

      assert(left!=NULL);
      ss << right->print_assembly();

      ss << "sw $2," << leftVariable->get_memOffset() << "($fp)" << "\n";
      ss << left->print_assembly_getaddress();
        ss << "lw $3," << leftVariable->get_memOffset() << "($fp)" << "\n";
      if(left->get_type()->get_typename() == "char")
      {
        ss << "sb	$3,0($2)" << "\n";
      }else
      {
      ss << "sw	$3,0($2)" << "\n";
      }
      ss << "add $2, $3, $0" << "\n";


     return ss.str();
   }
//========================================Operator ++ and --==============
  if(op=="++" || op == "--")
  {

    if(left != NULL)
    {
        assert(right==NULL);


        ss << left->print_assembly();
        ss << "add $8,$2,$0\n";
        if(op == "++")
        {
           ss << "addi $2,$2,1" << "\n";
        }else
         {
           ss << "sub $2,$2,1" << "\n";
         }

         ss << "add $3,$2,$0" << "\n";
         ss << left->print_assembly_getaddress();
         if(left->get_type()->get_typename() == "char")
         {
            ss << "sb $3,0($2)\n";
         }else
         {
         ss << "sw $3,0($2)\n";
         }
         ss << "add $2,$8,$0\n";
    }else
    {
       assert(right!=NULL);

       ss << right->print_assembly();
       if(op == "++")
       {
         ss << "addi $3,$2,1" << "\n";
       }else
       {
         ss << "sub $3,$2,1" << "\n";
       }
       ss << right->print_assembly_getaddress();
        if(right->get_type()->get_typename() == "char"){
       ss << "sb $3,0($2)\n";
     }else{
        ss << "sw $3,0($2)\n";
     }
       ss << "add $2,$3,$0" << "\n";
    }
    return ss.str();
  }

//==============================================================
bool Modyfiedleft = (op == "+=" || op == "-="|| op == "*="
|| op == "/="|| op== "%="|| op == "&="|| op == "<<="|| op ==">>=" || op =="|="|| op == "^=" );


   if(left != NULL)
   {
   ss << left->print_assembly();

  ss << "sw $2," << leftVariable->get_memOffset() << "($fp)" << "\n";
 }

   if(right != NULL)
   {
   ss << right->print_assembly();
 }
 if(left != NULL)
 {
  ss << "lw $3," << leftVariable->get_memOffset() << "($fp)" << "\n";
}
   if(op=="+") {
			ss << "add $2,$3,$2\n";
		} else if(op=="-") {
			ss << "sub $2,$3,$2\n";
		} else if(op=="&") {
			ss << "and $2,$2,$3\n";
		} else if(op=="^") {
			ss << "xor $2,$2,$3\n";
		} else if(op=="|") {
			ss << "or $2,$2,$3\n";
		} else if(op=="*") {
			ss << "mul $2,$2,$3\n";
		} else if(op=="<") {
			ss << "slt $2,$3,$2\n";
		} else if(op==">") {
			ss << "slt $2,$2,$3\n";
		} else if(op==">=") {
			ss << "sge $2,$3,$2\n";
		} else if(op=="<=") {
			ss << "sle $2,$3,$2\n";
		} else if(op=="==") {
			ss << "seq $2,$3,$2\n";
		} else if(op=="!=") {
			ss << "sne $2,$3,$2\n";
		} else if(op=="/") {
			ss << "div $2,$3,$2\n";
		} else if(op=="%") {
			ss << "div $3,$2\n";
			ss << "mfhi $2\n";
		} else if(op==">>") {
			ss << "srl $2,$3,$2\n";
		} else if(op=="<<") {
			ss << "sll $2,$3,$2\n";
		} else if(op=="&&") {
			ss << "sne $3, $3,$0\n";
			ss << "sne $2, $2,$0\n";
			ss << "and $2, $3,$2\n";
		} else if(op=="||") {
			ss << "sne $3,$3,$0\n";
			ss << "sne $2,$2,$0\n";
			ss << "or $2,$3,$2\n";
		}



//====================================================

    else if(op == "+=")
    {    // a += b   a = a + b a + b
      //a = b
      ss << "add $2,$3,$2\n";
    }else if(op == "|="){
    ss << "or $2,$2,$3\n";
    }
    else if(op == "-=")
    {// a -= b
      // a = a - b;
      ss << "sub $2,$3,$2\n";
    }else if(op == "*=")
    {
      ss << "mul $2,$3,$2\n";
    }else if(op == "/=")
    {
      ss << "div $2,$3,$2\n";
    }else if(op == "%=")
    {
      ss << "mod $2,$3,$2\n";
    }else if(op == "&=")
    {
      ss << "and $2,$3,$2\n";
    }else if(op == ">>=")
    {

      ss << "srl $2,$3,$2\n";
    }else if(op == "<<=")
    {
      ss << "sll $2,$3,$2\n";
    }else if(op == "^=")
    {
      ss << "xor $2,$2,$3\n";
    }
    if(Modyfiedleft)
    {
       assert(left!=NULL);
       ss << "add $3,$2,$0" << "\n";
       ss << left->print_assembly_getaddress();
       if (left->get_type()->get_typename() == "char")
       {
        ss << "sb	$3,0($2)" << "\n";
       }else
       {
       ss << "sw $3,0($2)" << "\n";
     }
       ss << "add $2,$3,$0" << "\n";
    }
		return ss.str();

 }


uint32_t BinaryOperator::getSize()
{
  if(left != NULL)
  {
    return left->getSize();
  }else
  {
    assert(right != NULL);
    return right->getSize();
  }
}

void BinaryOperator::set_type(deftype* _type)
 {

 }

 deftype* BinaryOperator::get_type()
 {
   if(type == NULL)
   {

   if(left != NULL)
   {
    type = left->get_type();
   }else if(right != NULL)
   {
    type = right->get_type();
  }else
  {
   type = find_type("int", "");
  }
  }
  return type;

 }
