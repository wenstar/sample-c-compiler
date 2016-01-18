%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int line = 1;
%}

%%

" "
"\r"
"	"
"//".*"\n" {
    line += 1;
    yylval = line;
}
"\n" {
    line += 1;
    yylval = line;
}
"'"."'" {
    return ASK;
    }
","		{
	return ',';
	}
";"		{
	return ';';
	}
"main"  {
    return MAIN;
}
"int"	{
	return INT;
	}
"char"	{
	return CHAR;
	}
"if"	{
	return IF;
	}
"while"	{
	return WHILE;
	}
"for"	{
	return FOR;
	}
"input" {
	return INPUT;
}
"print" {
    return PRINT;
}
[0-9][0-9]*	{
	yylval = atoi(yytext);
	return NUMBER;
	}
"["	{
	return '[';
	}	
"]"	{
	return ']';
	}	
"("	{
	return '(';
	}	
")"	{
	return ')';
	}	
"{"	{
	return '{';
	}	
"}"	{
	return '}';
	}	
"+"	{
	return PLUS;	
	}	
"-"	{
	return SUB;
	}	
"*"	{
	return MUL;
	}	
"/"	{
	return DIV;
	}	
"&&"	{
	return AND;
	}
"&"	{
	return '&';
	}
"||" {
	return OR;
	}
"|"	{
	return '|';
	}
"<="	{
	return NOTB;
	}
">="	{
	return NOTL;
	}
"<"	{
	return '<';
	}
">" {
	return '>';
	}
"!=" {
	return NOTE;
	}
"!"	{
	return '!';
	}
[a-zA-Z_][a-zA-Z0-9_]*"["	{
    return AR;
}
[a-zA-Z_][a-zA-Z0-9_]*	{
	return ID;
	}
"=="	{
	return EQUAL;
	}	
"="	{
	return '=';
	}
.	{
	printf("ERROR:(%d) %s是不合法的符号\n",line, yytext );
	}
%%
