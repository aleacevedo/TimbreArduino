 #include <UIPEthernet.h>
#include <Time.h>
#include <TimeLib.h>
#include <EEPROM.h>
#include <stdint.h>

#include "Reloj.h"
#include "Memoria.h"
#include "Acciones.h"

#define DEBUG 1
#define CANT_ACCIONES 13

static Funcion acciones[] = {Funcion(agregarUnHorario), Funcion(borrarUnHorario), Funcion(obtenerUnHorario), Funcion(configurarHoraActual), Funcion(obtenerHoraActual), Funcion(configurarModoVacaciones), Funcion(obtenerModoVacaciones), Funcion(configurarDiasLibres), Funcion(obtenerDiasLibres), Funcion(configurarDuracion), Funcion(obtenerDuracion), Funcion(configurarSilencios), Funcion(resetearDispositivo)};
static String comandos[] = {"A+", "A-", "A?", "HS", "H?", "VS", "V?", "LS", "L?", "DS", "D?", "SS", "RE"};

//REST Server
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xBB};
IPAddress ip(192, 168, 0, 178); 
EthernetServer server = EthernetServer(35);

tmElements_t horaActual;

void setup() {
  // put Ayour setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(8, INPUT);
  inicializarEthernet();
  seActualizoElHorario(10);
  if(DEBUG){Serial.begin(9600);}
  if(DEBUG){Serial.println(F("Inicializo"));}
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(8) == 1 && huboCorteDeLuz()) {
    volvioLaLuz();
    if(DEBUG){Serial.println(F("VOLVIO LA LUZ"));}
    inicializarEthernet();
  }

  if(digitalRead(8) == 0 && !huboCorteDeLuz()){
    seCortoLaLuz();
    if(DEBUG){Serial.println(F("SE CORTO LA LUZ"));}
  }

  obtenerHorario(horaActual);
  if(!estaActualizadoElHorario(horaActual.Wday)){
    if(DEBUG){Serial.println(F("ACTUALIZACION DIARIA DE HORARIO"));}
    actualizarHorario();
    seActualizoElHorario(horaActual.Wday);
  }

  if(!estaEnVacaciones() && !estaLibre(horaActual.Wday)){
    for(byte i = 0; i<obtenerCantidadHorarios(); i++){
      if(obtenerHora(i) != obtenerHoraUltimaActivacion() || obtenerMinutos(i) != obtenerMinutoUltimaActivacion() || horaActual.Wday != obtenerDiaUltimaActivacion()){
        if(obtenerHora(i) == horaActual.Hour && obtenerMinutos(i) == horaActual.Minute){
          setearUltimaActivacion(obtenerHora(i), obtenerMinutos(i), horaActual.Wday);
          if(obtenerSilencios(i)==0){
            sonarAlarma(esLargo(i));
          }else if(obtenerSilencios(i)==255){
          }else{
            restarSilencios(i);
          }
        }
      }
    }
  }
 buscarCliente();
}

void sonarAlarma(byte duracion){
  if(DEBUG){Serial.println(F("ALARMA"));}
  digitalWrite(2, HIGH);
  if(duracion == 0){
    delay(obtenerDuracionCorta() * 1000);
  }else{
    delay(obtenerDuracionLarga() * 1000);
  }
 digitalWrite(2,LOW);
}

void buscarCliente(){
  size_t size;
  if (EthernetClient client = server.available()){
    while((size = client.available()) > 0){
      char msg[size];
      size = client.read(msg,size);
      msg[size-1] = '\0';
      //msg = msg+2;
      if(DEBUG){testRest(&String(msg));}
      client.println(realizarAccion(&String(msg)));
      client.flush();
      //free(msg);
    }
  }
}

String realizarAccion(String* mensaje){
  String accion = mensaje->substring(0,mensaje->indexOf('/'));
  if(DEBUG){
    Serial.print(F("Accion: "));
    Serial.println(accion);
  }
  *mensaje = mensaje->substring(mensaje->indexOf('/') + 1);
  if(DEBUG){
    Serial.print(F("Mensaje: "));
    Serial.println(*mensaje);
  }
  for(size_t i = 0; i<CANT_ACCIONES; i++){
    if(comandos[i].equals(accion)){
      if(DEBUG){
        Serial.print(F("Numero de comando: "));
        Serial.println(i);
      }
      *mensaje = acciones[i].ejecutar(*mensaje);
      return *mensaje;
    }
  }
  return String("ERROR DE COMANDO");
}

int testRest(String* msg){
  //VectorDinamico cadena = VectorDinamico();
  Serial.println(F("Esta es una funcion de prueba"));
  Serial.print(F("Se ha recibido la siguiente linea: "));
  Serial.println(*msg);
}

void inicializarEthernet(){
  Ethernet.begin(mac, ip);
  server.begin();
}
