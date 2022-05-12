assume cs:code,ds:data
data segment
    aa dw 123AH
    x dw 100
    y dw 320
    z dw 200
    result dw 0
data ends

code segment
start:
    mov ax,data
    mov ds,ax
    mov ax,aa   ;将123AH储存在ax中

    ; 进行result=-x + （y-z）
    mov bx,0
    sub bx,x
    mov result,bx    ;得到-x
    mov bx,y
    sub bx,z    ;得到y-z
    add result,bx   ;得到 -x + （y-z)


    mov ax,4c00h
    int 21h
code ends
end start

