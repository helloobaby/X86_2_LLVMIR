	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 1
	.intel_syntax noprefix
	.file	"main.c"
	.def	 _root;
	.scl	2;
	.type	32;
	.endef
	.globl	_root                           # -- Begin function root
	.p2align	4, 0x90
_root:                                  # @root
# %bb.0:                                # %entry
	mov	eax, offset _eax
	mov	dword ptr [_ebx], 32
	mov	dword ptr [_eax], 0
	#APP

	mov	eax, dword ptr [@eax]

	#NO_APP
	ret
                                        # -- End function
