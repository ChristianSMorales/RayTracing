#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdio.h>

const int MaxReflections =
    5; // Aqui se debe definir el número de veces que rebota
const double LostEnergy = 0.20;
using namespace std;

//-----------------------------------------  VECTOR
class vector {
public:
  double x, y, z;
  vector() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  void operator=(double d) { // Asignación del mismo valor para x, y, z
    x = y = z = d;
  }

  vector operator+(vector p) { // Suma
    vector r;
    r.x = x + p.x;
    r.y = y + p.y;
    r.z = z + p.z;
    return r;
  }

  vector operator-(vector p) { // Resta
    vector r;
    r.x = x - p.x;
    r.y = y - p.y;
    r.z = z - p.z;
    return r;
  }

  vector operator*(double d) { // Multiplicación por Escalar
    vector v;
    v.x = x * d;
    v.y = y * d;
    v.z = z * d;
    return v;
  }

  vector operator/(double d) { // División por Escalar
    vector v;
    v.x = x / d;
    v.y = y / d;
    v.z = z / d;
    return v;
  }

  double operator*(vector v) { // Producto Escalar
    return x * v.x + y * v.y + z * v.z;
  }

  vector operator/(vector v) { // Producto cruz o vectorial (no división)
    vector r;
    r.x = y * v.z - z * v.y;
    r.y = z * v.x - x * v.z;
    r.z = x * v.y - y * v.x;
    return r;
  }

  double modulo() { // Módulo
    return sqrt(x * x + y * y + z * z);
  }
};
//-----------------------------------------  POINT
class point {
public:
  double x, y, z;
  point() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }

  void operator=(double d) { // Asignación del mismo valor para x, y, z
    x = y = z = d;
  }

  void assign(double d1, double d2, double d3) { // Asigna  x, y, z
    x = d1;
    y = d2;
    z = d3;
  }

  point operator+(point p) { // Suma de puntos
    point r;
    r.x = x + p.x;
    r.y = y + p.y;
    r.z = z + p.z;
    return r;
  }

  point operator+(vector v) { // Translación (Mover un punto)
    point r;
    r.x = x + v.x;
    r.y = y + v.y;
    r.z = z + v.z;
    return r;
  }

  vector operator-(point p) { // Resta de puntos = Vector
    vector v;
    v.x = x - p.x;
    v.y = y - p.y;
    v.z = z - p.z;
    return v;
  }

  point operator*(double d) { // Multiplicación por Escalar
    point p;
    p.x = x * d;
    p.y = y * d;
    p.z = z * d;
    return p;
  }

  point operator/(double d) { // División por Escalar
    point p;
    p.x = x / d;
    p.y = y / d;
    p.z = z / d;
    return p;
  }

  double distancia(point p) { // Distancia entre dos puntos
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2));
  }

  void clear() { // Limpieza del punto (setear todos los valores en 0)
    x = y = z = 0;
  }
};

//-----------------------------------------  TRIANGLE
// PROPORCIONADO POR EL DOCENTE
class triangle {
public:
  point p1, p2, p3, bc;
  vector n;
  triangle() {
    p1 = 0.0;
    p2 = 0.0;
    p3 = 0.0;
    bc = 0.0;
    n = 0.0;
  }

  void baricentro() { // Baricentro
    bc = (p1 + p2 + p3) / 3;
  }

  vector normalTriangle() { // Normal del triangulo
    n = (p2 - p1) / (p3 - p1);
    if (n.modulo() == 0)
      n = 0;
    else
      n = n / n.modulo();
    return n;
  }

  void clear() { // Setea los atributos
    p1 = 0.0;
    p2 = 0.0;
    p3 = 0.0;
    bc = 0.0;
    n = 0.0;
  }
};
//-----------------------------------------  PLANE
class plane {
public:
  point *p;    // Elementos tipo plano
  int NP;      // Número de planos
  triangle *t; // Elemento tipo triángulo
  int NT;      // Número de triangulos
  vector n;    // Vector normal del plano
  float minX, minY, minZ;
  float maxX, maxY, maxZ;
  // color c;
  // material m;

  plane() {
    p = NULL;
    NP = 0;
    t = NULL;
    NT = 0;
    n = 0;
    // Valores de Rango
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
  }

  void clear() { // Setear  Valores
    delete[] p;
    NP = 0;
    delete[] t;
    NT = 0;
    n = 0;
    // Valores de Rango
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
  }

