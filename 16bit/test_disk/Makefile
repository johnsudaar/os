boot_sect.bin: test_disk.asm ../utils/print_hex.asm ../utils/print_string.asm ../utils/disk.asm
	nasm test_disk.asm -f bin -o boot_sect.bin

run: boot_sect.bin
	qemu-system-i386 boot_sect.bin
