	.file	"view.c"
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

	.global	videoBuffer
	.data
	.align	2
	.type	videoBuffer,object
	.size	videoBuffer,4
videoBuffer:
	.word	100663296
	.text
	.align	2
	.global	cursor
	.type	cursor,function
cursor:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}
	and	r4, r1, #255	@  y
	and	r5, r0, #255	@  x
	add	r4, r4, r4, asl #2	@  y,  y
	rsb	r5, r5, r5, asl #4	@  x,  x
	mov	r4, r4, asl #1
	and	r7, r5, #255
	and	sl, r4, #255
	mov	r6, r2, asl #16
	sub	sp, sp, #4
	sub	fp, ip, #4
	mov	r6, r6, lsr #16
	ldr	r8, .L2
	mov	r0, r7
	mov	r1, sl
	mov	r2, #15
	mov	r3, #1
	add	r4, r4, #10
	str	r6, [sp, #0]
	and	r4, r4, #255
	mov	lr, pc
	bx	r8
	add	r5, r5, #15
	mov	r0, r7
	mov	r1, sl
	mov	r2, #1
	mov	r3, #10
	str	r6, [sp, #0]
	and	r5, r5, #255
	mov	lr, pc
	bx	r8
	mov	r0, r7
	mov	r1, r4
	mov	r2, #16
	mov	r3, #1
	str	r6, [sp, #0]
	mov	lr, pc
	bx	r8
	mov	r0, r5
	mov	r1, sl
	mov	r2, #1
	mov	r3, #10
	str	r6, [sp, #0]
	mov	lr, pc
	bx	r8
	ldmea	fp, {r4, r5, r6, r7, r8, sl, fp, sp, lr}
	bx	lr
.L3:
	.align	2
.L2:
	.word	drawLine
.Lfe1:
	.size	cursor,.Lfe1-cursor
	.align	2
	.global	drawPixel
	.type	drawPixel,function
drawPixel:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	and	r1, r1, #255	@  y
	ldr	r3, .L5
	rsb	r1, r1, r1, asl #4	@  y,  y
	and	r0, r0, #255	@  x
	add	r0, r0, r1, asl #4	@  x
	ldr	r1, [r3, #0]	@  videoBuffer
	mov	r0, r0, asl #1
	@ lr needed for prologue
	strh	r2, [r0, r1]	@ movhi 
	bx	lr
.L6:
	.align	2
.L5:
	.word	videoBuffer
.Lfe2:
	.size	drawPixel,.Lfe2-drawPixel
	.align	2
	.global	drawLine
	.type	drawLine,function
drawLine:
	@ Function supports interworking.
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, lr}
	and	r1, r1, #255	@  y
	and	r3, r3, #255	@  h
	add	r3, r1, r3	@  i,  h
	cmp	r1, r3	@  i
	and	r7, r0, #255	@  x
	and	r6, r2, #255	@  l
	ldrsh	r4, [sp, #24]	@  c,  c
	bge	.L19
	ldr	r8, .L22
	mov	r5, r3
	rsb	r0, r1, r1, asl #4	@  i,  i
.L17:
	add	r2, r7, r6	@  j,  l
	cmp	r7, r2	@  j
	bge	.L21
	add	r3, r7, r0, asl #4	@  j
	ldr	lr, [r8, #0]	@  videoBuffer
	mov	r3, r3, asl #1
	rsb	ip, r7, r2	@  j,  j
.L16:
	subs	ip, ip, #1	@  j,  j
	strh	r4, [r3, lr]	@ movhi 	@  c
	add	r3, r3, #2
	bne	.L16
.L21:
	add	r1, r1, #1	@  i,  i
	cmp	r1, r5	@  i
	add	r0, r0, #15
	blt	.L17
.L19:
	ldmfd	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
.L23:
	.align	2
.L22:
	.word	videoBuffer
.Lfe3:
	.size	drawLine,.Lfe3-drawLine
	.align	2
	.global	drawCase
	.type	drawCase,function
drawCase:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	and	r5, r0, #255	@  x,  x
	and	r4, r1, #255	@  y,  y
	sub	fp, ip, #4
	sub	sp, sp, #4
	mov	r1, r4	@  y
	mov	r0, r5	@  x
	ldr	r3, .L35
	mov	lr, pc
	bx	r3
	and	r0, r0, #255	@  n,  x
	cmp	r0, #9	@  n
	ldrls	pc, [pc, r0, asl #2]	@  n
	b	.L24
	.p2align 2
.L32:
	.word	.L26
	.word	.L27
	.word	.L28
	.word	.L29
	.word	.L30
	.word	.L24
	.word	.L24
	.word	.L24
	.word	.L24
	.word	.L31
.L26:
	add	r1, r4, r4, asl #2	@  y,  y
	rsb	r0, r5, r5, asl #4	@  x,  x
	mov	ip, #32000
	mov	r1, r1, asl #1
	mov	r2, #15
	mov	r3, #10
	and	r0, r0, #255	@  x
	and	r1, r1, #255	@  y
	add	ip, ip, #134
.L34:
	str	ip, [sp, #0]
	bl	drawLine
.L24:
	ldmea	fp, {r4, r5, fp, sp, lr}
	bx	lr
.L27:
	add	r1, r4, r4, asl #2	@  y,  y
	rsb	r0, r5, r5, asl #4	@  x,  x
	mov	r1, r1, asl #1
	mov	r2, #15
	mov	r3, #10
	and	r0, r0, #255	@  x
	and	r1, r1, #255	@  y
	mov	ip, #12672
	b	.L34
.L28:
	add	r1, r4, r4, asl #2	@  y,  y
	rsb	r0, r5, r5, asl #4	@  x,  x
	mov	ip, #32512
	mov	r1, r1, asl #1
	mov	r2, #15
	mov	r3, #10
	and	r0, r0, #255	@  x
	and	r1, r1, #255	@  y
	add	ip, ip, #224
	b	.L34
.L29:
	add	r1, r4, r4, asl #2	@  y,  y
	rsb	r0, r5, r5, asl #4	@  x,  x
	mov	ip, #31744
	mov	r1, r1, asl #1
	mov	r2, #15
	mov	r3, #10
	and	r0, r0, #255	@  x
	and	r1, r1, #255	@  y
	add	ip, ip, #25
	b	.L34
.L30:
	add	r1, r4, r4, asl #2	@  y,  y
	rsb	r0, r5, r5, asl #4	@  x,  x
	mov	ip, #6528
	mov	r1, r1, asl #1
	mov	r2, #15
	mov	r3, #10
	and	r0, r0, #255	@  x
	and	r1, r1, #255	@  y
	add	ip, ip, #31
	b	.L34
.L31:
	add	r1, r4, r4, asl #2	@  y,  y
	rsb	r0, r5, r5, asl #4	@  x,  x
	mov	r1, r1, asl #1
	mov	r2, #15
	mov	r3, #10
	and	r0, r0, #255	@  x
	and	r1, r1, #255	@  y
	mov	ip, #31
	b	.L34
.L36:
	.align	2
.L35:
	.word	checkMines
.Lfe4:
	.size	drawCase,.Lfe4-drawCase
	.ident	"GCC: (GNU) 3.2.2"
