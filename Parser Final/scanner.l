%option yylineno
%option header-file= "scanner.h"
%option outfile="scanner.c"

%{
#include "parser.h"
int yycolumn = 1;
#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;

int yyerror(char * s);
%}

digit		[0-9]+
string  \".+\"
float   [-]*[0-9]\.[0-9]+
ID      [a-zA-Z\_][a-zA-Z\_0-9]*

%s COMMENT

%%

"//"[^\n]* yycolumn = 1;
"/*"[\s\t]* BEGIN(COMMENT);

<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>[^*\n]+
<COMMENT>"*"
<COMMENT>\n  yycolumn = 1;

#[ \t ]*include[ \t ]*[\<\"][^ \t\n]+[\>\"]
#[ \t ]*define[ \t ]+[a-zA-Z0-9\_\(\)\[\]]+
#[ \t ]*define[ \t ]+[a-zA-Z\_]+[0-9]*[ \t ]+([0-9]+|\"[a-zA-Z\_]+\"|[\(\)\[\]\_a-zA-Z\+\-\*\\]+)
#[ \t ]*undef[ \t ]+([0-9]+|\"[\(\)\_a-zA-Z]+\")
#[ \t ]*ifdef[ \t ]+[\<\>A-Za-z0-9\_\"\"\(\)\[\]\{\}]+
#[ \t ]*ifndef[ \t ]+[\<\>A-Za-z0-9\_\"\"\(\)\[\]\{\}]+
#[ \t ]*if[ \t ]+[\<\>A-Za-z0-9\_\"\"\(\)\[\]\{\}]+
#[ \t ]*elif[ \t ]+[\<\>A-Za-z0-9\_\"\"\(\)\[\]\{\}]+
#[ \t ]*else
#[ \t ]*line[ \t ]+[0-9]+[ \t ]+\"[a-zA-Z\_]+\.(h|c)\"
#[ \t ]*endif
#[ \t ]*pragma[ \t ]+[\(\)_a-zA-Z0-9\t\s]+

"do"            return DO;
"auto"          return AUTO;
"break"			return BREAK;
"case"			return CASE;
"char"			return CHAR;
"const"			return CONST;
"continue"	    return CONTINUE;
"default"		return DEFAULT;
"double"		return DOUBLE;
"else"			return ELSE;
"enum"			return ENUM;
"extern"		return EXTERN;
"float"			return FLOAT;
"for"			return FOR;
"goto"		    return GOTO;
"if"			return IF;
"int"			return INT;
"long"			return LONG;
"register"	    return REGISTER;
"return"		return RETURN;
"short"			return SHORT;
"signed"	    return SIGNED;
"sizeof"	    return SIZEOF;
"static"		return STATIC;
"struct"		return STRUCT;
"switch"		return SWITCH;
"typedef"		return TYPEDEF;
"union"			return UNION;
"unsigned"	    return UNSIGNED;
"void"			return VOID;
"volatile"	    return VOLATILE;
"while"			return WHILE;
"_Alignas"      return ALIGNAS;
"_Alignof"      return ALIGNOF;
"_Atomic"       return ATOMIC;
"_Bool"        return BOOL;
"_Complex"     return COMPLEX;
"_Generic"     return GENERIC;
"_Imaginary"   return IMAGINARY;
"_Noreturn"    return NORETURN;
"_Static_assert" return STATIC_ASSERT;
"_Thread_local"  return THREAD_LOCAL;
"__func__"     return FUNC_NAME;


">>="		  	return RIGHT_ASSIGN;
"<<="			return LEFT_ASSIGN;
"+="			return ADD_ASSIGN;
"-="			return SUB_ASSIGN;
"*="		    return MUL_ASSIGN;
"/="			return DIV_ASSIGN;
"%="			return MOD_ASSIGN;
"&="			return AND_ASSIGN;
"^="			return XOR_ASSIGN;
"|="			return OR_ASSIGN;
">>"			return RIGHT_OP;
"<<"		    return LEFT_OP;
"++"			return INC_OP;
"--"			return DEC_OP;
"->"			return PTR_OP;
"&&"			return AND_OP;
"||"		    return OR_OP;
"<="			return LE_OP;
">="		    return GE_OP;
"=="		    return EQ_OP;
"!="		    return NE_OP;
";"			    return ';';
","			    return ',';
":"			    return ':';
"="			    return '=';
"("			    return '(';
")"			    return ')';
"."			    return '.';
"&"			    return '&';
"!"			    return '!';
"~"			    return '~';
"-"			    return '-';
"+"             return '+';
"*"			    return '*';
"/"			    return '/';
"<"			    return '<';
">"			    return '>';
"^"			    return '^';
"|"			    return '|';
"?"			    return '?';
"{"             return '{';
"}"             return '}';
"["             return'[';
"]"             return']';
"%"		        return '%';
{digit}         return I_CONSTANT;
{string}        return STRING_LITERAL;
{ID}            return IDENTIFIER;
{float}         return F_CONSTANT;
[ \t\v\f ]
[ \n ]          yycolumn = 1;
.
%%

int yywrap()
{
    yylineno = 1;
    return 1;
}
