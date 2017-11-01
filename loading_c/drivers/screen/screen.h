#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROW 25
#define MAX_COL 80

#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define CURSOR_HIGH_BYTE 14
#define CURSOR_LOW_BYTE 15

int get_screen_offset(int, int);
int get_cursor();
void set_cursor(int);
int handle_scrolling(int);
void print_char(char, int, int, char);
void print_at(char*, int, int);
void print(char*);
void clear_screen();

void print_byte(unsigned char);
void print_word(unsigned short);
#endif
