; Copy al sectors db in the disk dl to the address stored at bx:cx

[bits 16]
read_sectors:
	pusha

	push ax      ; push the number of sector that we cant to read onto the stack so we can use it later to check if everything was correctly executed

	mov ah, 0x02 ; Int 0x13, 0x02h : Load disk

	; -- Describe where to store it
	; We want to put it to (cx*16+dx) (if cx is 0xa000 and dx is 0x1234, it will be stored at 0xa1234)

	mov es, bx   ; Set the segment to cx
	mov bx, cx   ; Set the address to dx


	; -- Decribe what we are reading
	; mov dl, dl   ; Read from drive dl (Not usefull here, it's just here for clarity)
	mov cl, dh   ; Sector: bl
	mov ch, 0    ; Cylinder: 0
	mov dh, 0    ; Track: 0
	;mov al, al    ; Read al sector (Not usefull here, it's just here for clarity)

	; Call the interrupt
	int 0x13

	jc disk_error  ; jc (jump if carry bit is set) in this context: jump if error
	pop bx        ; pop the exepected number of message into the bl register

	cmp al, bl     ; al: number of sector writter and compare it to the expected number of sector (the one that we just poped from the stack into bl)
	jne disk_error ; If this is not 1, something bad happend

	; Everything went just fine, return
	popa
	ret

disk_error:                  ; If an error happened
	mov bx, DISK_ERROR_MESSAGE ; Print the DISK_ERROR_MESSAGE
	call print_string
	jmp $                      ; And freeze

; Data

DISK_ERROR_MESSAGE: db 'Disk error.',0
