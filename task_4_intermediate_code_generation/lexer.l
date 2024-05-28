%{
#include "y.tab.h"
extern YYSTYPE yylval;
int line_number = 0;
%}
%option yylineno

digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit}|_)*
A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]

%%

{A}{N}{D} { strcpy(yylval.nd_obj.name,(yytext)); return T_AND; }
{O}{R} { strcpy(yylval.nd_obj.name,(yytext)); return T_OR; }
{N}{O}{T} { strcpy(yylval.nd_obj.name,(yytext)); return T_NOT; }

{I}{F} { strcpy(yylval.nd_obj.name,(yytext)); return T_IF; }
{T}{H}{E}{N} { strcpy(yylval.nd_obj.name,(yytext)); return T_THEN; }
{E}{L}{S}{E} { strcpy(yylval.nd_obj.name,(yytext)); return T_ELSE; }

{W}{H}{I}{L}{E} { strcpy(yylval.nd_obj.name,(yytext)); return T_WHILE; }
{D}{O} { strcpy(yylval.nd_obj.name,(yytext)); return T_DO; }
{F}{O}{R} { strcpy(yylval.nd_obj.name,(yytext)); return T_FOR; }

{I}{N}{T}{E}{G}{E}{R} { strcpy(yylval.nd_obj.name,(yytext)); return INTEGER; }
{R}{E}{A}{L} { strcpy(yylval.nd_obj.name,(yytext)); return REAL; }
{B}{O}{O}{L}{E}{A}{N} { strcpy(yylval.nd_obj.name,(yytext)); return BOOLEAN; }
{S}{T}{R}{I}{N}{G} { strcpy(yylval.nd_obj.name,(yytext)); return STRING; }
{C}{H}{A}{R} { strcpy(yylval.nd_obj.name,(yytext)); return CHAR; }

{W}{R}{I}{T}{E} { strcpy(yylval.nd_obj.name,(yytext)); return WRITE; }
{R}{E}{A}{D} { strcpy(yylval.nd_obj.name,(yytext)); return READ; }

{T}{O} { strcpy(yylval.nd_obj.name,(yytext)); return TO; }
{D}{O}{W}{N}{T}{O} { strcpy(yylval.nd_obj.name,(yytext)); return DOWNTO; }

{B}{E}{G}{I}{N} { strcpy(yylval.nd_obj.name,(yytext)); return T_BEGIN; }
{E}{N}{D} { strcpy(yylval.nd_obj.name,(yytext)); return T_END; }

{V}{A}{R} { strcpy(yylval.nd_obj.name,(yytext)); return VAR; }
{C}{O}{N}{S}{T} { strcpy(yylval.nd_obj.name,(yytext)); return CONST; }
{P}{R}{O}{G}{R}{A}{M} { strcpy(yylval.nd_obj.name,(yytext)); return PROGRAM; }

{A}{R}{R}{A}{Y} { strcpy(yylval.nd_obj.name,(yytext)); return ARRAY; }
{O}{F} { strcpy(yylval.nd_obj.name,(yytext)); return OF; }

{identifier}    { strcpy(yylval.nd_obj.name,(yytext)); return T_IDENTIFIER; }
{digit}+        { strcpy(yylval.nd_obj.name,(yytext)); return T_INTEGER; }
{digit}+\.{digit}+ { strcpy(yylval.nd_obj.name,(yytext)); return T_REAL; }
["][^"]*["] { strcpy(yylval.nd_obj.name,(yytext)); return T_STRING; }
['][^']['] { strcpy(yylval.nd_obj.name,(yytext)); return T_CHAR; }

":=" { strcpy(yylval.nd_obj.name,(yytext)); return ASSIGNMENT; }
":" { strcpy(yylval.nd_obj.name,(yytext)); return COLON; }
";" { strcpy(yylval.nd_obj.name,(yytext)); return SEMICOLON; }
"," { strcpy(yylval.nd_obj.name,(yytext)); return COMMA; }
"." { strcpy(yylval.nd_obj.name,(yytext)); return DOT; }
".." { strcpy(yylval.nd_obj.name,(yytext)); return DOTDOT; }

"=" { strcpy(yylval.nd_obj.name,(yytext)); return EQUAL; }
"<>" { strcpy(yylval.nd_obj.name,(yytext)); return NOTEQUAL; }
"<=" { strcpy(yylval.nd_obj.name,(yytext)); return LESSEQUAL; }
"<" { strcpy(yylval.nd_obj.name,(yytext)); return LESS; }
">=" { strcpy(yylval.nd_obj.name,(yytext)); return GREATEREQUAL; }
">" { strcpy(yylval.nd_obj.name,(yytext)); return GREATER; }

"(" { strcpy(yylval.nd_obj.name,(yytext)); return LPAREN; }
")" { strcpy(yylval.nd_obj.name,(yytext)); return RPAREN; }
"[" { strcpy(yylval.nd_obj.name,(yytext)); return LBRACKET; }
"]" { strcpy(yylval.nd_obj.name,(yytext)); return RBRACKET; }

"+" { strcpy(yylval.nd_obj.name,(yytext)); return PLUS; }
"-" { strcpy(yylval.nd_obj.name,(yytext)); return MINUS; }
"*" { strcpy(yylval.nd_obj.name,(yytext)); return MUL; }
"/" { strcpy(yylval.nd_obj.name,(yytext)); return DIV; }
"%" { strcpy(yylval.nd_obj.name,(yytext)); return MOD; }


\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
[\n]                        { line_number++; }
.	                        { return *yytext; }

%%

int yywrap() {
    return 1;
}