  void normalPlane() { // Normal del plano = Normal del triangulo
    n = t[0].normalTriangle();
  }

  void newPoints(int N) { // Agrega más puntos
    int P;
    point *tp;
    tp = new point[NP + N];
    for (P = 0; P < NP; P++) {
      tp[P] = p[P];
    }
    for (P = NP; P < NP + N; P++) {
      tp[P].clear();
    }
    if (NP > 0) {
      delete[] p;
      p = NULL;
    }
    p = tp;
    NP += N;
  }

  void newTriangle(int N) { // Agrega más triangulos
    int T;
    triangle *aux;
    aux = new triangle[NT + N];
    for (T = 0; T < NT; T++) {
      aux[T] = t[T];
    }
    for (T = NT; T < NT + N; T++) {
      aux[T].clear();
    }
    if (NP > 0) {
      delete[] t;
      t = NULL;
    }
    t = aux;
    NT += N;
  }

  void pointGenTriangle() { // Transforma el plano en 2 triangulos
    newTriangle(NP - 2);
    int i = 1;
    for (int T = 0; T < NT; T++) {
      i--;
      t[T].p1.x = p[i].x;
      t[T].p1.y = p[i].y;
      t[T].p1.z = p[i].z;
      i++;
      if (i == NP)
        i = 0;
      t[T].p2.x = p[i].x;
      t[T].p2.y = p[i].y;
      t[T].p2.z = p[i].z;
      i++;
      if (i == NP)
        i = 0;
      t[T].p3.x = p[i].x;
      t[T].p3.y = p[i].y;
      t[T].p3.z = p[i].z;
      i++;
    }
  }

  void valuesDefault() { // Inicializa valores con el primer punto
    minX = p[0].x;
    minY = p[0].y;
    minZ = p[0].z;
    maxX = p[0].x;
    maxY = p[0].y;
    maxZ = p[0].z;
  }

  void obtenerRangos() { // Crea el rango del plano (min, max)
    for (int i = 0; i < NP; i++) {
      if (p[i].x < minX) {
        minX = p[i].x;
      }
      if (p[i].x > maxX) {
        maxX = p[i].x;
      }

      if (p[i].y < minY) {
        minY = p[i].y;
      }
      if (p[i].y > maxY) {
        maxY = p[i].y;
      }

      if (p[i].z < minZ) {
        minZ = p[i].z;
      }
      if (p[i].z > maxZ) {
        maxZ = p[i].z;
      }
    }
    // std::cout << "Rango en el eje X: " << minX << maxX << std::endl;
    // std::cout << "Rango en el eje Y: " << minY << maxY << std::endl;
    // std::cout << "Rango en el eje Z: " << minZ << maxZ << std::endl;
  }

  bool pointInPlane(point punto) { // Verifica si un punto esta en este Plano
    int accept = 0;
    if (punto.x >= minX && punto.x <= maxX) {
      accept++;
    }
    if (punto.y >= minY && punto.y <= maxY) {
      accept++;
    }
    if (punto.z >= minZ && punto.z <= maxZ) {
      accept++;
    }

    if (accept == 3) {
      return true;
    } else {
      return false;
    }
  }
};
//-----------------------------------------  SOURCE
// PROPORCIONADO POR EL DOCENTE
class source {
public:
  point p; // Posición
  // triangle IcoFace[20]; // Representación grafica de la fuente
  //  color color;         // Color de la fuente
  // double VisualRadius; // Radio Visual
  double eF;    // Energía de la fuente
  int NRAYS;    // Número de  rayos que parten de la fuente
  vector *Rays; // Dirección de partida de la fuente

  source() { // Inicializando las variables de la clase
    p = 0.0;
    eF = 0.0;
    NRAYS = 0;
    Rays = NULL;
  }

  void createRay(double x, double y, double z) { // Crea el Rayo
    if (NRAYS > 0)
      delete[] Rays;
    NRAYS = 1;
    Rays = new vector[NRAYS];
    Rays[0].x = x;
    Rays[0].y = y;
    Rays[0].z = z;
    Rays[0] = Rays[0] / Rays[0].modulo();
  }

