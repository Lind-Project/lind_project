	.file	"busywait.c"
	.text
	.section	.rodata
.LC0:
	.string	"Clocks per sec %d\n"
.LC1:
	.string	"Busy loop time %lld \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$10000, -36(%rbp)
	movq	$0, -32(%rbp)
	call	clock@PLT
	movq	%rax, -24(%rbp)
	jmp	.L2
.L3:
	addq	$1, -32(%rbp)
.L2:
	movl	-36(%rbp), %eax
	cltq
	imulq	$1000000, %rax, %rax
	cmpq	%rax, -32(%rbp)
	jl	.L3
	call	clock@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	subq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	$1000000, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Arch Linux 9.3.0-1) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
