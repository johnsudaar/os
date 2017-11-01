#ifndef KEYBOARD_H
#define KEYBOARD_H

#define IO_PORT 0x60

#define RELEASE_MASK 0x80

unsigned char get_kb_event();

unsigned char get_key_press();
unsigned char get_key_released();

char to_char(unsigned char key_code);

#define KEY_ENTER 0x1C
#define KEY_ESC   0x01

#endif
