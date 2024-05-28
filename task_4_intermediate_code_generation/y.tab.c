/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>

    extern char *yytext;
    extern int yylineno;
    void yyerror(const char *s);
    int yylex();
    int yywrap();

    struct node {
    struct node* children[20];
    char *token;
    };

    struct data_type {
        char* name;
        char* type;
        char* value;
        int line_number;
        int is_assigned;
    } symbol_table[40];

    struct node *head;
    int count = 0;
    int sem_error_count = 0;
    extern int line_number;
    char sem_errors[10][100];
    char reserved_arrays[100][100];
    int reserved_arrays_count = 0;
    char icg[500][100];
    int icg_count = 0;
    int temp_var = 0;
    int label = 0;
    int is_if = 0;
    int is_for = 0;
    int temp_label_1;
    int temp_label_2;

    int is_variable_present(char* name){
        for(int i = count - 1;i>=0;i--){
            if(strcmp(symbol_table[i].name,name)==0){
                return 1;
            }
        }
        return 0;
    }

    int is_variable_present_array(char* name){
        for(int i = 0;i<=reserved_arrays_count;i++){
            if(strcmp(reserved_arrays[i],name)==0){
                return 1;
            }
        }
        return 0;
    }

    void add_variable(char* name, char* type, int is_array, int start_index, int end_index) {
        if (is_variable_present(name) == 1 || is_variable_present_array(name) == 1) {
            sprintf(sem_errors[sem_error_count], "Line %d: Multiple declarations of \"%s\" not allowed\n", line_number + 1, name);
            sem_error_count++;
        } else {
            if (is_array) {
                for (int i = start_index; i <= end_index; i++) {
                    char array_instance[100];
                    sprintf(reserved_arrays[reserved_arrays_count],"%s",name);
                    reserved_arrays_count++;
                    sprintf(array_instance, "%s[%d]", name, i);
                    symbol_table[count].name = strdup(array_instance);
                    symbol_table[count].type = strdup(type);
                    symbol_table[count].line_number = line_number;
                    symbol_table[count].value = malloc(sizeof(char) * 100);
                    strcpy(symbol_table[count].value, "");
                    count++;
                }
            } else {
                symbol_table[count].name = strdup(name);
                symbol_table[count].type = strdup(type);
                symbol_table[count].line_number = line_number;
                symbol_table[count].value = malloc(sizeof(char) * 100);
                strcpy(symbol_table[count].value, "");
                count++;
            }
        }
    }

    void traverse_and_add(struct node* identifier_list_node, struct node* type_node) {
        if (strcmp(identifier_list_node->token, "identifier_list") == 0) {
            int child_index = 0;
            while (identifier_list_node->children[child_index] != NULL) {
                struct node* child_node = identifier_list_node->children[child_index];

                if (strcmp(child_node->token, "IDENTIFIER") == 0) {
                    if (strcmp(type_node->children[0]->token, "array_declaration") == 0) {
                        int start_index = atoi(type_node->children[0]->children[2]->children[0]->children[0]->token);
                        int end_index = atoi(type_node->children[0]->children[2]->children[2]->children[0]->token);
                        add_variable(child_node->children[0]->token, type_node->children[0]->children[5]->children[0]->token, 1, start_index, end_index);
                    } else {
                        add_variable(child_node->children[0]->token, type_node->children[0]->token, 0, 0, 0);
                    }
                } else if (strcmp(child_node->token, "identifier_list") == 0) {
                    traverse_and_add(child_node, type_node);
                }

                child_index += 2;
            }
        } else if (strcmp(identifier_list_node->token, "IDENTIFIER") == 0) {
            if (strcmp(type_node->children[0]->token, "array_declaration") == 0) {
                int start_index = atoi(type_node->children[0]->children[2]->children[0]->children[0]->token);
                int end_index = atoi(type_node->children[0]->children[2]->children[2]->children[0]->token);
                add_variable(identifier_list_node->children[0]->token, type_node->children[0]->children[5]->children[0]->token, 1, start_index, end_index);
            } else {
                add_variable(identifier_list_node->children[0]->token, type_node->children[0]->token, 0, 0, 0);
            }
        }
    }

    int check_type(int a, int b) {
        // valid additions
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 3 && b == 3) return 3;
        if (a == 4 && b == 4) return 4;
        if (a == 5 && b == 5) return 5;

        // adding int to real
        if (a == 1 && b == 2) return 2;
        if (a == 2 && b == 1) return 2;

        // invalid type mismatch
        char* type1 = "invalid";
        char* type2 = "invalid";

        switch (a) {
            case 1:
                type1 = "integer";
                break;
            case 2:
                type1 = "real";
                break;
            case 3:
                type1 = "char";
                break;
            case 4:
                type1 = "string";
                break;
            case 5:
                type1 = "boolean";
                break;
        }

        switch (b) {
            case 1:
                type2 = "integer";
                break;
            case 2:
                type2 = "real";
                break;
            case 3:
                type2 = "char";
                break;
            case 4:
                type2 = "string";
                break;
            case 5:
                type2 = "boolean";
                break;
        }

        sprintf(sem_errors[sem_error_count], "Line %d: Type mismatch: %s and %s\n", line_number + 1, type1, type2);
        sem_error_count++;
        return -1;
    }

    int check_assignment_type(int a, int b) {
        // valid additions
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 3 && b == 3) return 3;
        if (a == 4 && b == 4) return 4;
        if (a == 5 && b == 5) return 5;

        // only real can take in int value
        if (a == 2 && b == 1) return 2;

        // boolean values can be assigned to int and int to boolean
        if (a == 1 && b == 5) return 1;
        if (a==5 && b==1) return 5;

        // invalid type mismatch
        char* type1 = "invalid";
        char* type2 = "invalid";

        switch (a) {
            case 1:
                type1 = "integer";
                break;
            case 2:
                type1 = "real";
                break;
            case 3:
                type1 = "char";
                break;
            case 4:
                type1 = "string";
                break;
            case 5:
                type1 = "boolean";
                break;
        }

        switch (b) {
            case 1:
                type2 = "integer";
                break;
            case 2:
                type2 = "real";
                break;
            case 3:
                type2 = "char";
                break;
            case 4:
                type2 = "string";
                break;
            case 5:
                type2 = "boolean";
                break;
        }

        sprintf(sem_errors[sem_error_count], "Line %d: Assignment of %s to %s identifier\n", line_number + 1, type2, type1);
        sem_error_count++;
        return -1;
    }
    
    int check_condition_type(int a, int b) {
        // valid additions
        if (a == 1 && b == 1) return 1;
        if (a == 2 && b == 2) return 2;
        if (a == 3 && b == 3) return 3;
        if (a == 4 && b == 4) return 4;
        if (a == 5 && b == 5) return 5;

        // invalid type mismatch
        char* type1 = "invalid";
        char* type2 = "invalid";

        switch (a) {
            case 1:
                type1 = "integer";
                break;
            case 2:
                type1 = "real";
                break;
            case 3:
                type1 = "char";
                break;
            case 4:
                type1 = "string";
                break;
            case 5:
                type1 = "boolean";
                break;
        }

        switch (b) {
            case 1:
                type2 = "integer";
                break;
            case 2:
                type2 = "real";
                break;
            case 3:
                type2 = "char";
                break;
            case 4:
                type2 = "string";
                break;
            case 5:
                type2 = "boolean";
                break;
        }

        sprintf(sem_errors[sem_error_count], "Line %d: Type does not match for %s and %s identifier in Condition\n", line_number + 1, type2, type1);
        sem_error_count++;
        return -1;
    }

    void assign_variable(char* name,char* value){

    }

    int check_variable(char* name) {
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, name) == 0) {
                return 1;
            }
        }

        return 0;
    }

    int set_type(char* name){
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, name) == 0) {
                if (strcmp(symbol_table[i].type,"INTEGER") == 0) return 1;
                if (strcmp(symbol_table[i].type,"REAL") == 0) return 2;
                if (strcmp(symbol_table[i].type,"CHAR") == 0) return 3;
                if (strcmp(symbol_table[i].type,"STRING") == 0) return 4;
                if (strcmp(symbol_table[i].type,"BOOLEAN") == 0) return 5;
            }
        }
    return -1;
    }

    struct node* mknode(char *token) {	
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	char *newstr = (char *)malloc(strlen(token)+1);
	strcpy(newstr, token);
	newnode->token = newstr;
	return(newnode);
    }


