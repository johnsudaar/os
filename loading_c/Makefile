SRC=$(wildcard kernel/*.c)
HEADERS = $(wildcard kernel /*.h)
ASM_SOURCES = $(wildcard boot/utils/*.asm)
OBJ=$(SRC:.c=.o)

all: image.img

image.img: boot/loader.bin kernel.bin
	cat $^ > image.img

%.o: %.c ${HEADERS}
	gcc -mtune=i386 -m32 -march=i386 -ffreestanding -o $@ -c $<

kernel.bin:kernel_entry.o ${OBJ}
	ld -o kernel.bin -Ttext 0x1000 kernel_entry.o ${OBJ} -m elf_i386 --oformat binary

kernel_entry.o:kernel/entry.asm
	nasm kernel/entry.asm -f elf -o kernel_entry.o

%.bin:%.asm ${ASM_SOURCES}
	nasm $< -f bin -o $@ -I 'boot/utils/'

run: image.img
	qemu-system-i386 image.img

clean:
	rm ${OBJ}
	rm *.o
	rm *.bin

mr_proper: clean
	rm image.img
