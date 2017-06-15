; Goal: Read some bytes from the disk

[org 0x7c00]
	mov [BOOT_DRIVE], dl ; The bios set the boot disk into the dl register, so we store it, it might be usefull

	mov bp, 0x8000       ; Move the stack pointer out of our code
	mov sp, bp

	mov dl, [BOOT_DRIVE] ; Read from the boot drive
	mov dh, 0x02         ; Read the second sector
	mov bx, 0            ; Set the segment to 0
	mov cx, 0x9000       ; Set the store address to 0x9000
	call read_sector     ; Call the read_sector procedure

	mov dh, 0x03         ; Read the third sector
	mov cx, 0x9000 + 512 ; Store it to 0x9000 + 512
	call read_sector

	mov bx, 0x9000       ; Print the byte at 0x8000 (should be the first word of the 2nd sector (0xdead))
	call print_hex       ; Call the print_hex procedure

	mov bx, 0x9000 + 512 ; Print the byte as 0x9000 + 512 (should be the first word of the 3rd sector (0xbeef))
	call print_hex

	jmp $                ; Freeze

%include "../utils/disk.asm"
%include "../utils/print_hex.asm"
%include "../utils/print_string.asm"

; DATA

BOOT_DRIVE: db 0  ; Store the boot drive

times 510 - ($ - $$) db 0 ; GO to the last 2 bytes of the first sector
dw 0xaa55

times 256 dw 0xdead ; Fill the sector with 0xdead
times 256 dw 0xbeef ; Fill the sector with 0xbeef
