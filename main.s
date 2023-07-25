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
	ldr	r3, .L22
	sub	fp, ip, #4
	sub	sp, sp, #8
	sub	r9, fp, #41
	mov	lr, pc
	bx	r3
	mov	r2, #0
	str	r2, [fp, #-48]	@  downPressed
	ldr	r3, .L22+4
	mov	lr, pc
	bx	r3
	mov	r2, #1024
	ldr	sl, [fp, #-48]	@  rightPressed,  downPressed
	add	r2, r2, #3
	mov	r3, #67108864
	mov	r1, #256
	str	r2, [r3, #0]
	add	r1, r1, #67108866
	mov	r3, #128	@ movhi
	strb	sl, [fp, #-41]	@  aPressed
	strb	sl, [fp, #-42]	@  aPressed
	strh	r3, [r1, #0]	@ movhi 
	ldrb	r0, [fp, #-41]	@ zero_extendqisi2	@  timers
	ldrb	r1, [fp, #-42]	@ zero_extendqisi2
	add	ip, r0, r0, asl #2	@  timers,  timers
	add	r2, r1, r1, asl #2
	rsb	ip, ip, #150
	mov	r2, r2, lsr #2
	mov	ip, ip, asr #3
	add	r3, r1, r0	@  timers
	mov	r2, r2, asl #5
	add	r2, r2, ip, asl #10
	add	r3, r3, r3, asl #2
	add	r2, r2, r3, lsr #2
	mov	r2, r2, asl #16
	mov	r2, r2, lsr #16
	ldr	r3, .L22+8
	mov	lr, pc
	bx	r3
	ldr	r5, [fp, #-48]	@  upPressed,  downPressed
	mov	r7, sl	@  aPressed,  rightPressed
	mov	r6, sl	@  leftPressed,  rightPressed
	sub	r8, fp, #42
.L21:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #64
	mov	r4, r3, asr #6	@  timers
	cmp	r4, #0	@  timers
	movne	r5, #1	@  upPressed
	bne	.L6
	cmp	r5, #0	@  upPressed
	beq	.L6
	mov	r0, r4	@  timers
	mov	r1, r9
	mov	r2, r8
	ldr	r3, .L22+12
	mov	lr, pc
	bx	r3
	mov	r2, #67108864
	add	r2, r2, #256
	mvn	r3, #66060288
	ldrh	r1, [r2, #0]	@ movhi
	sub	r3, r3, #16128
	sub	r3, r3, #2
	umull	r2, r0, r3, r1
	mov	r0, r0, asl #10
	mov	r0, r0, lsr #16	@  timers
	ldr	r3, .L22+16
	mov	r5, r4	@  upPressed,  timers
	mov	lr, pc
	bx	r3
.L6:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #128
	mov	r4, r3, asr #7	@  downPressed
	cmp	r4, #0	@  downPressed
	movne	r3, #1
	strne	r3, [fp, #-48]	@  downPressed
	bne	.L9
	ldr	r2, [fp, #-48]	@  downPressed
	cmp	r2, #0
	beq	.L9
	mov	r0, #1
	mov	r1, r9
	mov	r2, r8
	ldr	r3, .L22+12
	mov	lr, pc
	bx	r3
	str	r4, [fp, #-48]	@  downPressed,  downPressed
.L9:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #32
	mov	r4, r3, asr #5	@  leftPressed
	cmp	r4, #0	@  leftPressed
	movne	r6, #1	@  leftPressed
	bne	.L12
	cmp	r6, #0	@  leftPressed
	beq	.L12
	mov	r0, #2
	mov	r1, r9
	mov	r2, r8
	ldr	r3, .L22+12
	mov	lr, pc
	bx	r3
	mov	r6, r4	@  leftPressed,  leftPressed
.L12:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	and	r3, r3, #16
	mov	r4, r3, asr #4	@  rightPressed
	cmp	r4, #0	@  rightPressed
	movne	sl, #1	@  rightPressed
	bne	.L15
	cmp	sl, #0	@  rightPressed
	beq	.L15
	mov	r0, #3
	mov	r1, r9
	mov	r2, r8
	ldr	r3, .L22+12
	mov	lr, pc
	bx	r3
	mov	sl, r4	@  rightPressed,  rightPressed
.L15:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	ands	r4, r3, #1	@  aPressed
	movne	r7, #1	@  aPressed
	bne	.L18
	cmp	r7, #0	@  aPressed
	beq	.L18
	ldrb	r0, [fp, #-41]	@ zero_extendqisi2	@  timers
	ldrb	r1, [fp, #-42]	@ zero_extendqisi2
	ldr	r3, .L22+20
	mov	lr, pc
	bx	r3
	mov	r7, r4	@  aPressed,  aPressed
.L18:
	mov	r2, #67108864
	add	r2, r2, #304
	ldrh	r3, [r2, #0]	@ movhi
	mvn	r3, r3
	tst	r3, #2
	beq	.L21
	ldr	r3, .L22+24
	mov	lr, pc
	bx	r3
	b	.L21
.L23:
	.align	2
.L22:
	.word	__main
	.word	ham_Init
	.word	cursor
	.word	move
	.word	grid
	.word	drawCase
	.word	reveal
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
	ldr	r3, .L34
	mov	lr, pc
	bx	r3
	cmp	r4, #3	@  sens
	ldrls	pc, [pc, r4, asl #2]	@  sens
	b	.L25
	.p2align 2
.L30:
	.word	.L26
	.word	.L27
	.word	.L28
	.word	.L29
.L26:
	ldrb	r3, [r6, #0]	@ * y
	sub	r3, r3, #1
.L33:
	strb	r3, [r6, #0]	@ * y
.L25:
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
	ldr	r3, .L34
	mov	lr, pc
	bx	r3
	ldmea	fp, {r4, r5, r6, fp, sp, lr}
	bx	lr
.L27:
	ldrb	r3, [r6, #0]	@ * y
	add	r3, r3, #1
	b	.L33
.L28:
	ldrb	r3, [r5, #0]	@ * x
	sub	r3, r3, #1
.L32:
	strb	r3, [r5, #0]	@ * x
	b	.L25
.L29:
	ldrb	r3, [r5, #0]	@ * x
	add	r3, r3, #1
	b	.L32
.L35:
	.align	2
.L34:
	.word	cursor
.Lfe2:
	.size	move,.Lfe2-move
	.ident	"GCC: (GNU) 3.2.2"
