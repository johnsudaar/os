int main(){
  char *video_memory = 0xb8000;
  *video_memory = 'X';
  *(video_memory + 1) = 0xf0;
  while(1) {
  }
}
