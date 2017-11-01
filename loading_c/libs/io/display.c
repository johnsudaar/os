#include "../../drivers/cmos/cmos.h"
#include "../../drivers/screen/screen.h"

void print_date() {
  print_byte(get_rtc_year());
  print_char('-', -1, -1, WHITE_ON_BLACK);
  print_byte(get_rtc_month());
  print_char('-', -1, -1, WHITE_ON_BLACK);
  print_byte(get_rtc_monthday());
  print_char(' ', -1, -1, WHITE_ON_BLACK);
  print_byte(get_rtc_hours());
  print_char('h', -1, -1, WHITE_ON_BLACK);
  print_byte(get_rtc_minutes());
  print_char('m', -1, -1, WHITE_ON_BLACK);
  print_byte(get_rtc_seconds());
  print_char('s', -1, -1, WHITE_ON_BLACK);
}
