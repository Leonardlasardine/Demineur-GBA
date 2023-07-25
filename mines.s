	.file	"mines.c"
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

	.text
	.align	2
	.global	grid
	.type	grid,function
grid:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	mov	lr, #0	@  posX
	ldr	r4, .L23
	sub	fp, ip, #4
	mov	ip, lr	@  posX
.L11:
	add	r3, lr, lr, asl #3	@  posX,  posX
	add	r1, r4, r3, asl #1
	mov	r2, #0	@  posY
.L10:
	add	r3, r2, #1	@  posY
	strb	ip, [r1, r2]	@  g
	and	r2, r3, #255	@  posY
	cmp	r2, #15	@  posY
	bls	.L10
	add	r3, lr, #1	@  posX
	and	lr, r3, #255	@  posX
	cmp	lr, #15	@  posX
	bls	.L11
	ldr	r3, .L23+4
	mov	lr, pc
	bx	r3
	ldr	r6, .L23+8
	ldr	r7, .L23
	mov	r5, #0	@  mines
.L16:
	mov	lr, pc
	bx	r6
	mov	r3, r0, asr #31	@  seed
	add	r3, r0, r3, lsr #28	@  seed
	bic	r3, r3, #15
	rsb	r4, r3, r0	@  seed
	mov	lr, pc
	bx	r6
	mov	r3, r0, asr #31	@  seed
	add	r3, r0, r3, lsr #28	@  seed
	bic	r3, r3, #15
	and	r4, r4, #255	@  mX
	rsb	r0, r3, r0	@  seed
	add	r4, r4, r4, asl #3	@  mX,  mX
	and	r0, r0, #255	@  mY
	add	r2, r7, r4, asl #1
	ldrb	r3, [r2, r0]	@ zero_extendqisi2	@  g
	add	r1, r5, #1	@  mines
	cmp	r3, #1
	movne	r3, #1
	andne	r5, r1, #255	@  mines
	strneb	r3, [r2, r0]	@  g
	cmp	r5, #20	@  mines
	bne	.L16
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L24:
	.align	2
.L23:
	.word	g
	.word	srand
	.word	rand
.Lfe1:
	.size	grid,.Lfe1-grid
	.align	2
	.global	checkMines
	.type	checkMines,function
checkMines:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, lr}
	and	r0, r0, #255	@  x,  n
	ldr	lr, .L42
	add	r3, r0, r0, asl #3	@  x,  x
	and	ip, r1, #255	@  y
	add	r3, lr, r3, asl #1
	ldrb	r2, [r3, ip]	@ zero_extendqisi2	@  g
	mov	r4, #0	@  n
	cmp	r2, #1
	addeq	r4, r4, #9	@  n,  n
	beq	.L27
	sub	r3, r0, #1	@  x
	and	r1, r3, #255	@  i
	add	r6, r0, #2	@  x
	cmp	r1, r6	@  i
	bge	.L27
	add	r0, ip, #2	@  y
	mov	r7, lr
	sub	r5, ip, #1	@  y
.L38:
	and	ip, r5, #255	@  j
	cmp	ip, r0	@  j
	bge	.L41
	add	r3, r1, r1, asl #3	@  i,  i
	add	lr, r7, r3, asl #1
.L37:
	ldrb	r2, [lr, ip]	@ zero_extendqisi2	@  g
	add	r3, ip, #1	@  j
	and	ip, r3, #255	@  j
	cmp	r2, #1
	add	r3, r4, #1	@  n
	andeq	r4, r3, #255	@  n
	cmp	ip, r0	@  j
	blt	.L37
.L41:
	add	r3, r1, #1	@  i
	and	r1, r3, #255	@  i
	cmp	r1, r6	@  i
	blt	.L38
.L27:
	mov	r0, r4	@  n
	ldmfd	sp!, {r4, r5, r6, r7, lr}
	bx	lr
.L43:
	.align	2
.L42:
	.word	g
.Lfe2:
	.size	checkMines,.Lfe2-checkMines
	.align	2
	.global	reveal
	.type	reveal,function
reveal:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	ldr	r6, .L59
	sub	fp, ip, #4
	mov	r5, #0	@  posX
.L54:
	mov	r4, #0	@  posY
.L53:
	mov	r1, r4	@  posY
	mov	r0, r5	@  posX
	mov	lr, pc
	bx	r6
	add	r3, r4, #1	@  posY
	and	r4, r3, #255	@  posY
	cmp	r4, #15	@  posY
	bls	.L53
	add	r3, r5, #1	@  posX
	and	r5, r3, #255	@  posX
	cmp	r5, #15	@  posX
	bls	.L54
	ldmea	fp, {r4, r5, r6, fp, sp, lr}
	bx	lr
.L60:
	.align	2
.L59:
	.word	drawCase
.Lfe3:
	.size	reveal,.Lfe3-reveal
	.comm	g, 324, 8
	.ident	"GCC: (GNU) 3.2.2"
