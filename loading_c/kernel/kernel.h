#ifndef KERNEL_H
#define KERNEL_H

unsigned char port_byte_in(unsigned short);
void port_byte_out(unsigned short, unsigned char);

unsigned short port_word_in(unsigned short);
void port_word_out(unsigned short, unsigned short);

void memory_copy(char *, char*, int);

#endif