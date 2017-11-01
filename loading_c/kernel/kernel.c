#include "../drivers/screen.h"
#include "../drivers/keyboard.h"

int main(){
  clear_screen();
  print("Started !\n");
  unsigned char value;
  while(1){
    value = get_key_released();
    print_char(to_char(value), -1, -1, 0);
  }
}
