// CMOS RTC Emulation
// Creates a faux CMOS buffer with populated RTC info from system time.
// Mostly for use in applications that call IOPORT 0x70-0x71 directly for
// RTC.

#include <time.h>

#ifndef _WIN32
    #include <pthread.h> 
#else 
    #include <processthreadsapi.h>    
#endif

#include "cmos_rtc.h"

// Misc Defines
#define CMOS_DATA_SZ 0x80
#define BIN2BCD(n) ( (((n) / 10) << 4) + ((n) % 10) )

// We'll only need one copy of these.
static unsigned char cmos_data[CMOS_DATA_SZ] = {0x00};
static unsigned char ctrl_register_port      = 0;
static unsigned char update_thread_running   = 0;

// Updates our CMOS Buffer's RTC registers from system time.
void update_rtc(){
    time_t rawtime;
    struct tm * today;
    update_thread_running = 1;
    while(update_thread_running){
        time ( &rawtime );
        today = localtime ( &rawtime );
        cmos_data[RTC_SECONDS]      = BIN2BCD(today->tm_sec);
        cmos_data[RTC_MINUTES]      = BIN2BCD(today->tm_min);
        cmos_data[RTC_HOURS]        = BIN2BCD(today->tm_hour);
        cmos_data[RTC_DAY_OF_MONTH] = BIN2BCD(today->tm_mday);
        cmos_data[RTC_MONTH]        = BIN2BCD(today->tm_mon + 1);
        // Note: Coming back from BCD this will show 2019 as '19'.
        // This is expected due to Y2K
        cmos_data[RTC_YEAR]         = BIN2BCD((today->tm_year + 1900) % 100);        
    }
}

void rtc_init(){
    #ifndef _WIN32
        pthread_t thread;
        pthread_create(&thread,NULL, update_rtc, NULL);
    #else
        CreateThread(NULL, 0, (void*)update_rtc, NULL, 0, NULL);
    #endif
}

void rtc_shutdown(){
    update_thread_running = 0;
}

void rtc_set_register(unsigned char port){
    ctrl_register_port = port;  
}

unsigned char rtc_get_register_value(){
    return cmos_data[ctrl_register_port];
}

