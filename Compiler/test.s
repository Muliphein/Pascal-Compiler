	.text
	.file	"test"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	2(%rsp), %rdx
	movq	%rsp, %rsi
	movl	$.L__unnamed_1, %edi
	xorl	%eax, %eax
	callq	scanf
	movzwl	(%rsp), %esi
	addw	2(%rsp), %si
	movw	%si, 4(%rsp)
	movl	$.L__unnamed_2, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"%hd%hd%*[^\n]"
	.size	.L__unnamed_1, 13

	.type	.L__unnamed_2,@object   # @1
.L__unnamed_2:
	.asciz	"%hd\n"
	.size	.L__unnamed_2, 5

	.section	".note.GNU-stack","",@progbits
