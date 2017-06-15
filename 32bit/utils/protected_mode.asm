; ---------------------------
; -      GDT DEFINITION     -
; ---------------------------

gdt_start:       ; Used for pointer arithmetics

gdt_null:        ; The first 8 bytes of the GDT table must be 0 (null descriptor)
	times 8 db 0

; Define a segment starting at 0x0 and a limit of 0xffffff for our code
; Flags:
;  * Present: 1
;  * Privilege: 0 (kernel)
;  * Executable: 1 (This will be used for code)
;  * Conforming: 0 (This can only be jumped to by a similar privilege level)
;  * Readable: 1 This part can be read
;  * Access bit: 0 (Internal)
;  * Granularity: 1 Use 4KiB blocks
;  * Size bit: 1 (32 bit protected mode)
gdt_code:         ; Code segement
	dw 0xffff       ; Limit (bits 0 - 15)
	dw 0x0          ; Base (bits 0 - 15)
	db 0x0          ; Base (bits 16 - 23)
	db 10011010b    ; Access bytes (According to our flag)
	db 11001111b    ; First 4 bits: Flags, last 4 bits: Limit (16-19)
	db 0x0          ; Base (bits 24-31)

; Define a segment starting at 0x0 and a limit of 0xffffff for oud data
; Flags:
;   * Present: 1
;   * Privilege: 0 (kernel)
;   * Executable: 0 (This will be used for data)
;   * Direction: 0 (Grow up)
;   * Writable: 1 (Can be written)
;   * Accessed bit: 0 (internal)
;   * Granularity: 1 Use 4KiB blocks
;   * Size bit: 1 (32 bit protected mode)
gdt_data:        ; Data segment
	dw 0xffff      ; Limit (bots 0 - 15)
	dw 0x0         ; Base (bits 0 - 15)
	db 0x0         ; Base (bits 16 - 23)
	db 10010010b   ; Access bytes (According to our flags)
	db 11001111b   ; First 4 bits: Flags, last 4 bits: Limit (bits 16 - 19)
	db 0x0         ; Base (bits 24 - 31)

gdt_end:         ; Use for pointer arithmetics

; The gdt descriptor must have 6 bytes in total:
;  - The first 2 ones are the GDT size - 1
;  - The last 4 ones are the GDT address
gdt_descriptor:
	dw gdt_start - gdt_end - 1 ; The gdt size - 1. That's where the gdt_start and gdt_end labels became handy
	dd gdt_start               ; The gdt location

; Some handy const for the GDT semgments
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


; ---------------------------
; -   SWITCHING TO 32BITS   -
; ---------------------------

switch_to_protected_mode:
	cli ; Clear interrupts CPU will ignore any interrupts. This is done to prevent 16 bit interrupts to cause a CPU
			; during the crash

	lgdt [gdt_descriptor] ; Load the GDT

	; Actually switching to a 32bit
	; To do that, we must set the first bit of cr0 to 1
	; cr0 is not directly accessible, so we use eax as a buffer
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	; Welcome in 32bit mode
	jmp CODE_SEG:init_protected_mode

[bits 32]
init_protected_mode:
	; Now that we are in protected mode, we must update our segment registers
	mov ax, DATA_SEG
	mov dx, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	; Lets initialize the stack position
	mov ebp, 0x90000
	mov esp, ebp

	; Okay we are ready to run in 32bit mode
	call start_protected_mode

