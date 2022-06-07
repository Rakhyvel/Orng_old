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
	mov QWORD [rbp-8], 0
	; load int
	mov QWORD [rbp-16], 0
;0	phi QWORD [rbp-16]
;0	phi QWORD [rbp-8]
	jmp .L2
.L2:
	; load int
	mov rcx, 100
	; lt
	cmp QWORD [rbp-16], rcx
	setl dl
	cmp dl, 0
	je .L13
	jmp .L3
.L3:
	; load int
	mov QWORD [rbp-24], 0
;0	phi QWORD [rbp-24]
	jmp .L4
.L4:
	; load int
	mov rdx, 100
	; lt
	cmp QWORD [rbp-24], rdx
	setl cl
	cmp cl, 0
	je .L12
	jmp .L5
.L5:
	; load int
	mov QWORD [rbp-32], 0
;0	phi QWORD [rbp-32]
	jmp .L6
.L6:
	; load int
	mov rcx, 100
	; lt
	cmp QWORD [rbp-32], rcx
	setl dl
	cmp dl, 0
	je .L11
	jmp .L7
.L7:
	; load int
	mov QWORD [rbp-40], 0
;0	phi QWORD [rbp-40]
	jmp .L8
.L8:
	; load int
	mov rdx, 100
	; lt
	cmp QWORD [rbp-40], rdx
	setl cl
	cmp cl, 0
	je .L10
	jmp .L9
.L9:
	; add
	mov rcx, QWORD [rbp-8]
	add rcx, QWORD [rbp-16]
	; add
	mov rdx, rcx
	add rdx, QWORD [rbp-24]
	; add
	mov rcx, rdx
	add rcx, QWORD [rbp-32]
	; add
	mov QWORD [rbp-8], rcx
	mov rbx, [rbp-40]
	add [rbp-8], rbx
	; load int
	mov rdx, 1
	; add
	add QWORD [rbp-40], rdx
;1	phi QWORD [rbp-40]
;1	phi QWORD [rbp-8]
	jmp .L8
.L10:
	; load int
	mov rcx, 1
	; add
	add QWORD [rbp-32], rcx
;1	phi QWORD [rbp-32]
	jmp .L6
.L11:
	; load int
	mov rdx, 1
	; add
	add QWORD [rbp-24], rdx
;1	phi QWORD [rbp-24]
	jmp .L4
.L12:
	; load int
	mov rcx, 1
	; add
	add QWORD [rbp-16], rcx
;1	phi QWORD [rbp-16]
	jmp .L2
.L13:
	; return
	mov rax, QWORD [rbp-8]
	jmp .L0
.L0:
	sub rsp, 128
	pop rbp
	ret
