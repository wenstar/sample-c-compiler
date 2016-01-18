/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     CHAR = 259,
     NUMBER = 260,
     IF = 261,
     ELSE = 262,
     EQUAL = 263,
     PLUS = 264,
     SUB = 265,
     MUL = 266,
     DIV = 267,
     ID = 268,
     WHILE = 269,
     FOR = 270,
     AND = 271,
     OR = 272,
     NOTB = 273,
     NOTL = 274,
     NOTE = 275,
     ASK = 276,
     INPUT = 277,
     PRINT = 278,
     MAIN = 279,
     AR = 280
   };
#endif
/* Tokens.  */
#define INT 258
#define CHAR 259
#define NUMBER 260
#define IF 261
#define ELSE 262
#define EQUAL 263
#define PLUS 264
#define SUB 265
#define MUL 266
#define DIV 267
#define ID 268
#define WHILE 269
#define FOR 270
#define AND 271
#define OR 272
#define NOTB 273
#define NOTL 274
#define NOTE 275
#define ASK 276
#define INPUT 277
#define PRINT 278
#define MAIN 279
#define AR 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

