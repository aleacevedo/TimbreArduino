#include <EEPROM.h>

#define byte uint8_t

#define CANT_HORARIOS 256 //Direecion donde se encuentran la cantidad de horarios guardados
#define POS_HORA 0 //Posicion de la hora con respecto a la posicion del horarios
#define POS_MINUTOS 1 //Posicion de los minutos con respecto a la posicion del horarios
#define POS_DURACION 2 //Posicion de la duracion con respecto a la posicion del horarios
#define POS_SILENCIOS 3 //Posicion de la cantidad de silencios con respecto a la posicion del horarios
#define MAXIMA_CANTIDAD_HORARIOS 255
#define DIAS_LIBRES 257 //Direccion a partir de la que encontramos los dias libres
#define DURACION_CORTA 270 //Direccion donde se encuentra la duracion de los horarios cortos
#define DURACION_LARGA 271 //Direccion donde se encuentra la duracion de los horarios largos
#define MODO_VACACIONES 275 //Direccion donde se encuentra el estado del modo vacaciones
#define CORTE_LUZ 276 //Direccion donde se encuentra el estado de la luz
#define ACTUALIZACION_HORARIO 277 //Direccion donde se encuentra el ultimo dia en el que se actualizo el horario
#define ULTIMO_LEIDO 279 // Direccion donde se encuentra el indice del ultimo horario leido
#define ULTIMA_ACTIVACION 280 // Direccion donde se encuentra la informacion de la ultima activacion del timbre


byte obtenerCantidadHorarios();
byte obtenerProximaPosicion();
byte obtenerHora(byte indice);
byte obtenerMinutos(byte indice);
byte esLargo(byte indice);
byte obtenerSilencios(byte indice);
byte obtenerPosicion(byte indice);
byte obtenerDuracionLarga();
byte obtenerDuracionCorta();
byte obtenerUltimoLeido();
byte obtenerHoraUltimaActivacion();
byte obtenerMinutoUltimaActivacion();
byte obtenerDiaUltimaActivacion();
void sumarCantidadHorarios();
void restarCantidadHorarios();
void setearDuracionLarga(byte duracion);
void setearDuracionCorta(byte duracion);
void restaurarDeFabrica();
void seActualizoElHorario(byte dia);
void sumarUltimoLeido();
void resetearUltimoLeido();
void setearUltimaActivacion(byte hora, byte minuto, byte dia);
bool agregarHorario(byte hora, byte minutos, byte duracion);
bool setearSilencios(byte indice, byte dias);
bool restarSilencios(byte indice);
bool borrarHorario(byte indice);
bool marcarDiaLibre(byte dia);
bool desmarcarDiaLibre(byte dia);
bool estaLibre(byte dia);
bool setearModoVacaciones();
bool dessetearModoVacaciones();
bool estaEnVacaciones();
bool seCortoLaLuz();
bool volvioLaLuz();
bool huboCorteDeLuz();
bool estaActualizadoElHorario(byte dia);
