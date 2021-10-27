#include "ntp.h"
#include <stdio.h>
#include <time.h>

int main()
{
    time_t ntp_time;
    ntp_time = NTP_Update();
    printf( "Time: %s", ctime(&ntp_time));
    return 0;
}
