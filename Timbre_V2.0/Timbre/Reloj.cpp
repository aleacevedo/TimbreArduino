#include "Reloj.h"

bool actualizarHorario(){
  tmElements_t horarioActual;
  if(ntpCheckTime(horarioActual)){
    return RTC.write(horarioActual);
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
