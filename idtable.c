#ifndef idtable_h
#define idtable_h
#include<stdio.h>
#include "stack.h"
#define MAX_IDLENGTH 32
#define MAX_IDTABLE 100
#define MAXREG 8
int curr_type = 0;//用于确定类型
int curr_addr = 0;
int idcount = -1;
struct iditem
{
    char name[MAX_IDLENGTH];
    int type;
    int addr;
    int reg;
    int used;
    int array;
};
typedef struct iditem iditem;
iditem idtable[MAX_IDTABLE];




//register
int co = 3;
Stack swap;
int reg[MAXREG] = {-1,-1,-1,-1,-1,-1,-1,-1};//－1为空，否则存对应id号
char regname[MAXREG][3]={"al\0","ah\0","bl\0","bh\0","cl\0","ch\0","dl\0","dh\0"};
void rel_reg(int t){
    if(reg[t] == -1){
        return;
    }
    else{
        printf("MOV ID[%xh], %s\n", idtable[reg[t]].addr,regname[t]);
        idtable[reg[t]].reg = -1;
        idtable[reg[t]].used = 1;
        reg[t] = -1;
    }
}
int emp_reg(){
    for (int i = 0; i < MAXREG; i++)
    {
        if (reg[i] == -1)
        {
            return i;
        }
    }
    rel_reg(co);
    co++;
    return co-1;
}
void give_id_reg(int idnum){
    int te = emp_reg();
    idtable[idnum].reg =te;
    reg[te] = idnum;
    if (idtable[idnum].used == 1) {
        printf("MOV %s, ID[%xh]\n", regname[te],idtable[idnum].addr);
    }
    return;
}
void bind_id_reg(int idnum, int regnum){
    if(idtable[idnum].reg != -1){
        printf("ERROR BIND\n");
        return;
    }
    if(reg[regnum] != -1){
        printf("ERROR BIND\n");
        return;
    }
    idtable[idnum].reg = regnum;
    reg[regnum] = idnum;
    return;
}
void rel_all_reg(){
    rel_reg(0);
    rel_reg(1);
    rel_reg(2);
    rel_reg(3);
    rel_reg(4);
    rel_reg(5);
    rel_reg(6);
    rel_reg(7);
}
//void push_reg(int t){
//    printf("PUSH %s\n",regname[t]);
//    Stack_Push(&swap,reg[t]);
//    idtable[reg[t]].reg = -1;
//    reg[t] = -1;
//}
//void pop_reg(int t){
//    printf("POP %s\n",regname[t]);
//    reg[t] = Stack_Top(&swap);
//    idtable[reg[t]].reg = t;
//    Stack_Pop(&swap);
//}
///
///
//

//查找id
int searchtable(char* text)
{
    for(int i=0; i <= idcount; i++){
        if(!strcmp(text,idtable[i].name)){
            return i;
        }
    }
    return -1;
}
int searchtable_array(char* text)
{
    for(int i=0; i <= idcount; i++){
        if(!strncmp(text,idtable[i].name,2)){
            return i;
        }
    }
    return -1;
}
//插入id
int newid(char* text)
{
    idcount += 1;
    strcpy(idtable[idcount].name,text);
    idtable[idcount].type = curr_type;
    idtable[idcount].addr = curr_addr;
    if (curr_type == 0) {
        curr_addr += 1;
    }
    else{
        curr_addr += 1;
    }
    idtable[idcount].reg = -1;
    idtable[idcount].used = 0;
    idtable[idcount].array = -1;
    return idcount;
}
int newarray(char* text, int num)
{
    char name[MAX_IDLENGTH];
    int a = idcount + 1;
    for (int i = 0; i < num; i++) {
        sprintf(name,"%s%d]",text,i);
        newid(name);
        idtable[idcount-1].array = 1;
    }
    return a;
}
//需要使用某id前进行查询，返回其存储的寄存器号
int need_id(int idnum){
    if(idtable[idnum].reg == -1)
        give_id_reg(idnum);
    return idtable[idnum].reg;
}
//输出符号表
void print_idtable(){
    int i =0;
    while (i <= idcount) {
        printf("ID:%d %s TYPE:%d ADDR:0x%x\n",i, idtable[i].name, idtable[i].type, idtable[i].addr);
        i++;
    }
    return;
}


#endif /* idtable_h */