#line 407 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_AND = 258,                   /* T_AND  */
    T_OR = 259,                    /* T_OR  */
    T_NOT = 260,                   /* T_NOT  */
    T_IF = 261,                    /* T_IF  */
    T_THEN = 262,                  /* T_THEN  */
    T_ELSE = 263,                  /* T_ELSE  */
    T_WHILE = 264,                 /* T_WHILE  */
    T_DO = 265,                    /* T_DO  */
    T_FOR = 266,                   /* T_FOR  */
    INTEGER = 267,                 /* INTEGER  */
    REAL = 268,                    /* REAL  */
    BOOLEAN = 269,                 /* BOOLEAN  */
    STRING = 270,                  /* STRING  */
    CHAR = 271,                    /* CHAR  */
    WRITE = 272,                   /* WRITE  */
    READ = 273,                    /* READ  */
    TO = 274,                      /* TO  */
    DOWNTO = 275,                  /* DOWNTO  */
    T_BEGIN = 276,                 /* T_BEGIN  */
    T_END = 277,                   /* T_END  */
    VAR = 278,                     /* VAR  */
    CONST = 279,                   /* CONST  */
    PROGRAM = 280,                 /* PROGRAM  */
    ARRAY = 281,                   /* ARRAY  */
    OF = 282,                      /* OF  */
    T_IDENTIFIER = 283,            /* T_IDENTIFIER  */
    T_INTEGER = 284,               /* T_INTEGER  */
    T_REAL = 285,                  /* T_REAL  */
    T_STRING = 286,                /* T_STRING  */
    T_CHAR = 287,                  /* T_CHAR  */
    ASSIGNMENT = 288,              /* ASSIGNMENT  */
    COLON = 289,                   /* COLON  */
    SEMICOLON = 290,               /* SEMICOLON  */
    COMMA = 291,                   /* COMMA  */
    DOT = 292,                     /* DOT  */
    DOTDOT = 293,                  /* DOTDOT  */
    EQUAL = 294,                   /* EQUAL  */
    NOTEQUAL = 295,                /* NOTEQUAL  */
    LESSEQUAL = 296,               /* LESSEQUAL  */
    LESS = 297,                    /* LESS  */
    GREATEREQUAL = 298,            /* GREATEREQUAL  */
    GREATER = 299,                 /* GREATER  */
    LPAREN = 300,                  /* LPAREN  */
    RPAREN = 301,                  /* RPAREN  */
    LBRACKET = 302,                /* LBRACKET  */
    RBRACKET = 303,                /* RBRACKET  */
    PLUS = 304,                    /* PLUS  */
    MINUS = 305,                   /* MINUS  */
    MUL = 306,                     /* MUL  */
    DIV = 307,                     /* DIV  */
    MOD = 308                      /* MOD  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define T_AND 258
#define T_OR 259
#define T_NOT 260
#define T_IF 261
#define T_THEN 262
#define T_ELSE 263
#define T_WHILE 264
#define T_DO 265
#define T_FOR 266
#define INTEGER 267
#define REAL 268
#define BOOLEAN 269
#define STRING 270
#define CHAR 271
#define WRITE 272
#define READ 273
#define TO 274
#define DOWNTO 275
#define T_BEGIN 276
#define T_END 277
#define VAR 278
#define CONST 279
#define PROGRAM 280
#define ARRAY 281
#define OF 282
#define T_IDENTIFIER 283
#define T_INTEGER 284
#define T_REAL 285
#define T_STRING 286
#define T_CHAR 287
#define ASSIGNMENT 288
#define COLON 289
#define SEMICOLON 290
#define COMMA 291
#define DOT 292
#define DOTDOT 293
#define EQUAL 294
#define NOTEQUAL 295
#define LESSEQUAL 296
#define LESS 297
#define GREATEREQUAL 298
#define GREATER 299
#define LPAREN 300
#define RPAREN 301
#define LBRACKET 302
#define RBRACKET 303
#define PLUS 304
#define MINUS 305
#define MUL 306
#define DIV 307
#define MOD 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 337 "parser.y"
 
    struct var_name { 
        char name[100]; 
        struct node* nd;
        int type;
        int t;
        int integer_val;
        char character_val;
        float real_val;
        int is_array;
        int is_assigned;
        char if_body[10];
        char else_body[10];
        int array_index;
    } nd_obj;

#line 583 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_AND = 3,                      /* T_AND  */
  YYSYMBOL_T_OR = 4,                       /* T_OR  */
  YYSYMBOL_T_NOT = 5,                      /* T_NOT  */
  YYSYMBOL_T_IF = 6,                       /* T_IF  */
  YYSYMBOL_T_THEN = 7,                     /* T_THEN  */
  YYSYMBOL_T_ELSE = 8,                     /* T_ELSE  */
  YYSYMBOL_T_WHILE = 9,                    /* T_WHILE  */
  YYSYMBOL_T_DO = 10,                      /* T_DO  */
  YYSYMBOL_T_FOR = 11,                     /* T_FOR  */
  YYSYMBOL_INTEGER = 12,                   /* INTEGER  */
  YYSYMBOL_REAL = 13,                      /* REAL  */
  YYSYMBOL_BOOLEAN = 14,                   /* BOOLEAN  */
  YYSYMBOL_STRING = 15,                    /* STRING  */
  YYSYMBOL_CHAR = 16,                      /* CHAR  */
  YYSYMBOL_WRITE = 17,                     /* WRITE  */
  YYSYMBOL_READ = 18,                      /* READ  */
  YYSYMBOL_TO = 19,                        /* TO  */
  YYSYMBOL_DOWNTO = 20,                    /* DOWNTO  */
  YYSYMBOL_T_BEGIN = 21,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 22,                     /* T_END  */
  YYSYMBOL_VAR = 23,                       /* VAR  */
  YYSYMBOL_CONST = 24,                     /* CONST  */
  YYSYMBOL_PROGRAM = 25,                   /* PROGRAM  */
  YYSYMBOL_ARRAY = 26,                     /* ARRAY  */
  YYSYMBOL_OF = 27,                        /* OF  */
  YYSYMBOL_T_IDENTIFIER = 28,              /* T_IDENTIFIER  */
  YYSYMBOL_T_INTEGER = 29,                 /* T_INTEGER  */
  YYSYMBOL_T_REAL = 30,                    /* T_REAL  */
  YYSYMBOL_T_STRING = 31,                  /* T_STRING  */
  YYSYMBOL_T_CHAR = 32,                    /* T_CHAR  */
  YYSYMBOL_ASSIGNMENT = 33,                /* ASSIGNMENT  */
  YYSYMBOL_COLON = 34,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 35,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_DOT = 37,                       /* DOT  */
  YYSYMBOL_DOTDOT = 38,                    /* DOTDOT  */
  YYSYMBOL_EQUAL = 39,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 40,                  /* NOTEQUAL  */
  YYSYMBOL_LESSEQUAL = 41,                 /* LESSEQUAL  */
  YYSYMBOL_LESS = 42,                      /* LESS  */
  YYSYMBOL_GREATEREQUAL = 43,              /* GREATEREQUAL  */
  YYSYMBOL_GREATER = 44,                   /* GREATER  */
  YYSYMBOL_LPAREN = 45,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 46,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 47,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 48,                  /* RBRACKET  */
  YYSYMBOL_PLUS = 49,                      /* PLUS  */
  YYSYMBOL_MINUS = 50,                     /* MINUS  */
  YYSYMBOL_MUL = 51,                       /* MUL  */
  YYSYMBOL_DIV = 52,                       /* DIV  */
  YYSYMBOL_MOD = 53,                       /* MOD  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_program = 55,                   /* program  */
  YYSYMBOL_variable_declaration_part = 56, /* variable_declaration_part  */
  YYSYMBOL_variable_declarations = 57,     /* variable_declarations  */
  YYSYMBOL_variable_declaration = 58,      /* variable_declaration  */
  YYSYMBOL_identifier_list = 59,           /* identifier_list  */
  YYSYMBOL_type = 60,                      /* type  */
  YYSYMBOL_array_declaration = 61,         /* array_declaration  */
  YYSYMBOL_range = 62,                     /* range  */
  YYSYMBOL_statement_part = 63,            /* statement_part  */
  YYSYMBOL_compound_statement = 64,        /* compound_statement  */
  YYSYMBOL_statement_list = 65,            /* statement_list  */
  YYSYMBOL_statement = 66,                 /* statement  */
  YYSYMBOL_assignment_statement = 67,      /* assignment_statement  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_logical_or_expression = 69,     /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 70,    /* logical_and_expression  */
  YYSYMBOL_relational_expression = 71,     /* relational_expression  */
  YYSYMBOL_additive_expression = 72,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 73, /* multiplicative_expression  */
  YYSYMBOL_primary_expression = 74,        /* primary_expression  */
  YYSYMBOL_identifier_or_array = 75,       /* identifier_or_array  */
  YYSYMBOL_identifier = 76,                /* identifier  */
  YYSYMBOL_constant = 77,                  /* constant  */
  YYSYMBOL_if_token = 78,                  /* if_token  */
  YYSYMBOL_if_statement = 79,              /* if_statement  */
  YYSYMBOL_80_1 = 80,                      /* $@1  */
  YYSYMBOL_81_2 = 81,                      /* $@2  */
  YYSYMBOL_else_statement = 82,            /* else_statement  */
  YYSYMBOL_for_statement = 83,             /* for_statement  */
  YYSYMBOL_84_3 = 84,                      /* $@3  */
  YYSYMBOL_85_4 = 85,                      /* $@4  */
  YYSYMBOL_while_statement = 86,           /* while_statement  */
  YYSYMBOL_87_5 = 87,                      /* $@5  */
  YYSYMBOL_88_6 = 88,                      /* $@6  */
  YYSYMBOL_write_statement = 89,           /* write_statement  */
  YYSYMBOL_write_params = 90,              /* write_params  */
  YYSYMBOL_read_statement = 91             /* read_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   380,   380,   407,   420,   431,   444,   458,   466,   482,
     492,   502,   512,   521,   530,   556,   576,   585,   604,   616,
     629,   636,   643,   650,   657,   664,   671,   680,   748,   763,
     776,   808,   821,   853,   866,   894,   922,   950,   978,  1006,
    1036,  1049,  1064,  1081,  1094,  1109,  1124,  1143,  1182,  1191,
    1214,  1244,  1276,  1285,  1295,  1305,  1313,  1324,  1335,  1335,
    1335,  1355,  1366,  1372,  1371,  1449,  1448,  1527,  1531,  1526,
    1556,  1577,  1587,  1612,  1627,  1659
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_AND", "T_OR",
  "T_NOT", "T_IF", "T_THEN", "T_ELSE", "T_WHILE", "T_DO", "T_FOR",
  "INTEGER", "REAL", "BOOLEAN", "STRING", "CHAR", "WRITE", "READ", "TO",
  "DOWNTO", "T_BEGIN", "T_END", "VAR", "CONST", "PROGRAM", "ARRAY", "OF",
  "T_IDENTIFIER", "T_INTEGER", "T_REAL", "T_STRING", "T_CHAR",
  "ASSIGNMENT", "COLON", "SEMICOLON", "COMMA", "DOT", "DOTDOT", "EQUAL",
  "NOTEQUAL", "LESSEQUAL", "LESS", "GREATEREQUAL", "GREATER", "LPAREN",
  "RPAREN", "LBRACKET", "RBRACKET", "PLUS", "MINUS", "MUL", "DIV", "MOD",
  "$accept", "program", "variable_declaration_part",
  "variable_declarations", "variable_declaration", "identifier_list",
  "type", "array_declaration", "range", "statement_part",
  "compound_statement", "statement_list", "statement",
  "assignment_statement", "expression", "logical_or_expression",
  "logical_and_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "primary_expression", "identifier_or_array",
  "identifier", "constant", "if_token", "if_statement", "$@1", "$@2",
  "else_statement", "for_statement", "$@3", "$@4", "while_statement",
  "$@5", "$@6", "write_statement", "write_params", "read_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-49)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -14,   -15,    35,   -49,    10,   -49,    26,   -15,    48,   -49,
      36,    13,    34,     6,    37,   -49,   -15,    24,   -15,   -49,
     -49,   -15,    27,    28,   -49,    55,    43,   -49,    47,    32,
       1,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,    38,   -49,   -49,   -49,     1,    49,    -9,   -15,
     -49,     6,     1,     1,   -49,   -49,   -49,   -49,     1,   -49,
      77,    80,    12,    14,   -47,   -49,   -49,   -49,    57,    74,
       1,   -49,   -49,   -26,    41,   -49,   -49,    40,    44,    82,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,    53,    45,   -49,    46,    -3,   -49,   -49,
     -49,   -49,    48,    80,    12,    14,    14,    14,    14,    14,
      14,   -47,   -47,   -49,   -49,   -49,    63,    68,    48,     1,
       1,   -49,   -49,   -49,   -49,    24,   -49,    86,    88,    91,
     -49,   -49,   -49,    48,   -49,    48,    48,   -49,   -49,   -49
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    52,     0,     1,     0,     0,     0,     3,
       0,     0,     7,     0,     0,    16,     4,     0,     0,    57,
      67,     0,     0,     0,    26,     0,     0,    20,     0,    50,
       0,    21,    22,    23,    24,    25,     2,     5,     9,    10,
      11,    12,     0,     6,    13,     8,     0,     0,     0,     0,
      17,    19,     0,     0,    53,    54,    55,    56,     0,    58,
      28,    29,    31,    33,    40,    43,    47,    48,     0,     0,
       0,    71,    72,     0,     0,    18,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,    70,    75,
      51,    49,     0,    30,    32,    38,    39,    35,    34,    37,
      36,    41,    42,    44,    45,    46,     0,     0,     0,     0,
       0,    73,    74,    59,    15,     0,    69,     0,     0,    62,
      14,    63,    65,     0,    60,     0,     0,    61,    64,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -49,   -49,   -49,    84,   -49,    83,   -23,   -49,   -49,   -49,
      -8,    52,   -49,   -49,   -44,   -49,    25,    23,   -25,   -21,
     -48,   -10,     0,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     8,     9,    10,    11,    43,    44,    94,    14,
      24,    25,    26,    27,    59,    60,    61,    62,    63,    64,
      65,    66,    29,    67,    30,    31,    79,   129,   134,    32,
     135,   136,    33,    46,   118,    34,    73,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      15,     4,    69,    28,    90,    91,    92,    12,    76,    77,
      97,     1,    19,     3,    78,    20,    12,    21,    12,     3,
      98,    47,    71,    22,    23,     3,    96,    13,   121,     3,
      54,    55,    56,    57,     3,     5,    38,    39,    40,    74,
      41,    28,   113,   114,   115,     6,    58,    17,    72,     7,
      42,    82,    83,    84,    85,    86,    87,   105,   106,   107,
     108,   109,   110,    88,    89,   119,   120,   111,   112,    13,
      18,    16,    48,    49,    36,   127,   128,    50,    51,    53,
      52,    80,    70,    81,    95,    68,    93,    99,   100,   102,
     101,   116,   124,   117,   123,   125,   131,   122,   132,   133,
      37,    45,   130,    75,   104,   103,     0,     0,     0,     0,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   137,     0,   138,   139
};

static const yytype_int16 yycheck[] =
{
       8,     1,    46,    13,    51,    52,    53,     7,    52,    53,
      36,    25,     6,    28,    58,     9,    16,    11,    18,    28,
      46,    21,    31,    17,    18,    28,    70,    21,    31,    28,
      29,    30,    31,    32,    28,     0,    12,    13,    14,    49,
      16,    51,    90,    91,    92,    35,    45,    34,    48,    23,
      26,    39,    40,    41,    42,    43,    44,    82,    83,    84,
      85,    86,    87,    49,    50,    19,    20,    88,    89,    21,
      36,    35,    45,    45,    37,   119,   120,    22,    35,    47,
      33,     4,    33,     3,    10,    47,    29,    46,    48,     7,
      46,    38,    29,    48,   102,    27,    10,    97,    10,     8,
      16,    18,   125,    51,    81,    80,    -1,    -1,    -1,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   133,    -1,   135,   136
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    55,    28,    76,     0,    35,    23,    56,    57,
      58,    59,    76,    21,    63,    64,    35,    34,    36,     6,
       9,    11,    17,    18,    64,    65,    66,    67,    75,    76,
      78,    79,    83,    86,    89,    91,    37,    57,    12,    13,
      14,    16,    26,    60,    61,    59,    87,    76,    45,    45,
      22,    35,    33,    47,    29,    30,    31,    32,    45,    68,
      69,    70,    71,    72,    73,    74,    75,    77,    47,    68,
      33,    31,    76,    90,    75,    65,    68,    68,    68,    80,
       4,     3,    39,    40,    41,    42,    43,    44,    49,    50,
      51,    52,    53,    29,    62,    10,    68,    36,    46,    46,
      48,    46,     7,    70,    71,    72,    72,    72,    72,    72,
      72,    73,    73,    74,    74,    74,    38,    48,    88,    19,
      20,    31,    76,    64,    29,    27,    64,    68,    68,    81,
      60,    10,    10,     8,    82,    84,    85,    64,    64,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    57,    57,    58,    59,    59,    60,
      60,    60,    60,    60,    61,    62,    63,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    67,    68,    69,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      72,    72,    72,    73,    73,    73,    73,    74,    74,    74,
      75,    75,    76,    77,    77,    77,    77,    78,    80,    81,
      79,    82,    82,    84,    83,    85,    83,    87,    88,    86,
      89,    90,    90,    90,    90,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     2,     2,     3,     3,     1,     3,     1,
       1,     1,     1,     1,     6,     3,     1,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     3,
       1,     4,     1,     1,     1,     1,     1,     1,     0,     0,
       7,     2,     0,     0,     9,     0,     9,     0,     0,     6,
       4,     1,     1,     3,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PROGRAM identifier SEMICOLON variable_declaration_part statement_part DOT  */
