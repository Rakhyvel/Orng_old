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
	mov QWORD [rbp-8], 0
	; load int
	mov QWORD [rbp-16], 0
	jmp .L2
.L2:
	; load int
	mov rbx, 10
	; lt
	cmp [rbp-16], rbx
	setl cl
	; branch
	cmp cl, 0
	je .L10
	jmp .L3
.L3:
	; load int
	mov rcx, 1
	; add
	mov rbx, rcx
	add rbx, [rbp-8]
	; copy :)
	mov [rbp-8], rbx
	; load int
	mov rbx, 8
	; lt
	cmp rbx, [rbp-16]
	setl cl
	; branch
	cmp cl, 0
	je .L6
	jmp .L4
.L4:
	; load int
	mov rcx, 16
	; return
	mov rax, rcx
	jmp .L0
.L6:
	jmp .L8
.L8:
	jmp .L9
.L9:
	; load int
	mov rcx, 1
	; add
	mov rbx, [rbp-16]
	add rbx, rcx
	; copy :)
	mov [rbp-16], rbx
	jmp .L2
.L10:
	; copy :)
	mov rbx, [rbp-8]
	mov [rbp-24], rbx
	jmp .L11
.L11:
	; return
	mov rax, QWORD [rbp-24]
	jmp .L0
.L0:
	sub rsp, 128
	pop rbp
	ret
