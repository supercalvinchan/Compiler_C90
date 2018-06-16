%code requires{
  #include "ast.hpp"
  #include "iostream"

  #include <stdio.h>
  #include <cassert>

  extern Expression *g_root; // A way of getting the AST out

#define YYDEBUG 1
  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

  using namespace std;
}

// Represents the value associated with any kind of
// AST node.
%union{
  Expression *expr;
  double number;
  std::string *string;
  Parameters *p_ptr;
  statement *s_str;
  statementlist *slist_ptr;
  declare *dec_ptr;
  Compoundstatement * compound_ptr;
  parameter_list *plist_ptr;
  argument_list *arg_ptr;
  external *ex_ptr;
  Function_Declaration *f_ptr;
  declaration_list* dlist_ptr;
  init_declarelist* init_listptr;
  deftype* Pdt;
}

%token T_NUMBER T_VARIABLE T_LBRACKET T_RBRACKET T_TIMES T_DIVIDE T_PLUS T_MINUS T_EXPONENT MIDDLE_RBRACKET MIDDLE_LBRACKET DOT AND EXCLANATION TIDLE PERCENTAGE SMALLER LARGER OR QUESTION ELLIPSIS RIGHT_ASSIGN LEFT_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN RIGHT_OP LEFT_OP INC_OP DEC_OP PTR_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP SEMICOLUMN LARGE_RBRACKET LARGE_MBRACKET COMMA COLON EQUAL

%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VIOLATILE WHILE
%type <dlist_ptr> DECLARATION_LIST
%type <init_listptr> INIT_DECLARATOR_LIST
%type <slist_ptr> STATEMENT_LIST
%type <f_ptr> FUNCTION
%type <expr> CONSTANT_EXPRESSION POSTFIX_EXPRESSION DECLARATOR ASSIGNMENT_EXRRESSION PRIMARY_EXPRESSION UNARY_EXPRESSION CAST_EXPRESSION MULTIPLICATIVE_EXPRESSION ADDITIVE_EXPRESSION SHIFT_EXPRESSION RELATIONAL_EXPRESSION EQUALITY_EXPRESSION AND_EXPRESSION EXCLUSIVE_OR_EXPRESSION INCLUSIVE_OR_EXPRESSION LOGICAL_AND_EXPRESSION LOGICAL_OR_EXPRESSION CONDITIONAL_EXPRESSION EXPRESSION INIT_DECLARATOR DIRECT_DECLARATOR PROGRAM TRANSLATION_UNIT INITIALIZER INITIALIZER_LIST
%type <ex_ptr> EXTERNAL_DECLARATION
%type <number> T_NUMBER
%type <p_ptr> PARAMETERS
%type <plist_ptr> PARAMETERS_LIST
%type <dec_ptr> DECLARATION
%type <compound_ptr> COMPOUND_STATEMENT
%type <s_str> JUMP_STATEMENT STATEMENT EXPRESSION_STATEMENT SELECTION_STATEMENT ITERATION_STATEMENT LABEL_STATEMENT
%type <arg_ptr> ARGUMENT_EXPRESSION_LIST
%type <string> DOT STRUCT_OR_UNION STRUCT UNION SIZEOF TYPE_QUALIFIER_LIST INC_OP DEC_OP DO WHILE PERCENTAGE T_DIVIDE RIGHT_OP LEFT_OP GE_OP LE_OP LARGER SMALLER NE_OP EQ_OP T_EXPONENT OR AND_OP OR_OP GOTO CONTINUE BREAK POINTER RETURN TYPEDEF EXTERN STATIC AUTO REGISTER STORAGE_CLASS_SPECIFIER VIOLATILE CONST TYPE_QUALIFIER EQUAL MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN ASSIGNMENT_OPERATOR T_VARIABLE VOID CHAR INT LONG FLOAT DOUBLE SIGNED UNSIGNED UNARY_OPERATOR AND T_TIMES T_PLUS T_MINUS TIDLE EXCLANATION
%type <Pdt> TYPE_SPECIFIER SPECIFIER_QUANTIFIER_LIST DECLARATION_SPECIFIERS TYPE_NAME STRUCT_OR_UNION_SPECIFIER

%start PROGRAM

%%
PROGRAM : TRANSLATION_UNIT		{ g_root = $1; }

TRANSLATION_UNIT:	EXTERNAL_DECLARATION	{$$ = $1;}

