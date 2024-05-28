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
    WRITELN = 274,                 /* WRITELN  */
    TO = 275,                      /* TO  */
    DOWNTO = 276,                  /* DOWNTO  */
    T_BEGIN = 277,                 /* T_BEGIN  */
    T_END = 278,                   /* T_END  */
    VAR = 279,                     /* VAR  */
    CONST = 280,                   /* CONST  */
    PROCEDURE = 281,               /* PROCEDURE  */
    FUNCTION = 282,                /* FUNCTION  */
    PROGRAM = 283,                 /* PROGRAM  */
    ARRAY = 284,                   /* ARRAY  */
    OF = 285,                      /* OF  */
    T_IDENTIFIER = 286,            /* T_IDENTIFIER  */
    T_INTEGER = 287,               /* T_INTEGER  */
    T_REAL = 288,                  /* T_REAL  */
    T_STRING = 289,                /* T_STRING  */
    T_CHAR = 290,                  /* T_CHAR  */
    T_TRUE = 291,                  /* T_TRUE  */
    T_FALSE = 292,                 /* T_FALSE  */
    T_MAXINT = 293,                /* T_MAXINT  */
    ASSIGNMENT = 294,              /* ASSIGNMENT  */
    COLON = 295,                   /* COLON  */
    SEMICOLON = 296,               /* SEMICOLON  */
    COMMA = 297,                   /* COMMA  */
    DOT = 298,                     /* DOT  */
    DOTDOT = 299,                  /* DOTDOT  */
    EQUAL = 300,                   /* EQUAL  */
    NOTEQUAL = 301,                /* NOTEQUAL  */
    LESSEQUAL = 302,               /* LESSEQUAL  */
    LESS = 303,                    /* LESS  */
    GREATEREQUAL = 304,            /* GREATEREQUAL  */
    GREATER = 305,                 /* GREATER  */
    LPAREN = 306,                  /* LPAREN  */
    RPAREN = 307,                  /* RPAREN  */
    LBRACKET = 308,                /* LBRACKET  */
    RBRACKET = 309,                /* RBRACKET  */
    PLUS = 310,                    /* PLUS  */
    MINUS = 311,                   /* MINUS  */
    MUL = 312,                     /* MUL  */
    DIV = 313,                     /* DIV  */
    MOD = 314                      /* MOD  */
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
#define WRITELN 274
#define TO 275
#define DOWNTO 276
#define T_BEGIN 277
#define T_END 278
#define VAR 279
#define CONST 280
#define PROCEDURE 281
#define FUNCTION 282
#define PROGRAM 283
#define ARRAY 284
#define OF 285
#define T_IDENTIFIER 286
#define T_INTEGER 287
#define T_REAL 288
#define T_STRING 289
#define T_CHAR 290
#define T_TRUE 291
#define T_FALSE 292
#define T_MAXINT 293
#define ASSIGNMENT 294
#define COLON 295
#define SEMICOLON 296
#define COMMA 297
#define DOT 298
#define DOTDOT 299
#define EQUAL 300
#define NOTEQUAL 301
#define LESSEQUAL 302
#define LESS 303
#define GREATEREQUAL 304
#define GREATER 305
#define LPAREN 306
#define RPAREN 307
#define LBRACKET 308
#define RBRACKET 309
#define PLUS 310
#define MINUS 311
#define MUL 312
#define DIV 313
#define MOD 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "BTC24ETH.y"
 
    struct var_name { 
        char name[100]; 
        struct node* nd;
    } nd_obj;

#line 192 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
