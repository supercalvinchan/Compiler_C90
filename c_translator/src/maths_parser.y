%code requires{
  #include "ast.hpp"
  #include "iostream"

  #include <stdio.h>
  #include <cassert>
  #include <string>
  #include <sstream>

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
  statement *s_ptr;
  Function_Declaration *f_ptr;
  Parameters* p_ptr;
  parameter_list* plist_ptr;
   Declarator* d_ptr;
   external* ex_ptr;
}

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_XOR
%token T_LBRACKET T_RBRACKET
%token T_NUMBER T_VARIABLE

%token RIGHT_OP LEFT_OP INC_OP DEC_OP PTR_OP
%token AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP
%token SEMICOLUMN LARGE_RBRACKET LARGE_MBRACKET COMMA COLON EQUAL ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN MIDDLE_RBRACKET MIDDLE_LBRACKET
%token DOT AND EXCLANATION PERCENTAGE
%token SMALLER LARGER OR QUESTION DO

%token CONST ELSE FOR IF INT DOUBLE LONG RETURN SHORT SIGNED UNSIGNED VOID WHILE FLOAT

%type <expr>  DIRECT_DECLARATOR INIT_DECLARATOR_LIST INIT_DECLARATOR DECLARATOR INITIALIZER_LIST INITIALIZER  ARGUMENT_EXPRESSION_LIST POSTFIX_EXPRESSION UNARY_EXPRESSION RELATIONAL_EXPRESSION EQUALITY_EXPRESSION CAST_EXPRESSION MULTIPLICATIVE_EXPRESSION ADDITIVE_EXPRESSION LOGICAL_AND_EXPRESSION LOGICAL_OR_EXPRESSION CONDITIONAL_EXPRESSION PRIMARY_EXPRESSION ASSIGNMENT_EXPRESSION	EXPRESSION  PROGRAM TRANSLATION_UNIT BINARY_AND_EXPRESSION BINARY_EXCLUSIVE_OR_EXPRESSION BINARY_INCLUSIVE_OR_EXPRESSION
%type <d_ptr> DECLARATION DECLARATION_LIST
%type <s_ptr> EXPRESSION_STATEMENT ITERATION_STATEMENT SELECTION_STATEMENT STATEMENT	STATEMENT_LIST JUMP_STATEMENT COMPOUND_STATEMENT
%type <f_ptr> FUNCTION_DEFINITION
%type <ex_ptr> EXTERNAL_DECLARATION 
%type <plist_ptr>PARAMETERS_LIST
%type <p_ptr> PARAMETERS
%type <number> T_NUMBER
%type <string> WHILE DO SPECIFIER_QUANTIFIER_LIST EQ_OP T_DIVIDE SMALLER LARGER AND_OP OR_OP EQUAL ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN DECLARATION_SPECIFIERS TYPE_SPECIFIER INT DOUBLE FLOAT LONG SHORT T_VARIABLE RETURN ASSIGNMENT_OPERATOR T_PLUS T_MINUS T_TIMES PERCENTAGE AND OR T_XOR LE_OP GE_OP NE_OP UNARY_OPERATOR T_LBRACKET T_RBRACKET MIDDLE_LBRACKET MIDDLE_RBRACKET

%start PROGRAM

%%

PROGRAM : TRANSLATION_UNIT		{ g_root = $1; }

TRANSLATION_UNIT:	EXTERNAL_DECLARATION	{$$ = $1;}
/*NOTE: for scope, when external/statementlist encounter declaration(list), it add the variable to the member list
 * in itself. When external/statementlist encounter function, it copy the list to the function, in other words
 * the function "inherit" the list from its parent 
 * 
 */
EXTERNAL_DECLARATION:	FUNCTION_DEFINITION	{ $$ = new external(); $$->add($1); }
                    | EXTERNAL_DECLARATION FUNCTION_DEFINITION { $$->add($2); }
                    | DECLARATION { $$ = new external(); $$->add($1); $$->add($1->get_id());}
                    | EXTERNAL_DECLARATION DECLARATION { $$->add($2); $$->add($2->get_id());}

FUNCTION_DEFINITION : DECLARATION_SPECIFIERS T_VARIABLE T_LBRACKET T_RBRACKET COMPOUND_STATEMENT  { $$ = new Function_Declaration(*$1, *$2, $5, NULL); }
					| DECLARATION_SPECIFIERS T_VARIABLE T_LBRACKET PARAMETERS_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new Function_Declaration(*$1, *$2, $6, $4); }
					| DECLARATION_SPECIFIERS T_VARIABLE T_LBRACKET T_RBRACKET SEMICOLUMN  { $$ = new Function_Declaration(*$1, *$2, NULL, NULL); }
					| DECLARATION_SPECIFIERS T_VARIABLE T_LBRACKET PARAMETERS_LIST T_RBRACKET SEMICOLUMN { $$ = new Function_Declaration(*$1, *$2, NULL, $4); }
					
