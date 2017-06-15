# 32 bit

Here we have a simple code starting in 16 bit, switching to 32 bit protected mode and printing a string to the screen.

The `utils/` folder contain two utility functions.

 * `print_string` that will print the string present in the EBX register (in 32 bit PM)
 * `protected_mode` that provide all the code needed to switch into 32 bit protected mode.

The `simple_boot_pm/` folder contains the code that use this two utilities to jump into 32bits protected mode and print a string.


