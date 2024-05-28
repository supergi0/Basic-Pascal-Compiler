%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>
    #include"lex.yy.c"
    
    void yyerror(const char *s);
    int yylex();
    int yywrap();
%}
 
%union { 
    struct var_name { 
        char name[100]; 
        struct node* nd;
    } nd_obj;
}
 
%token <nd_obj> T_AND T_OR T_NOT
%token <nd_obj> T_IF T_THEN T_ELSE
%token <nd_obj> T_WHILE T_DO T_FOR
%token <nd_obj> INTEGER REAL BOOLEAN STRING CHAR
%token <nd_obj> WRITE READ WRITELN
%token <nd_obj> TO DOWNTO
%token <nd_obj> T_BEGIN T_END
%token <nd_obj> VAR CONST PROCEDURE FUNCTION PROGRAM
%token <nd_obj> ARRAY OF
%token <nd_obj> T_IDENTIFIER T_INTEGER T_REAL T_STRING T_CHAR T_TRUE T_FALSE T_MAXINT
%token <nd_obj> ASSIGNMENT COLON SEMICOLON COMMA DOT DOTDOT
%token <nd_obj> EQUAL NOTEQUAL LESSEQUAL LESS GREATEREQUAL GREATER
%token <nd_obj> LPAREN RPAREN LBRACKET RBRACKET
%token <nd_obj> PLUS MINUS MUL DIV MOD
 
%start program
%type<nd_obj> program variable_declaration_part statement_part compound_statement statement assignment_statement expression
%type<nd_obj> if_statement for_statement while_statement write_statement read_statement array_declaration
%type<nd_obj> primary_expression constant additive_expression multiplicative_expression relational_expression logical_and_expression logical_or_expression identifier_or_array
 
%%

program:
    PROGRAM T_IDENTIFIER SEMICOLON
    variable_declaration_part
    statement_part
    DOT
;

variable_declaration_part:
    VAR variable_declarations
;

variable_declarations:
    variable_declaration SEMICOLON
    | variable_declaration SEMICOLON variable_declarations
;

variable_declaration:
    T_IDENTIFIER_LIST COLON type
;

T_IDENTIFIER_LIST:
    T_IDENTIFIER
    | T_IDENTIFIER COMMA T_IDENTIFIER_LIST
;

type:
    INTEGER
    | REAL
    | BOOLEAN
    | CHAR
    | array_declaration
;

array_declaration:
    ARRAY LBRACKET range RBRACKET OF type
;

range:
    T_INTEGER DOTDOT T_INTEGER
;

statement_part:
    compound_statement
;

compound_statement:
    T_BEGIN statement_list T_END
;

statement_list:
    statement SEMICOLON statement_list |
    statement SEMICOLON
;

statement:
    assignment_statement
    | if_statement
    | for_statement
    | while_statement
    | write_statement
    | read_statement
    | compound_statement
;

assignment_statement:
    T_IDENTIFIER ASSIGNMENT expression
    | T_IDENTIFIER LBRACKET expression RBRACKET ASSIGNMENT expression
;

expression:
    logical_or_expression
;

logical_or_expression:
    logical_and_expression
    | logical_or_expression T_OR logical_and_expression
;

logical_and_expression:
    relational_expression
    | logical_and_expression T_AND relational_expression
;

relational_expression:
    additive_expression
    | relational_expression LESS additive_expression
    | relational_expression LESSEQUAL additive_expression
    | relational_expression GREATER additive_expression
    | relational_expression GREATEREQUAL additive_expression
    | relational_expression EQUAL additive_expression
    | relational_expression NOTEQUAL additive_expression
;

additive_expression:
    multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
;

multiplicative_expression:
    primary_expression
    | multiplicative_expression MUL primary_expression
    | multiplicative_expression DIV primary_expression
    | multiplicative_expression MOD primary_expression
;

primary_expression:
    identifier_or_array
    | constant
    | LPAREN expression RPAREN
;

identifier_or_array:
    T_IDENTIFIER
    | T_IDENTIFIER LBRACKET expression RBRACKET 
;

constant:
    T_INTEGER
    | T_REAL
    | T_STRING
    | T_CHAR
    | T_TRUE
    | T_FALSE
    | T_MAXINT
;

if_statement:
    T_IF expression T_THEN compound_statement
    | T_IF expression T_THEN compound_statement T_ELSE compound_statement
;

for_statement:
    T_FOR T_IDENTIFIER ASSIGNMENT expression TO expression T_DO compound_statement
    | T_FOR T_IDENTIFIER ASSIGNMENT expression DOWNTO expression T_DO compound_statement
;

while_statement:
    T_WHILE expression T_DO compound_statement
;

write_statement:
    WRITE LPAREN write_params RPAREN
    | WRITELN LPAREN write_params RPAREN
;

write_params:
    T_STRING
    | T_IDENTIFIER
    | write_params COMMA T_STRING
    | write_params COMMA T_IDENTIFIER
;

read_statement:
    READ LPAREN identifier_or_array RPAREN
;

%%

int main() {
    yyparse();
    printf("valid input\n");
}
 
void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Syntax error at token: %s\n", yytext);
    fprintf(stderr, "Error occurred at line: %d\n", yylineno);
    exit(1);
}