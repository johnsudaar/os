disk.bin: boot.asm ../utils/print_string.asm ../utils/protected_mode.asm
	nasm boot.asm -f bin -o disk.bin

run: disk.bin
	qemu-system-x86_64 disk.bin
