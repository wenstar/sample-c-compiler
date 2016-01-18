.model small
.data
ID db 100 DUP(0)
.code
start:
MOV ax, @data
MOV ds, ax
MOV al, 0
MOV ah, 10
MOV bl, 0
MOV ID[1h], al
MOV ID[2h], ah
MOV ID[3h], bl
L1:
MOV al, ID[1h]
CMP al, 20
JAE L2
MOV ID[1h], al
MOV al, ID[1h]
MOV ah, ID[2h]
CMP al, ah
JAE L3
MOV ID[1h], al
MOV ID[2h], ah
L4:
MOV al, ID[3h]
CMP al, 5
JAE L5
MOV ID[3h], al
MOV dl, '+'
MOV ah, 02h
INT 21h
MOV ah, ID[3h]
MOV al, ah
ADD al, 1
MOV ah, al
MOV ID[0h], al
MOV ID[3h], ah
JMP L4
L5:
L3:
MOV al, ID[0h]
MOV ah, ID[1h]
MOV al, ah
ADD al, 1
MOV ah, al
MOV ID[0h], al
MOV ID[1h], ah
L6:
MOV al, ID[3h]
CMP al, 10
JAE L7
MOV ID[3h], al
MOV dl, '-'
MOV ah, 02h
INT 21h
MOV al, ID[0h]
MOV ah, ID[3h]
MOV al, ah
ADD al, 1
MOV ah, al
MOV ID[0h], al
MOV ID[3h], ah
JMP L6
L7:
MOV dl, '!'
MOV ah, 02h
INT 21h
JMP L1
L2:
MOV ah, 4ch
INT 21h
end start
