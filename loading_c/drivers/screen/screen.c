#include "../../libs/low_level/low_level.h"
#include "../../libs/utils/utils.h"
#include "screen.h"

// Convert X Y position into ram offset
int get_screen_offset(int col, int row) {
  // Since there is 2 byte per char (the char and an attribute byte), we multiply the result by 2
  return (row * MAX_COL + col) * 2;
}


// Return the cursor position on the screen
int get_cursor() {
  // The cursor is stored in 16 bits so there is two different instruction to get the low and high bits

  // Send the high bits command
  port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE);

  // Get the high bits
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;

  // Send the low bits command
  port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE);

  // Get the low bits
  offset += port_byte_in(REG_SCREEN_DATA);

  // The position reported by the VGA driver returns the number of chars not the real memory offset
  return offset * 2;
}

void set_cursor(int offset) {
  // The function is pretty much the same thing that the get_cursor but in reverse

  offset /= 2;

  port_byte_out(REG_SCREEN_CTRL, CURSOR_HIGH_BYTE);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, CURSOR_LOW_BYTE);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset));
}

int handle_scrolling(int offset) {
  // Handle scrolling if necessary
  // This function only manage one line scroll but this is not a problem since this function should only be called in print_char which can only affect a single line

  // This function return the new offset


  // If the offset is lower than the max screen size do nothing
  if(offset < MAX_ROW * MAX_COL * 2) {
    return offset;
  }


  // If the offset is outside the max screen size start the scroll routine

  // For each line, copy its content to the previous line
  for (int i=1; i<MAX_ROW; i++) {
    memory_copy(get_screen_offset(0,i) + VIDEO_ADDRESS , get_screen_offset (0,i-1) + VIDEO_ADDRESS, MAX_COL *2);
  }

  // Clear the last line
  char* last_line = get_screen_offset(0,MAX_ROW -1) + VIDEO_ADDRESS;
  for (int i=0; i < MAX_COL *2; i++) {
    last_line[i] = 0;
  }

  // Compute the new offset position
  offset -= 2* MAX_COL;
  return offset;
}

void print_char(char character, int col, int row, char attrs) {
  // Print a char at a specified position


  unsigned char *video_memory = (unsigned char*) VIDEO_ADDRESS;

  // If no attrs was send, assume that the user want to print a white char on a black background
  if(attrs == 0) {
    attrs = WHITE_ON_BLACK;
  }

  int offset;

  // if col or row is negative, use the cursor position, otherwise use the user coordinates
  if (col >= 0 && row >= 0) {
    // Transform user coordinate to memory offset
    offset = get_screen_offset(col, row);
  } else {
    offset = get_cursor();
  }

  // if the character is a '\n' do nothing and set the offset to the end of the line
  // the new line logic will be done by the end of this routine
  if(character == '\n') {
    int row = offset / (2*MAX_COL);
    offset = get_screen_offset(MAX_COL-1, row);
  } else {
    // If it's a valid char add it to the video memory with its attrs
    video_memory[offset] = character;
    video_memory[offset+1] = attrs;
  }

  // Go to the next chars
  offset += 2;

  // Handle scrolling if necessary
  offset = handle_scrolling(offset);

  // Set the cursor to the new offset
  set_cursor(offset);
}

void print_at(char *message, int col, int row) {
  // Print a null terminated string to a specific position
  // If the position is -1 -1, print it at the cursor position


  if(col >= 0 && row >= 0) {
    // If a position is not -1 -1, set the cursor to the desired position
    set_cursor(get_screen_offset(col, row));
  }

  int i = 0;
  // For each char of the null terminated string
  while(message[i] != 0) {
    // Print the char at the cursor
    print_char(message[i], -1, -1, WHITE_ON_BLACK);
    i++;
  }
}

void print(char *message) {
  // Print a null terminated string at the cursor position
  print_at(message, -1, -1);
}

void clear_screen() {
  // Clear the screen by resetting the video memory

  unsigned char *video_memory = (unsigned char*) VIDEO_ADDRESS;
  for(int i = 0; i < MAX_COL * MAX_ROW * 2 ; i ++) {
    video_memory[i] = 0;
  }

  // Reset the cursor too
  set_cursor(get_screen_offset(0,0));
}

void print_byte(unsigned char value) {
  // Print a byte in hex form

  // Print the 4 higher bits
  print_char(to_hex(value >> 4), -1, -1, WHITE_ON_BLACK);

  // Print the 4 lower bits
  print_char(to_hex(value), -1, -1, WHITE_ON_BLACK);
}

void print_word(unsigned short value) {
  // Print a word in hex form

  // Print the 8 higher bits
  print_byte(value >> 8);
  // Print the 8 lower bits
  print_byte(value);
}