PARAMETERS_LIST : PARAMETERS {$$ = new parameter_list(); $$->add($1); }
                | PARAMETERS_LIST COMMA PARAMETERS { $$->add($3); }

PARAMETERS :  SPECIFIER_QUANTIFIER_LIST T_VARIABLE { $$ = new Parameters(*$1, *$2); }
          | SPECIFIER_QUANTIFIER_LIST T_TIMES T_VARIABLE{ $$ = new Parameters(*$1, *$3); }


SPECIFIER_QUANTIFIER_LIST : TYPE_SPECIFIER SPECIFIER_QUANTIFIER_LIST
                          | TYPE_SPECIFIER { $$ = $1; }

//statement    if/else  function body for/while loop
STATEMENT_LIST:	STATEMENT			{ $$ = new statementlist(); $$->add($1); }
				|STATEMENT_LIST STATEMENT { $$->add($2); }

STATEMENT:	JUMP_STATEMENT { $$ = $1; }	//return
			| COMPOUND_STATEMENT { $$ = $1; }	//{}
          | SELECTION_STATEMENT { $$ = $1;}	//if
          | ITERATION_STATEMENT { $$ = $1; }   //while for
          | EXPRESSION_STATEMENT { $$ = $1; }

EXPRESSION_STATEMENT : SEMICOLUMN
                     | EXPRESSION SEMICOLUMN { $$ = new Expression_DO($1); }



ITERATION_STATEMENT : WHILE T_LBRACKET EXPRESSION T_RBRACKET STATEMENT { $$ = new whilestatement(*$1, $3, $5); }
					| DO STATEMENT WHILE T_LBRACKET EXPRESSION T_RBRACKET SEMICOLUMN { $$ = new whilestatement(*$1, $5, $2); }
					|FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT T_RBRACKET STATEMENT	{$$ = new forstatement($3, $4, NULL, $6);}   //for(int i = 0; i < 5;) C90 standard
					|FOR T_LBRACKET EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION T_RBRACKET STATEMENT {$$ = new forstatement($3, $4, $5, $7);}//for(int i = 0; i < 5; i++)
					
SELECTION_STATEMENT : IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT { $$ = new ifstatement(NULL, $5, $3); }
                    | IF T_LBRACKET EXPRESSION T_RBRACKET STATEMENT ELSE STATEMENT { $$ = new ifstatement($7, $5, $3); }


COMPOUND_STATEMENT:	LARGE_RBRACKET LARGE_MBRACKET { $$ = new Compoundstatement(NULL, NULL); }
						| LARGE_RBRACKET STATEMENT_LIST LARGE_MBRACKET { $$ = new Compoundstatement($2, NULL); }
						| LARGE_RBRACKET DECLARATION_LIST LARGE_MBRACKET{ $$ = new Compoundstatement(NULL, $2); }
						| LARGE_RBRACKET DECLARATION_LIST STATEMENT_LIST LARGE_MBRACKET{ $$ = new Compoundstatement($3, $2); }

DECLARATION_LIST : DECLARATION { $$ = new declaration_list(); $$->add($1); $$->addVar($1->get_id()); }
                | DECLARATION_LIST DECLARATION { $$->add($2); $$->addVar($1->get_id());}



DECLARATION : DECLARATION_SPECIFIERS SEMICOLUMN { $$ = new Declarator(*$1, NULL); }
            | DECLARATION_SPECIFIERS INIT_DECLARATOR_LIST SEMICOLUMN{ $$ = new Declarator(*$1, $2); }


INIT_DECLARATOR_LIST : INIT_DECLARATOR { $$ = new init_declarelist(); $$->add($1); }
                    | INIT_DECLARATOR_LIST COMMA INIT_DECLARATOR	{$1->add($3); }			// not sure what does this represent

INIT_DECLARATOR : DECLARATOR { $$ = new init_declare($1, NULL); }
                | DECLARATOR EQUAL INITIALIZER { $$ = new init_declare($1, $3); }	

INITIALIZER : ASSIGNMENT_EXPRESSION { $$ = $1; }
            | LARGE_RBRACKET INITIALIZER_LIST LARGE_MBRACKET
            |  LARGE_RBRACKET INITIALIZER_LIST COMMA LARGE_MBRACKET


DECLARATOR  : T_TIMES DIRECT_DECLARATOR
            | DIRECT_DECLARATOR MIDDLE_RBRACKET T_NUMBER MIDDLE_LBRACKET
            | DIRECT_DECLARATOR { $$ = $1; }

