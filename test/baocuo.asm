.model small
.data
ID db 100 DUP(0)
.code
start:
MOV ax, @data
MOV ds, ax
ERROR:(3) a 重复声明的ID
ERROR:(5) e 未声明的ID
ERROR:(6) ~是不合法的符号
ERROR:(9) 语法错误，无法匹配
MOV al, 0
MOV ah, al
ERROR: c = a 类型错误，char和int无法匹配
MOV bl, al
MOV ah, 4ch
INT 21h
end start
