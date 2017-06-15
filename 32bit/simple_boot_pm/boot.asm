[org 0x7c00]
	; 16 bit section, just load data and switch to 32bits
	call switch_to_protected_mode ; 16bit, no thanks let's go to 32bit
	jmp $ ; We will never go back there

%include "../utils/protected_mode.asm"
%include "../utils/print_string.asm"

[bits 32]
; Code executed in 32bit protected mode
start_protected_mode: ; Protected mode entry point called by the switch_to_protected_mode routine
	mov ebx, HELLO_WORLD
	call print_string
	jmp $

; Data
HELLO_WORLD: db 'Welcome in 32-bit protected mode!',0

times 510 - ($ - $$) db 0
dw 0xaa55
