#ifndef tree_h
#define tree_h
#include "stack.h"
#include "idtable.c"
#define MAX_CHILDREN 4
int addr = 0;
int sig = 1;
Stack sigsi;
Stack sigsw;
int re,re1,ans;
union nodeattr {
	int op;				// 表达式结点，子类型是运算类型时，用op保存具体运算
	int vali;				// 表达式结点，常量表达式时，用vali保存整型常量值
	int type;
	char valc;			// 字符值
	int idnum;
};
typedef union nodeattr nodeattr;
struct node
{
	struct node *children[MAX_CHILDREN];	// 孩子结点
	int kind;					// 结点类型
	int kind_kind;				// 子类型
	nodeattr attr;				// 结点属性
	int addr;
};
typedef struct node node;
enum					// 结点类型——kind
{
	STMT_NODE = 0,
	EXPR_NODE,
	DECL_NODE,
    FUNC_NODE
};
enum
{
    MAIN_FUNC,
    FUNCS_FUNC,
    VOID_FUNC
};
enum					// 语句结点子类型——kindkind
{
	IF_STMT = 0,
	WHILE_STMT,
	INPUT_STMT,
	PRINT_STMT,
	ASS_STMT,
	STMTS_STMT,
};

enum					// 表达式结点子类型——kindkind
{
	TYPE_EXPR = 0,
	OP_EXPR,
	NOT_EXPR,
	ARRAY_EXPR,
	CONST_EXPR,
	ID_EXPR,
	CHAR_EXPR
};

enum					// 声明结点子类型——kindkind

{
	VAR_DECL = 0,
	ARRAY_DECL,
};

enum					// 运算——op
{
	OPLUS = 0,
	OMINUS,
	OEQUAL,
	OLESS,
	OBIG,
	ONE
};

enum
{
	TINT = 0,
	TCHAR = 1
};


