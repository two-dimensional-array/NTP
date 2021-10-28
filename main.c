#include "ntp.h"
#include <stdio.h>
#include <sys/time.h>

#define NTP_REQUEST_PERIOD 30 //period for request difference with NTP server in seconds

int main()
{
    struct timeval pervios_time = {0,0};
    struct timeval current_time = {0,0};
    while (1)
    {
        gettimeofday(&current_time, NULL);
        if ((current_time.tv_sec - pervios_time.tv_sec) > NTP_REQUEST_PERIOD)
        {
            pervios_time = current_time;
            printf("Difference with NTP server %lf seconds\n", NTP_Difference());
        }
    }
    return 0;
}
