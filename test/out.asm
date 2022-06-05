[bits 64]
global _start

section .data
dummy	db 0

section .bss

section .code
_start:
main:
	push rbp
	mov rbp, rsp
	add rsp, 128
.L1:
	; load int
	mov rcx, 0
	; copy
	mov QWORD [rbp-8], rcx
	; load int
	mov rcx, 4
	; copy
	mov QWORD [rbp-16], rcx
	; load int
	mov rcx, 3
	; load ident
	mov rdx, QWORD [rbp-16]
	; add
	mov rdi, rcx
	add rdi, rdx
	; copy
	mov QWORD [rbp-8], rdi
	; load ident
	mov rdi, QWORD [rbp-8]
	; load ident
	mov rdx, QWORD [rbp-16]
	; add
	mov rcx, rdi
	add rcx, rdx
	; return
	mov rax, rcx
.L0:
	sub rsp, 128
	pop rbp
	ret