EXTERNAL_DECLARATION:	FUNCTION{ $$ = new external(); $$->add($1); }
                    | EXTERNAL_DECLARATION FUNCTION { $$->add($2); }
                    | DECLARATION{ $$ = new external(); $$->add($1); }
                    | EXTERNAL_DECLARATION DECLARATION { $$->add($2); }

FUNCTION : DECLARATION_SPECIFIERS T_VARIABLE T_LBRACKET T_RBRACKET COMPOUND_STATEMENT {
          $$ = new Function_Declaration(*$2, NULL, $5); $$->set_type($1); }
        | DECLARATION_SPECIFIERS T_VARIABLE T_LBRACKET PARAMETERS_LIST T_RBRACKET COMPOUND_STATEMENT  {
              $$ = new Function_Declaration(*$2, $4, $6); $$->set_type($1); }
        | DECLARATION_SPECIFIERS T_VARIABLE T_RBRACKET PARAMETERS_LIST T_RBRACKET SEMICOLUMN
         {
           $$ = new Function_Declaration(*$2, $4, NULL); $$->set_type($1); }
        | DECLARATION_SPECIFIERS POINTER T_VARIABLE T_RBRACKET PARAMETERS_LIST T_RBRACKET COMPOUND_STATEMENT{
           $$ = new Function_Declaration(*$3, $5, $7); $$->set_type(new deftype(*$2, "", NULL)); }
        |  DECLARATION_SPECIFIERS POINTER T_VARIABLE T_LBRACKET T_RBRACKET COMPOUND_STATEMENT{
                  $$ = new Function_Declaration(*$3, NULL, $6); $$->set_type(new deftype(*$2, "", NULL)); }


PARAMETERS :  SPECIFIER_QUANTIFIER_LIST T_VARIABLE  {
          $$ = new Parameters($1, *$2, 1); $$->set_type($1); }
          | SPECIFIER_QUANTIFIER_LIST POINTER T_VARIABLE {
                    $$ = new Parameters($1, *$3, 1); $$->set_type(new deftype(*$2, "", NULL));}
          | SPECIFIER_QUANTIFIER_LIST T_VARIABLE MIDDLE_LBRACKET CONSTANT_EXPRESSION MIDDLE_RBRACKET {
               $$ = new Parameters($1, *$2, (int)($4->get_value())); $$->set_type($1);}


PARAMETERS_LIST : PARAMETERS { $$ = new parameter_list(); $$->add_list($1); }
                | PARAMETERS_LIST COMMA PARAMETERS { $$->add_list($3); }

SPECIFIER_QUANTIFIER_LIST : TYPE_SPECIFIER SPECIFIER_QUANTIFIER_LIST
                          | TYPE_SPECIFIER { $$ = $1; }
                          | TYPE_QUALIFIER SPECIFIER_QUANTIFIER_LIST
                          | TYPE_QUALIFIER { $$ = new deftype(*$1, "", NULL); }

COMPOUND_STATEMENT :	LARGE_RBRACKET LARGE_MBRACKET {}
                   | LARGE_RBRACKET STATEMENT_LIST LARGE_MBRACKET{ $$ = new Compoundstatement(NULL, $2); }
                   | LARGE_RBRACKET DECLARATION_LIST LARGE_MBRACKET{ $$ = new Compoundstatement($2, NULL);}
                   | LARGE_RBRACKET DECLARATION_LIST STATEMENT_LIST LARGE_MBRACKET{ $$ = new Compoundstatement($2, $3); }

STATEMENT_LIST:	STATEMENT { $$ = new statementlist();  $$->add_list($1); }
						|STATEMENT_LIST STATEMENT {$$->add_list($2); }

STATEMENT:	JUMP_STATEMENT { $$ = $1; }
					| COMPOUND_STATEMENT { $$ = $1; }
          | SELECTION_STATEMENT { $$ = $1; }
          | ITERATION_STATEMENT { $$ = $1; }
          | EXPRESSION_STATEMENT { $$ = $1; }
          | LABEL_STATEMENT { $$ = $1; }

LABEL_STATEMENT : T_VARIABLE COLON STATEMENT
                | CASE CONDITIONAL_EXPRESSION COLON STATEMENT
                | DEFAULT COLON STATEMENT

JUMP_STATEMENT : RETURN SEMICOLUMN  { $$ = new jump_statement(NULL); }
          		 | RETURN EXPRESSION SEMICOLUMN  { $$ = new jump_statement($2); }
               | GOTO T_VARIABLE SEMICOLUMN
               | CONTINUE SEMICOLUMN { $$ = new jump_statement(NULL); }
               | BREAK SEMICOLUMN   { $$ = new jump_statement(NULL); }

