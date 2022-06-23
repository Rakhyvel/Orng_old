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
	mov rbx, 0
	; copy :)
	mov [rbp-8], rbx
	; load int
	mov rbx, 0
	; copy :)
	mov [rbp-16], rbx
	jmp .L2
.L2:
	; load int
	mov rbx, 10
	; lt
	cmp [rbp-16], rbx
	setl cl
	; branch
	cmp cl, 0
	je .L9
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
	mov rbx, 0
	; lt
	cmp rbx, [rbp-8]
	setl cl
	; branch
	cmp cl, 0
	je .L5
	jmp .L4
.L4:
	; load int
	mov rcx, 5
	; copy :)
	mov [rbp-24], rcx
	jmp .L0
.L5:
	jmp .L6
.L6:
	jmp .L7
.L7:
	; load int
	mov rcx, 4
	; copy :)
	mov [rbp-8], rcx
	jmp .L8
.L8:
	; load int
	mov rbx, 1
	; add
	mov rcx, [rbp-16]
	add rcx, rbx
	; copy :)
	mov [rbp-16], rcx
	jmp .L2
.L9:
	; copy :)
	mov rbx, [rbp-8]
	mov [rbp-32], rbx
	jmp .L0
.L0:
	mov rax, QWORD [rbp-32]
	sub rsp, 128
	pop rbp
	ret
