.model small
.data
ID db 100 DUP(0)
.code
start:
MOV ax, @data
MOV ds, ax
MOV al, 1
MOV ah, 'c'
MOV bl, 1
MOV ID[1h], al
MOV ID[2h], ah
MOV al, ID[1h]
ADD al, 48
MOV dl, al
MOV ah, 02h
INT 21h
SUB al, 48
MOV ID[1h], al
MOV al, ID[2h]
MOV dl, al
MOV ah, 02h
INT 21h
MOV ID[2h], al
MOV dl, bl
MOV ah, 02h
INT 21h
MOV dl, 'a'
MOV ah, 02h
INT 21h
MOV dl, 1
MOV ah, 02h
INT 21h
MOV ah, 4ch
INT 21h
end start
