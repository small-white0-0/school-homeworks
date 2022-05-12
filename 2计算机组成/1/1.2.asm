assume ds:data,cs:code
data segment
    a db 0AAH
    b db 0BBH
    x db 90
    y db 90
    z db -90
    result db 0
data ends

code segment

start:
    mov ax,data
    mov ds,ax
    ;交换变量的值
    mov al,a
    mov bl,b
    mov a,bl
    mov b,al
    ;计算result=-x +（y-z）
    mov al,0
    sub al,x
    mov ah,y
    sub ah,z
    add al,ah
    mov result,al

    mov ax,4c00h
    int 21h
code ends

end start
