#ifndef __NTP_H__
#define __NTP_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define NTP_TIMESTAMP_DELTA 2208988800ULL
#define NTP_HOST_NAME       "us.pool.ntp.org"
#define NTP_PORT            123

typedef struct NTP_Packet
{
#if __BYTE_ORDER == __BID_ENDIAN
    uint8_t li : 2;
    uint8_t vn : 3;
    uint8_t mode : 3;
#else
    uint8_t mode : 3;
    uint8_t vn : 3;
    uint8_t li : 2;
#endif
    uint8_t stratum;
    uint8_t poll;
    uint8_t precision;
    uint32_t root_delay;
    uint32_t root_dispersion;
    uint32_t ref_id;
    uint32_t ref_timesamp_s;
    uint32_t ref_timesamp_f;
    uint32_t orig_timesamp_s;
    uint32_t orig_timesamp_f;
    uint32_t rx_timesamp_s;
    uint32_t rx_timesamp_f;
    uint32_t tx_timesamp_s;
    uint32_t tx_timesamp_f;
}ntp_packet_t;

struct timeval NTP_Update(void);
double NTP_Difference(void);

#endif