#line 384 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("program");

        (yyvsp[-5].nd_obj).nd = mknode("PROGRAM");
        (yyvsp[-5].nd_obj).nd->children[0] = mknode((yyvsp[-5].nd_obj).name);

        (yyvsp[-3].nd_obj).nd = mknode("SEMICOLON");
        (yyvsp[-3].nd_obj).nd->children[0] = mknode((yyvsp[-3].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("DOT");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-5].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-4].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[3] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[4] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[5] = (yyvsp[0].nd_obj).nd;
        head = (yyval.nd_obj).nd;
    }
#line 1769 "y.tab.c"
    break;

  case 3: /* variable_declaration_part: VAR variable_declarations  */
#line 408 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("variable_declaration_part");

        (yyvsp[-1].nd_obj).nd = mknode("VAR");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[0].nd_obj).nd;
    }
#line 1783 "y.tab.c"
    break;

  case 4: /* variable_declarations: variable_declaration SEMICOLON  */
#line 421 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("variable_declarations");
        
        (yyvsp[0].nd_obj).nd = mknode("SEMICOLON");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[0].nd_obj).nd;
    }
#line 1797 "y.tab.c"
    break;

  case 5: /* variable_declarations: variable_declaration SEMICOLON variable_declarations  */
#line 432 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("variable_declarations");
        
        (yyvsp[-1].nd_obj).nd = mknode("SEMICOLON");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;
    }