  void changeEnergy(double energy) { // Cambia la Energia de la fuente
    eF = energy;
  }
};
//-----------------------------------------  REFLECTION
// Para almacenar los reflejos de los rayos
struct reflection { // +1; Porque tambien colocamos el punto inicial
  point puntos[MaxReflections + 1];  // Puntos de choque
  vector viRays[MaxReflections + 1]; // Vector incidente que sale de cada punto
                                     // de choque
  int planes[MaxReflections + 1];           // Plano donde ocurre el choque
  int timesReflection;                      // Número de reflexiones
  double energyCurrent[MaxReflections + 1]; // Energia actual
  bool lost;                                // Se se pierde el rayo
};

//-----------------------------------------  PLANE COLLISION
// Para almacenar el plano donde colisiona
struct planeCollision {
  // Valores -1 para indicar que no tiene asigna nada
  int plane = -1;       // Plano donde choca
  double distance = -1; // Distancia del punto inicial al punto de choque
  bool notJustOne =
      false; // Si choca en más de un plano (esquinas de 2 ó 3 planos)
};

//-----------------------------------------  ROOM
class room {
public:
  plane *p; // Elemento tipo plano
  int NP;   // Número de  planos
  source s; // Fuentes sonoras
  int NS;   // numero de fuentes
  /*receptor *r; // receptores/ microfonos
  int NR; // numero de receptores */

  room() {
    p = NULL;
    NP = 0;
    NS = 0;
  }

  void clear() { // Setea los valores
    if (NP > 0) {
      delete[] p;
      p = NULL;
    }
    NP = 0;
  }

  void NewPlanes(int N) { // Agrega más planos
    int P;
    plane *tp;
    tp = new plane[NP + N];
    for (P = 0; P < NP; P++) {
      tp[P] = p[P];
    }
    for (P = NP; P < NP + N; P++) {
      tp[P].clear();
    }
    if (NP > 0) {
      delete[] p;
      p = NULL;
    }
    p = tp;
    NP += N;
  }

  void NewSource(source fuente) { // Agrega la fuente sonora
    s = fuente;
    NS++;
  }

  double d(vector n, point po, vector vi,
           point o) { // Distancia (d) -> Para calcular Punto de Choque
    double distance;
    double m = vi * n;
    vector va = po - o;
    if (m == 0) {
      distance = -1;
    } else {
      distance = (n * va) / m;
    }
    return distance;
  }

  vector normal(vector v) { // Calcula el vector unitario
    double m;
    vector u;
    m = v * v;
    u = v / m;
    return u;
  }

  static int compararDistancias(
      const void *a,
      const void *b) { // Ordenar de menor a mayor una lista(planeCollision)
    const planeCollision *colA = (const planeCollision *)a;
    const planeCollision *colB = (const planeCollision *)b;

    if (colA->distance < colB->distance) {
      return -1;
    } else if (colA->distance > colB->distance) {
      return 1;
    }
    return 0;
  }

  planeCollision
  collisionGetPlane(vector vi,
                    point o) { // Obtiene el plano con el que colisiona
    // Valores -1 para indicar que no tiene asigna nada
    int trueCollisionPlane = -1; // Plano donde colisiona
    double distanceCollisionPlane =
        -1; // Distancia del origen al punto de choque

    planeCollision result;
    planeCollision *collision = new planeCollision[NP];

    for (int j = 0; j < NP;
         j++) { // Recorre todos los planos buscando punto de choque
      if (((p[j].n * vi) < 0)) { // Verifica si existe una colision con el plano
        collision[j].plane = j;  // Guarda el plano de choque
        collision[j].distance =
            d(p[j].n, p[j].p[0], vi, o); // Guarda la distancia de choque
      } else {
        collision[j].plane = j;     // Guarda el plano de choque
        collision[j].distance = -1; // Sin distancia
      }
    }

    qsort(
        collision, NP, sizeof(planeCollision),
        compararDistancias); // Ordena la lista de planos donde existe colision
    for (int j = 0; j < NP; j++) { // Solo para mostrar
      printf("\nPLANO(%d) : DISTANCE (%f)", (collision[j].plane + 1),
             collision[j].distance);
    }

    for (int j = 0; j < NP; j++) {
      if (collision[j].distance == distanceCollisionPlane &&
          distanceCollisionPlane !=
              -1) { // Si se repite la dsitancia es que choca en 2 ó 3 planos
        result.plane = collision[j].plane; // Uno de los planos donde choca
        result.distance = collision[j].distance;
        result.notJustOne = true; // Choca
        break;
      }
      if ((distanceCollisionPlane == -1 &&
           collision[j].distance > distanceCollisionPlane) ||
          (distanceCollisionPlane != -1 &&
           collision[j].distance <
               distanceCollisionPlane)) { // Toda el plano con menor distancia
                                          // sin contar las de (-1)
        distanceCollisionPlane = collision[j].distance;
        trueCollisionPlane = collision[j].plane;
        // Plano donde colisiona
        result.plane = trueCollisionPlane;
        result.distance = distanceCollisionPlane;
        result.notJustOne = false; // No choca
      }
    }
    printf("\nCHOCA CON ESQUINAS?: %s\n", result.notJustOne ? "Si" : "No");
    return result;
  }