ITERATION_STATEMENT : WHILE T_LBRACKET EXPRESSION T_RBRACKET STATEMENT { $$ = new whilestatement(*$1, $3, $5); }
                    | DO STATEMENT WHILE T_LBRACKET EXPRESSION T_RBRACKET SEMICOLUMN { $$ = new whilestatement(*$1, $5, $2); }
                    | FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT T_RBRACKET STATEMENT { $$ = new forstatement($3, $4, $6, NULL); }
                    | FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION T_RBRACKET STATEMENT { $$ = new forstatement($3, $4, $7, $5); }

SELECTION_STATEMENT : IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT { $$ = new ifstatement($5, NULL, $3); }
                    | IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT ELSE STATEMENT { $$ = new ifstatement($5, $7, $3); }
                    | SWITCH T_LBRACKET EXPRESSION T_RBRACKET STATEMENT { $$ = new ifstatement($5, NULL, $3); }

EXPRESSION_STATEMENT : SEMICOLUMN {}
                     | EXPRESSION SEMICOLUMN { $$ = new expressionstatement($1); }

EXPRESSION : ASSIGNMENT_EXRRESSION { $$ = new Expressionlist(); $$ -> add_List($1); }
          | EXPRESSION COMMA ASSIGNMENT_EXRRESSION {$$-> add_List($3);}

DECLARATION_LIST : DECLARATION { $$ = new declaration_list(); $$ -> add_List($1); }
                | DECLARATION_LIST DECLARATION { $$ -> add_List($2); }

DECLARATION : DECLARATION_SPECIFIERS SEMICOLUMN { $$ = new declare($1, NULL); $$->set_type($1); }
            | DECLARATION_SPECIFIERS INIT_DECLARATOR_LIST SEMICOLUMN { $$ = new declare($1, $2);  $$->set_type($1);}

DECLARATION_SPECIFIERS : TYPE_SPECIFIER  { $$ = $1; }
                       | TYPE_SPECIFIER DECLARATION_SPECIFIERS { $$ = $2; }
                       | TYPE_QUALIFIER  { $$ = new deftype(*$1, "", NULL); }
                       | TYPE_QUALIFIER DECLARATION_SPECIFIERS { $$ = $2; }
                       | STORAGE_CLASS_SPECIFIER { $$ = new deftype(*$1, "", NULL); }
                       | STORAGE_CLASS_SPECIFIER DECLARATION_SPECIFIERS  { $$ = $2; }

INIT_DECLARATOR_LIST : INIT_DECLARATOR { $$ = new init_declarelist(); $$->add_List($1); }
                    | INIT_DECLARATOR_LIST COMMA INIT_DECLARATOR {$1->add_List($3); }

INIT_DECLARATOR : DECLARATOR { $$ = new init_declare($1, NULL); }
                | DECLARATOR EQUAL INITIALIZER { $$ = new init_declare($1, $3); }

DECLARATOR  :  DIRECT_DECLARATOR { $$ = $1; }

INITIALIZER : ASSIGNMENT_EXRRESSION { $$ = $1; }
            | LARGE_RBRACKET INITIALIZER_LIST LARGE_MBRACKET { $$ = $2; }
            | LARGE_RBRACKET INITIALIZER_LIST COMMA LARGE_MBRACKET { $$ = $2; }

INITIALIZER_LIST : INITIALIZER { $$ = new initializerlist(); $$ -> add_List($1); }
                 | INITIALIZER_LIST COMMA INITIALIZER { $1 -> add_List($3); }

TYPE_QUALIFIER : CONST { $$ = $1; }
              | VIOLATILE { $$ = $1; }

STORAGE_CLASS_SPECIFIER : TYPEDEF { $$ = $1; }
                        | EXTERN { $$ = $1; }
                        | STATIC { $$ = $1; }
                        | AUTO { $$ = $1; }
                        | REGISTER { $$ = $1; }

DIRECT_DECLARATOR : T_VARIABLE { $$ = new Variable(NULL, *$1, 1); }
                  | T_LBRACKET DECLARATOR T_RBRACKET { $$ = $2; }
                  | T_VARIABLE MIDDLE_LBRACKET CONSTANT_EXPRESSION MIDDLE_RBRACKET {
                  $$ = new Variable(NULL, *$1, (uint32_t)($3->get_value()));}

CONSTANT_EXPRESSION : CONDITIONAL_EXPRESSION