#line 1812 "y.tab.c"
    break;

  case 6: /* variable_declaration: identifier_list COLON type  */
#line 445 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("variable_declaration");
        (yyvsp[-1].nd_obj).nd = mknode("COLON");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);
        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;

        traverse_and_add((yyvsp[-2].nd_obj).nd,(yyvsp[0].nd_obj).nd);
    }
#line 1827 "y.tab.c"
    break;

  case 7: /* identifier_list: identifier  */
#line 459 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("identifier_list");
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        sprintf(icg[icg_count++],"%s = NULL\n", (yyvsp[0].nd_obj).nd->children[0]->token);
    }
#line 1838 "y.tab.c"
    break;

  case 8: /* identifier_list: identifier COMMA identifier_list  */
#line 467 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("identifier_list");

        (yyvsp[-1].nd_obj).nd = mknode("COMMA");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;

        sprintf(icg[icg_count++],"%s = NULL\n", (yyvsp[-2].nd_obj).nd->children[0]->token);
    }
#line 1855 "y.tab.c"
    break;

  case 9: /* type: INTEGER  */
#line 483 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("type");

        (yyvsp[0].nd_obj).nd = mknode("INTEGER");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 1868 "y.tab.c"
    break;

  case 10: /* type: REAL  */
#line 493 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("type");

        (yyvsp[0].nd_obj).nd = mknode("REAL");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 1881 "y.tab.c"
    break;

  case 11: /* type: BOOLEAN  */
#line 503 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("type");

        (yyvsp[0].nd_obj).nd = mknode("BOOLEAN");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 1894 "y.tab.c"
    break;

  case 12: /* type: CHAR  */
#line 513 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("type");

        (yyvsp[0].nd_obj).nd = mknode("CHAR");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 1907 "y.tab.c"
    break;

  case 13: /* type: array_declaration  */
#line 522 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("type");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 1917 "y.tab.c"
    break;

  case 14: /* array_declaration: ARRAY LBRACKET range RBRACKET OF type  */
#line 531 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("array_declaration");

        (yyvsp[-5].nd_obj).nd = mknode("ARRAY");
        (yyvsp[-5].nd_obj).nd->children[0] = mknode((yyvsp[-5].nd_obj).name);

        (yyvsp[-4].nd_obj).nd = mknode("LBRACKET");
        (yyvsp[-4].nd_obj).nd->children[0] = mknode((yyvsp[-4].nd_obj).name);

        (yyvsp[-2].nd_obj).nd = mknode("RBRACKET");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[-1].nd_obj).nd = mknode("OF");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-5].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-4].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[3] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[4] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[5] = (yyvsp[0].nd_obj).nd;
    }
#line 1944 "y.tab.c"
    break;

  case 15: /* range: T_INTEGER DOTDOT T_INTEGER  */
#line 557 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("range");

        (yyvsp[-2].nd_obj).nd = mknode("INTEGER");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[-1].nd_obj).nd = mknode("DOTDOT");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("INTEGER");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;
    }
#line 1965 "y.tab.c"
    break;

  case 16: /* statement_part: compound_statement  */
#line 577 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement_part");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 1975 "y.tab.c"
    break;

  case 17: /* compound_statement: T_BEGIN statement_list T_END  */
#line 586 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("compound_statement");

        (yyvsp[-2].nd_obj).nd = mknode("BEGIN");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("END");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);


        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;

    }
