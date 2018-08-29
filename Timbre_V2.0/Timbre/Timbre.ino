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
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF};
IPAddress ip(192, 168, 0, 199); 
EthernetServer server = EthernetServer(35);

tmElements_t horaActual;
byte horaUltimaAlarma = 0;
byte minutoUltimaAlarma = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(8, INPUT);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  actualizarHorario();
  if(DEBUG){Serial.println(F("Inicializo"));}
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(8) == 1 && huboCorteDeLuz()) {
    volvioLaLuz();
    Ethernet.begin(mac, ip);
  }

  if(digitalRead(8) == 0 && !huboCorteDeLuz()){
    seCortoLaLuz();
  }

  obtenerHorario(horaActual);
  if(!estaActualizadoElHorario(horaActual.Wday)){
    actualizarHorario();
    seActualizoElHorario(horaActual.Wday);
  }

  if(!estaEnVacaciones() && !estaLibre(horaActual.Wday)){
    for(byte i = 0; i<obtenerCantidadHorarios(); i++){
      if(obtenerHora(i) != horaUltimaAlarma && obtenerMinutos(i) != minutoUltimaAlarma){
        if(obtenerHora(i) == horaActual.Hour && obtenerMinutos(i) == horaActual.Minute){
          horaUltimaAlarma = obtenerHora(i);
          minutoUltimaAlarma = obtenerMinutos(i);
          if(obtenerSilencios(i)==0){
            sonarAlarma(esLargo(i));
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
      char* msg = (char*)malloc(size);
      size = client.read(msg,size);
      if(DEBUG){testRest(&String(msg));}
      client.println(realizarAccion(&String(msg)));
      client.flush();
      free(msg);
    }
  }
}

String realizarAccion(String* mensaje){
  String accion = mensaje->substring(0,mensaje->indexOf('/'));
  if(DEBUG){Serial.println(accion);}
  *mensaje = mensaje->substring(mensaje->indexOf('/') + 1);
  if(DEBUG){Serial.println(*mensaje);}
  for(size_t i = 0; i<CANT_ACCIONES; i++){
    if(comandos[i].equals(accion)){
      if(DEBUG){Serial.println(i);}
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
