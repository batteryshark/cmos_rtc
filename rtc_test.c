#include <stdio.h>
#include <time.h>
#include "cmos_rtc.h"

#define BCD2BIN(n) ( ((n) >> 4) * 10 + ((n) & 0x0F) )

int main(){
printf("Starting Test...\n");
rtc_init();
sleep(2);
unsigned char year,month,day,hours,minutes,seconds = 0;
rtc_set_register(RTC_YEAR);
year = BCD2BIN(rtc_get_register_value());

rtc_set_register(RTC_MONTH);
month = BCD2BIN(rtc_get_register_value());

rtc_set_register(RTC_DAY_OF_MONTH);
day = BCD2BIN(rtc_get_register_value());

rtc_set_register(RTC_HOURS);
hours = BCD2BIN(rtc_get_register_value());

rtc_set_register(RTC_MINUTES);
minutes = BCD2BIN(rtc_get_register_value());

rtc_set_register(RTC_SECONDS);
seconds = BCD2BIN(rtc_get_register_value());

printf("RTC: %d %d %d %d:%d:%d\n",year,month,day,hours,minutes,seconds);
sleep(2);
rtc_shutdown();
printf("Test OK!\n");
return 0;
}