#line 1995 "y.tab.c"
    break;

  case 18: /* statement_list: statement SEMICOLON statement_list  */
#line 605 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement_list");

        (yyvsp[-1].nd_obj).nd = mknode("SEMICOLON");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;
    }
#line 2010 "y.tab.c"
    break;

  case 19: /* statement_list: statement SEMICOLON  */
#line 617 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement_list");

        (yyvsp[0].nd_obj).nd = mknode("SEMICOLON");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[0].nd_obj).nd;
    }
#line 2024 "y.tab.c"
    break;

  case 20: /* statement: assignment_statement  */
#line 630 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2034 "y.tab.c"
    break;

  case 21: /* statement: if_statement  */
#line 637 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2044 "y.tab.c"
    break;

  case 22: /* statement: for_statement  */
#line 644 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2054 "y.tab.c"
    break;

  case 23: /* statement: while_statement  */
#line 651 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2064 "y.tab.c"
    break;

  case 24: /* statement: write_statement  */
#line 658 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2074 "y.tab.c"
    break;

  case 25: /* statement: read_statement  */
#line 665 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2084 "y.tab.c"
    break;

  case 26: /* statement: compound_statement  */
#line 672 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("statement");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 2094 "y.tab.c"
    break;

  case 27: /* assignment_statement: identifier_or_array ASSIGNMENT expression  */
#line 681 "parser.y"
    {
        check_assignment_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);

        (yyval.nd_obj).nd = mknode("assignment_statement");

        (yyvsp[-1].nd_obj).nd = mknode("ASSIGNMENT");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-2].nd_obj).nd->children[0]->children[0]->token) == 0) {
                if((yyvsp[0].nd_obj).type == 1){
                    sprintf(symbol_table[i].value, "%d", (yyvsp[0].nd_obj).integer_val);
                }
                if((yyvsp[0].nd_obj).type == 2){
                    sprintf(symbol_table[i].value, "%f", (yyvsp[0].nd_obj).real_val);
                }
                if((yyvsp[0].nd_obj).type == 3){
                    sprintf(symbol_table[i].value, "%c", (yyvsp[0].nd_obj).character_val);
                }
            }
        }

        if((yyvsp[-2].nd_obj).is_array==0){
            sprintf(icg[icg_count++],"%s = t%d\n",(yyvsp[-2].nd_obj).nd->children[0]->children[0]->token,(yyvsp[0].nd_obj).t);
        }
        else{
            if((yyvsp[-2].nd_obj).type == 1){
                // int
                sprintf(icg[icg_count++],"t%d = 4 * %d\n",temp_var++,(yyvsp[-2].nd_obj).array_index);
            }
            else if((yyvsp[-2].nd_obj).type == 2){
                // real
                sprintf(icg[icg_count++],"t%d = 8 * %d\n",temp_var++,(yyvsp[-2].nd_obj).array_index);
            }
            else if((yyvsp[-2].nd_obj).type == 3){
                // char
                sprintf(icg[icg_count++],"t%d = 1 * %d\n",temp_var++,(yyvsp[-2].nd_obj).array_index);
            }

            sprintf(icg[icg_count++], "t%d = &%s\n", temp_var++, (yyvsp[-2].nd_obj).nd->children[0]->children[0]->token);
            sprintf(icg[icg_count++], "t%d = t%d + t%d\n", temp_var, temp_var - 2, temp_var - 1);
            sprintf(icg[icg_count++], "*t%d = t%d\n", temp_var, (yyvsp[0].nd_obj).t);
        }

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-2].nd_obj).nd->children[0]->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }
    }
#line 2163 "y.tab.c"
    break;

  case 28: /* expression: logical_or_expression  */
#line 749 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = (yyvsp[0].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;
    }
#line 2179 "y.tab.c"
    break;

  case 29: /* logical_or_expression: logical_and_expression  */
#line 764 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("logical_or_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = (yyvsp[0].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;
    }
#line 2195 "y.tab.c"
    break;

  case 30: /* logical_or_expression: logical_or_expression T_OR logical_and_expression  */
#line 777 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("logical_or_expression");
        if((yyvsp[-2].nd_obj).type != 5 || (yyvsp[0].nd_obj).type !=5){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected boolean type for OR statement \n",line_number+1);
        }
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd = mknode("OR");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;  

        if(is_if == 1) {
            sprintf(icg[icg_count++], "\nIF t%d OR t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        } 
        else if(is_for == 1) {
            sprintf(icg[icg_count++], "\nIF t%d OR t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t = temp_var++;
            sprintf(icg[icg_count++], "t%d = %d OR t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }    
    }
#line 2228 "y.tab.c"
    break;

  case 31: /* logical_and_expression: relational_expression  */
#line 809 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("logical_and_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = (yyvsp[0].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;
    }
#line 2244 "y.tab.c"
    break;

  case 32: /* logical_and_expression: logical_and_expression T_AND relational_expression  */
#line 822 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("logical_and_expression");
        if((yyvsp[-2].nd_obj).type != 5 || (yyvsp[0].nd_obj).type !=5){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected boolean type for AND statement \n",line_number+1);
        }
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd = mknode("AND");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        if(is_if == 1) {
            sprintf(icg[icg_count++], "\nIF t%d AND t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        } 
        else if(is_for == 1) {
            sprintf(icg[icg_count++], "\nIF t%d AND t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t = temp_var++;
            sprintf(icg[icg_count++], "t%d = %d AND t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        } 
    }
#line 2277 "y.tab.c"
    break;

  case 33: /* relational_expression: additive_expression  */
#line 854 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = (yyvsp[0].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;
    }
#line 2293 "y.tab.c"
    break;

  case 34: /* relational_expression: relational_expression LESS additive_expression  */
#line 867 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = check_condition_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd = mknode("LESS");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d < t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else if(is_for == 1){
            sprintf(icg[icg_count++], "\nIF t%d < t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d < t%d", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }
    }
#line 2324 "y.tab.c"
    break;

  case 35: /* relational_expression: relational_expression LESSEQUAL additive_expression  */
#line 895 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = check_condition_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd = mknode("LESSEQUAL");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d <= t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else if(is_for == 1){
            sprintf(icg[icg_count++], "\nIF t%d <= t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d <= t%d", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }
    }
#line 2355 "y.tab.c"
    break;

  case 36: /* relational_expression: relational_expression GREATER additive_expression  */
#line 923 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = check_condition_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("GREATER");
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d > t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else if(is_for == 1){
            sprintf(icg[icg_count++], "\nIF t%d > t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d > t%d", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }
    }
#line 2386 "y.tab.c"
    break;

  case 37: /* relational_expression: relational_expression GREATEREQUAL additive_expression  */
#line 951 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = check_condition_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("GREATEREQUAL");
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d >= t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else if(is_for == 1){
            sprintf(icg[icg_count++], "\nIF t%d >= t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d >= t%d", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }
    }
#line 2417 "y.tab.c"
    break;

  case 38: /* relational_expression: relational_expression EQUAL additive_expression  */
#line 979 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = check_condition_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd = mknode("EQUAL");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d == t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else if(is_for == 1){
            sprintf(icg[icg_count++], "\nIF t%d == t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d == t%d", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }
    }
#line 2448 "y.tab.c"
    break;

  case 39: /* relational_expression: relational_expression NOTEQUAL additive_expression  */
#line 1007 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("relational_expression");
        (yyval.nd_obj).type = check_condition_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyval.nd_obj).type = 5;
        (yyvsp[-1].nd_obj).nd = mknode("NOTEQUAL");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        if(is_if == 1){
            sprintf(icg[icg_count++], "\nIF t%d != t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else if(is_for == 1){
            sprintf(icg[icg_count++], "\nIF t%d != t%d GOTO L%d ELSE GOTO L%d\n", (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t, label, label + 1);
            sprintf((yyval.nd_obj).if_body, "L%d", label++);
            sprintf((yyval.nd_obj).else_body, "L%d", label++);
        }
        else {
            (yyval.nd_obj).t  = temp_var++;
            sprintf(icg[icg_count++],"t%d = t%d != t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
        }
    }
#line 2479 "y.tab.c"
    break;

  case 40: /* additive_expression: multiplicative_expression  */
#line 1037 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("additive_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = (yyvsp[0].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;
    }
#line 2495 "y.tab.c"
    break;

  case 41: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 1050 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("additive_expression");
        (yyval.nd_obj).type = check_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("PLUS");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        (yyval.nd_obj).t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d + t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
    }
#line 2513 "y.tab.c"
    break;

  case 42: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 1065 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("additive_expression");
        (yyval.nd_obj).type = check_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("MINUS");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        (yyval.nd_obj).t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d - t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
    }
#line 2531 "y.tab.c"
    break;

  case 43: /* multiplicative_expression: primary_expression  */
#line 1082 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("multiplicative_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = (yyvsp[0].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;
    }
