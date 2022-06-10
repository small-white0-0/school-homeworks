assume cs:code,ss:stacks,ds:data

data segment
    A       db 12
    B       db 5
    product db 0
    source  db '20210428', 13,10,'$'
    key1    db 5,0,6,2,3,1,4,6
    key2    db 5,2,6,-2,3,-1,4,6
data ends

stacks segment
           db 16 dup(0)
stacks ends

code segment
    start: 
           mov  ax,data
           mov  ds,ax
           mov  ax,stacks
           mov  ss,ax

    ; 乘法实现 AxB
           mov  al,A
           mov  ah,al
           mov  cx,0
           mov  cl,B
    loop1: 
           add  al,ah
           loop loop1
           mov  product,al
        
    ; 字符串加密解密1，由于异或可逆，故用一个函数实现即可
           call L2               ;加密
           lea  dx,source
           call output

           call L2               ;解密
           lea  dx,source
           call output
    
    ; 字符串加密解密2，由于移位不能用重复操作进行，故用两个函数分别实现加密和解密
           call L3
           lea  dx,source
           call output

           call L4
           lea  dx,source
           call output

           mov  ax,4c00h
           int  21h
    ;后面是实现的函数部分
    L2:    
           push di
           push cx
           push ax

           mov  di,0
           mov  cl,8

    L2_1:  
           mov  al,source[di]
           mov  ah,key1[di]
           xor  al,ah
           mov  source[di],al
           inc  di
           loop L2_1

           pop  ax
           pop  cx
           pop  di
           ret
    L3:    
           push di
           push cx
           push ax

           mov  di,0
           mov  cl,8
    L3_1:  
           mov  al,source[di]
           mov  ah,key2[di]
           cmp  ah,0
           jge  L3_R
           jnge L3_L
    L3_R:  
           push cx
           mov  cl,ah
           ror  al,cl
           pop  cx
           jmp  L3_c
    L3_L:  
           push cx
           
           mov  cx,0
           sub  cl,ah
           rol  al,cl
           pop  cx
           jmp  L3_c
    L3_c:  
           mov  source[di],al
           inc  di
           loop L3_1
           
           pop  ax
           pop  cx
           pop  di
           ret

    L4:    
           push di
           push cx
           push ax

           mov  di,0
           mov  cl,8
    L4_1:  
           mov  al,source[di]
           mov  ah,key2[di]
           cmp  ah,0
           jge  L4_L
           jnge L4_R
    L4_L:  
           push cx
           mov  cl,ah
           rol  al,cl
           pop  cx
           jmp  L4_c
    L4_R:  
           push cx
           mov  cx,0
           sub  cl,ah
           ror  al,cl
           pop  cx
           jmp  L4_c
    L4_c:  
           mov  source[di],al
           inc  di
           loop L4_1
           
           pop  ax
           pop  cx
           pop  di
           ret
    output:
           push ax
           mov  ax,0900h
           int  21h
           pop  ax
           ret
code ends
end start