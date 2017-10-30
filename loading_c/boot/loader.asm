[org 0x7c00]
  ; This booloade does the following;
	; * Load the disk sector int 16bit mode it's easier
	; * Switch to 32bit mode
	; * Launch the kernel main method

	mov [BOOT_DRIVE], dl   ; Store the boot drive id
	mov bp, 0x8000         ; Init the stack pointers
	mov sp, bp

	mov bx, LOADING_KERNEL ; Print the loading message
	call print_string

	; Loading the kernel code from the hard drive
	mov dl, [BOOT_DRIVE]   ; Fetch the source from the boot drive
	mov dh, 0x02           ; Start on the second sector
	mov bx, 0              ; Segment 0
	mov cx, KERNEL_ADDRESS ; At the kernel address
	mov al, 4              ; Read 1 sector
	call read_sectors      ; Laucn the sector reading procedure

	mov bx, KERNEL_LOADED  ; Print the kernel loadied message
	call print_string

	call switch_to_protected_mode ; Switch to 32bits protected mode.


%include 'disk.asm'
%include 'print_string_16bit.asm'
%include 'protected_mode.asm'
%include 'print_string_32bit.asm'

[bits 32]
	start_protected_mode:       ; 32bit protected mode entry point
		mov ebx, LAUNCHING_KERNEL ; Display a message saying that we successfully are in 32bit mode
		call print_string_e

		call KERNEL_ADDRESS       ; Launch the kernel code

; DATA
BOOT_DRIVE: db 0
KERNEL_ADDRESS equ 0x1000

LOADING_KERNEL: db 'Loading kernel...',0
KERNEL_LOADED: db ' Kernel loaded. Using 32bit mode...',0
LAUNCHING_KERNEL: db ' 32bit mode on. Launching kernel',0

; Padding fill the remaining space on that sector
times 510 - ($ - $$) db 0
dw 0xaa55 ; BIOS boot sector magic number
