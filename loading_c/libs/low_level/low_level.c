// Read a byte from a specific port
unsigned char port_byte_in(unsigned short port) {
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

// Write a byte to a specific port
void port_byte_out(unsigned short port, unsigned char data) {
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

// Write a word (16 bits) to a specific port
unsigned short port_word_in(unsigned short port) {
  unsigned short result;
  __asm__("in %%dx, %%al" : "=a" (result): "d" (port));
  return result;
}

// Write a word (16 bits) to a specific port
void port_word_out(unsigned short port, unsigned short data) {
  __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}
