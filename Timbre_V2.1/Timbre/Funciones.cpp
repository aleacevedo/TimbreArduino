#include "Funciones.h"

Funcion::Funcion(String (*funcion)()){
  callback = funcion;
}

String Funcion::ejecutar(String cadena){
  return callback(cadena);
}
