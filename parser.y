%{
#include <stdio.h>
#define YYSTYPE struct node*
#include <string.h>
#include "tree.h"
#include "idtable.c"
void yyerror (const char *error);
char* yytext;
int yylex();
struct node *root;
char arrayname[MAX_IDLENGTH];
%}
%token ',' ';' INT CHAR NUMBER IF ELSE '[' ']' '(' ')' '{' '}' '=' EQUAL PLUS SUB MUL DIV ID WHILE FOR AND OR NOTB NOTL NOTE '!' '>' '<' '|' '&' ASK INPUT PRINT MAIN AR 
%%
/*funcs   :funcs func{
            struct node*p = malloc(sizeof(*p));
            setnode(p, FUNC_NODE, FUNCS_FUNC, addr++, $1, $2, NULL,NULL);
            $$ = p;
            root = p;
            }
        |func{
            root = $1;
            $$ = $1;
            }
        ;
func    :MAIN '(' ')' '{' stmts '}' {
            struct node*p = malloc(sizeof(*p));
            setnode(p, FUNC_NODE, MAIN_FUNC, addr++, $5, NULL, NULL,NULL);
            $$ =p;
            }
        |FU ')' '{' stmts '}'{
            struct node*p = malloc(sizeof(*p));
            setnode(p, FUNC_NODE, VOID_FUNC, addr++, $4, NULL, NULL,NULL);
            $$ = p;
        }*/
func    :MAIN '(' ')''{'stmts'}'{
            $$ = $5;
            root = $$;
        }
stmts	:stmts stmt{
			struct node*p = malloc(sizeof(*p));
			setnode(p, STMT_NODE, STMTS_STMT, addr++, $1, $2, NULL,NULL);
			$$ = p;
			}
		|stmt{
			$$ = $1;
			}
        ;
stmt	:type idlist ';' {
			struct node* p = malloc(sizeof(*p));
			setnode(p, DECL_NODE, VAR_DECL, addr++, $1, $2, NULL, NULL);
			$$ = p;
			}
        |type arraylist ';' {
            struct node* p = malloc(sizeof(*p));
            setnode(p, DECL_NODE, VAR_DECL, addr++, $1, $2, NULL, NULL);
            $$ = p;
            }
		|IF '('expr')''{'stmts'}'{
			struct node* p = malloc(sizeof(*p));
			setnode(p, STMT_NODE, IF_STMT, addr++, $3, $6, NULL, NULL);
			$$ = p;
			}
        |array '=' expr ';' {
            struct node*p = malloc(sizeof(*p));
            setnode(p, STMT_NODE, ASS_STMT, addr++, $1, $3,NULL,NULL);
            $$ = p;
            }
		|ID {
			int temp = searchtable(yytext);
            if(temp < 0){
                printf("ERROR:(%d) %s 未声明的ID\n",(int)yylval,yytext);
            }
			struct node*t = malloc(sizeof(*t));
			setnode(t, EXPR_NODE, ID_EXPR, addr++, NULL, NULL, NULL, NULL);
            setnodeattrs(&t->attr,temp);
			$1 = t;
			}	'=' expr ';'{
			struct node*p = malloc(sizeof(*p));
			setnode(p, STMT_NODE, ASS_STMT, addr++, $1, $4,NULL,NULL);
			$$ = p;
            }

        |WHILE '('expr')''{'stmts'}'{
            struct node* p = malloc(sizeof(*p));
            setnode(p, STMT_NODE, WHILE_STMT, addr++, $3, $6, NULL, NULL);
            $$ = p;
        }
        |PRINT'('factor')'';'{
            struct node* p = malloc(sizeof(*p));
            setnode(p, STMT_NODE, PRINT_STMT, addr++, $3, NULL, NULL, NULL);
            $$ = p;
        }
        |INPUT'('factor')'';'{
            struct node* p = malloc(sizeof(*p));
            setnode(p, STMT_NODE, INPUT_STMT, addr++, $3, NULL, NULL, NULL);
            $$ = p;
        }
        ;

expr	:simple_expr EQUAL simple_expr{
			struct node*p = malloc(sizeof(*p));
			setnode(p, EXPR_NODE, OP_EXPR, addr++, $1, $3,NULL,NULL);
			setnodeattro(&p->attr,OEQUAL);
			$$ = p;
			}
        |simple_expr '<' simple_expr{
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, OP_EXPR, addr++, $1, $3,NULL,NULL);
            setnodeattro(&p->attr,OLESS);
            $$ = p;
            }
        |simple_expr '>' simple_expr{
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, OP_EXPR, addr++, $1, $3,NULL,NULL);
            setnodeattro(&p->attr,OBIG);
            $$ = p;
        }
        |simple_expr NOTE simple_expr{
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, OP_EXPR, addr++, $1, $3,NULL,NULL);
            setnodeattro(&p->attr,ONE);
            $$ = p;
        }
		|simple_expr{
			$$ = $1;
			}
		;
simple_expr: simple_expr PLUS term{
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, OP_EXPR, addr++, $1, $3,NULL,NULL);
            setnodeattro(&p->attr,OPLUS);
            $$ = p;
            }
		|simple_expr SUB term
		|term{
			$$ = $1;
			}
		;