ASSIGNMENT_EXRRESSION : CONDITIONAL_EXPRESSION { $$ = $1; }
                      | UNARY_EXPRESSION ASSIGNMENT_OPERATOR ASSIGNMENT_EXRRESSION { $$ = new BinaryOperator($1,*$2,$3);}

CONDITIONAL_EXPRESSION : LOGICAL_OR_EXPRESSION { $$ = $1; }
                      | LOGICAL_OR_EXPRESSION QUESTION EXPRESSION COLON CONDITIONAL_EXPRESSION

LOGICAL_OR_EXPRESSION : LOGICAL_AND_EXPRESSION { $$ = $1; }
                      | LOGICAL_OR_EXPRESSION OR_OP LOGICAL_AND_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

LOGICAL_AND_EXPRESSION : INCLUSIVE_OR_EXPRESSION { $$ = $1; }
                       | LOGICAL_AND_EXPRESSION AND_OP INCLUSIVE_OR_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

INCLUSIVE_OR_EXPRESSION : EXCLUSIVE_OR_EXPRESSION { $$ = $1; }
                        | INCLUSIVE_OR_EXPRESSION OR EXCLUSIVE_OR_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

EXCLUSIVE_OR_EXPRESSION : AND_EXPRESSION { $$ = $1; }
                        | EXCLUSIVE_OR_EXPRESSION T_EXPONENT AND_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

AND_EXPRESSION : EQUALITY_EXPRESSION { $$ = $1; }
               | AND_EXPRESSION AND EQUALITY_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

EQUALITY_EXPRESSION : RELATIONAL_EXPRESSION { $$ = $1; }
                    | EQUALITY_EXPRESSION EQ_OP RELATIONAL_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                    | EQUALITY_EXPRESSION NE_OP RELATIONAL_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

RELATIONAL_EXPRESSION : SHIFT_EXPRESSION { $$ = $1; }
                      | RELATIONAL_EXPRESSION SMALLER SHIFT_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                      | RELATIONAL_EXPRESSION LARGER SHIFT_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                      | RELATIONAL_EXPRESSION LE_OP SHIFT_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                      | RELATIONAL_EXPRESSION GE_OP SHIFT_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

SHIFT_EXPRESSION : ADDITIVE_EXPRESSION { $$ = $1; }
                 | SHIFT_EXPRESSION LEFT_OP ADDITIVE_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                 | SHIFT_EXPRESSION RIGHT_OP ADDITIVE_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

ADDITIVE_EXPRESSION : MULTIPLICATIVE_EXPRESSION { $$ = $1; }
                    | ADDITIVE_EXPRESSION T_PLUS MULTIPLICATIVE_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                    | ADDITIVE_EXPRESSION T_MINUS MULTIPLICATIVE_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

MULTIPLICATIVE_EXPRESSION : CAST_EXPRESSION { $$ = $1; }
                          | MULTIPLICATIVE_EXPRESSION T_TIMES CAST_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }
                          | MULTIPLICATIVE_EXPRESSION T_DIVIDE CAST_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3);}
                          | MULTIPLICATIVE_EXPRESSION PERCENTAGE CAST_EXPRESSION { $$ = new BinaryOperator($1,*$2,$3); }

CAST_EXPRESSION : UNARY_EXPRESSION { $$ = $1; }
                | T_LBRACKET TYPE_NAME T_RBRACKET CAST_EXPRESSION

TYPE_NAME : TYPE_SPECIFIER { $$ = $1; }

UNARY_EXPRESSION : POSTFIX_EXPRESSION { $$ = $1; }
                 | INC_OP UNARY_EXPRESSION { $$ = new BinaryOperator(NULL,*$1,$2); }
                 | DEC_OP UNARY_EXPRESSION { $$ = new BinaryOperator(NULL,*$1,$2); }
                 | UNARY_OPERATOR CAST_EXPRESSION { $$ = new BinaryOperator(NULL,*$1,$2); }
                 | SIZEOF UNARY_EXPRESSION { $$ = new BinaryOperator(NULL,*$1,$2); }
                 | SIZEOF T_LBRACKET TYPE_NAME T_RBRACKET{
                 primaryexpression* variable = new primaryexpression($3->get_typename(), 0, NULL);
                 $$ = new BinaryOperator(NULL,*$1,variable); }

ARGUMENT_EXPRESSION_LIST : ASSIGNMENT_EXRRESSION { $$ = new argument_list($1); }
                        | ARGUMENT_EXPRESSION_LIST COMMA ASSIGNMENT_EXRRESSION { $$ -> add_List($3); }