void setnodeattro( nodeattr* attr, int i)
{
	attr->op = i;
}
void setnodeattri( nodeattr* attr, int i)
{
	attr->vali = i;
}
void setnodeattrc( nodeattr* attr, char c)
{
	attr->valc = c;
}
void setnodeattrt( nodeattr* attr, int i)
{
	attr->type =i;
}
void setnodeattrs( nodeattr* attr, int i)
{
	attr->idnum = i;
}
void setnode( node* p,
		int kind,
		int kind_kind,
		int addr,
		node *child1,
		node *child2,
		node* child3,
		node*child4)
{
	p->kind = kind;
	p->kind_kind = kind_kind;
	p->addr = addr;
	p->children[0] = child1;
	p->children[1] = child2;
	p->children[2] = child3;
	p->children[3] = child4;
}
void start( node* node)
{
	switch(node->kind){
        case FUNC_NODE:
        {
            switch (node->kind_kind) {
                case MAIN_FUNC:
                    break;
                case VOID_FUNC:
                    break;
                default:
                    break;
            }
        }
		case STMT_NODE:
			{
				switch(node->kind_kind){
					case IF_STMT:
						printf("L%d:\n",Stack_Top(&sigsi));
						Stack_Pop(&sigsi);
						break;
					case ASS_STMT:
						if ((node->children[0]->kind_kind == ID_EXPR)
								&&(node->children[1]->kind_kind == ID_EXPR)) {
							if (idtable[node->children[0]->attr.idnum].type
									!= idtable[node->children[1]->attr.idnum].type) {
								printf("ERROR: %s = %s 类型错误，char和int无法匹配\n",
										idtable[node->children[0]->attr.idnum].name,
										idtable[node->children[1]->attr.idnum].name);
							}
						}
                        if (node->children[0]->kind_kind == ID_EXPR) {
                            re = need_id(node->children[0]->attr.idnum);
                            if (node->children[1]->kind_kind == CONST_EXPR) {
                                printf("MOV %s, %d\n",regname[re],node->children[1]->attr.vali);
                            }
                            else if(node->children[1]->kind_kind == ID_EXPR){
                                re1 = need_id(node->children[1]->attr.idnum);
                                printf("MOV %s, %s\n",regname[re],regname[re1]);
                            }
                            else if(node->children[1]->kind_kind == CHAR_EXPR){
                                re1 = need_id(node->children[1]->attr.idnum);
                                printf("MOV %s, '%c'\n",regname[re],node->children[1]->attr.valc);
                            }
                            else if(node->children[1]->kind_kind == OP_EXPR){
                                printf("MOV %s, %s\n",regname[re],regname[ans]);
                            }
                            else if(node->children[1]->kind_kind == ARRAY_EXPR){
                                printf("MOV %s, ID[si+%d]\n",regname[re],idtable[node->children[1]->attr.idnum].addr);
                            }
                        }
                        else if (node->children[0]->kind_kind == ARRAY_EXPR) {
                            re = emp_reg();
                            if (node->children[1]->kind_kind == CONST_EXPR) {
                                printf("MOV ID[si+%d], %d\n",idtable[node->children[0]->attr.idnum].addr,node->children[1]->attr.vali);
                            }
                            else if(node->children[1]->kind_kind == ID_EXPR){
                                re1 = need_id(node->children[1]->attr.idnum);
                                printf("MOV ID[si+%d], %s\n",idtable[node->children[0]->attr.idnum].addr,regname[re1]);
                            }
                            else if(node->children[1]->kind_kind == CHAR_EXPR){
                                re1 = need_id(node->children[1]->attr.idnum);
                                printf("MOV ID[si+%d], '%c'\n",idtable[node->children[0]->attr.idnum].addr,node->children[1]->attr.valc);
                            }
                            else if(node->children[1]->kind_kind == OP_EXPR){
                                printf("MOV ID[si+%d], %s\n",idtable[node->children[0]->attr.idnum].addr,regname[ans]);
                            }
                            else if(node->children[1]->kind_kind == ARRAY_EXPR){
                                printf("MOV ID[si+%d], ID[si+%d]\n",idtable[node->children[0]->attr.idnum].addr,
                                       idtable[node->children[1]->attr.idnum].addr);
                            }
                        }
						

						//                    re = (char)emp_reg();
						//                    printf("MOV si, %xh\n",idtable[node->children[0]->attr.idnum].addr);
						//                    if (node->children[1]->kind_kind == CONST_EXPR){
						//                        printf("MOV %cl, %d\n",re,node->children[1]->attr.vali);
						//                        printf("MOV [si], %cl\n", re);
						//                        }
												//                        printf("MOV %cl, %cl\n", re, ans);
						//                        printf("MOV [si], %cl\n",re);
						//                        rel_reg(ans);
						//                    }
						//                        rel_reg(re);
						break;
				case WHILE_STMT:
						rel_all_reg();
						printf("JMP L%d\n",Stack_Top(&sigsw));;
						printf("L%d:\n",Stack_Top(&sigsi));
						Stack_Pop(&sigsw);
                        Stack_Pop(&sigsi);
						break;
				case INPUT_STMT:
						//                    if (check_reg('a')) {
						//                        re = emp_reg();
						//                        printf("MOV %cx, ax\n",re);
						//                        check_temp1 = 1;
						//                    }
						//                    else {
						//                        re = emp_reg(); //re = 'a';
						//                    }
						rel_reg(0);
						rel_reg(1);
						printf("MOV ah, 01h\n");
						printf("INT 21h\n");
						if (idtable[node->children[0]->attr.idnum].type == 0) {
							printf("SUB al, 48\n");
						}
						if(idtable[node->children[0]->attr.idnum].reg == -1){
							bind_id_reg(node->children[0]->attr.idnum, 0);
						}
						else{
							re = idtable[node->children[0]->attr.idnum].reg;
							printf("MOV %s, al\n",regname[re]);
						}
						//                    if(check_temp1) {
						//                        printf("MOV ax, e%cx\n",re);
						//                    }
						//                    rel_reg(re);
						break;
				case PRINT_STMT:
						//                    if (check_reg('a')) {
						//                        re = emp_reg();
						//                        printf("MOV %cx, ax\n",re);
						//                        check_temp1 = 1;
						//                    }
						////                    if (check_reg('d')) {
						////                        re1 = emp_reg();
						////                        printf("MOV %cx, ax\n",re1);
						////                        check_temp2 = 1;
						////                    }
						rel_reg(0);
						rel_reg(1);
						rel_reg(6);
						if (node->children[0]->kind_kind == ID_EXPR) {
							re = need_id(node->children[0]->attr.idnum);
							if (idtable[node->children[0]->attr.idnum].type == 0) {
								printf("ADD %s, 48\n",regname[re]);
							}
							printf("MOV dl, %s\n",regname[re]);
							printf("MOV ah, 02h\n");
							printf("INT 21h\n");
							if (idtable[node->children[0]->attr.idnum].type == 0) {
								printf("SUB %s, 48\n",regname[re]);
							}
						}
                        if (node->children[0]->kind_kind == ARRAY_EXPR) {
                            re = emp_reg();
                            if (idtable[node->children[0]->attr.idnum].type == 0) {
                                printf("MOV %s, 48\n",regname[re]);
                                printf("ADD ID[si+%d], %s\n",idtable[node->children[0]->attr.idnum].addr,regname[re]);
                            }
                            printf("MOV dl, ID[si+%d]\n",idtable[node->children[0]->attr.idnum].addr);
                            printf("MOV ah, 02h\n");
                            printf("INT 21h\n");
                            if (idtable[node->children[0]->attr.idnum].type == 0) {
                                printf("SUB ID[si+%d], %s\n",idtable[node->children[0]->attr.idnum].addr,regname[re]);
                            }
                        }
						else if (node->children[0]->kind_kind == CHAR_EXPR) {
							printf("MOV dl, '%c'\n",node->children[0]->attr.valc);
							printf("MOV ah, 02h\n");
							printf("INT 21h\n");
						}
						else if (node->children[0]->kind_kind == CONST_EXPR) {
							printf("MOV dl, %d\n",node->children[0]->attr.vali);
							printf("MOV ah, 02h\n");
							printf("INT 21h\n");
						}
						//                    if(check_temp1) {
						//                        printf("MOV ax, e%cx\n",re);
						//                        rel_reg(re);
						//                    }
						//                    if(check_temp2) {
						//                        printf("MOV ax, e%cx\n",re1);
						//                        rel_reg(re1);
						//                    }
						break;
				default:
						break;
			}
	}
        break;
	case EXPR_NODE:
	{
		switch(node->kind_kind)
		{
			case OP_EXPR:
				switch(node->attr.op)
				{
					case OPLUS:
						ans = need_id(0);
						if(node->children[0]->kind_kind == ID_EXPR){
							re = need_id(node->children[0]->attr.idnum);
							printf("MOV %s, %s\n",regname[ans],regname[re]);
						}
						if(node->children[1]->kind_kind == ID_EXPR){
							re1 = need_id(node->children[1]->attr.idnum);
							printf("ADD %s, %s\n",regname[ans],regname[re1]);
						}
						else{
							printf("ADD %s, %d\n",regname[ans],node->children[1]->attr.vali);
						}
						break;
					case OMINUS:
						break;
					case OLESS:
						if (node->children[0]->kind_kind == ID_EXPR) {
							re = need_id(node->children[0]->attr.idnum);
						}
						if (node->children[1]->kind_kind == ID_EXPR) {
							re1 = need_id(node->children[1]->attr.idnum);
							printf("CMP %s, %s\n", regname[re], regname[re1]);
						}
						else if (node->children[1]->kind_kind == CONST_EXPR) {
							printf("CMP %s, %d\n", regname[re], node->children[1]->attr.vali);
						}
						printf("JAE L%d\n",sig);
						Stack_Push(&sigsi,sig++);
						rel_all_reg();
						break;
					case ONE:
						if (node->children[0]->kind_kind == ID_EXPR) {
							re = need_id(node->children[0]->attr.idnum);
						}
						if (node->children[1]->kind_kind == ID_EXPR) {
							re1 = need_id(node->children[1]->attr.idnum);
							printf("CMP %s, %s\n", regname[re], regname[re1]);
						}
						else if (node->children[1]->kind_kind == CONST_EXPR) {
							printf("CMP %s, %d\n", regname[re], node->children[1]->attr.vali);
						}
						printf("CMP %s, %s\n", regname[re], regname[re1]);
						printf("JZ L%d\n",sig);
						Stack_Push(&sigsi,sig++);
						rel_all_reg();
						break;
					case OBIG:
						if (node->children[0]->kind_kind == ID_EXPR) {
							re = need_id(node->children[0]->attr.idnum);
						}
						if (node->children[1]->kind_kind == ID_EXPR) {
							re1 = need_id(node->children[1]->attr.idnum);
							printf("CMP %s, %s\n", regname[re], regname[re1]);
						}
						else if (node->children[1]->kind_kind == CONST_EXPR) {
							printf("CMP %s, %d\n", regname[re], node->children[1]->attr.vali);
						}
						printf("CMP %s, %s\n", regname[re], regname[re1]);
						printf("JBE L%d\n",sig);
						Stack_Push(&sigsi,sig++);
						rel_all_reg();
						break;
					case OEQUAL:
						if (node->children[0]->kind_kind == ID_EXPR) {
							re = need_id(node->children[0]->attr.idnum);
						}
						if (node->children[1]->kind_kind == ID_EXPR) {
							re1 = need_id(node->children[1]->attr.idnum);
							printf("CMP %s, %s\n", regname[re], regname[re1]);
						}
						else if (node->children[1]->kind_kind == CONST_EXPR) {
							printf("CMP %s, %d\n", regname[re], node->children[1]->attr.vali);
						}
						printf("CMP %s, %s\n", regname[re], regname[re1]);
						printf("JNZ L%d\n",sig);
						Stack_Push(&sigsi,sig++);
						rel_all_reg();
						break;
					default:
						break;
				}
				break;
			case CONST_EXPR:
				break;	
			case ARRAY_EXPR:
                if (node->children[0]->kind_kind == ID_EXPR) {
                    rel_reg(4);
                    rel_reg(5);
                    re = need_id(node->children[0]->attr.idnum);
                    printf("MOV cl, %s\n",regname[re]);
                    printf("MOV ch, 0\n");
                    printf("MOV si, cx\n");
                }
                if (node->children[0]->kind_kind == OP_EXPR){
                    rel_reg(4);
                    rel_reg(5);
                    re = need_id(node->children[0]->attr.idnum);
                    printf("MOV cl, %s\n",regname[ans]);
                    printf("MOV ch, 0\n");
                    printf("MOV si, cx\n");
                }
				break;
			default:
				break;
		}
		break;
	}
	case DECL_NODE:
	{
		switch(node->kind_kind)
		{
			case VAR_DECL:
				break;
            case ARRAY_DECL:
                break;
			default:
				break;
		}
		break;
	}
            break;
	default:
            break;
}
}

int print(node *t){
	printf("%d:%d,%d",t->addr,t->kind,t->kind_kind);
	for (int i = 0; i<3; i++) {
		if(t->children[i]!=NULL){
			printf(",%d",t->children[i]->addr);
		}
	}
	printf("\n");
	return 0;
}
int scantree( node* t)
{
	if (t->kind == STMT_NODE
			&& t->kind_kind == WHILE_STMT )// while循环提前输出标号
	{
		rel_all_reg();
		printf("L%d:\n",sig);
		Stack_Push(&sigsw,sig);
        sig++;
	}
	if(t->children[0] != NULL)
	{
		scantree(t->children[0]);
	}
	if(t->children[1] != NULL)
	{
		scantree(t->children[1]);
	}
	start(t);
	return 0;
}
int checktree( node* t)
{

	if(t->children[0] != NULL)
	{
		checktree(t->children[0]);
	}
	if(t->children[1] != NULL)
	{
		checktree(t->children[1]);
	}
	print(t);
	return 0;
}

#endif /* tree_h */

