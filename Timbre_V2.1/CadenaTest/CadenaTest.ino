#include "Funciones.h"

//Funcion funciones[] = {Funcion(print_1), Funcion(print_2)};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //funciones[0].ejecutar()
  Funcion funciones[] = {Funcion(print_1), Funcion(print_2)};
  Serial.println((int)funciones[0].ejecutar(7));
  funciones[1].ejecutar(0);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int print_1(int i){
  Serial.println("Hola yo soy print 1");
  return i;
}


void print_2(){
  Serial.println("Hola yo soy print 2");
}


void print_3(){
  Serial.println("Hola yo soy print 3");
}


void print_4(){
  Serial.println("Hola yo soy print 4");
}

void ejecutarFuncion(int (*funcion)()){
  funcion();
}

