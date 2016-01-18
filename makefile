compiler:	lexer.l parser.y tree.h stack.h idtable.c
	bison -d parser.y
	flex lexer.l
	gcc -std=c99 -o $@ parser.tab.c lex.yy.c