DIRECT_DECLARATOR : T_VARIABLE { $$ = new Variables(*$1); }
                  | T_LBRACKET DECLARATOR T_RBRACKET
				|DIRECT_DECLARATOR MIDDLE_LBRACKET MIDDLE_RBRACKET	{$$ = new Array($1, NULL);}
				|DIRECT_DECLARATOR MIDDLE_LBRACKET T_NUMBER MIDDLE_RBRACKET {$$ = new Array($1, $3);}


INITIALIZER_LIST : INITIALIZER
                | INITIALIZER_LIST COMMA INITIALIZER


JUMP_STATEMENT:		RETURN SEMICOLUMN		{ $$ = new jump_statement(NULL, *$1); }  //return nothing
						|RETURN EXPRESSION SEMICOLUMN		{ $$ = new jump_statement($2, *$1); }//return something

//statement ends

//specifiers, data types
DECLARATION_SPECIFIERS :	TYPE_SPECIFIER { $$ = $1; }	//things like long int, combination of specifiers that build up a single specifier to declar an object or variable
                       | TYPE_SPECIFIER DECLARATION_SPECIFIERS

TYPE_SPECIFIER : INT	{ $$ = $1;  } //data_types like int short char long float, check yacc
				|DOUBLE	{$$ = $1;}
				|SHORT	{$$ = $1;}
				|LONG	{$$ = $1;}
				|FLOAT	{$$ = $1;}

EXPRESSION : ASSIGNMENT_EXPRESSION	{ $$ = $1; }
           | EXPRESSION COMMA ASSIGNMENT_EXPRESSION



ASSIGNMENT_EXPRESSION : CONDITIONAL_EXPRESSION { $$ = $1; }
                      | POSTFIX_EXPRESSION ASSIGNMENT_OPERATOR ASSIGNMENT_EXPRESSION { $$ = new BinaryOperator($1, *$2, $3); }

ASSIGNMENT_OPERATOR : EQUAL { $$ = $1; }
					|ADD_ASSIGN	{ $$ = $1; }			// +=
					|SUB_ASSIGN	{ $$ = $1; }			// -=
					|MUL_ASSIGN	{ $$ = $1; }			// *=
					|DIV_ASSIGN	{ $$ = $1; }			// /=
					|MOD_ASSIGN	{ $$ = $1; }			// %=
					// operators below have no direct corresponding opreator in python
					|LEFT_ASSIGN	{ $$ = $1; }		// <<=
					|RIGHT_ASSIGN	{ $$ = $1; }		// >>=
					|AND_ASSIGN		{ $$ = $1; }		// &=
					|XOR_ASSIGN		{ $$ = $1; }		// ^=
					|OR_ASSIGN		{ $$ = $1; }		// |=

CONDITIONAL_EXPRESSION : LOGICAL_OR_EXPRESSION { $$ = $1; }
                       | LOGICAL_OR_EXPRESSION QUESTION EXPRESSION COLON CONDITIONAL_EXPRESSION //TODO: ternary expression

LOGICAL_OR_EXPRESSION : LOGICAL_AND_EXPRESSION { $$ = $1; }
                      | LOGICAL_OR_EXPRESSION OR_OP LOGICAL_AND_EXPRESSION { $$ = new BinaryOperator($1, *$2, $3); }

LOGICAL_AND_EXPRESSION : BINARY_INCLUSIVE_OR_EXPRESSION { $$ = $1; }
                       | LOGICAL_AND_EXPRESSION AND_OP BINARY_INCLUSIVE_OR_EXPRESSION {$$ = new BinaryOperator($1, *$2, $3);}

EQUALITY_EXPRESSION : RELATIONAL_EXPRESSION { $$ = $1; }
                    | EQUALITY_EXPRESSION EQ_OP RELATIONAL_EXPRESSION {$$ = new BinaryOperator($1, *$2, $3);}  // a==b
					| EQUALITY_EXPRESSION NE_OP RELATIONAL_EXPRESSION {$$ = new BinaryOperator($1, *$2, $3);}  // a!=b
					
BINARY_AND_EXPRESSION	: EQUALITY_EXPRESSION	{ $$ = $1; }
				| BINARY_AND_EXPRESSION AND EQUALITY_EXPRESSION	{$$ = new BinaryOperator($1, *$2, $3);}

BINARY_EXCLUSIVE_OR_EXPRESSION : BINARY_AND_EXPRESSION	{ $$ = $1; }
						| BINARY_EXCLUSIVE_OR_EXPRESSION T_XOR BINARY_AND_EXPRESSION	{$$ = new BinaryOperator($1, *$2, $3);}

BINARY_INCLUSIVE_OR_EXPRESSION: BINARY_EXCLUSIVE_OR_EXPRESSION	{ $$ = $1; }
						| BINARY_INCLUSIVE_OR_EXPRESSION OR BINARY_EXCLUSIVE_OR_EXPRESSION	{$$ = new BinaryOperator($1, *$2, $3);}

