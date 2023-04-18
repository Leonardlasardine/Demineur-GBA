	.file	"main.c"
@ GNU C version 3.2.2 (arm-thumb-elf)
@	compiled by GNU C version 3.2 20020927 (prerelease).
@ options passed:  -fpreprocessed -mthumb-interwork -mlong-calls -O2 -Wall
@ -fverbose-asm
@ options enabled:  -fdefer-pop -fomit-frame-pointer
@ -foptimize-sibling-calls -fcse-follow-jumps -fcse-skip-blocks
@ -fexpensive-optimizations -fthread-jumps -fstrength-reduce -fpeephole
@ -fforce-mem -ffunction-cse -fkeep-static-consts -fcaller-saves
@ -freg-struct-return -fgcse -fgcse-lm -fgcse-sm -frerun-cse-after-loop
@ -frerun-loop-opt -fdelete-null-pointer-checks -fschedule-insns
@ -fschedule-insns2 -fsched-interblock -fsched-spec -fbranch-count-reg
@ -freorder-blocks -fcprop-registers -fcommon -fverbose-asm -fgnu-linker
@ -fregmove -foptimize-register-move -fargument-alias -fstrict-aliasing
@ -fmerge-constants -fident -fpeephole2 -fguess-branch-probability
@ -fmath-errno -ftrapping-math -mapcs -mapcs-frame -mapcs-32 -msoft-float
@ -mthumb-interwork -mlong-calls

	.global	__main
	.text
	.align	2
	.global	main
	.type	main,function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
	ldr	r3, .L36
	sub	fp, ip, #4
	sub	sp, sp, #8
	mov	r9, #0	@  downPressed
	mov	lr, pc
	bx	r3
	ldr	r3, .L36+4
	mov	lr, pc
	bx	r3
	mov	r2, #1024
	add	r2, r2, #3
	mov	r3, #67108864
	str	r2, [r3, #0]
	str	r9, [fp, #-48]	@  rightPressed,  aPressed
	strb	r9, [fp, #-41]
	strb	r9, [fp, #-42]
	ldr	r0, .L36+8
	mov	lr, pc
	bx	r0
	ldrb	r0, [fp, #-41]	@ zero_extendqisi2	@  posX
	ldrb	r1, [fp, #-42]	@ zero_extendqisi2	@  posY
	add	ip, r0, r0, asl #2	@  posX,  posX
	add	r2, r1, r1, asl #2	@  posY,  posY
	rsb	ip, ip, #150
	mov	r2, r2, lsr #2
	mov	ip, ip, asr #3
	add	r3, r1, r0	@  posY,  posX
	mov	r2, r2, asl #5
	add	r2, r2, ip, asl #10
	add	r3, r3, r3, asl #2
	add	r2, r2, r3, lsr #2
	mov	r2, r2, asl #16
	mov	r2, r2, lsr #16
	ldr	r3, .L36+12
	mov	lr, pc
	bx	r3
	ldr	r8, .L36+16
	ldr	r7, [fp, #-48]	@  posX,  aPressed
	mov	sl, r9	@  rightPressed,  downPressed
	mov	r6, r9	@  upPressed,  downPressed
	mov	r5, r9	@  leftPressed,  rightPressed
.L13:
	mov	r4, #0	@  posY
.L12:
	mov	r1, r4	@  posY
	mov	r0, r7	@  posX
	mov	lr, pc
	bx	r8
	add	r3, r4, #1	@  posY
	and	r4, r3, #255	@  posY
	cmp	r4, #15	@  posY
	bls	.L12
	add	r3, r7, #1	@  posX
	and	r7, r3, #255	@  posX
	cmp	r7, #15	@  posX
	bls	.L13
	sub	r8, fp, #41	@  posY
	sub	r7, fp, #42
.L32:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #64
	mov	r4, r3, asr #6	@  posX
	cmp	r4, #0	@  posX
	movne	r6, #1	@  upPressed
	bne	.L18
	cmp	r6, #0	@  upPressed
	beq	.L18
	mov	r0, r4	@  posX
	mov	r1, r8	@  posY
	mov	r2, r7
	ldr	r3, .L36+20
	mov	lr, pc
	bx	r3
	mov	r6, r4	@  upPressed,  posX
.L18:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #128
	mov	r4, r3, asr #7	@  downPressed
	cmp	r4, #0	@  downPressed
	movne	r9, #1	@  downPressed
	bne	.L21
	cmp	r9, #0	@  downPressed
	beq	.L21
	mov	r0, #1
	mov	r1, r8	@  posY
	mov	r2, r7
	ldr	r3, .L36+20
	mov	lr, pc
	bx	r3
	mov	r9, r4	@  downPressed,  downPressed
.L21:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #32
	mov	r4, r3, asr #5	@  leftPressed
	cmp	r4, #0	@  leftPressed
	movne	r5, #1	@  leftPressed
	bne	.L24
	cmp	r5, #0	@  leftPressed
	beq	.L24
	mov	r0, #2
	mov	r1, r8	@  posY
	mov	r2, r7
	ldr	r3, .L36+20
	mov	lr, pc
	bx	r3
	mov	r5, r4	@  leftPressed,  leftPressed
.L24:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #16
	mov	r4, r3, asr #4	@  rightPressed
	cmp	r4, #0	@  rightPressed
	movne	sl, #1	@  rightPressed
	bne	.L27
	cmp	sl, #0	@  rightPressed
	beq	.L27
	mov	r0, #3
	mov	r1, r8	@  posY
	mov	r2, r7
	ldr	r3, .L36+20
	mov	lr, pc
	bx	r3
	mov	sl, r4	@  rightPressed,  rightPressed
.L27:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	ands	r4, r3, #1	@  aPressed
	movne	r3, #1
	strne	r3, [fp, #-48]	@  aPressed
	bne	.L32
	ldr	r3, [fp, #-48]	@  aPressed
	cmp	r3, #0
	beq	.L32
	ldrb	r0, [fp, #-41]	@ zero_extendqisi2	@  posX
	ldrb	r1, [fp, #-42]	@ zero_extendqisi2	@  posY
	ldr	r3, .L36+16
	mov	lr, pc
	bx	r3
	str	r4, [fp, #-48]	@  aPressed,  aPressed
	b	.L32
.L37:
	.align	2
.L36:
	.word	__main
	.word	ham_Init
	.word	grid
	.word	cursor
	.word	drawCase
	.word	move
.Lfe1:
	.size	main,.Lfe1-main
	.align	2
	.global	move
	.type	move,function
move:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	ldrb	r3, [r1, #0]	@ zero_extendqisi2	@  sens, * x
	mov	r4, r0	@  sens
	mov	r5, r1	@  x
	mov	r6, r2	@  y
	ldrb	r1, [r2, #0]	@ zero_extendqisi2	@  x, * y
	mov	r0, r3	@  sens
	sub	fp, ip, #4
	mov	r2, #0
	ldr	r3, .L48
	mov	lr, pc
	bx	r3
	cmp	r4, #3	@  sens
	ldrls	pc, [pc, r4, asl #2]	@  sens
	b	.L39
	.p2align 2
.L44:
	.word	.L40
	.word	.L41
	.word	.L42
	.word	.L43
.L40:
	ldrb	r3, [r6, #0]	@ * y
	sub	r3, r3, #1
.L47:
	strb	r3, [r6, #0]	@ * y
.L39:
	ldrb	r0, [r5, #0]	@ zero_extendqisi2	@  sens, * x
	ldrb	r1, [r6, #0]	@ zero_extendqisi2	@  x, * y
	add	ip, r0, r0, asl #2	@  sens,  sens
	add	r2, r1, r1, asl #2	@  x,  x
	rsb	ip, ip, #150
	mov	r2, r2, lsr #2
	mov	ip, ip, asr #3
	add	r3, r1, r0	@  x,  sens
	mov	r2, r2, asl #5
	add	r2, r2, ip, asl #10
	add	r3, r3, r3, asl #2
	add	r2, r2, r3, lsr #2
	mov	r2, r2, asl #16
	mov	r2, r2, lsr #16	@  y
	ldr	r3, .L48
	mov	lr, pc
	bx	r3
	ldmea	fp, {r4, r5, r6, fp, sp, lr}
	bx	lr
.L41:
	ldrb	r3, [r6, #0]	@ * y
	add	r3, r3, #1
	b	.L47
.L42:
	ldrb	r3, [r5, #0]	@ * x
	sub	r3, r3, #1
.L46:
	strb	r3, [r5, #0]	@ * x
	b	.L39
.L43:
	ldrb	r3, [r5, #0]	@ * x
	add	r3, r3, #1
	b	.L46
.L49:
	.align	2
.L48:
	.word	cursor
.Lfe2:
	.size	move,.Lfe2-move
	.ident	"GCC: (GNU) 3.2.2"
