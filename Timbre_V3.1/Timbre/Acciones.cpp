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
  String respuesta = "";
  if(indice >= obtenerCantidadHorarios()){
    resetearUltimoLeido();
    return "FIN";
  }
  sumarUltimoLeido();
  respuesta.concat(obtenerHora(indice));
  respuesta.concat(":");
  respuesta.concat(obtenerMinutos(indice));
  if(esLargo(indice)){
    respuesta.concat(":L:");
  }else{
    respuesta.concat(":C:");
  }
  respuesta.concat(obtenerSilencios(indice));
  return respuesta;
}

String configurarHoraActual(String horario){
  if(horario[0]=='A'){
    seActualizoElHorario(10);
    return "OK AUTO";
  }
  tmElements_t horaActual;
  horaActual.Hour = horario.substring(0, horario.indexOf(':')).toInt();
  horaActual.Minute = horario.substring(horario.indexOf(':')+1, horario.indexOf(':')+3).toInt();
  horaActual.Wday = horario.substring(horario.indexOf(':')+4).toInt();;
  horaActual.Second = 0;
  setearHorario(horaActual);
  seActualizoElHorario(horaActual.Wday);
  return "OK";
}

String obtenerHoraActual(String nada){
  String respuesta = "";
  tmElements_t horaActual;
  obtenerHorario(horaActual);
  respuesta.concat(horaActual.Hour);
  respuesta.concat(":");
  respuesta.concat(horaActual.Minute);
  respuesta.concat(":");
  respuesta.concat(horaActual.Wday);
  return respuesta;
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
  return String(obtenerDuracionLarga()) + "/" + String(obtenerDuracionCorta());
}

String configurarSilencios(String data){
  byte indice = data.substring(0,data.indexOf(':')).toInt();
  byte cantidad = data.substring(data.indexOf(':')+1).toInt();
  if(!setearSilencios(indice, cantidad)){return "FALLO";}
  return "OK";
}

String resetearDispositivo(String nada){
  restaurarDeFabrica();
  return "OK;";
}
