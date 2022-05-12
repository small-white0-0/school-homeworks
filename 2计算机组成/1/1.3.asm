assume ds:data,cs:code

data segment

data ends

code segment

start:
    mov ax,data
    mov ds,ax

    ;测试零标志位
    mov ax,1
    sub ax,ax

    ;测试进位位
    ;这里注意结果不要让最高位（符号位）为1,会导致sf变为1,影响符号位测试代码的显示效果
    mov al,200
    mov ah,60
    add al,ah

    ;测试符号位
    mov ax,0
    mov dx,3
    sub ax,dx

    ;测试溢出位
    mov al,127
    add al,al

    mov ax,4c00h
    int 21h
code ends

end start