.model small
.data
ID db 100 DUP(0)
.code
start:
MOV ax, @data
MOV ds, ax
MOV ah, 01h
INT 21h
SUB al, 48
MOV ah, al
MOV ID[1h], al
MOV ID[2h], ah
MOV al, ID[2h]
ADD al, 48
MOV dl, al
MOV ah, 02h
INT 21h
SUB al, 48
MOV ah, 4ch
INT 21h
end start
ID:0 ans TYPE:0 ADDR:0x0
ID:1 i TYPE:0 ADDR:0x1
ID:2 a TYPE:0 ADDR:0x2
