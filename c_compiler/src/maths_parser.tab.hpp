/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/maths_parser.y" /* yacc.c:1909  */

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

#line 63 "src/maths_parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_NUMBER = 258,
    T_VARIABLE = 259,
    T_LBRACKET = 260,
    T_RBRACKET = 261,
    T_TIMES = 262,
    T_DIVIDE = 263,
    T_PLUS = 264,
    T_MINUS = 265,
    T_EXPONENT = 266,
    MIDDLE_RBRACKET = 267,
    MIDDLE_LBRACKET = 268,
    DOT = 269,
    AND = 270,
    EXCLANATION = 271,
    TIDLE = 272,
    PERCENTAGE = 273,
    SMALLER = 274,
    LARGER = 275,
    OR = 276,
    QUESTION = 277,
    ELLIPSIS = 278,
    RIGHT_ASSIGN = 279,
    LEFT_ASSIGN = 280,
    ADD_ASSIGN = 281,
    SUB_ASSIGN = 282,
    MUL_ASSIGN = 283,
    DIV_ASSIGN = 284,
    MOD_ASSIGN = 285,
    AND_ASSIGN = 286,
    XOR_ASSIGN = 287,
    OR_ASSIGN = 288,
    RIGHT_OP = 289,
    LEFT_OP = 290,
    INC_OP = 291,
    DEC_OP = 292,
    PTR_OP = 293,
    AND_OP = 294,
    OR_OP = 295,
    LE_OP = 296,
    GE_OP = 297,
    EQ_OP = 298,
    NE_OP = 299,
    SEMICOLUMN = 300,
    LARGE_RBRACKET = 301,
    LARGE_MBRACKET = 302,
    COMMA = 303,
    COLON = 304,
    EQUAL = 305,
    AUTO = 306,
    BREAK = 307,
    CASE = 308,
    CHAR = 309,
    CONST = 310,
    CONTINUE = 311,
    DEFAULT = 312,
    DO = 313,
    DOUBLE = 314,
    ELSE = 315,
    ENUM = 316,
    EXTERN = 317,
    FLOAT = 318,
    FOR = 319,
    GOTO = 320,
    IF = 321,
    INT = 322,
    LONG = 323,
    REGISTER = 324,
    RETURN = 325,
    SHORT = 326,
    SIGNED = 327,
    SIZEOF = 328,
    STATIC = 329,
    STRUCT = 330,
    SWITCH = 331,
    TYPEDEF = 332,
    UNION = 333,
    UNSIGNED = 334,
    VOID = 335,
    VIOLATILE = 336,
    WHILE = 337
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "src/maths_parser.y" /* yacc.c:1909  */

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

#line 176 "src/maths_parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED  */