  reflection *rayTracing() {
    int collisionPlane = -1; // Plano donde choca
    int cantReflections = 0; // Veces que se refleja
    double distance = 0;     // Distancia (Para calcular el punto de choque)
    point puntoCollision;    // Punto de choque
    bool flag = false;       // Terminar
    vector vi;               // Vector incidente
    vector vr;               // Vector reflejo
    double energy = s.eF;
    point origen;
    
    origen.assign(s.p.x, s.p.y, s.p.z); // Punto de origen
    reflection *raysReflection =
        new reflection[s.NRAYS]; // Reflexiones de los rayos

    for (int i = 0; i < s.NRAYS; i++) { // Recorre todos los rayos
      vi = s.Rays[i];                   // Vector incidente

      raysReflection[i].timesReflection = 0;
      raysReflection[i].lost = false;
      raysReflection[i].puntos[0] = origen;
      raysReflection[i].viRays[0] = vi; // Agrega el vector incidente
      raysReflection[i].planes[0] = -1; // Agrega el plano (no existe)
      raysReflection[i].energyCurrent[0] = energy; // Agrega la energia
      while (!flag) {
        planeCollision getPlane =
            collisionGetPlane(vi, origen); //  Encontrar en que plano se choca
        distance = d(p[getPlane.plane].n, p[getPlane.plane].p[0], vi,
                     origen); // Calcular distancia

        // VECTORES REFLEJOS
        if (getPlane.notJustOne) { // Verificar si choca en las esquinas
          vr = vi * -1;            // Giramos al vector incidente
        } else {
          vr = (vi) - (p[getPlane.plane].n) * 2 * (p[getPlane.plane].n * vi);
        }

        puntoCollision = origen + (vi * distance); // Punto donde colisiona

        if (!p[getPlane.plane].pointInPlane(
                puntoCollision)) { // 1era Condición de parada: -1; Comprueba si el punto no esta en el plano
          flag = true;             // Termina el programa
        }

        if (getPlane.plane == -1 ||
            flag == true) { // 2da Condición de parada: -1; Hace
                            // referencia que no hay plano donde choca
          raysReflection[i].lost = true; // El rayo se pierde
          flag = true;                   // Termina el programa
          raysReflection[i].timesReflection =
              cantReflections; // Asigna la cantidad de reflexiones
        } else {               // Si hay plano donde chocar
          cantReflections++;   // Aumenta el numero de reflexiones
          raysReflection[i].puntos[cantReflections] =
              puntoCollision; // Agrega un punto de choque a la lista

          raysReflection[i].viRays[cantReflections] =
              vr; // Agrega el vector incidente
          energy = (energy) * (1 - LostEnergy);
          raysReflection[i].energyCurrent[cantReflections] =
              energy; // Reduce la energia
          raysReflection[i].planes[cantReflections] =
              getPlane.plane; // Agrega el plano
          printf("\nPLANO (%d) VECTOR REFLEJO: (%f %f %f)\n",
                 (raysReflection[i].planes[cantReflections] + 1), vr.x, vr.y,
                 vr.z);
        }

        if (cantReflections ==
            MaxReflections) { // 3ra Condición de parada: Completa el número de
                              // veces que debe reflejarse
          raysReflection[i].timesReflection =
              cantReflections; // Asigna la cantidad de reflexiones
          flag = true;         // Termina el programa
          raysReflection[i].lost = false;
        }

        // CAMBIO DE POSICIÓN
        vi = vr;                 // Nuevo vector incidente
        origen = puntoCollision; // Nuevo punto de partida
      }
    }
    return raysReflection;
  }
};