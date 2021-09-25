## すぐ忘れるのでassemblyのメモ

- jmpのオペランドにアドレスを入れたい場合  
 `mov rax, addr`  
 `jmp rax`  
 でアドレスにジャンプできる
 e.g.) say_hello()のアドレスが0x402280だった場合  
 `mov rax, 0x402280`  
 `jmp rax`
 で`hello`が出力されるよ  

- 逆アセンブルmemo1  
 実行形式(rasm)を`objdump -d rasm`した時、 
 1142の時に使用されるripの値は、0x1142  
 なので、edxに代入される値は、0x401c(=0x1142 + 0x2eda)  
 0000000000001134 <func>:  
    1134:	f3 0f 1e fa          	endbr64  
    1138:	55                   	push   %rbp
    1139:	48 89 e5             	mov    %rsp,%rbp  
    113c:	8b 15 da 2e 00 00    	mov    0x2eda(%rip),%edx        # 401c <extvalue>  
    1142:	8b 05 f4 2e 00 00    	mov    0x2ef4(%rip),%eax        # 403c <extbssvalue>  
    1148:	01 c2                	add    %eax,%edx  
    114a:	8b 05 c4 2e 00 00    	mov    0x2ec4(%rip),%eax        # 4014 <value>  
    1150:	01 c2                	add    %eax,%edx  
    1152:	8b 05 d0 2e 00 00    	mov    0x2ed0(%rip),%eax        # 4028 <bssvalue>  
    1158:	01 d0                	add    %edx,%eax  
    115a:	5d                   	pop    %rbp  
    115b:	c3                   	retq  
 0x401cは、実行形式(rasm)を`readelf -S -r -s rasm`した時の、  
 シンボルテーブルにあるextvalueの値と一致する  
 