#line 2547 "y.tab.c"
    break;

  case 44: /* multiplicative_expression: multiplicative_expression MUL primary_expression  */
#line 1095 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("multiplicative_expression");
        (yyval.nd_obj).type = check_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("MUL");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd;

        (yyval.nd_obj).t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d * t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
    }
#line 2565 "y.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression DIV primary_expression  */
#line 1110 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("multiplicative_expression");
        (yyval.nd_obj).type = check_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("DIV");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        (yyval.nd_obj).t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d / t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);
    }
#line 2583 "y.tab.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression MOD primary_expression  */
#line 1125 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("multiplicative_expression");
        (yyval.nd_obj).type = check_type((yyvsp[-2].nd_obj).type,(yyvsp[0].nd_obj).type);
        (yyvsp[-1].nd_obj).nd = mknode("MOD");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        (yyval.nd_obj).t = temp_var++;
        sprintf(icg[icg_count++], "t%d = t%d %% t%d\n", (yyval.nd_obj).t, (yyvsp[-2].nd_obj).t, (yyvsp[0].nd_obj).t);

       
    }
#line 2603 "y.tab.c"
    break;

  case 47: /* primary_expression: identifier_or_array  */
#line 1144 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("primary_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).t = temp_var++;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
        if((yyvsp[0].nd_obj).is_array==0){
        sprintf(icg[icg_count++],"t%d = %s\n",(yyval.nd_obj).t,(yyvsp[0].nd_obj).nd->children[0]->children[0]->token);
        }
        else{
            char buffer[256];
            sprintf(buffer,"%s[0]",(yyvsp[0].nd_obj).nd->children[0]->children[0]->token);
            sprintf(icg[icg_count++],"t%d = %s\n",(yyval.nd_obj).t,buffer);
        }

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[0].nd_obj).nd->children[0]->children[0]->token) == 0) {
                if(symbol_table[i].is_assigned!=1){
                    sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" used before assignment\n",line_number+1,(yyvsp[0].nd_obj).nd->children[0]->children[0]->token);
                    sem_error_count++;
                    break;
                }
                else{
                    (yyval.nd_obj).is_assigned = 1;
                }
            }
        }

        (yyval.nd_obj).integer_val = (yyvsp[0].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[0].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).character_val;

    }
#line 2645 "y.tab.c"
    break;

  case 48: /* primary_expression: constant  */
#line 1183 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("primary_expression");
        (yyval.nd_obj).type = (yyvsp[0].nd_obj).type;
        (yyval.nd_obj).t = temp_var++;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
        sprintf(icg[icg_count++],"t%d = %s\n",(yyval.nd_obj).t,(yyvsp[0].nd_obj).nd->children[0]->token);
    }
#line 2657 "y.tab.c"
    break;

  case 49: /* primary_expression: LPAREN expression RPAREN  */
#line 1192 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("primary_expression");
        (yyval.nd_obj).type = (yyvsp[-1].nd_obj).type;
        (yyvsp[-2].nd_obj).nd = mknode("LPAREN");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("RPAREN");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[0].nd_obj).nd; 

        (yyval.nd_obj).t = (yyvsp[-1].nd_obj).t;

        (yyval.nd_obj).integer_val = (yyvsp[-1].nd_obj).integer_val;
        (yyval.nd_obj).real_val = (yyvsp[-1].nd_obj).real_val;
        (yyval.nd_obj).character_val = (yyvsp[-1].nd_obj).character_val;
    }
#line 2681 "y.tab.c"
    break;

  case 50: /* identifier_or_array: identifier  */
#line 1215 "parser.y"
    {
        // this checks for undeclared variables
        if(check_variable((yyvsp[0].nd_obj).nd->children[0]->token)==0){
            sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" not declared\n",line_number+1,(yyvsp[0].nd_obj).nd->children[0]->token);
            sem_error_count++;
        }
        (yyval.nd_obj).is_array = 0;
        (yyval.nd_obj).type = set_type((yyvsp[0].nd_obj).nd->children[0]->token);


        (yyval.nd_obj).nd = mknode("identifier_or_array");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[0].nd_obj).nd->children[0]->token) == 0) {
                if((yyval.nd_obj).type == 1){
                    (yyval.nd_obj).integer_val = atoi(symbol_table[i].value);
                }
            }
        }

    }
#line 2714 "y.tab.c"
    break;

  case 51: /* identifier_or_array: identifier LBRACKET expression RBRACKET  */
#line 1245 "parser.y"
    {
        // this checks for undeclared array variables
        if(check_variable((yyvsp[-3].nd_obj).nd->children[0]->token)==0){
            sprintf(sem_errors[sem_error_count],"Line %d: Array Variable \"%s\" not declared\n",line_number+1,(yyvsp[-3].nd_obj).nd->children[0]->token);
            sem_error_count++;
        }
        (yyval.nd_obj).is_array = 1;
        (yyval.nd_obj).type = set_type((yyvsp[-3].nd_obj).nd->children[0]->token);

        (yyval.nd_obj).array_index = (yyvsp[-1].nd_obj).integer_val;

        (yyval.nd_obj).nd = mknode("identifier_or_array");

        (yyvsp[-2].nd_obj).nd = mknode("LBRACKET");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("RBRACKET");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-1].nd_obj).nd; 
        (yyval.nd_obj).nd->children[3] = (yyvsp[0].nd_obj).nd; 

        if((yyvsp[-1].nd_obj).type != 1){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected integer type in array \"%s\"\n",line_number+1,(yyvsp[-3].nd_obj).nd->children[0]->token);
        }
    }
#line 2747 "y.tab.c"
    break;

  case 52: /* identifier: T_IDENTIFIER  */
#line 1277 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("IDENTIFIER");

        (yyval.nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);
    }
#line 2757 "y.tab.c"
    break;

  case 53: /* constant: T_INTEGER  */
#line 1286 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("INTEGER_CONSTANT");
        (yyval.nd_obj).type = 1;
        (yyval.nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);
        (yyval.nd_obj).is_assigned = 1;

        (yyval.nd_obj).integer_val = atoi((yyvsp[0].nd_obj).name);
    }
#line 2770 "y.tab.c"
    break;

  case 54: /* constant: T_REAL  */
#line 1296 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("REAL_CONSTANT");
        (yyval.nd_obj).type = 2;
        (yyval.nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);
        (yyval.nd_obj).is_assigned = 1;

        (yyval.nd_obj).real_val = atof((yyvsp[0].nd_obj).name);
    }
#line 2783 "y.tab.c"
    break;

  case 55: /* constant: T_STRING  */
#line 1306 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("STRING_CONSTANT");
        (yyval.nd_obj).type = 3;
        (yyval.nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);
        (yyval.nd_obj).is_assigned = 1;
    }
#line 2794 "y.tab.c"
    break;

  case 56: /* constant: T_CHAR  */
