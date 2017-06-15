print_string:           ; Take a string store in the BX register and print it
	pusha 								; Store the current registry values
	mov ah, 0x0e          ; Call 0x10 (0x03h) : TTY Write (BIOS)

print_string_main:
	mov cx, [bx]          ; Store the current value into the C register
	cmp cl, 0             ; If the lower byte is 0
	je print_string_end   ; Jump to the end

	mov al, cl            ; Move the loweer byte into the lower al registry (TTY print)
	int 0x10              ; Call the 0x10 instruction
	add bx, 0x01          ; Advance the string pointer to the next byte
	jmp print_string_main ; Jump to the next routine

print_string_end:       ; print_string_end print_string cleanup
	popa                  ; Pop the registry values
	ret                   ; Return to the caller