RELATIONAL_EXPRESSION : ADDITIVE_EXPRESSION { $$ = $1; }
						|RELATIONAL_EXPRESSION SMALLER ADDITIVE_EXPRESSION {$$ = new BinaryOperator($1, *$2, $3);}  // Comparison: <
						|RELATIONAL_EXPRESSION LARGER ADDITIVE_EXPRESSION  {$$ = new BinaryOperator($1, *$2, $3);}
						|RELATIONAL_EXPRESSION LE_OP ADDITIVE_EXPRESSION  {$$ = new BinaryOperator($1, *$2, $3);}
						|RELATIONAL_EXPRESSION GE_OP ADDITIVE_EXPRESSION  {$$ = new BinaryOperator($1, *$2, $3);}
						
ADDITIVE_EXPRESSION : MULTIPLICATIVE_EXPRESSION { $$ = $1; }
                    | ADDITIVE_EXPRESSION T_PLUS MULTIPLICATIVE_EXPRESSION  {$$ = new BinaryOperator($1, *$2, $3);}   //a+b
                    | ADDITIVE_EXPRESSION T_MINUS MULTIPLICATIVE_EXPRESSION  {$$ = new BinaryOperator($1, *$2, $3);}//a-b

MULTIPLICATIVE_EXPRESSION : CAST_EXPRESSION { $$ = $1; }
                          | MULTIPLICATIVE_EXPRESSION T_TIMES CAST_EXPRESSION  {$$ = new BinaryOperator($1, *$2, $3);}//a*b
                          | MULTIPLICATIVE_EXPRESSION T_DIVIDE CAST_EXPRESSION {$$ = new BinaryOperator($1, *$2, $3);}//a/b
						|MULTIPLICATIVE_EXPRESSION PERCENTAGE CAST_EXPRESSION {$$ = new BinaryOperator($1, *$2, $3);}//a%b
						
CAST_EXPRESSION : T_LBRACKET TYPE_SPECIFIER T_RBRACKET CAST_EXPRESSION
                | UNARY_EXPRESSION { $$ = $1; }

UNARY_EXPRESSION : POSTFIX_EXPRESSION { $$ = $1; }
					| INC_OP UNARY_EXPRESSION {string tmp0 = "="; string tmp1 = "+";$$ = new BinaryOperator($2, tmp0, new BinaryOperator($2, tmp1, new Number(1)));}
					| DEC_OP UNARY_EXPRESSION {string tmp0 = "="; string tmp1 = "-";$$ = new BinaryOperator($2, tmp0, new BinaryOperator($2, tmp1, new Number(1)));}
					| UNARY_OPERATOR CAST_EXPRESSION {$$ = new BinaryOperator(NULL, *$1, $2);}    //here is where u handle negative numbers
					
UNARY_OPERATOR : T_MINUS		{$$ = $1;}
				|T_PLUS		{$$ = $1;}
				
POSTFIX_EXPRESSION : PRIMARY_EXPRESSION { $$ = $1; }
					| POSTFIX_EXPRESSION T_LBRACKET T_RBRACKET { string tmp = "("; $$ = new postfix($1, NULL); $$->set_type(tmp);}
					| POSTFIX_EXPRESSION T_LBRACKET ARGUMENT_EXPRESSION_LIST T_RBRACKET { string tmp = "("; $$ = new postfix($1, $3); $$->set_type(tmp); }
					| POSTFIX_EXPRESSION MIDDLE_LBRACKET EXPRESSION MIDDLE_RBRACKET { string tmp = "["; $$ = new postfix($1, $3); $$->set_type(tmp);}
					| POSTFIX_EXPRESSION INC_OP	{string tmp0 = "="; string tmp1 = "+";$$ = new BinaryOperator($1, tmp0, new BinaryOperator($1, tmp1, new Number(1)));}   // i++   -> i = i + 1
					| POSTFIX_EXPRESSION DEC_OP	{string tmp0 = "="; string tmp1 = "-";$$ = new BinaryOperator($1, tmp0, new BinaryOperator($1, tmp1, new Number(1)));}
					
ARGUMENT_EXPRESSION_LIST : ASSIGNMENT_EXPRESSION { $$ = new argumentList(); $$->add($1); }
                        | ARGUMENT_EXPRESSION_LIST COMMA ASSIGNMENT_EXPRESSION	{$1->add($3);}	//TODO:need to implement this



PRIMARY_EXPRESSION : T_NUMBER { $$ = new Number($1); }
                   | T_VARIABLE { $$ = new Variables(*$1); }
                   | T_LBRACKET EXPRESSION T_RBRACKET { $$ = $2; }


%%

Expression *g_root; // Definition of variable (to match declaration earlier)

Expression *parseAST()
{
g_root=0;
  yyparse();


  return g_root;
}
