	.file	"fork.c"
	.section	.rodata
.LC0:
	.string	"%#x\n"
.LC1:
	.string	"forking 1"
.LC2:
	.string	"forking 2"
.LC3:
	.string	"forking 3"
.LC4:
	.string	"forking 4"
.LC5:
	.string	"forking 5"
.LC6:
	.string	"forking 6"
.LC7:
	.string	"forking 7"
.LC8:
	.string	"forking 8"
.LC9:
	.string	"forking 9"
.LC10:
	.string	"forking 10"
.LC11:
	.string	"fork() failed"
.LC12:
	.string	"child succeeded"
.LC13:
	.string	"parent waiting"
	.align 8
.LC14:
	.string	"parent %d succeeded after waiting on %d\n"
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
	naclsspq	$16, %r15
	mov	$0x1000650, %r10
	jmp	*%r10
	call	getpid
	movl	$.LC0, %edx
	mov	%edx, %edx
	; movl	%eax, %esi
	leaq	(%rip), %rsi
	movl	%edx, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %edi
	call	puts
	movl	$.LC2, %edi
	call	puts
	movl	$.LC3, %edi
	call	puts
	movl	$.LC4, %edi
	call	puts
	movl	$.LC5, %edi
	call	puts
	movl	$.LC6, %edi
	call	puts
	movl	$.LC7, %edi
	call	puts
	movl	$.LC8, %edi
	call	puts
	movl	$.LC9, %edi
	call	puts
	movl	$.LC10, %edi
	call	puts
	movl	$0, %edi
	leaq	(%rip), %r12
	call	fflush
	call	fork
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$-1, %eax
	je	.L3
	testl	%eax, %eax
	je	.L4
	jmp	.L6
	.align 32
.L3:
	movl	$.LC11, %edi
	call	perror
	movl	$0, %edi
	call	fflush
	movl	$1, %edi
	call	exit
	.align 32
.L10:
	jmp	*%r12
.L4:
	call	getpid
	movl	$.LC0, %edx
	mov	%edx, %edx
	; movl	%eax, %esi
	leaq	(%rip), %rsi
	movl	%edx, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC12, %edi
	call	puts
	call	getpid
	movl	$.LC0, %edx
	mov	%edx, %edx
	movl	%eax, %esi
	movl	%edx, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	fflush
	movl	$0, %edi
	call	exit
	.align 32
.L6:
	movl	$.LC13, %edi
	call	puts
	movl	$0, %edi
	call	fflush
	movl	$0, %eax
	leal	-8(%rbp), %eax
	movl	%eax, %edi
	call	wait
	call	getpid
	movl	$.LC14, %edx
	mov	%edx, %ecx
	movl	-4(%rbp), %edx
	movl	%eax, %esi
	movl	%ecx, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	fflush
	movl	$0, %eax
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
