[bits 64]
global _start

section .data
	dummy	db 0
	$LCR64_0	dq 8.400000
	$LCR64_1	dq 3.500000


section .code
_start:
main:
	push rbp
	mov rbp, rsp
	add rsp, 128
.L1:
	; load real
	movsd xmm0, [$LCR64_0]
	; copy :)
	movsd [rbp-8], xmm0
	; load real
	movsd xmm0, [$LCR64_1]
	; copy :)
	movsd [rbp-16], xmm0
	; add
	movsd xmm0, [rbp-8]
	addsd xmm0, [rbp-16]
	; convert
	cvttsd2si rbx, xmm0
	; return
	mov rax, rbx
	jmp .L0
.L0:
	sub rsp, 128
	pop rbp
	ret
