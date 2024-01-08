#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "cabecera.h"

room r;

// PROPORCIONADO POR EL DOCENTE
void CargarCubo() {
  // Inicializaciones cubo
  r.clear();
  r.NewPlanes(6);
  //-- Cuadrado 1 (AZUL) --
  r.p[0].newPoints(4);
  r.p[0].p[0].x = -2.0f;
  r.p[0].p[0].y = 2.0f;
  r.p[0].p[0].z = 2.0f;
  r.p[0].p[1].x = -2.0f;
  r.p[0].p[1].y = -2.0f;
  r.p[0].p[1].z = 2.0f;
  r.p[0].p[2].x = -2.0f;
  r.p[0].p[2].y = -2.0f;
  r.p[0].p[2].z = -2.0f;
  r.p[0].p[3].x = -2.0f;
  r.p[0].p[3].y = 2.0f;
  r.p[0].p[3].z = -2.0f;

  r.p[0].pointGenTriangle(); // Trianguliza
  r.p[0].normalPlane();      // Normal del plano
  r.p[0].obtenerRangos();    // Coloca el rango

  //-- Cuadrado 2 (NARANJA) --
  r.p[1].newPoints(4);
  r.p[1].p[0].x = 2.0f;
  r.p[1].p[0].y = 2.0f;
  r.p[1].p[0].z = 2.0f;
  r.p[1].p[1].x = 2.0f;
  r.p[1].p[1].y = 2.0f;
  r.p[1].p[1].z = -2.0f;
  r.p[1].p[2].x = 2.0f;
  r.p[1].p[2].y = -2.0f;
  r.p[1].p[2].z = -2.0f;
  r.p[1].p[3].x = 2.0f;
  r.p[1].p[3].y = -2.0f;
  r.p[1].p[3].z = 2.0f;

  r.p[1].pointGenTriangle();
  r.p[1].normalPlane();
  r.p[1].obtenerRangos();

  //-- Cuadrado 3 (VERDE) --
  r.p[2].newPoints(4);
  r.p[2].p[0].x = -2.0f;
  r.p[2].p[0].y = -2.0f;
  r.p[2].p[0].z = 2.0f;
  r.p[2].p[1].x = 2.0f;
  r.p[2].p[1].y = -2.0f;
  r.p[2].p[1].z = 2.0f;
  r.p[2].p[2].x = 2.0f;
  r.p[2].p[2].y = -2.0f;
  r.p[2].p[2].z = -2.0f;
  r.p[2].p[3].x = -2.0f;
  r.p[2].p[3].y = -2.0f;
  r.p[2].p[3].z = -2.0f;

  r.p[2].pointGenTriangle();
  r.p[2].normalPlane();
  r.p[2].obtenerRangos();

  //-- Cuadrado 4 (MORADO) --
  r.p[3].newPoints(4);
  r.p[3].p[0].x = 2.0f;
  r.p[3].p[0].y = 2.0f;
  r.p[3].p[0].z = 2.0f;
  r.p[3].p[1].x = -2.0f;
  r.p[3].p[1].y = 2.0f;
  r.p[3].p[1].z = 2.0f;
  r.p[3].p[2].x = -2.0f;
  r.p[3].p[2].y = 2.0f;
  r.p[3].p[2].z = -2.0f;
  r.p[3].p[3].x = 2.0f;
  r.p[3].p[3].y = 2.0f;
  r.p[3].p[3].z = -2.0f;

  r.p[3].pointGenTriangle();
  r.p[3].normalPlane();
  r.p[3].obtenerRangos();

  //-- Cuadrado 5 (AMARILLO) --
  r.p[4].newPoints(4);
  r.p[4].p[0].x = -2.0f;
  r.p[4].p[0].y = -2.0f;
  r.p[4].p[0].z = 2.0f;
  r.p[4].p[1].x = -2.0f;
  r.p[4].p[1].y = 2.0f;
  r.p[4].p[1].z = 2.0f;
  r.p[4].p[2].x = 2.0f;
  r.p[4].p[2].y = 2.0f;
  r.p[4].p[2].z = 2.0f;
  r.p[4].p[3].x = 2.0f;
  r.p[4].p[3].y = -2.0f;
  r.p[4].p[3].z = 2.0f;

  r.p[4].pointGenTriangle();
  r.p[4].normalPlane();
  r.p[4].obtenerRangos();

  //-- Cuadrado 6 (NEGRO) --
  r.p[5].newPoints(4);
  r.p[5].p[0].x = -2.0f;
  r.p[5].p[0].y = 2.0f;
  r.p[5].p[0].z = -2.0f;
  r.p[5].p[1].x = -2.0f;
  r.p[5].p[1].y = -2.0f;
  r.p[5].p[1].z = -2.0f;
  r.p[5].p[2].x = 2.0f;
  r.p[5].p[2].y = -2.0f;
  r.p[5].p[2].z = -2.0f;
  r.p[5].p[3].x = 2.0f;
  r.p[5].p[3].y = 2.0f;
  r.p[5].p[3].z = -2.0f;

  r.p[5].pointGenTriangle();
  r.p[5].normalPlane();
  r.p[5].obtenerRangos();
};

void printResults(const reflection *datos, int NRays) {
  printf("\n\n***      Datos obtenidos durante el movimiento      ***\n");
  for (int i = 0; i < NRays; i++) {
    printf("->%s\n", datos[i].lost ? "Se pierde" : "No se pierde");
    printf("->Número de reflexiones: %d\n", datos[i].timesReflection);
    for (int j = 0; j < datos[i].timesReflection + 1; j++) {
      printf("\nChoque[%d]\n", j);
      printf("Punto: (%f, %f, %f)\n", datos[i].puntos[j].x,
             datos[i].puntos[j].y, datos[i].puntos[j].z);
      printf("Vi: (%f, %f, %f)\n", datos[i].viRays[j].x, datos[i].viRays[j].y,
             datos[i].viRays[j].z);
      printf("Plano de Choque: %d\n", (datos[i].planes[j] + 1));
      printf("Energia Actual: %f\n", datos[i].energyCurrent[j]);
    }
  }
}

int main(int argc, char const *argv[]) {
  CargarCubo();

  source fuente;
  fuente.p.assign(-3, 0, 0); // Punto
  fuente.createRay(2, 1, 0); // Rayo
  fuente.changeEnergy(1000);

  r.NewSource(fuente); // Agrega la fuente al room

  printf("Punto de origen: (%f, %f, %f)\n", r.s.p.x, r.s.p.y, r.s.p.z);
  printf("Dirección del rayo: (%f, %f, %f)\n", r.s.Rays[0].x, r.s.Rays[0].y,
         r.s.Rays[0].z);

  reflection *datos = r.rayTracing(); // Trazado de rayos
  printResults(datos, r.s.NRAYS);     // Resultados

  return 0;
}
