boot_sect.bin: bootloader.asm
	nasm bootloader.asm -f bin -o boot_sect.bin

run: boot_sect.bin
	qemu-system-i386 boot_sect.bin