#line 1314 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("CHAR_CONSTANT");
        (yyval.nd_obj).type = 4;
        (yyval.nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);
        (yyval.nd_obj).is_assigned = 1;

        (yyval.nd_obj).character_val = (yyvsp[0].nd_obj).name[0];
    }
#line 2807 "y.tab.c"
    break;

  case 57: /* if_token: T_IF  */
#line 1325 "parser.y"
{
    is_if = 1;
    (yyval.nd_obj).nd = mknode("IF");

    (yyvsp[0].nd_obj).nd = mknode((yyvsp[0].nd_obj).name);

    (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
}
#line 2820 "y.tab.c"
    break;

  case 58: /* $@1: %empty  */
#line 1335 "parser.y"
                        {sprintf(icg[icg_count++], "\nLABEL %s:\n", (yyvsp[0].nd_obj).if_body);}
#line 2826 "y.tab.c"
    break;

  case 59: /* $@2: %empty  */
#line 1335 "parser.y"
                                                                                                            {sprintf(icg[icg_count++], "\nLABEL %s:\n", (yyvsp[-3].nd_obj).else_body);}
#line 2832 "y.tab.c"
    break;

  case 60: /* if_statement: if_token expression $@1 T_THEN compound_statement $@2 else_statement  */
#line 1336 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("if_statement");

        if((yyvsp[-5].nd_obj).type != 5){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected bool type for condition in if statement\n",line_number+1);
        }

        (yyvsp[-3].nd_obj).nd = mknode("THEN");
        (yyvsp[-3].nd_obj).nd->children[0] = mknode((yyvsp[-3].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-6].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-5].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-3].nd_obj).nd; 
        (yyval.nd_obj).nd->children[3] = (yyvsp[-2].nd_obj).nd; 
        (yyval.nd_obj).nd->children[4] = (yyvsp[0].nd_obj).nd; 
        is_if = 0;
    }
#line 2854 "y.tab.c"
    break;

  case 61: /* else_statement: T_ELSE compound_statement  */
#line 1356 "parser.y"
{
    (yyval.nd_obj).nd = mknode("else_statement");

    (yyvsp[-1].nd_obj).nd = mknode("ELSE");
    (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

    (yyval.nd_obj).nd->children[0] = (yyvsp[-1].nd_obj).nd;
    (yyval.nd_obj).nd->children[1] = (yyvsp[0].nd_obj).nd;
}
#line 2868 "y.tab.c"
    break;

  case 62: /* else_statement: %empty  */
#line 1366 "parser.y"
{
    (yyval.nd_obj).nd = NULL;
}
#line 2876 "y.tab.c"
    break;

  case 63: /* $@3: %empty  */
#line 1372 "parser.y"
    {
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-5].nd_obj).nd->children[0]->token) == 0) {
                if((yyvsp[-3].nd_obj).type == 1){
                    sprintf(symbol_table[i].value,"%d",(yyvsp[-3].nd_obj).integer_val);
                }
                if((yyvsp[-3].nd_obj).type == 2){
                    sprintf(symbol_table[i].value, "%f", (yyvsp[-3].nd_obj).real_val);
                }
                if((yyvsp[-3].nd_obj).type == 3){
                    sprintf(symbol_table[i].value, "%c", (yyvsp[-3].nd_obj).character_val);
                }
            }
        }

        temp_label_1 = label++;
        temp_label_2 = label++;
        sprintf(icg[icg_count++],"%s = t%d\n",(yyvsp[-5].nd_obj).nd->children[0]->token,(yyvsp[-3].nd_obj).t);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_1);
        sprintf(icg[icg_count++], "IF %s >= t%d GOTO L%d\n", (yyvsp[-5].nd_obj).nd->children[0]->token, (yyvsp[-1].nd_obj).t, temp_label_2);

      //  if($2.is_assigned != 1){
       //     sprintf(sem_errors[sem_error_count++],"Line %d: Identifier \"%s\" is not assigned any value\n",line_number+1,$2.nd->children[0]->token);
      //  }

      for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-5].nd_obj).nd->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }
    }
#line 2922 "y.tab.c"
    break;

  case 64: /* for_statement: T_FOR identifier ASSIGNMENT expression TO expression T_DO $@3 compound_statement  */
#line 1414 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("for_statement");

        (yyvsp[-8].nd_obj).nd = mknode("FOR");
        (yyvsp[-8].nd_obj).nd->children[0] = mknode((yyvsp[-8].nd_obj).name);

        (yyvsp[-6].nd_obj).nd = mknode("ASSIGNMENT");
        (yyvsp[-6].nd_obj).nd->children[0] = mknode((yyvsp[-6].nd_obj).name);

        (yyvsp[-4].nd_obj).nd = mknode("TO");
        (yyvsp[-4].nd_obj).nd->children[0] = mknode((yyvsp[-4].nd_obj).name);

        (yyvsp[-2].nd_obj).nd = mknode("DO");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-8].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-7].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-6].nd_obj).nd; 
        (yyval.nd_obj).nd->children[3] = (yyvsp[-5].nd_obj).nd;
        (yyval.nd_obj).nd->children[4] = (yyvsp[-4].nd_obj).nd; 
        (yyval.nd_obj).nd->children[5] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[6] = (yyvsp[-2].nd_obj).nd; 
        (yyval.nd_obj).nd->children[7] = (yyvsp[0].nd_obj).nd;

        if((yyvsp[-5].nd_obj).type != 1 || (yyvsp[-3].nd_obj).type != 1){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected integer type for identifier \"%s\"\n",line_number+1,(yyvsp[-7].nd_obj).nd->children[0]->token);
        }


        sprintf(icg[icg_count++], "%s = %s - 1\n",(yyvsp[-7].nd_obj).nd->children[0]->token,(yyvsp[-7].nd_obj).nd->children[0]->token);
        sprintf(icg[icg_count++], "GOTO L%d\n", temp_label_1);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_2);
    }
#line 2960 "y.tab.c"
    break;

  case 65: /* $@4: %empty  */
#line 1449 "parser.y"
    {
        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-5].nd_obj).nd->children[0]->token) == 0) {
                if((yyvsp[-3].nd_obj).type == 1){
                    sprintf(symbol_table[i].value,"%d",(yyvsp[-3].nd_obj).integer_val);
                }
                if((yyvsp[-3].nd_obj).type == 2){
                    sprintf(symbol_table[i].value, "%f", (yyvsp[-3].nd_obj).real_val);
                }
                if((yyvsp[-3].nd_obj).type == 3){
                    sprintf(symbol_table[i].value, "%c", (yyvsp[-3].nd_obj).character_val);
                }
            }
        }

        temp_label_1 = label++;
        temp_label_2 = label++;
        sprintf(icg[icg_count++],"%s = t%d\n",(yyvsp[-5].nd_obj).nd->children[0]->token,(yyvsp[-3].nd_obj).t);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_1);
        sprintf(icg[icg_count++], "IF %s <= t%d GOTO L%d\n", (yyvsp[-5].nd_obj).nd->children[0]->token, (yyvsp[-1].nd_obj).t, temp_label_2);

        //if($2.is_assigned != 1){
        //    sprintf(sem_errors[sem_error_count++],"Line %d: Identifier \"%s\" is not assigned any value\n",line_number+1,$2.nd->children[0]->token);
       // }

       for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-5].nd_obj).nd->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }
    }
#line 3006 "y.tab.c"
    break;

  case 66: /* for_statement: T_FOR identifier ASSIGNMENT expression DOWNTO expression T_DO $@4 compound_statement  */
