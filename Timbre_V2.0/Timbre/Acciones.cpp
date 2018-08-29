#include "Acciones.h"
 
String agregarUnHorario(String horario){
  byte hora = horario.substring(0, horario.indexOf(':')).toInt();
  horario = horario.substring(horario.indexOf(':')+1);
  byte minutos = horario.substring(0, horario.indexOf(':')).toInt();
  bool tipo = horario.indexOf('L') != -1;
  if(!agregarHorario(hora, minutos, tipo)){return "FALLO";}
  return "OK";
}

String borrarUnHorario(String indice){
  if(!borrarHorario(indice.toInt())){return "FALLO";}
  return "OK";
}

String obtenerUnHorario(String nada){
  byte indice = obtenerUltimoLeido();
  if(indice == obtenerCantidadHorarios()){
    resetearUltimoLeido();
    return "FIN";
  }
  sumarUltimoLeido();
  if(esLargo(indice)){
    return String(obtenerHora(indice)) + ":" + String(obtenerMinutos(indice)) + ":L:" + String(obtenerSilencios(indice));
  }else{
    return String(obtenerHora(indice)) + ":" + String(obtenerMinutos(indice)) + ":C:" + String(obtenerSilencios(indice));
  }
}

String configurarHoraActual(String horario){
  tmElements_t horaActual;
  if(horario.equals("AUTO")){
    if(!actualizarHorario()){return "FALLO";}
    return "OK";
  }
  byte hora = horario.substring(0, horario.indexOf(':')).toInt();
  byte minutos = horario.substring(horario.indexOf(':')+1).toInt();
  horaActual.Hour = hora;
  horaActual.Minute = minutos;
  horaActual.Second = 0;
  setearHorario(horaActual);
  return "OK";
}

String obtenerHoraActual(String nada){
  tmElements_t horaActual;
  obtenerHorario(horaActual);
  return String(horaActual.Hour) + ":" + String(horaActual.Minute);
}

String obtenerModoVacaciones(String nada){
  if(estaEnVacaciones()){
    return "On";
  }
  else{
    return "Off";
  }
}

String configurarModoVacaciones(String nada){
  if(estaEnVacaciones()){dessetearModoVacaciones();}
  else{ setearModoVacaciones();}
  return "OK";
}

String configurarDiasLibres(String dias){
  for(byte i = 0; i < 8; i++){
    if(dias.indexOf(String(i))==-1){
      desmarcarDiaLibre(i);
    }else{
      marcarDiaLibre(i);
    }
  }
  return ("OK");
}

String obtenerDiasLibres(String nada){
  String respuesta = "";
  for(int i = 1; i < 8; i++ ){
    if(estaLibre(i)){
      respuesta = respuesta + String(i);
    }
  }
  return respuesta;
}

String configurarDuracion(String duracion){
  byte largo = duracion.substring(0,duracion.indexOf(':')).toInt();
  byte corto = duracion.substring(duracion.indexOf(':')+1).toInt();
  setearDuracionCorta(corto);
  setearDuracionLarga(largo);
  return "OK";
}

String obtenerDuracion(String nada){
  return "L:" + String(obtenerDuracionLarga()) + "/L:" + String(obtenerDuracionCorta());
}

String configurarSilencios(String data){
  byte indice = data.substring(0,data.indexOf(':')).toInt();
  byte cantidad = data.substring(data.indexOf(':')).toInt();
  setearSilencios(indice, cantidad);
  return "OK";
}

String resetearDispositivo(String nada){
  restaurarDeFabrica();
  return "OK;";
}
