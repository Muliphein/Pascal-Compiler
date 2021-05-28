	.text
	.file	"module-test"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entrypoint
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$.Lformat, %edi
	movl	$.Lworld, %esi
	xorl	%eax, %eax
	callq	printf
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.Lformat,@object        # @format
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lformat:
	.asciz	"Hello, %s.\n"
	.size	.Lformat, 12

	.type	.Lworld,@object         # @world
.Lworld:
	.asciz	"World"
	.size	.Lworld, 6

	.section	".note.GNU-stack","",@progbits
