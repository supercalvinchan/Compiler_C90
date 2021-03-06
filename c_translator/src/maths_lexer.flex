%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "maths_parser.tab.hpp"
%}
FLOATING_SUFFIX           [flFL]
SIGN                      [+-]
DIGIT                     [0-9]
DIGIT_SEQUENCE            ([0-9]+)
EXPONEN_PART              ([eE]{SIGN}?{DIGIT}+)
FRACTIONAL_CONSTANT       ((({DIGIT_SEQUENCE})?\.{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}\.))
FLOATING_CONSTANT         ({SIGN}?(({FRACTIONAL_CONSTANT}{EXPONEN_PART}?{FLOATING_SUFFIX}?)|({DIGIT_SEQUENCE}{EXPONEN_PART}{FLOATING_SUFFIX}?)))

LONG_SUFFIX               [lL]
UNSIGNED_SUFFIX           [uU]
INTEGER_SUFFIX            (({UNSIGNED_SUFFIX}{LONG_SUFFIX}?)|({LONG_SUFFIX}{UNSIGNED_SUFFIX}?))
HEXADECIMAL_DIGIT         [0-9a-fA-F]
NONDIGIT                  [_a-zA-Z]
OCTAL_DIGIT               [0-7]
NONZERO_DIGIT             [1-9]
HEXADECIMAL_CONSTANT      (0[xX]{HEXADECIMAL_DIGIT}+)
OCTAL_CONSTANT            (0{OCTAL_DIGIT}+)
DECIMAL_CONSTANT          (0|({NONZERO_DIGIT}{DIGIT}*))
INTEGER_CONSTANT          (({DECIMAL_CONSTANT}|{OCTAL_CONSTANT}|{HEXADECIMAL_CONSTANT}){INTEGER_SUFFIX}?)

OCTAL_ESCAPE_SEQ          (\\{OCTAL_DIGIT}{1,3})
SIMPLE_ESCAPE_SEQ         [\'\"\?\\abfnrtv]
HEXADECIMAL_ESCAPE_SEQ    (\\x{HEXADECIMAL_DIGIT}+)
ESCAPE_SEQ                ((\\{SIMPLE_ESCAPE_SEQ})|({OCTAL_ESCAPE_SEQ})|({HEXADECIMAL_ESCAPE_SEQ}))
CHARACTER_CONSTANT        (L?\'([^\\\'\n]|{ESCAPE_SEQ})+\')
IDENTIFIER                ({NONDIGIT}({DIGIT}|{NONDIGIT})*)
STRINGLITERAL             (L?\"([^"\\\n]|{ESCAPE_SEQ})*\")
COMMENT                   (\/\/[^\n]*)|(\/\\*(.*?)\\*\/)
WHITE_SPACE               [ ]
TAB                       [\t]
NEW_LINE                  [\n\r]
PREPROCESSOR              (\#[^\n]*)

%%


"const"				{ yylval.string = new string("const"); return CONST; }
"else"				{  return ELSE; }
"for"				  { return FOR; }
"if"				  { return IF; }
"int"				  { yylval.string = new string("int"); return INT; }
"double"			{yylval.string = new string("double"); return DOUBLE;}
"long"				{ yylval.string = new string("long"); return LONG; }
"float"				{ yylval.string = new string("float"); return FLOAT;}
"return"			{yylval.string = new string("return");return RETURN; }
"short"				{ yylval.string = new string("short");return SHORT; }
"signed"			{ yylval.string = new string("signed");return SIGNED; }
"unsigned"		{ yylval.string = new string("unsigned");return UNSIGNED; }
"void"				{ yylval.string = new string("void");return VOID; }
"while"				{ yylval.string = new string("while"); return WHILE; }
"do"          { yylval.string = new string("do"); return DO; }



">>"          { yylval.string = new string(">>");return RIGHT_OP; }
"<<"          { yylval.string = new string("<<");return LEFT_OP; }
"++"          { yylval.string = new string("++");return INC_OP; }
"--"          { yylval.string = new string("--");return DEC_OP; }

"->"          { yylval.string = new string("->");return PTR_OP; }

"&&"          { yylval.string = new string("&&");return AND_OP; }
"||"          { yylval.string = new string("||");return OR_OP; }
"<="          { yylval.string = new string("<=");return LE_OP; }
">="          { yylval.string = new string(">=");return GE_OP; }
"=="          { yylval.string = new string("==");return EQ_OP; }
"!="          { yylval.string = new string("!=");return NE_OP; }

">>="			{yylval.string = new string(">>="); return RIGHT_ASSIGN;}
"<<="			{yylval.string = new string("<<="); return LEFT_ASSIGN;}
"+="			{yylval.string = new string("+="); return ADD_ASSIGN;}
"-="			{yylval.string = new string("-="); return SUB_ASSIGN;}
"*="			{yylval.string = new string("*="); return MUL_ASSIGN;}
"/="			{yylval.string = new string("/="); return DIV_ASSIGN;}
"%="			{yylval.string = new string("%="); return MOD_ASSIGN;}
"&="			{yylval.string = new string("&="); return AND_ASSIGN;}
"^="			{yylval.string = new string("^="); return XOR_ASSIGN;}
"|="			{yylval.string = new string("|="); return OR_ASSIGN;}

";"            { yylval.string = new string(";"); return SEMICOLUMN; }
"{"            { return LARGE_RBRACKET; } //waht does this token name mean?
"}"            { return LARGE_MBRACKET; }
","            { return COMMA; }
":"            { return COLON; }
"="            { yylval.string = new string("=");return EQUAL; }
"("             { return T_LBRACKET; }
")"             { return T_RBRACKET; }
"]"             { return MIDDLE_RBRACKET; }
"["             { return MIDDLE_LBRACKET; }
"."             { return DOT; }
"&"             { yylval.string = new string("&");return AND; }
"!"             { return EXCLANATION; }

"-"             { yylval.string = new string("-");return T_MINUS; }
"+"             { yylval.string = new string("+");return T_PLUS; }
"*"             { yylval.string = new string("*");return T_TIMES; }
"/"             { yylval.string = new string("/");return T_DIVIDE; }
"%"             { yylval.string = new string("%");return PERCENTAGE; }
"<"              { yylval.string = new string("<");return SMALLER; }
">"             { yylval.string = new string(">");return LARGER; }
"^"            { yylval.string = new string("^");return T_XOR; }
"|"             { yylval.string = new string("|");return OR; }
"?"              { return QUESTION; }
(\/\/[^\n]*)|(\/\\*(.*?)\\*\/)			{;}



{STRINGLITERAL}         {yylval.string = new string(yytext);   return T_VARIABLE;}
{IDENTIFIER}            { yylval.string=new std::string(yytext); return T_VARIABLE; }
{INTEGER_CONSTANT}      {yylval.number = atoi(yytext);          return T_NUMBER;}
{CHARACTER_CONSTANT}    {yylval.string = new string(yytext);   return T_NUMBER;}
{FLOATING_CONSTANT}     {yylval.number = atof(yytext);         return T_NUMBER;}
[ \t\r\n]+		          {;}
{COMMENT}                {;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%


void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
