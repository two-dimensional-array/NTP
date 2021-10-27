#include "ntp.h"
#include <stdio.h>
#include <time.h>

int main()
{
    printf("Difference with NTP server %f seconds\n", difftime(time(NULL), NTP_Update()));
    return 0;
}
