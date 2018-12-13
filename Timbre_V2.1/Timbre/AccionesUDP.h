#include <UIPEthernet.h>
#include <Time.h>
#include <TimeLib.h>

#define TIME_ZONE -3
#define LOCAL_PORT 8080
#define BROADCAST_PORT 21027

bool ntpCheckTime (time_t &tm);
void annoucmentUdp(IPAddress ip);
void setUdp();
