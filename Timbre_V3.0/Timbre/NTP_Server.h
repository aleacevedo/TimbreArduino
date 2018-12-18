
#include <Time.h>
#include <TimeLib.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

#define TIME_ZONE -3
#define LOCAL_PORT 8080

bool ntpCheckTime (time_t &tm);
void setUdp();
