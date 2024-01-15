#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "cabecera.h"

Room room;

// PROPORCIONADO POR EL DOCENTE
void CargarCubo()
{
  // Inicializaciones cubo
  room.clear();
  room.newPlanes(6);
  // Left Plane
  room.planePointer[0].newPoints(4);
  room.planePointer[0].planePointer[0].x = -2.0f;
  room.planePointer[0].planePointer[0].y = 2.0f;
  room.planePointer[0].planePointer[0].z = 2.0f;
  room.planePointer[0].planePointer[1].x = -2.0f;
  room.planePointer[0].planePointer[1].y = -2.0f;
  room.planePointer[0].planePointer[1].z = 2.0f;
  room.planePointer[0].planePointer[2].x = -2.0f;
  room.planePointer[0].planePointer[2].y = -2.0f;
  room.planePointer[0].planePointer[2].z = -2.0f;
  room.planePointer[0].planePointer[3].x = -2.0f;
  room.planePointer[0].planePointer[3].y = 2.0f;
  room.planePointer[0].planePointer[3].z = -2.0f;

  room.planePointer[0].pointGenTriangle(); // Trianguliza
  room.planePointer[0].normalPlane();      // Normal del plano
  room.planePointer[0].obtenerRangos();    // Coloca el rango


  // Right Plane
  room.planePointer[1].newPoints(4);
  room.planePointer[1].planePointer[0].x = 2.0f;
  room.planePointer[1].planePointer[0].y = 2.0f;
  room.planePointer[1].planePointer[0].z = 2.0f;
  room.planePointer[1].planePointer[1].x = 2.0f;
  room.planePointer[1].planePointer[1].y = 2.0f;
  room.planePointer[1].planePointer[1].z = -2.0f;
  room.planePointer[1].planePointer[2].x = 2.0f;
  room.planePointer[1].planePointer[2].y = -2.0f;
  room.planePointer[1].planePointer[2].z = -2.0f;
  room.planePointer[1].planePointer[3].x = 2.0f;
  room.planePointer[1].planePointer[3].y = -2.0f;
  room.planePointer[1].planePointer[3].z = 2.0f;

  room.planePointer[1].pointGenTriangle();
  room.planePointer[1].normalPlane();
  room.planePointer[1].obtenerRangos();

  // Down Plane
  room.planePointer[2].newPoints(4);
  room.planePointer[2].planePointer[0].x = -2.0f;
  room.planePointer[2].planePointer[0].y = -2.0f;
  room.planePointer[2].planePointer[0].z = 2.0f;
  room.planePointer[2].planePointer[1].x = 2.0f;
  room.planePointer[2].planePointer[1].y = -2.0f;
  room.planePointer[2].planePointer[1].z = 2.0f;
  room.planePointer[2].planePointer[2].x = 2.0f;
  room.planePointer[2].planePointer[2].y = -2.0f;
  room.planePointer[2].planePointer[2].z = -2.0f;
  room.planePointer[2].planePointer[3].x = -2.0f;
  room.planePointer[2].planePointer[3].y = -2.0f;
  room.planePointer[2].planePointer[3].z = -2.0f;

  room.planePointer[2].pointGenTriangle();
  room.planePointer[2].normalPlane();
  room.planePointer[2].obtenerRangos();

  // Up Plane
  room.planePointer[3].newPoints(4);
  room.planePointer[3].planePointer[0].x = 2.0f;
  room.planePointer[3].planePointer[0].y = 2.0f;
  room.planePointer[3].planePointer[0].z = 2.0f;
  room.planePointer[3].planePointer[1].x = -2.0f;
  room.planePointer[3].planePointer[1].y = 2.0f;
  room.planePointer[3].planePointer[1].z = 2.0f;
  room.planePointer[3].planePointer[2].x = -2.0f;
  room.planePointer[3].planePointer[2].y = 2.0f;
  room.planePointer[3].planePointer[2].z = -2.0f;
  room.planePointer[3].planePointer[3].x = 2.0f;
  room.planePointer[3].planePointer[3].y = 2.0f;
  room.planePointer[3].planePointer[3].z = -2.0f;

  room.planePointer[3].pointGenTriangle();
  room.planePointer[3].normalPlane();
  room.planePointer[3].obtenerRangos();

  // Front Plane
  room.planePointer[4].newPoints(4);
  room.planePointer[4].planePointer[0].x = -2.0f;
  room.planePointer[4].planePointer[0].y = -2.0f;
  room.planePointer[4].planePointer[0].z = 2.0f;
  room.planePointer[4].planePointer[1].x = -2.0f;
  room.planePointer[4].planePointer[1].y = 2.0f;
  room.planePointer[4].planePointer[1].z = 2.0f;
  room.planePointer[4].planePointer[2].x = 2.0f;
  room.planePointer[4].planePointer[2].y = 2.0f;
  room.planePointer[4].planePointer[2].z = 2.0f;
  room.planePointer[4].planePointer[3].x = 2.0f;
  room.planePointer[4].planePointer[3].y = -2.0f;
  room.planePointer[4].planePointer[3].z = 2.0f;

  room.planePointer[4].pointGenTriangle();
  room.planePointer[4].normalPlane();
  room.planePointer[4].obtenerRangos();

  // Back Plane
  room.planePointer[5].newPoints(4);
  room.planePointer[5].planePointer[0].x = -2.0f;
  room.planePointer[5].planePointer[0].y = 2.0f;
  room.planePointer[5].planePointer[0].z = -2.0f;
  room.planePointer[5].planePointer[1].x = -2.0f;
  room.planePointer[5].planePointer[1].y = -2.0f;
  room.planePointer[5].planePointer[1].z = -2.0f;
  room.planePointer[5].planePointer[2].x = 2.0f;
  room.planePointer[5].planePointer[2].y = -2.0f;
  room.planePointer[5].planePointer[2].z = -2.0f;
  room.planePointer[5].planePointer[3].x = 2.0f;
  room.planePointer[5].planePointer[3].y = 2.0f;
  room.planePointer[5].planePointer[3].z = -2.0f;

  room.planePointer[5].pointGenTriangle();
  room.planePointer[5].normalPlane();
  room.planePointer[5].obtenerRangos();

  room.toStringPlanes();

};

