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

#line 63 "src/maths_parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_TIMES = 258,
    T_DIVIDE = 259,
    T_PLUS = 260,
    T_MINUS = 261,
    T_XOR = 262,
    T_LBRACKET = 263,
    T_RBRACKET = 264,
    T_NUMBER = 265,
    T_VARIABLE = 266,
    RIGHT_OP = 267,
    LEFT_OP = 268,
    INC_OP = 269,
    DEC_OP = 270,
    PTR_OP = 271,
    AND_OP = 272,
    OR_OP = 273,
    LE_OP = 274,
    GE_OP = 275,
    EQ_OP = 276,
    NE_OP = 277,
    SEMICOLUMN = 278,
    LARGE_RBRACKET = 279,
    LARGE_MBRACKET = 280,
    COMMA = 281,
    COLON = 282,
    EQUAL = 283,
    ADD_ASSIGN = 284,
    SUB_ASSIGN = 285,
    MUL_ASSIGN = 286,
    DIV_ASSIGN = 287,
    MOD_ASSIGN = 288,
    LEFT_ASSIGN = 289,
    RIGHT_ASSIGN = 290,
    AND_ASSIGN = 291,
    XOR_ASSIGN = 292,
    OR_ASSIGN = 293,
    MIDDLE_RBRACKET = 294,
    MIDDLE_LBRACKET = 295,
    DOT = 296,
    AND = 297,
    EXCLANATION = 298,
    PERCENTAGE = 299,
    SMALLER = 300,
    LARGER = 301,
    OR = 302,
    QUESTION = 303,
    DO = 304,
    CONST = 305,
    ELSE = 306,
    FOR = 307,
    IF = 308,
    INT = 309,
    DOUBLE = 310,
    LONG = 311,
    RETURN = 312,
    SHORT = 313,
    SIGNED = 314,
    UNSIGNED = 315,
    VOID = 316,
    WHILE = 317,
    FLOAT = 318
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
  statement *s_ptr;
  Function_Declaration *f_ptr;
  Parameters* p_ptr;
  parameter_list* plist_ptr;
   Declarator* d_ptr;
   external* ex_ptr;

#line 151 "src/maths_parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED  */
