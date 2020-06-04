	.file	"fork.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"forking"
.LC2:
	.string	"fork() failed"
	.align 8
.LC3:
	.string	"child %d succeeded after waiting on %d\n"
	.align 8
.LC4:
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
	call	getpid
	movl	$.LC0, %edx
	mov	%edx, %edx
	movl	%eax, %esi
	movl	%edx, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %edi
	call	puts
	movl	$0, %edi
	call	fflush
	call	fork
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$-1, %eax
	je	.L3
	testl	%eax, %eax
	je	.L4
	jmp	.L9
	.align 32
.L3:
	movl	$.LC2, %edi
	call	perror
	movl	$0, %edi
	call	fflush
	movl	$1, %edi
	call	exit
	.align 32
.L4:
	call	fork
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$-1, %eax
	je	.L6
	testl	%eax, %eax
	je	.L7
	jmp	.L10
	.align 32
.L6:
	movl	$.LC2, %edi
	call	perror
	movl	$0, %edi
	call	fflush
	movl	$1, %edi
	call	exit
	.align 32
.L7:
	movl	$16, %edx
	movl	$c2.3376, %esi
	movl	$1, %edi
	call	write
	movl	$0, %edi
	call	exit
	.align 32
.L10:
	movl	$14, %edx
	movl	$c1.3375, %esi
	movl	$1, %edi
	call	write
	leal	-8(%rbp), %ecx
	movl	-4(%rbp), %eax
	movl	$0, %edx
	movl	%ecx, %esi
	movl	%eax, %edi
	call	waitpid
	call	getpid
	movl	$.LC3, %edx
	mov	%edx, %ecx
	movl	-4(%rbp), %edx
	movl	%eax, %esi
	movl	%ecx, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	fflush
	movl	$16, %edx
	movl	$c2.3376, %esi
	movl	$1, %edi
	call	write
	movl	$0, %edi
	call	exit
	.align 32
.L9:
	movl	$15, %edx
	movl	$p1.3377, %esi
	movl	$1, %edi
	call	write
	movl	$0, %eax
	leal	-8(%rbp), %eax
	movl	%eax, %edi
	call	wait
	call	getpid
	movl	$.LC4, %edx
	mov	%edx, %ecx
	movl	-4(%rbp), %edx
	movl	%eax, %esi
	movl	%ecx, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	fflush
	movl	$17, %edx
	movl	$p2.3378, %esi
	movl	$1, %edi
	call	write
	movl	$0, %eax
	movq	%rbp, %rsp
	popq	%r11
	naclrestbp	%r11d, %r15
	popq	%r11
	nacljmp	%r11d,%r15
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 16
	.type	c2.3376, @object
	.size	c2.3376, 17
c2.3376:
	.string	"child succeeded\n"
	.type	c1.3375, @object
	.size	c1.3375, 15
c1.3375:
	.string	"child waiting\n"
	.align 16
	.type	p1.3377, @object
	.size	p1.3377, 16
p1.3377:
	.string	"parent waiting\n"
	.align 16
	.type	p2.3378, @object
	.size	p2.3378, 18
p2.3378:
	.string	"parent succeeded\n"
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
