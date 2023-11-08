	.file	"pipe.c"
	.option pic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata
	.align	3
.LC2:
	.string	"Time elapsed for context switch: %.10f seconds\n"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-112
	sd	ra,104(sp)
	sd	s0,96(sp)
	addi	s0,sp,112
	addi	a5,s0,-64
	mv	a0,a5
	call	pipe@plt
	call	fork@plt
	mv	a5,a0
	bne	a5,zero,.L2
	sw	zero,-52(s0)
	j	.L3
.L4:
	lw	a5,-64(s0)
	addi	a4,s0,-65
	li	a2,1
	mv	a1,a4
	mv	a0,a5
	call	read@plt
	lw	a5,-60(s0)
	addi	a4,s0,-65
	li	a2,1
	mv	a1,a4
	mv	a0,a5
	call	write@plt
.L3:
	lw	a5,-52(s0)
	sext.w	a4,a5
	li	a5,999
	ble	a4,a5,.L4
	j	.L5
.L2:
	li	a5,120
	sb	a5,-105(s0)
	addi	a5,s0,-88
	li	a1,0
	mv	a0,a5
	call	gettimeofday@plt
	sw	zero,-20(s0)
	j	.L6
.L7:
	lw	a5,-60(s0)
	addi	a4,s0,-105
	li	a2,1
	mv	a1,a4
	mv	a0,a5
	call	write@plt
	lw	a5,-64(s0)
	addi	a4,s0,-105
	li	a2,1
	mv	a1,a4
	mv	a0,a5
	call	read@plt
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L6:
	lw	a5,-20(s0)
	sext.w	a4,a5
	li	a5,999
	ble	a4,a5,.L7
	addi	a5,s0,-104
	li	a1,0
	mv	a0,a5
	call	gettimeofday@plt
	ld	a4,-104(s0)
	ld	a5,-88(s0)
	sub	a5,a4,a5
	sd	a5,-32(s0)
	ld	a4,-96(s0)
	ld	a5,-80(s0)
	sub	a5,a4,a5
	sd	a5,-40(s0)
	ld	a5,-32(s0)
	fcvt.d.l	fa4,a5
	ld	a5,-40(s0)
	fcvt.d.l	fa3,a5
	lla	a5,.LC0
	fld	fa5,0(a5)
	fmul.d	fa5,fa3,fa5
	fadd.d	fa5,fa4,fa5
	fsd	fa5,-48(s0)
	fld	fa4,-48(s0)
	lla	a5,.LC1
	fld	fa5,0(a5)
	fdiv.d	fa5,fa4,fa5
	fmv.x.d	a1,fa5
	lla	a0,.LC2
	call	printf@plt
.L5:
	li	a5,0
	mv	a0,a5
	ld	ra,104(sp)
	ld	s0,96(sp)
	addi	sp,sp,112
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	3
.LC0:
	.word	-1598689907
	.word	1051772663
	.align	3
.LC1:
	.word	0
	.word	1084178432
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
