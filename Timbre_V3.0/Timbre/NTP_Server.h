#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dhcp.h>
#include <EthernetServer.h>
#include <Dns.h>
#include <EthernetUdp.h>

//#include <UIPEthernet.h>

#include <Time.h>
#include <TimeLib.h>

#define TIME_ZONE -3

bool ntpCheckTime (time_t &tm);
