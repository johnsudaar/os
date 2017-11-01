#include "../kernel/kernel.h"
#include "keyboard.h"
#include "screen.h"


const char key_codes[0x40] = {
// 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 0
  'a', 'z', 'e', 'r', 't', 'i', 'u', 'i', 'o', 'p', 0x0, 0x0, '\n',0x0, 'q', 's', // 1
  'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0x0, 0x0, 0x0, 0x0, 'w', 'x', 'c', 'v', // 2
  'b', 'n', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 3

};

unsigned char get_kb_event() {
  unsigned char initial_value = port_byte_in(IO_PORT);
  unsigned char new_value = initial_value;

  while(initial_value == new_value) {
    new_value = port_byte_in(IO_PORT);
  }

  return new_value;
}

unsigned char get_key_press() {
  unsigned char event;
  do {
    event = get_kb_event();
  }while(event & RELEASE_MASK);

  return event;
}

unsigned char get_key_released() {
  unsigned char event;
  do {
    event = get_kb_event();
  }while(! (event & RELEASE_MASK));
  return event & (~RELEASE_MASK);
}

char to_char(unsigned char key_code) {
  if(key_code > 0x3F) {
    return '?';
  }
  if(key_codes[key_code] == 0x0) {
    return '?';
  }
  return key_codes[key_code];
}
