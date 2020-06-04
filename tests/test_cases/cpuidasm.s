	.file	"cpuid.c"
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
	pushq	%rbx
	naclsspq	$24, %r15
	movl	$0, %eax
/APP
/ 7 "cpuid.c" 1
	cpuid
/ 0 "" 2
/NO_APP
	movl	%eax, -20(%rbp)
	movl	%ebx, -32(%rbp)
	movl	%ecx, -24(%rbp)
	movl	%edx, -28(%rbp)
	leal	-32(%rbp), %eax
	mov	%eax, %eax
	movl	%eax, %edi
	.cfi_offset 3, -24
	call	puts
	movl	$0, %eax
	naclaspq	$24, %r15
	popq	%rbx
	popq	%r11
	naclrestbp	%r11d, %r15
	popq	%r11
	nacljmp	%r11d,%r15
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
