#include "Reloj.h"

bool actualizarHorario(){
  time_t horarioActual;
  if(ntpCheckTime(horarioActual)){
    return RTC.set(horarioActual);
  }
  return false;
}

bool setearHorario(tmElements_t &horarioActual){
  return RTC.write(horarioActual);
}

bool obtenerHorario(tmElements_t &tm){
  RTC.read(tm);
  return true;
}
