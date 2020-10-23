	.file	"busywait.c"
	.section	.rodata
.LC0:
	.string	"Clocks per sec %d\n"
.LC1:
	.string	"Busy loop time %lld \n"
	.text
	.align 32
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	naclsspq	$48, %r15
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	$10000, -20(%rbp)
	movq	$0, -16(%rbp)
	call	clock
	movl	%eax, -28(%rbp)
	jmp	.L2
	.align 32
.L3:
	addq	$1, -16(%rbp)
	.align 32
.L2:
	movl	-20(%rbp), %eax
	imull	$1000000, %eax, %eax
	cltq
	cmpq	-16(%rbp), %rax
	jg	.L3
	call	clock
	movl	%eax, -24(%rbp)
	movl	-28(%rbp), %eax
	movl	-24(%rbp), %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	cltq
	movq	%rax, -8(%rbp)
	movl	$.LC0, %eax
	mov	%eax, %eax
	movl	$1000000, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %eax
	mov	%eax, %edx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	%edx, %edi
	movl	$0, %eax
	call	printf
	movq	%rbp, %rsp
	popq	%r11
	naclrestbp	%r11d, %r15
	popq	%r11
	nacljmp	%r11d,%r15
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