term	:term MUL factor
		|term DIV factor
		|factor{
			$$ = $1;
			}
		;
factor	:'(' expr ')'{
			$$ = $2;
			}
        |ASK{
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, CHAR_EXPR, addr++, NULL, NULL, NULL,NULL);
            setnodeattrc(&p->attr,(char)yytext[1]);
            $$ = p;
            
        }
		|NUMBER{
			struct node*p = malloc(sizeof(*p));
			setnode(p, EXPR_NODE, CONST_EXPR, addr++, NULL, NULL, NULL,NULL);
			setnodeattri(&p->attr,(int)yylval);
			$$ = p;
			
			}
        |ID {
            int temp = searchtable(yytext);
            if(temp < 0){
                printf("ERROR:(%d) %s 未声明的ID\n",(int)yylval,yytext);
            }
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, ID_EXPR, addr++, NULL, NULL, NULL, NULL);
            setnodeattrs(&p->attr,temp);
            $$ = p;
        }
        |array {
            $$ = $1;
        }
array   :AR{
            strcpy(arrayname, yytext);
            } simple_expr ']'{
                int temp = searchtable_array(arrayname);
                //printf("%d",temp);
                if(temp < 0){
                    printf("ERROR:(%d) %s 未声明的数组\n",(int)yylval,yytext);
                }
                struct node*p = malloc(sizeof(*p));
                setnode(p, EXPR_NODE, ARRAY_EXPR, addr++, $3, NULL, NULL, NULL);
                setnodeattrs(&p->attr,temp);;
                if($3->kind_kind == CONST_EXPR){
                    if((int)yylval >= idtable[p->attr.idnum].array){
                        printf("ERROR: 数组越界\n");
                    }
                    p -> attr.idnum = p->attr.idnum + (int)yylval;
                    p -> kind_kind = ID_EXPR;
                    idtable[p -> attr.idnum].array = -1;
                }
                $$ = p;
            }
        ;
idlist	: idlist ',' ID {
            int temp = searchtable(yytext);
            if(temp >= 0){
                printf("ERROR:(%d) %s 重复声明的ID\n",(int)yylval,yytext);
            }
            temp = newid(yytext);
			struct node*t = malloc(sizeof(*t));
			setnode(t, EXPR_NODE, ID_EXPR, addr++, NULL, NULL, NULL, NULL); 
			setnodeattrs(&t->attr,temp);
			$3 = t;
			
			struct node*p = malloc(sizeof(*p));
			setnode(p, EXPR_NODE, ID_EXPR, addr++, $1, $3, NULL, NULL); 
			$$ = p;
			
			}
		| ID { 
            int temp = searchtable(yytext);
            if(temp >= 0){
                printf("ERROR:(%d) %s 重复声明的ID\n",(int)yylval,yytext);
            }
            temp = newid(yytext);
			struct node*p = malloc(sizeof(*p));
			setnode(p, EXPR_NODE, ID_EXPR, addr++, NULL, NULL, NULL, NULL);
			setnodeattrs(&p->attr,temp);
			$$ = p;
			}
arraylist : AR {
            int temp = searchtable(yytext);
            if(temp >= 0){
                printf("ERROR:(%d) %s 重复声明的数组\n",(int)yylval,yytext);
            }
            //printf("%s\n",yytext);
            strcpy(arrayname,yytext);
            struct node*p = malloc(sizeof(*p));
            setnode(p, EXPR_NODE, ID_EXPR, addr++, NULL, NULL, NULL, NULL);
			$1 = p;
            } NUMBER {
                int temp = newarray(arrayname,(int)yylval);
                setnodeattrs(&($1->attr),temp);
                idtable[$1 -> attr.idnum].array = (int)yylval;
                setnodeattrs(&$1->attr, temp);
                //printf("%d",temp);
            }']'{
			$$ = $1;
			}
        ;

type	: INT	{
			struct node*p = malloc(sizeof(*p));
			setnode(p, EXPR_NODE, TYPE_EXPR, addr++, NULL, NULL, NULL, NULL);
			setnodeattrt(&p->attr, TINT);
            curr_type = TINT;
			$$ = p;
			
			}
		| CHAR	{
			struct node*p = malloc(sizeof(*p));
			setnode(p, EXPR_NODE, TYPE_EXPR, addr++, NULL, NULL, NULL, NULL);
			setnodeattrt(&p->attr, TCHAR);
            curr_type = TCHAR;
			$$ = p;
			
			}	
		;
%%
int main ()
{
    printf(".model small\n.data\nID db 100 DUP(0)\n.code\nstart:\nMOV ax, @data\nMOV ds, ax\n");
    Stack_Init(&sigsi);
    Stack_Init(&sigsw);
    newid("ans");
	yyparse ();
    scantree(root);
    printf("MOV ah, 4ch\nINT 21h\nend start\n");
//    print_idtable();
    return 0;
}

void yyerror (const char *error)
{
    printf("ERROR:(%d) 语法错误，无法匹配\n",(int)yylval);
	return;
}
