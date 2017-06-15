# OS

How hard could it be to write an os?

Let's try it !

I'm learning how to write an OS from scratch, for now, nothing fancy, i can just print some strings to a screen (Yay i guess?)

The `16bit/` folder is the first one i created. This is in the simplified 16bit processor mode and use some bios instruction to help me (so it's basically cheating).

If the project inside the folder can be run, a Makefile will be present. To run the code just type:

```shell
$ make run
```

## Tools

### Install the tools

```
$ apt install qemu nasm
```

### Use the tools

To compile my ASM code i use nasm:

```shell
$ nasm [FILE.ASM] -i bin -o [OUTPUT_FILE.bin]
```

And to run it i use qemu:

```shell
$ qemu-system-i386  [INPUT_FILE.bin]
```

## Usefull qemu trics

### Debug mode

To enter qemu debug mode press: ctrl-alt-shift-1

#### Print a value

```
print $ebx
```

Will print the value of the ebx register

#### Inspect memory:

```
x $ebx
```

Will print the value at the address pointed by EBX

