%{
#include <stdlib.h>
#include <stdio.h>

int line_number = 1;

%}

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

{A}{N}{D} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "AND"); }
{O}{R} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "OR"); }
{N}{O}{T} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "NOT"); }

{I}{F} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "IF"); }
{T}{H}{E}{N} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "THEN"); }
{E}{L}{S}{E} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "ELSE"); }

{W}{H}{I}{L}{E} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "WHILE"); }
{D}{O} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "DO"); }
{F}{O}{R} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "FOR"); }

{I}{N}{T}{E}{G}{E}{R} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "INTEGER"); }
{R}{E}{A}{L} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "REAL"); }
{B}{O}{O}{L}{E}{A}{N} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "BOOLEAN"); }
{S}{T}{R}{I}{N}{G} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "STRING"); }
{C}{H}{A}{R} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "CHAR"); }

{W}{R}{I}{T}{E} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "WRITE"); }
{W}{R}{I}{T}{E}{L}{N} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "WRITELN"); }
{R}{E}{A}{D} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "READ"); }

{T}{R}{U}{E} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "TRUE"); }    
{F}{A}{L}{S}{E} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "FALSE"); }
{M}{A}{X}{I}{N}{T} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "MAXINT"); }

{T}{O} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "TO"); }
{D}{O}{W}{N}{T}{O} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "DOWNTO"); }

{B}{E}{G}{I}{N} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "BEGIN"); }
{E}{N}{D} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "END"); }

{V}{A}{R} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "VAR"); }
{C}{O}{N}{S}{T} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "CONST"); }
{P}{R}{O}{C}{E}{D}{U}{R}{E} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "PROCEDURE"); }
{F}{U}{N}{C}{T}{I}{O}{N} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "FUNCTION"); }
{P}{R}{O}{G}{R}{A}{M} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "PROGRAM"); }

{A}{R}{R}{A}{Y} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "ARRAY"); }
{O}{F} { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "OF"); }

[a-zA-Z][a-zA-Z0-9_]* { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "IDENTIFIER"); }
[0-9]+ { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "INTEGER"); }
[0-9]+"\."[0-9]+ { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "REAL"); }

["][^"]*["] { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "STRING"); }
['].['] { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "CHAR"); }

":=" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "ASSIGNMENT"); }
":" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "COLON"); }
"," { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "COMMA"); }
"." { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "DOT"); }
".." { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "DOTDOT"); }
";" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "SEMICOLON"); }

"=" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "EQUAL"); }
"<>" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "NOTEQUAL"); }
"<=" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "LESSEQUAL"); }
">=" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "GREATEREQUAL"); }
"<" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "LESS"); }
">" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "GREATER"); }

"(" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "LPAREN"); }
")" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "RPAREN"); }
"[" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "LBRACKET"); }
"]" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "RBRACKET"); }

"+" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "PLUS"); }
"-" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "MINUS"); }
"*" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "MUL"); }
"/" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "DIV"); }
"%" { printf("%d\t\t%s\t\t%s\n", line_number,yytext, "MOD"); }

[\t\t\f] {}

\n { line_number++; }

" " {}

. { printf("%d\t\t\t\t%s\t\t%s\n", line_number,yytext, "ERROR"); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]){
    printf("\nLINE NUMBER        LEXEME        TOKEN TYPE    \n");
    printf("-------------------------------------------------\n");
    yylex();
    return 0;
}
