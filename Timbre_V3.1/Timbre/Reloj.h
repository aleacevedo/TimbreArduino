#include "AccionesUDP.h"
#include <DS1307RTC.h>
#include <Time.h>
#include <TimeLib.h>

bool actualizarHorario();
bool setearHorario(tmElements_t &tm);
bool obtenerHorario(tmElements_t &tm);
