#include "../../libs/low_level/low_level.h"
#include "keyboard.h"

// Corresponding table between keycodes and ASCII char
const char key_codes[0x40] = {
// 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 0
  'a', 'z', 'e', 'r', 't', 'i', 'u', 'i', 'o', 'p', 0x0, 0x0, '\n',0x0, 'q', 's', // 1
  'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0x0, 0x0, 0x0, 0x0, 'w', 'x', 'c', 'v', // 2
  'b', 'n', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, // 3

};

unsigned char get_kb_event() {
  // Poll a keyboard event

  // Get the initial port value
  unsigned char initial_value = port_byte_in(IO_PORT);
  unsigned char new_value = initial_value;

  // Wait for a new value to arrive at this port
  while(initial_value == new_value) {
    new_value = port_byte_in(IO_PORT);
  }

  // Return the new value
  return new_value;
}

unsigned char get_key_press() {
  // Poll a key press event and return the keycode
  unsigned char event;

  do {
    // Wait for a new keyboard event
    event = get_kb_event();

    // if in the event code the KEY_RELEASE bit is set to 1, wait for a new event, otherwise, return the keycode
  }while(event & RELEASE_MASK);

  return event;
}

unsigned char get_key_released() {
  // Poll a key release event and return the key code
  unsigned char event;

  do {
    // Wait for a new keyboard event
    event = get_kb_event();
    // if in the new event code the KEY_RELEASE bit is set to 0, wait for a new event, otherwise return the keycode
  }while(! (event & RELEASE_MASK));

  // Unset the KEY RELEASE bit so the event code is coverted to a keycode
  // I.e. if the event code is 10001010 (key e released)
  // it will return 00001010 (key e)
  return event & (~RELEASE_MASK);
}

char to_char(unsigned char key_code) {
  // TODO: Move that into a lib, support more keys and think about keyboard layout
  // Transform a key code to a char (if possible)

  if(key_code > 0x3F) {
    // If the key_code is outside our key code table
    return '?';
  }
  if(key_codes[key_code] == 0x0) {
    // If the keycode table return 0
    return '?';
  }
  return key_codes[key_code];
}
