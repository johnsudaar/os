#include "../../libs/low_level/low_level.h"
#include "cmos.h"

unsigned char read_from_CMOS(unsigned char address) {
  port_byte_out(CMOS_REGISTER_PORT, address);
  return port_byte_in(CMOS_DATA_PORT);
}

void write_to_CMOS(unsigned char address, unsigned char value) {
  port_byte_out(CMOS_REGISTER_PORT, address);
  port_byte_out(CMOS_DATA_PORT, value);
}

void set_rtc_mode(char binary, char format_24h) {
  // If format_24h is set to 1, the clock format will be set to 24h otherwise it will set 12h
  // If the binary is set to 1, the clock output will be set to binary otherwise it will be set to BCD

  unsigned char value = 0;
  if(binary) {
    value = value | FORMAT_BINARY;
  }

  if(format_24h) {
    value = value | FORMAT_24H;
  }

  write_to_CMOS(CMOS_STATUS_B, value);
}

unsigned char get_rtc_seconds() {
  return read_from_CMOS(CMOS_RTC_SECONDS);
}

unsigned char get_rtc_minutes() {
  return read_from_CMOS(CMOS_RTC_MINUTES);
}

unsigned char get_rtc_hours() {
  return read_from_CMOS(CMOS_RTC_HOURS);
}

unsigned char get_rtc_weekday() {
  return read_from_CMOS(CMOS_RTC_WEEKDAY);
}

unsigned char get_rtc_monthday() {
  return read_from_CMOS(CMOS_RTC_MONTH_DAY);
}

unsigned char get_rtc_month() {
  return read_from_CMOS(CMOS_RTC_MONTH);
}

unsigned char get_rtc_year() {
  return read_from_CMOS(CMOS_RTC_YEAR);
}
