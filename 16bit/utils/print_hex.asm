; Print the hex value of the memory address pointed by bx

HEX_OUT: db ' 0x0000',0            ; Base message string

print_hex:                         ; Print the hexadecimal value stored at the bx address
	pusha                            ; Push the registers to the stack
	mov ax, [bx]                     ; Get the value stored at this location. The AX register will be rotated 4 bits by 4 bits to print each hexa char (1 hexa char = 4 bit)
	mov bx, HEX_OUT                  ; Store the message string to a register so we can play with him a bit
	add bx, 0x6                      ; Get to the sixth char (the end of the string). We will write the string starting from the end since we will use a right shift
	call print_hex_main              ; Call 4 time the mail routine (once for each hexadecimal digit)
	call print_hex_main
	call print_hex_main
	call print_hex_main
	mov bx, HEX_OUT                  ; Prepare for the print_string function call, move the HEX_OUT address to the bx register so it can be printed
	call print_string                ; Call the print_string function
	popa                             ; Pop the registers
	ret                              ; Return to the caller

print_hex_main:                    ; Entrypoint for the main print_hex routine: add a single hexadecimal digit to the output string
	mov cx, ax                       ; Mov the current value to the cx register so that we can do some arithmetics with it
	and cl, 0xf                      ; Mask every bits except for the last 4
	cmp cl, 0xa                      ; If the resulting value is a number call the number routie else call the letter digit
	jl print_hex_store_digit
	jmp print_hex_store_letter

print_hex_store_digit:
	add cl, 0x30                     ; Add the resulting value (0-9) to the '0' ascii digit so it will return a valid ascii code (between '0' and '9')
	jmp print_hex_store_and_advance

print_hex_store_letter:
	add cl, 0x37                     ; Add the resulting value (10-15) to the 'a'-10 ascii letter so it will return a valid ascii code (between 'a' and 'f')
	jmp print_hex_store_and_advance

print_hex_store_and_advance:
	mov [bx], cl                     ; Move the computed ascii code to the main string
	sub bx, 0x1                      ; Go to the next previous digit
	shr ax, 0x4                      ; Shift 4 binary digit to the right so we can relaunch the same procedure for the 4 next ones
	ret                              ; Get back to the caller

