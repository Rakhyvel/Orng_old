[bits 64]
global _start
extern printf

section .data
msg			db "Hello World! %d %d %d", 13, 10, 0
msg.len		equ $ - msg
x			dq 15

section .code
_start:
	mov rbx, 0
.loop:
	cmp rbx, 9
	jg .end
	mov r9, rbx
	mov r8, rbx
	mov rdx, rbx
	mov rcx, msg
	call printf
	add rsp, 24
	inc rbx
	jmp .loop
.end:
	mov rax, 0
	ret