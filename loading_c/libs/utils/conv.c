char to_hex(char value) {
  value = value & 0x0F;

  if(value < 10) {
    return '0' + value;
  } else{
    return 'A' - 10 + value;
  }
}
