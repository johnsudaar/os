; -----------------
; -  Hello worldi -
; -----------------

;[org 0x7c00] ; Compensate for the BIOS padding (our program start at the 0x7c00 address

mov bx, 0x7c0 ; We cannot assign directly to bs
mov ds, bx    ; Set our segment to 0x7c0 (So our address will be 0x7c0 * 16 + address) (so it's the same thing that the org method)

; More interrupts documentation here: https://en.wikipedia.org/wiki/BIOS_interrupt_call

mov ah, 0x0e ; ax register: 0x0eXX : (Print the al (XX) char) -> Write char in tty mode

mov al, 'H' ; Storing the first char
int 0x10 ; Call the interrupt (Video services)
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
int 0x10 ; Print l twice
mov al, 'o'
int 0x10
mov al, ' '
int 0x10

mov bp, 0x8000 ; Load data far from our own code
mov sp, bp     ; Initialize the Stack Pointer to BP

push 'A' ; Push some values to the stack
push 'B'
push 'C'

pop bx ; Pop the first value ('C') and store it into the bx register
mov al, bl
int 0x10

pop bx ; Pop the second value ('B') and store it into the bx register
mov al, bl
int 0x10

mov al, [0x7ffe] ; (0x8000 - 0x02 (we are in 16bit since we did'nt tell the processor otherwise) so this should be 'A')
                 ; This is just here to prove that we could do show how bp and sp works (since A is in the two address 0x7fff and 0x7ffe)
int 0x10

mov al, ' '
int 0x10

mov bx, startup_message ; Storing the data into the bx register
call print_string       ; Calling the print_string routine

mov al, ' '
int 0x10

mov bx, msg_a
call print_hex

mov bx, msg_b
call print_hex

jmp $ ; Endless loop (Jum here)

; Include dependencies
%include "../utils/print_string.asm"
%include "../utils/print_hex.asm"

; --------
; - DATA -
; --------
startup_message:
	db 'Booting JOSHUA OS v1.0', 0

msg_a: dw 0x1234
msg_b: dw 0xabcd

; -----------------------------------
; -  Padding and BIOS magic number  -
; -----------------------------------
times 510 - ($ - $$) db 0

; Bios magic number
dw 0xaa55