#line 1491 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("for_statement");

        (yyvsp[-8].nd_obj).nd = mknode("FOR");
        (yyvsp[-8].nd_obj).nd->children[0] = mknode((yyvsp[-8].nd_obj).name);

        (yyvsp[-6].nd_obj).nd = mknode("ASSIGNMENT");
        (yyvsp[-6].nd_obj).nd->children[0] = mknode((yyvsp[-6].nd_obj).name);

        (yyvsp[-4].nd_obj).nd = mknode("DOWNTO");
        (yyvsp[-4].nd_obj).nd->children[0] = mknode((yyvsp[-4].nd_obj).name);

        (yyvsp[-2].nd_obj).nd = mknode("DO");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-4].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-8].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-7].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-6].nd_obj).nd; 
        (yyval.nd_obj).nd->children[3] = (yyvsp[-5].nd_obj).nd;
        (yyval.nd_obj).nd->children[4] = (yyvsp[-4].nd_obj).nd; 
        (yyval.nd_obj).nd->children[5] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[6] = (yyvsp[-2].nd_obj).nd; 
        (yyval.nd_obj).nd->children[7] = (yyvsp[0].nd_obj).nd;

        if((yyvsp[-5].nd_obj).type != 1 || (yyvsp[-3].nd_obj).type != 1){
            sprintf(sem_errors[sem_error_count++],"Line %d: Expected integer type for identifier \"%s\"\n",line_number+1,(yyvsp[-7].nd_obj).nd->children[0]->token);
        }

        sprintf(icg[icg_count++], "%s = %s - 1\n",(yyvsp[-7].nd_obj).nd->children[0]->token,(yyvsp[-7].nd_obj).nd->children[0]->token);
        sprintf(icg[icg_count++], "GOTO L%d\n", temp_label_1);
        sprintf(icg[icg_count++], "\nLABEL L%d:\n", temp_label_2);
    }
#line 3043 "y.tab.c"
    break;

  case 67: /* $@5: %empty  */
#line 1527 "parser.y"
    {
        is_for = 1;
    }
#line 3051 "y.tab.c"
    break;

  case 68: /* $@6: %empty  */
#line 1531 "parser.y"
    {
        sprintf(icg[icg_count++], "\nLABEL %s:\n", (yyvsp[-1].nd_obj).if_body);
    }
#line 3059 "y.tab.c"
    break;

  case 69: /* while_statement: T_WHILE $@5 expression T_DO $@6 compound_statement  */
#line 1535 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("while_statement");

        (yyvsp[-5].nd_obj).nd = mknode("WHILE");
        (yyvsp[-5].nd_obj).nd->children[0] = mknode((yyvsp[-5].nd_obj).name);

        (yyvsp[-2].nd_obj).nd = mknode("DO");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-5].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[3] = (yyvsp[0].nd_obj).nd;
        is_for = 0;

      sprintf(icg[icg_count++],"GOTO %s\n",(yyvsp[-3].nd_obj).if_body);
      sprintf(icg[icg_count++], "\nLABEL %s:\n", (yyvsp[-3].nd_obj).else_body);
    }
#line 3082 "y.tab.c"
    break;

  case 70: /* write_statement: WRITE LPAREN write_params RPAREN  */
#line 1557 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("write_statement");

        (yyvsp[-3].nd_obj).nd = mknode("WRITE");
        (yyvsp[-3].nd_obj).nd->children[0] = mknode((yyvsp[-3].nd_obj).name);

        (yyvsp[-2].nd_obj).nd = mknode("LPAREN");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("RPAREN");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[3] = (yyvsp[0].nd_obj).nd;
    }
#line 3104 "y.tab.c"
    break;

  case 71: /* write_params: T_STRING  */
#line 1578 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("write_params");

        (yyvsp[0].nd_obj).nd = mknode("STRING");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 3117 "y.tab.c"
    break;

  case 72: /* write_params: identifier  */
#line 1588 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("write_params");

        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[0].nd_obj).nd->children[0]->token) == 0) {
                if(symbol_table[i].is_assigned!=1){
                    sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" used before assignment\n",line_number+1,(yyvsp[0].nd_obj).nd->children[0]->token);
                    sem_error_count++;
                    break;
                }
                else{
                    (yyval.nd_obj).is_assigned = 1;
                }
            }
        }
    }
#line 3145 "y.tab.c"
    break;

  case 73: /* write_params: write_params COMMA T_STRING  */
#line 1613 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("write_params");

        (yyvsp[-1].nd_obj).nd = mknode("COMMA");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("STRING");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[0] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;
    }
#line 3163 "y.tab.c"
    break;

  case 74: /* write_params: write_params COMMA identifier  */
#line 1628 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("write_params");

        (yyvsp[-1].nd_obj).nd = mknode("COMMA");
        (yyvsp[-1].nd_obj).nd->children[0] = mknode((yyvsp[-1].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[0] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[0] = (yyvsp[0].nd_obj).nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[0].nd_obj).nd->children[0]->token) == 0) {
                if(symbol_table[i].is_assigned!=1){
                    sprintf(sem_errors[sem_error_count],"Line %d: Variable \"%s\" used before assignment\n",line_number+1,(yyvsp[0].nd_obj).nd->children[0]->token);
                    sem_error_count++;
                    break;
                }
                else{
                    (yyval.nd_obj).is_assigned = 1;
                }
            }
        }
    }
#line 3196 "y.tab.c"
    break;

  case 75: /* read_statement: READ LPAREN identifier_or_array RPAREN  */
#line 1660 "parser.y"
    {
        (yyval.nd_obj).nd = mknode("read_statement");

        (yyvsp[-3].nd_obj).nd = mknode("READ");
        (yyvsp[-3].nd_obj).nd->children[0] = mknode((yyvsp[-3].nd_obj).name);

        (yyvsp[-2].nd_obj).nd = mknode("LPAREN");
        (yyvsp[-2].nd_obj).nd->children[0] = mknode((yyvsp[-2].nd_obj).name);

        (yyvsp[0].nd_obj).nd = mknode("RPAREN");
        (yyvsp[0].nd_obj).nd->children[0] = mknode((yyvsp[0].nd_obj).name);

        (yyval.nd_obj).nd->children[0] = (yyvsp[-3].nd_obj).nd;
        (yyval.nd_obj).nd->children[1] = (yyvsp[-2].nd_obj).nd;
        (yyval.nd_obj).nd->children[2] = (yyvsp[-1].nd_obj).nd;
        (yyval.nd_obj).nd->children[3] = (yyvsp[0].nd_obj).nd;

        for (int i = 0; i < count; i++) {
            char *name_copy = strdup(symbol_table[i].name);
            char *bracket_position = strchr(name_copy, '[');
            if (bracket_position != NULL) {
                *bracket_position = '\0';
            }
            if (strcmp(name_copy, (yyvsp[-1].nd_obj).nd->children[0]->children[0]->token) == 0) {
                symbol_table[i].is_assigned = 1;
            }
        }

    }
#line 3230 "y.tab.c"
    break;


#line 3234 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1691 "parser.y"


extern FILE *yyin;
FILE* output;
void printtree(struct node* head, int n, int depth, int child){
	
	if(head==NULL){
		return;
	}
	fprintf(output,"{");
	
	/* fprintf(output,"%s=%d:%d=", head->token, depth, child); */
	fprintf(output,"%s", head->token);
	for(int i=0; i<20; i++){
		printtree(head->children[i], n+1, depth+1, i);
	}
	fprintf(output,"}");
}

int main(int argc, char* argv[]) {
    char* filename = argv[1];
    FILE *input_file = fopen(filename, "r");
    yyin = input_file;
    yyparse();
    fclose(input_file);

    printf("\n\n");
    printf("\t\t\t\t\t\t\t   PHASE 4: INTERMEDIATE CODE GENERATION \n\n");
    for(int i=0; i<icg_count; i++){
        printf("%s", icg[i]);
    }
    printf("\n\n");

    output = fopen("output.txt","w+");
    printtree(head, 1, 0, 0);
    fclose(output);
}

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Syntax error at token: %s\n", yytext);
    fprintf(stderr, "Error occurred at line: %d\n", yylineno);
    exit(1);
}
