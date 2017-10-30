#include "../drivers/screen.h"

int main(){
  clear_screen();
  print("Start!");
  for(int i = 0; i < MAX_ROW -2 ; i++){
  print("Hello world\n");
  }
  print("Scroll ? \n");
  print("Scroll2 ? \n");
  while(1) {
  }
}
