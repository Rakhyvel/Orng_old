[bits 64]
global _start

section .data
	dummy	db 0


section .code
_start:
main:
	push rbp
	mov rbp, rsp
	add rsp, 128
.L1:
	; load int
	mov BYTE [rbp-1], 0
	; load int
	mov QWORD [rbp-16], 0
	jmp .L2
.L2:
	; load int
	mov rbx, 9
	; lt
	cmp [rbp-16], rbx
	setl cl
	; branch
	cmp cl, 0
	je .L11
	jmp .L3
.L3:
	; branch
	cmp BYTE [rbp-1], 0
	je .L9
	jmp .L4
.L4:
	; load int
	mov BYTE [rbp-1], 0
	jmp .L6
.L6:
	; copy :)
	mov [rbp-17], cl
	jmp .L7
.L7:
	jmp .L8
.L8:
	; load int
	mov rcx, 1
	; add
	mov rbx, [rbp-16]
	add rbx, rcx
	; copy :)
	mov [rbp-16], rbx
	jmp .L2
.L9:
	; load int
	mov BYTE [rbp-1], 1
	jmp .L10
.L10:
	jmp .L6
.L11:
	; branch
	cmp BYTE [rbp-1], 0
	je .L13
	jmp .L12
.L12:
	; load int
	mov QWORD [rbp-32], 4
	; return
	mov rax, QWORD [rbp-32]
	jmp .L0
.L13:
	; load int
	mov QWORD [rbp-40], 5
	; return
	mov rax, QWORD [rbp-40]
	jmp .L0
.L0:
	sub rsp, 128
	pop rbp
	ret