POSTFIX_EXPRESSION : PRIMARY_EXPRESSION { $$ = $1; }
                   | POSTFIX_EXPRESSION T_LBRACKET T_RBRACKET { $$ = new function_calling(NULL, $1->get_id(), NULL); }
                   | POSTFIX_EXPRESSION T_LBRACKET ARGUMENT_EXPRESSION_LIST T_RBRACKET { $$ = new function_calling(NULL, $1->get_id(),$3); }
                   | POSTFIX_EXPRESSION DOT T_VARIABLE {
                    primaryexpression* P = new primaryexpression(*$3, 0);
                   $$ = new BinaryOperator($1,*$2, P); }
                   | POSTFIX_EXPRESSION PTR_OP T_VARIABLE
                   | POSTFIX_EXPRESSION INC_OP { $$ = new BinaryOperator($1,*$2, NULL); }
                   | POSTFIX_EXPRESSION DEC_OP { $$ = new BinaryOperator($1,*$2, NULL); }

PRIMARY_EXPRESSION : T_NUMBER { $$ = new primaryexpression("", $1); }
                   | T_VARIABLE { $$ = new primaryexpression(*$1, 0); }
                   | T_LBRACKET EXPRESSION T_RBRACKET { $$ = $2; }
                   | T_VARIABLE MIDDLE_LBRACKET EXPRESSION MIDDLE_RBRACKET { $$ = new primaryexpression(*$1, 0, $3); }


ASSIGNMENT_OPERATOR : EQUAL { $$ = $1; }
                   | MUL_ASSIGN { $$ = $1; } //*=
                   | DIV_ASSIGN { $$ = $1; } // /=
                   | MOD_ASSIGN { $$ = $1; }  // %=
                   | ADD_ASSIGN { $$ = $1; }  // +=
                   | SUB_ASSIGN { $$ = $1; }  // -=
                   | LEFT_ASSIGN { $$ = $1; } // <<=
                   | RIGHT_ASSIGN { $$ = $1; } // >>=
                   | AND_ASSIGN { $$ = $1; } // &=
                   | XOR_ASSIGN { $$ = $1; }  // ^=
                   | OR_ASSIGN { $$ = $1; }  // |=

UNARY_OPERATOR : AND { $$ = $1; }
               | T_TIMES { $$ = $1; }
               | T_PLUS { $$ = $1; }
               | T_MINUS { $$ = $1; }
               | TIDLE { $$ = $1; }
               | EXCLANATION { $$ = $1; }


TYPE_QUALIFIER_LIST : TYPE_QUALIFIER
                    : TYPE_QUALIFIER_LIST TYPE_QUALIFIER


POINTER : T_TIMES { $$ = $1; }
        | T_TIMES POINTER  { $$ = $1; }

TYPE_SPECIFIER : VOID { $$ = new deftype(*$1, "", NULL);  }
               | CHAR { $$ = new deftype(*$1, "", NULL);  }
               | INT { $$ = new deftype(*$1, "", NULL);  }
               | LONG { $$ = new deftype(*$1, "", NULL);  }
               | FLOAT { $$ = new deftype(*$1, "", NULL);  }
               | DOUBLE { $$ = new deftype(*$1, "", NULL);  }
               | SIGNED { $$ = new deftype(*$1, "", NULL);  }
               | UNSIGNED { $$ = new deftype(*$1, "", NULL);  }
               | POINTER  { $$ = new deftype(*$1, "", NULL);  }
               | TYPE_SPECIFIER POINTER { $$ = new deftype(*$2, "", NULL);  }
               | STRUCT_OR_UNION_SPECIFIER { $$ = $1; }

STRUCT_OR_UNION_SPECIFIER : STRUCT_OR_UNION T_VARIABLE LARGE_RBRACKET DECLARATION_LIST LARGE_MBRACKET {
                              $$ = new deftype(*$1, *$2, $4); }
	                        | STRUCT_OR_UNION LARGE_RBRACKET DECLARATION_LIST LARGE_MBRACKET {
                                    $$ = new deftype(*$1, "", $3); }
	                        | STRUCT_OR_UNION T_VARIABLE { $$ = new deftype(*$1, *$2, NULL); }

STRUCT_OR_UNION : STRUCT { $$ = $1; }
                | UNION  { $$ = $1; }


%%

Expression *g_root; // Definition of variable (to match declaration earlier)

Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
