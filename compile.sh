cc -m32 ./rtc_test.c ./cmos_rtc.c -lpthread -o testlinux32.elf
cc ./rtc_test.c ./cmos_rtc.c -lpthread -o testlinux64.elf
x86_64-w64-mingw32-gcc ./rtc_test.c ./cmos_rtc.c -o ./testwin64.exe
i686-w64-mingw32-gcc   ./rtc_test.c ./cmos_rtc.c -o ./testwin32.exe