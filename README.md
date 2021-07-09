# cmos_rtc

Emulation/Compatibility Wrapper of a CMOS RTC

Designed for instances where legacy applications query the 
RTC directly for time-related stuff via ioport 0x70-0x71 which 
doesn't work in modern Windows and not without permissions
in Linux.

Compiles with msvc or GCC for 32 or 64bit systems.