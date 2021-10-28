#include "ntp.h"

void error( char* msg )
{
    perror(msg);
    exit(0);
}

struct timeval NTP_Update(void)
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    ntp_packet_t packet;
    struct timeval ntp_time;
    memset(&packet, 0, sizeof(ntp_packet_t));
    packet.li = 0;
    packet.vn = 3;
    packet.mode = 3;
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    server = gethostbyname(NTP_HOST_NAME);
    if (server == NULL)
    {
        error("ERROR, no such host");
    }
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(NTP_PORT);
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in)) < 0)
    {
        error("ERROR connecting");
    }
    if (write(sockfd, &packet, sizeof(ntp_packet_t)) < 0)
    {
        error("ERROR writing to socket");
    }
    if (read(sockfd, &packet, sizeof(ntp_packet_t)) < 0)
    {
        error("ERROR reading from socket");
    }
    ntp_time.tv_sec = (ntohl(packet.tx_timesamp_s) - NTP_TIMESTAMP_DELTA);
    ntp_time.tv_usec = (ntohl(packet.tx_timesamp_f) / 4295); //translating fraction of seconds in milliseconds
    return ntp_time;
}

double NTP_Difference(void)
{
    struct timeval ntp_time = NTP_Update();
    struct timeval current_time;
    double ntp_time_s = 0.0, current_time_s = 0.0;
    gettimeofday(&current_time, NULL);
    ntp_time_s = ntp_time.tv_sec + ((double)ntp_time.tv_usec / 1000000);
    current_time_s = current_time.tv_sec + ((double)current_time.tv_usec / 1000000);
    return ntp_time_s - current_time_s;
}
