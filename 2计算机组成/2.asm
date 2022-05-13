assume ds:data,cs:code
data segment
    AS db 5 dup(?)
    AD db 5 dup(?)
    MIN db 0
data ends

code segment

start:
    mov ax,data
    mov ds,ax

;; 设置si,di的值
    mov si,offset AS
    mov di,offset AD

;; 赋予AS[1,2,3,4,5]初值
    mov cx,lengthof AS
    mov bx,0    ; bx做下标
    mov dl,1
loop1:
    mov [si][bx],dl
    inc bx
    inc dl
    loop loop1


;; 复制AS到AD
    mov cx,lengthof AS
    mov bx,0
loop2:
    mov al,[si][bx]
    mov [di][bx],al

    inc bx
    loop loop2

;; 找出最小值
    mov cx,lengthof AS
    mov bx,0
    mov al,[si][bx]
    mov MIN,al      ;首先把第一个作为最小的

    dec cx
    inc bx
loop3:
    mov al,[si][bx]
    cmp al,MIN
    jnb po        ;如果AD[bx]不小于MIN,则跳过
    
    mov MIN,al

po:
    inc bx
    loop loop3

;; 左移AS元素
    mov cx,lengthof AS
    mov bx,0
    dec cx          ;只循环前N-1个
    mov al,AS[0]    ;保存最左边的元素
    
    ; 让si从AS的第二个开始的地址,di则是从AS的第一开始的地址
    mov di,si
    inc si
loop4:
    mov ah,[si][bx]
    mov [di][bx],ah
    inc bx
    loop loop4
    
    mov [di][bx],al ;将第一个放到最右边

    mov ax,4c00h
    int 21h

code ends

end start