void printResults(const reflection *datos, int NRays)
{
  printf("\n\n***Datos obtenidos durante el movimiento      ***\n");
  for (int i = 0; i < NRays; i++)
  {
    printf("%s\n", datos[i].lost ? "Se pierde" : "No se pierde");
    printf("Número de reflexiones: %d\n", datos[i].timesReflection);
    for (int j = 0; j < datos[i].timesReflection + 1; j++)
    {
      printf("\nChoque[%d]\n", j);
      printf("Punto: (%f, %f, %f)\n", datos[i].puntos[j].x,
             datos[i].puntos[j].y, datos[i].puntos[j].z);
      printf("Vi: (%f, %f, %f)\n", datos[i].vectorIncidenteRays[j].x, datos[i].vectorIncidenteRays[j].y,
             datos[i].vectorIncidenteRays[j].z);
      printf("Plano de Choque: %d\n", (datos[i].planes[j]));
      printf("Energia Actual: %f\n", datos[i].energyCurrent[j]);
    }
  }
}

int main(int argc, char const *argv[])
{
  CargarCubo();

  Source fuente;
  fuente.initPoint.assign(0, 0, 0);  // Punto

  //fuente.createRay(1, 0, -0.5); // Rayo
  fuente.createRays(12);
  fuente.changeEnergy(1000);

  room.NewSource(fuente); // Agrega la fuente al room

  //printf("Punto de origen: (%f, %f, %f)\n", r.s.p.x, r.s.p.y, r.s.p.z);
  //printf("Dirección del rayo: (%f, %f, %f)\n", r.s.Rays[0].x, r.s.Rays[0].y, r.s.Rays[0].z);

  printf("\n");
  for(int i=0; i<12; i++){
    printf("\nDireccion del rayo [%i]: (%f, %f, %f)\n",i+1, room.source.rays[i].x, room.source.rays[i].y, room.source.rays[i].z);
    reflection *datos = room.rayTracing(room.source.rays[i]);
    printf("--------------------------------------------------------------------------------------------\n");

  }


  //reflection *datos = r.rayTracing(); // Trazado de rayos
  //printResults(datos, r.s.NRAYS);     // Resultados

  return 0;
}
