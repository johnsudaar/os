#include "screen.h"
#include "../kernel/kernel.h"

int get_screen_offset(int col, int row) {
  return (row * MAX_COL + col) * 2;
}

int get_cursor() {
  port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2; // Cursor reported by the VGA driver returns the number of chars not the real memory offset
}

void set_cursor(int offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset));
}

int handle_scrolling(int offset) {
  if(offset < MAX_ROW * MAX_COL * 2) {
    return offset;
  }

  int i;
  for (i=1; i<MAX_ROW; i++) {
    memory_copy(get_screen_offset (0,i) + VIDEO_ADDRESS , get_screen_offset (0,i-1) + VIDEO_ADDRESS, MAX_COL *2);
  }

  char* last_line = get_screen_offset(0,MAX_ROW -1) + VIDEO_ADDRESS;
  for (i=0; i < MAX_COL *2; i++) {
    last_line[i] = 0;
  }
  offset -= 2* MAX_COL;
  return offset;
}

void print_char(char character, int col, int row, char attrs) {
  unsigned char *video_memory = (unsigned char*) VIDEO_ADDRESS;
  if(attrs == 0) {
    attrs = WHITE_ON_BLACK;
  }

  int offset;

  if (col >= 0 && row >= 0) {
    offset = get_screen_offset(col, row);
  } else {
    offset = get_cursor();
  }

  if(character == '\n') {
    int row = offset / (2*MAX_COL);
    offset = get_screen_offset(MAX_COL-1, row);
  } else {
    video_memory[offset] = character;
    video_memory[offset+1] = attrs;
  }

  offset += 2;
  offset = handle_scrolling(offset);
  set_cursor(offset);
}

void print_at(char *message, int col, int row) {
  if(col >= 0 && row >= 0){
    set_cursor(get_screen_offset(col, row));
  }

  int i = 0;
  while(message[i] != 0) {
    print_char(message[i], -1, -1, WHITE_ON_BLACK);
    i++;
  }
}

void print(char *message) {
  print_at(message, -1, -1);
}

void clear_screen() {
  for(int i = 0; i < MAX_COL; i++) {
    for(int j = 0; j < MAX_ROW ; j++) {
      print_char(' ', i, j, WHITE_ON_BLACK);
    }
  }

  set_cursor(get_screen_offset(0,0));
}

