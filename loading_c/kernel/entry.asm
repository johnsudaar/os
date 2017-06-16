; This entryp.asm file is here to make sure that we hump directly to the C main function. Because we can't rely
; on gcc to put it at the right place.
[bits 32]
[extern main]  ; Decalre that we will be referencing an external symbol: main (from our kenel main function)
call main        ; Call the kernel main function
jmp $            ; Freeze (loop forever)
