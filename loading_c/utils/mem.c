void memory_copy(char *source, char* dest, int size) {
  for(int i = 0; i < size ; i++) {
    dest[i] = source[i];
  }
}
