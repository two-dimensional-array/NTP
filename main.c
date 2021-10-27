#include "ntp.h"
#include <stdio.h>
#include <time.h>

#define NTP_REQUEST_PERIOD 30 //period for request difference with NTP server in seconds

int main()
{
    time_t current_time = 0;
    while (1)
    {
        if (difftime(time(NULL), current_time) > NTP_REQUEST_PERIOD)
        {
            time(&current_time);
            printf("Difference with NTP server %f seconds\n", difftime(time(NULL), NTP_Update()));
        }
    }
    return 0;
}
