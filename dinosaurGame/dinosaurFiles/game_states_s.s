	.arch msp430g2553

	.p2align 1,0

	.data
	.global mute
mute:
	.word 0

	.text
	.extern switch_state_down
	.extern highscore
	;; .extern score
	.extern dinosaur_jump
	.extern dinosaur_down
	.extern playing
	;; .extern din1
	;; .extern buzzer_set_period
	;; .extern freq1
	;; .extern play_track
	.extern continue_game
jt:
	.word default
	.word case_1
	.word case_2
	.word case_3
	.word case_4
	.word case_5

	.global game_controls
game_controls:
				; verify the range is not greater than 5
	mov #0x05, r13
	cmp &switch_state_down, r13
	jnc default
				; indexing to jump table
	mov &switch_state_down, r12
	add r12, r12 		; double for word size (2 bytes)
	mov jt(r12), r0
	
case_1:				; reset highscore
	mov #0x00, &highscore
	mov #0x00, &switch_state_down
	jmp end_switch
case_2:				; jump
	mov #0x01, &dinosaur_jump
	mov #0x00, &switch_state_down
	jmp end_switch
case_3:				; jump booster
	mov #0x01, &dinosaur_down
	mov #0x00, &switch_state_down
	jmp end_switch
case_4:				; start/pause
	mov #0x00, &dinosaur_jump
	mov #0x00, &dinosaur_down
	mov &playing, &mute
	mov &playing, r14
	mov #0x01, &playing
	sub r14, &playing
	mov #0x00, &switch_state_down
	jmp end_switch
case_5:				; mute
	mov &mute, r15
	mov #0x01, &mute
	sub r15, &mute
	mov #0x00, &switch_state_down
	jmp end_switch
default:			; continue
				; mov &din1, r13		; move structure to register for indexing (only ints in din1)
				;cmp #0x80,2(r13)	; (2)r13 = din1.dy therefore verifies din1.dy < 128
	;; cmp #0x80, dy
	;; jc ignore_d_jump
				;cmp 2(r13),6(r13)	; (6)r13 = din1.old_dy therefore verifies din1.old_dy >= din1.dy
	;; cmp dy, old_dy
	;; jnc ignore_d_jump
	;; mov #0x00, &dinosaur_down
	;; mov #0x00, &dinosaur_jump
;; ignore_d_jump:
				; skips disabling dinosaur_down and dinosaur_jump
	;; cmp #0x00, &mute
;; 	jz play_song
;; 	mov #0x00, r12
;; 	call buzzer_set_period
;; 	jmp end_switch
;; play_song:
				; play the song of the game
	;; call play_track
	call #continue_game
end_switch:			; implicit return
	pop r0
