assume cs:code,ss:stack,es:display

display segment
    output  dw 16 dup(0)
display ends
    
stack segment
          db 32 dup(0)
stack ends

code segment
    start:
          mov  ax,stack
          mov  ss,ax

          mov  di,0
          mov  cx,0
    loop1:
          mov  ah,01h
          int  21h
          inc  cx               ;记录输入的字符数

          mov  ah,0ah           ;加入颜色信息
          mov  bl,al            ;根据第7位判断是否字母
          and  bl,40h
          cmp  bl,0
          jne  L1               ;调用L1, 将字母大小写转换
          je   L2               ;是数字，结束循环，准备输出
    L1:   
          xor  al,20h           ;利用异或，让第6位取反，进行字母大小写转换
          push ax               ;用栈实现输出倒序
          jmp  loop1
    L2:   
          push ax
        
          mov  ax,0b810h
          mov  es,ax
          
          mov  di,0
    loop2:
          pop  ax
          mov  output[di],ax

          inc  di
          inc  di
          loop loop2


          mov  ax,4c00h
          int  21h
              

code ends

end start