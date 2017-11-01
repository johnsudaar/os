# OS

How hard could it be to write an os?

Let's try it !

I'm learning how to write an OS from scratch, for now, nothing fancy, i can just print some strings to a screen (Yay i guess?)

The `16bit/` folder is the first one i created. This is in the simplified 16bit processor mode and use some bios instruction to help me (so it's basically cheating).

The `32bit/` golder is the second one i created. This contains code to jump from 16bit to 32bit protected mode and display a simple string.

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

To enter qemu debug mode press: ctrl-alt-shift-2

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

## Documentation

 * An *awesome* introduction by Nick Blundell [source](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
 * Intel manual [source](https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf)
 * A BIOS manual that i used to get a list of all the BIOS interrupts [source](http://www.esapcsolutions.com/ecom/drawings/PhoenixBIOS4_rev6UserMan.pdf)
 * Global descriptor table [source](http://wiki.osdev.org/Global_Descriptor_Table)
 * OS DEV WIKI [link](http://wiki.osdev.org/Main_Page)
