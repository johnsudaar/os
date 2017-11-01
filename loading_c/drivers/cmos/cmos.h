#ifndef CMOS_H
#define CMOS_H

#define CMOS_REGISTER_PORT 0x70
#define CMOS_DATA_PORT     0x71

#define CMOS_RTC_SECONDS   0x00
#define CMOS_RTC_MINUTES   0x02
#define CMOS_RTC_HOURS     0x04
#define CMOS_RTC_WEEKDAY   0x06
#define CMOS_RTC_MONTH_DAY 0x07
#define CMOS_RTC_MONTH     0x08
#define CMOS_RTC_YEAR      0x09

#define CMOS_STATUS_A      0x0A
#define CMOS_STATUS_B      0x0B

#define FORMAT_24H         0x02
#define FORMAT_BINARY      0x04

unsigned char read_from_CMOS(unsigned char);
void write_to_CMOS(unsigned char, unsigned char);

void set_rtc_mode(char, char);

unsigned char get_rtc_seconds();
unsigned char get_rtc_minutes();
unsigned char get_rtc_hours();
unsigned char get_rtc_weekday();
unsigned char get_rtc_monthday();
unsigned char get_rtc_month();
unsigned char get_rtc_year();

#endif
