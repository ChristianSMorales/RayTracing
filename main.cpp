#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "cabecera.h"

int main(int argc, char const *argv[]) {
  source fuente;
  fuente.p.assign(-3, 0, 0); // Punto
  fuente.createRay(2, 1, 0); // Rayo
  fuente.changeEnergy(1000);
  fuente.NRAYS = 10;
  printf("Datos de la fuente:(Posicion inicial: %f\nNumero de rayos de la fuente: %f\n Densidad de rayos: %f\nEnergia inicial: %f",
    fuente.p,
    fuente.eF,
    fuente.NRAYS,
    fuente.Rays,
    );
  return 0;
}
