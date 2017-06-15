boot_sect.bin: bootloader.asm ../utils/print_hex.asm ../utils/print_string.asm
	nasm bootloader.asm -f bin -o boot_sect.bin

run: boot_sect.bin
	qemu-system-i386 boot_sect.bin
