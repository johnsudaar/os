[bits 32]
; Print the null terminaed string present in the ebx register

; To do so, we must directly write into the device memory.
; This device is a screen of 80x25 chars.
; Each chars is represented in memory by two bytes. The first one is the ASCII char and the second one is some metadata like BG and FG colors.

; Constants
VIDEO_MEMORY: equ 0xb8000 ; Pointer to the VIDEO MEMORY
WHITE_ON_BLACK: equ 0x0f

print_string_e:           ; Print the string store in the EBX registry
	pusha
	mov edx, VIDEO_MEMORY   ; We will print the string at the char (0,0) so we initialise EDX (our cursor) to the very beginning of our video memory

print_string_e_loop:      ; This is our main loop, it will iterate over our string and print the char
	mov al, [ebx]           ; Load the current char into the al registry
	mov ah, WHITE_ON_BLACK  ; Set the ah registry to the WHITE_ON_BLACK metadata

	cmp al, 0               ; If the current char is 0
	je print_string_e_end   ; Stop the loop

	mov [edx], ax           ; Store the ax register (reminder: ax is ah:al) into the video memory (store the current char at the cursor location)

	add edx, 2              ; Move the cursor to the next position (advance two bytes)
	add ebx, 1              ; Go to the next char in the string
	jmp print_string_e_loop ; Loop

print_string_e_end:       ; End of the print_string function. Just some cleanup
	popa
	ret
