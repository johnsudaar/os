#include "../drivers/screen/screen.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/cmos/cmos.h"
#include "../libs/io/io.h"

int main(){
  clear_screen();
  print("Started !\n");
  set_rtc_mode(0,1);
  print_date();
  print("\n");
  unsigned char value;
  while(1){
    value = get_key_released();
    print_char(to_char(value), -1, -1, 0);
  }
}
