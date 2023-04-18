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
	ldr	r6, .L20
	ldr	r7, .L20+4
	sub	fp, ip, #4
	mov	r5, #0	@  mines
.L6:
	mov	lr, pc
	bx	r6
	mov	r3, r0, asr #31
	add	r3, r0, r3, lsr #28
	bic	r3, r3, #15
	rsb	r4, r3, r0
	mov	lr, pc
	bx	r6
	mov	r3, r0, asr #31
	add	r3, r0, r3, lsr #28
	bic	r3, r3, #15
	add	r4, r4, #2
	rsb	r0, r3, r0
	and	r4, r4, #255	@  mX
	add	r0, r0, #2
	add	r4, r4, r4, asl #3	@  mX,  mX
	and	r0, r0, #255	@  mY
	add	r2, r7, r4, asl #1
	ldrb	r3, [r2, r0]	@ zero_extendqisi2	@  y
	add	r1, r5, #1	@  mines
	cmp	r3, #1
	movne	r3, #1
	andne	r5, r1, #255	@  mines
	strneb	r3, [r2, r0]	@  y
	cmp	r5, #20	@  mines
	bne	.L6
	ldmea	fp, {r4, r5, r6, r7, fp, sp, lr}
	bx	lr
.L21:
	.align	2
.L20:
	.word	rand
	.word	y
.Lfe1:
	.size	grid,.Lfe1-grid
	.align	2
	.global	checkMines
	.type	checkMines,function
checkMines:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
	mov	r0, #0
	bx	lr
.Lfe2:
	.size	checkMines,.Lfe2-checkMines
	.comm	y, 324, 8
	.ident	"GCC: (GNU) 3.2.2"
