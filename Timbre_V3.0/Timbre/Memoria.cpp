#include "Memoria.h"

byte obtenerCantidadHorarios(){
  // Devuelven la cantidad de horarios guardados en memoria EEPROM que posee el timbre MAX 64 direcciones (O a 255). Esta informacion se encunetra en la direccion 256.
  return EEPROM.read(CANT_HORARIOS);
}

byte obtenerProximaPosicion(){
  // Devuelve la proxima posicion donde se guardara el nuevo horario
  return (byte)(obtenerCantidadHorarios() * 4);
}

byte obtenerPosicion(byte indice){
  // Devuelve la direccion en la EEPROM a partir del indice
  return indice*4;
}

byte obtenerHora(byte indice){
  return EEPROM.read(obtenerPosicion(indice)+POS_HORA);
}

byte obtenerMinutos(byte indice){
  return EEPROM.read(obtenerPosicion(indice)+POS_MINUTOS);
}

byte esLargo(byte indice){
  return EEPROM.read(obtenerPosicion(indice)+POS_DURACION);
}

byte obtenerSilencios(byte indice){
  return EEPROM.read(obtenerPosicion(indice)+POS_SILENCIOS);
}

byte obtenerDuracionCorta(){
  return EEPROM.read(DURACION_CORTA);
}

byte obtenerDuracionLarga(){
  return EEPROM.read(DURACION_LARGA);
}

byte obtenerUltimoLeido(){
  return EEPROM.read(ULTIMO_LEIDO);
}

byte obtenerHoraUltimaActivacion(){
  return EEPROM.read(ULTIMA_ACTIVACION);
}

byte obtenerMinutoUltimaActivacion(){
  return EEPROM.read(ULTIMA_ACTIVACION+1);
}

byte obtenerDiaUltimaActivacion(){
  return EEPROM.read(ULTIMA_ACTIVACION+2);
}

void sumarCantidadHorarios(){
  // Aumenta en uno la cantidad de horarios
  EEPROM.write(CANT_HORARIOS, obtenerCantidadHorarios()+1);
}

void restarCantidadHorarios(){
  // Resta en uno la cantidad de horarios
  EEPROM.write(CANT_HORARIOS, obtenerCantidadHorarios()-1);
}

void setearDuracionCorta(byte duracion){
  EEPROM.write(DURACION_CORTA, duracion);
}

void setearDuracionLarga(byte duracion){
  EEPROM.write(DURACION_LARGA, duracion);
}

void seActualizoElHorario(byte dia){
  EEPROM.write(ACTUALIZACION_HORARIO, dia);
}

void sumarUltimoLeido(){
  EEPROM.write(ULTIMO_LEIDO, obtenerUltimoLeido()+1);
}

void resetearUltimoLeido(){
  EEPROM.write(ULTIMO_LEIDO, 0);
}

void setearUltimaActivacion(byte hora, byte minuto, byte dia){
  EEPROM.write(ULTIMA_ACTIVACION, hora);
  EEPROM.write(ULTIMA_ACTIVACION+1, minuto);
  EEPROM.write(ULTIMA_ACTIVACION+2, dia);
}

bool agregarHorario(byte hora, byte minutos, byte duracion){
  // Guarda en la memoria EEPROM el nuevo horario
  if(obtenerCantidadHorarios()>=MAXIMA_CANTIDAD_HORARIOS){
    return false;
  }
  EEPROM.write(obtenerProximaPosicion()+POS_HORA, hora);
  EEPROM.write(obtenerProximaPosicion()+POS_MINUTOS, minutos);
  EEPROM.write(obtenerProximaPosicion()+POS_DURACION, duracion);
  EEPROM.write(obtenerProximaPosicion()+POS_SILENCIOS, 0);
  sumarCantidadHorarios();
  return true;
}

bool setearSilencios(byte indice, byte dias){
  if(indice>=obtenerCantidadHorarios()  || dias<0){
    return false;
  }
  EEPROM.write(obtenerPosicion(indice)+POS_SILENCIOS, dias);
  return true;
}

bool restarSilencios(byte indice){
  return setearSilencios(indice, obtenerSilencios(indice)-1);
}

bool borrarHorario(byte indice){
  // Se borrara el timbre que se encuentre en la posicion del indice
  if(indice>=obtenerCantidadHorarios()){
    return false;
  }
  for(indice; indice <= obtenerCantidadHorarios(); indice++){
    EEPROM.write(obtenerPosicion(indice)+POS_HORA, obtenerHora(indice+1));
    EEPROM.write(obtenerPosicion(indice)+POS_MINUTOS, obtenerMinutos(indice+1));
    EEPROM.write(obtenerPosicion(indice)+POS_DURACION, esLargo(indice+1));
    EEPROM.write(obtenerPosicion(indice)+POS_SILENCIOS, obtenerSilencios(indice+1));
  }
  restarCantidadHorarios();
  return true;
}

bool estaLibre(byte dia){
  //Devuelve true si el dia esta libre false en caso contrario
  return EEPROM.read(DIAS_LIBRES+dia);
}

bool marcarDiaLibre(byte dia){
  //Devuelve true si lo marc,o devuelve false si ya estaba marcado
  if(estaLibre(dia)){
    return false;
  }
  EEPROM.write(DIAS_LIBRES+dia, true);
}

bool desmarcarDiaLibre(byte dia){
  //Devuelve true si lo desmarco, devuelve false si ya estaba desmarcado
  if(!estaLibre(dia)){
    return false;
  }
  EEPROM.write(DIAS_LIBRES+dia, false);
}

bool setearModoVacaciones(){
  if(estaEnVacaciones()){
    return false;
  }
  EEPROM.write(MODO_VACACIONES, true);
  return true;
}

bool dessetearModoVacaciones(){
  if(!estaEnVacaciones()){
    return false;
  }
  EEPROM.write(MODO_VACACIONES, false);
  return true;
}

bool estaEnVacaciones(){
  return EEPROM.read(MODO_VACACIONES);
}

void restaurarDeFabrica(){
  for(int i = 0; i<=256; i++){
    EEPROM.write(i,255);
  }
  for(byte i = 0; i<=7; i++){
    desmarcarDiaLibre(i);
  }
  EEPROM.write(CANT_HORARIOS, 0);
  resetearUltimoLeido();
  dessetearModoVacaciones();
  volvioLaLuz();
  setearDuracionCorta(4);
  setearDuracionLarga(8);
}

bool huboCorteDeLuz(){
  return EEPROM.read(CORTE_LUZ);
}

bool seCortoLaLuz(){
  if(huboCorteDeLuz()){
    return false;
  }
  EEPROM.write(CORTE_LUZ, true);
  return true;
}

bool volvioLaLuz(){
  if(!huboCorteDeLuz()){
    return false;
  }
  EEPROM.write(CORTE_LUZ, false);
  return true;
}

bool estaActualizadoElHorario(byte dia){
  return dia == EEPROM.read(ACTUALIZACION_HORARIO);
}
