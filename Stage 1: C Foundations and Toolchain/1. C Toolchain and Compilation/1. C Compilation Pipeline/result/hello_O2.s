	.text
	.file	"hello.c"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$7627112, 3(%rsp)               # imm = 0x746168
	movl	$1752394561, (%rsp)             # imm = 0x68736B41
	leaq	.L.str(%rip), %rdi
	movq	%rsp, %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__const.main.name,@object     # @__const.main.name
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__const.main.name:
	.asciz	"Akshat"
	.size	.L__const.main.name, 7

	.type	.L.str,@object                  # @.str
.L.str:
	.asciz	"Hello %s\n"
	.size	.L.str, 10

	.ident	"Ubuntu clang version 18.1.3 (1ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
