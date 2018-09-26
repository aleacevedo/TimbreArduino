#include "Memoria.h"
#include "Reloj.h"


class Funcion{
  public:
    Funcion(String (*funcion)());
    String ejecutar(String cadena);

  private:
    String (*callback)(String cadena);
};
