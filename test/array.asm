.model small
.data
ID db 100 DUP(0)
.code
start:
MOV ax, @data
MOV ds, ax
MOV al, 0
MOV ID[1h], al
L1:
MOV al, ID[1h]
CMP al, 7
JAE L2
MOV ID[1h], al
MOV al, ID[1h]
MOV cl, al
MOV ch, 0
MOV si, cx
MOV ID[si+2], al
MOV ah, al
ADD ah, 1
MOV al, ah
MOV ID[1h], al
MOV ID[0h], ah
JMP L1
L2:
MOV al, ID[1h]
MOV al, 0
MOV ID[1h], al
L3:
MOV al, ID[1h]
CMP al, 7
JAE L4
MOV ID[1h], al
MOV al, ID[1h]
MOV cl, al
MOV ch, 0
MOV si, cx
MOV ID[1h], al
MOV al, 48
ADD ID[si+2], al
MOV dl, ID[si+2]
MOV ah, 02h
INT 21h
SUB ID[si+2], al
MOV al, ID[0h]
MOV ah, ID[1h]
MOV al, ah
ADD al, 1
MOV ah, al
MOV ID[0h], al
MOV ID[1h], ah
JMP L3
L4:
MOV ah, 4ch
INT 21h
end start
