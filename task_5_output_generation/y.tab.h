/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 363 "parser.y"
 
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

#line 190 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
