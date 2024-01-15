#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdio.h>

const int MaxReflections = 50;   // Max buncings
const double LostEnergy = 0.50; // Init Energy
const float PI = 3.141592;
using namespace std;

//----------VECTOR----------
class vector1
{
  // Constructor
public:
  double x, y, z;
  vector1()
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
  // Operators overload

  // init a Vector with d value in each component
  void operator=(double d)
  {
    x = y = z = d;
  }
  // Sums two vectos
  vector1 operator+(vector1 p)
  {
    vector1 r;
    r.x = x + p.x;
    r.y = y + p.y;
    r.z = z + p.z;
    return r;
  }
  // thisVector - pVector
  vector1 operator-(vector1 p)
  {
    vector1 r;
    r.x = x - p.x;
    r.y = y - p.y;
    r.z = z - p.z;
    return r;
  }
  // d factor like d*V
  vector1 operator*(double d)
  {
    vector1 v;
    v.x = x * d;
    v.y = y * d;
    v.z = z * d;
    return v;
  }
  // 1/d factor like (1/d)*V
  vector1 operator/(double d)
  {
    vector1 v;
    v.x = x / d;
    v.y = y / d;
    v.z = z / d;
    return v;
  }
  // Scalar Vectorial product
  double operator*(vector1 v)
  {
    return x * v.x + y * v.y + z * v.z;
  }
  // Vectorial Product
  vector1 operator/(vector1 v)
  {
    vector1 r;
    r.x = y * v.z - z * v.y;
    r.y = z * v.x - x * v.z;
    r.z = x * v.y - y * v.x;
    return r;
  }
  // Vector magnitude
  double modulo()
  { // Módulo
    return sqrt(x * x + y * y + z * z);
  }
};
//----------POINT----------
class point
{
  // Constructor
public:
  double x, y, z;
  point()
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
  // Init Point with same components
  void operator=(double d)
  {
    x = y = z = d;
  }
  // Asign the components of a point
  void assign(double d1, double d2, double d3)
  {
    x = d1;
    y = d2;
    z = d3;
  }
  // thisPoint + pPoint
  point operator+(point p)
  {
    point r;
    r.x = x + p.x;
    r.y = y + p.y;
    r.z = z + p.z;
    return r;
  }
  // thisPoint + pVector = Point
  point operator+(vector1 v)
  { // Translación (Mover un punto)
    point r;
    r.x = x + v.x;
    r.y = y + v.y;
    r.z = z + v.z;
    return r;
  }
  // thisPoint - pPoint = Vector
  vector1 operator-(point p)
  { // Resta de puntos = Vector
    vector1 v;
    v.x = x - p.x;
    v.y = y - p.y;
    v.z = z - p.z;
    return v;
  }
  // d factor
  point operator*(double d)
  { // Multiplicación por Escalar
    point p;
    p.x = x * d;
    p.y = y * d;
    p.z = z * d;
    return p;
  }
  // 1/d factor
  point operator/(double d)
  { // División por Escalar
    point p;
    p.x = x / d;
    p.y = y / d;
    p.z = z / d;
    return p;
  }
  // Gap between two points
  double distancia(point p)
  { // Distancia entre dos puntos
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2));
  }
  // reset Point
  void clear()
  { // Limpieza del punto (setear todos los valores en 0)
    x = y = z = 0;
  }
};

//----------TRIANGLE----------
class triangle
{
  // Constructor
public:
  point p1, p2, p3, bc;
  vector1 n;
  triangle()
  {
    p1 = 0.0;
    p2 = 0.0;
    p3 = 0.0;
    bc = 0.0;
    n = 0.0;
  }
  // Calculate baricentro
  void baricentro()
  {
    bc = (p1 + p2 + p3) / 3;
  }
  // Calculate Normal Vector from triangle
  vector1 normalTriangle()
  {
    n = (p2 - p1) / (p3 - p1);
    if (n.modulo() == 0)
      n = 0;
    else
      n = n / n.modulo();
    return n;
  }
  // Reset triangle
  void clear()
  { // Setea los atributos
    p1 = 0.0;
    p2 = 0.0;
    p3 = 0.0;
    bc = 0.0;
    n = 0.0;
  }
};
//----------PLANE----------
class plane
{
  // Constructor
public:
  point *planePointer;    // Elementos tipo plano
  int numberOfPlanes;      // Número de planos
  triangle *trianglePointer; // Elemento tipo triángulo
  int numberOfTriangles;      // Número de triangulos
  vector1 normalVector;   // Vector normal del plano
  float minX, minY, minZ;
  float maxX, maxY, maxZ;

  plane()
  {
    planePointer = NULL;
    numberOfPlanes = 0;
    trianglePointer = NULL;
    numberOfTriangles = 0;
    normalVector = 0;
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
  }
  // Reset plane
  void clear()
  {
    delete[] planePointer;
    numberOfPlanes = 0;
    delete[] trianglePointer;
    numberOfTriangles = 0;
    normalVector = 0;
    minX = 0;
    minY = 0;
    minZ = 0;
    maxX = 0;
    maxY = 0;
    maxZ = 0;
  }
  // Calculate normal vector from plane/triangle
  void normalPlane()
  { // Normal del plano = Normal del triangulo
    normalVector = trianglePointer[0].normalTriangle();
  }
  // Add Points to plane
  void newPoints(int numberOfPoints)
  { // Agrega más puntos
    int pointIndex;
    point *totalPointsPointer;
    totalPointsPointer = new point[numberOfPlanes + numberOfPoints];
    for (pointIndex = 0; pointIndex < numberOfPlanes; pointIndex++)
    {
      totalPointsPointer[pointIndex] = planePointer[pointIndex];
    }
    for (pointIndex = numberOfPlanes; pointIndex < numberOfPlanes + numberOfPoints; pointIndex++)
    {
      totalPointsPointer[pointIndex].clear();
    }
    if (numberOfPlanes > 0)
    {
      delete[] planePointer;
      planePointer = NULL;
    }
    planePointer = totalPointsPointer;
    numberOfPlanes += numberOfPoints;
  }
  // Add triangles to plane
  void newTriangle(int N)
  {
    int T;
    triangle *aux;
    aux = new triangle[numberOfTriangles + N];
    for (T = 0; T < numberOfTriangles; T++)
    {
      aux[T] = trianglePointer[T];
    }
    for (T = numberOfTriangles; T < numberOfTriangles + N; T++)
    {
      aux[T].clear();
    }
    if (numberOfPlanes > 0)
    {
      delete[] trianglePointer;
      trianglePointer = NULL;
    }
    trianglePointer = aux;
    numberOfTriangles += N;
  }
  // transform a plane in two triangles
  void pointGenTriangle()
  {
    newTriangle(numberOfPlanes - 2);
    int i = 1;
    for (int T = 0; T < numberOfTriangles; T++)
    {
      i--;
      trianglePointer[T].p1.x = planePointer[i].x;
      trianglePointer[T].p1.y = planePointer[i].y;
      trianglePointer[T].p1.z = planePointer[i].z;
      i++;
      if (i == numberOfPlanes)
        i = 0;
      trianglePointer[T].p2.x = planePointer[i].x;
      trianglePointer[T].p2.y = planePointer[i].y;
      trianglePointer[T].p2.z = planePointer[i].z;
      i++;
      if (i == numberOfPlanes)
        i = 0;
      trianglePointer[T].p3.x = planePointer[i].x;
      trianglePointer[T].p3.y = planePointer[i].y;
      trianglePointer[T].p3.z = planePointer[i].z;
      i++;
    }
  }
  // Init edge values
  void valuesDefault()
  {
    minX = planePointer[0].x;
    minY = planePointer[0].y;
    minZ = planePointer[0].z;
    maxX = planePointer[0].x;
    maxY = planePointer[0].y;
    maxZ = planePointer[0].z;
  }
  // Calculate ranges for the plane
  void obtenerRangos()
  {
    for (int i = 0; i < numberOfPlanes; i++)
    {
      if (planePointer[i].x < minX)
      {
        minX = planePointer[i].x;
      }
      if (planePointer[i].x > maxX)
      {
        maxX = planePointer[i].x;
      }

      if (planePointer[i].y < minY)
      {
        minY = planePointer[i].y;
      }
      if (planePointer[i].y > maxY)
      {
        maxY = planePointer[i].y;
      }

      if (planePointer[i].z < minZ)
      {
        minZ = planePointer[i].z;
      }
      if (planePointer[i].z > maxZ)
      {
        maxZ = planePointer[i].z;
      }
    }
  }

  // Is this Point in that plane?
  bool pointInPlane(point punto)
  {
    int accept = 0;
    if (punto.x >= minX && punto.x <= maxX)
    {
      accept++;
    }
    if (punto.y >= minY && punto.y <= maxY)
    {
      accept++;
    }
    if (punto.z >= minZ && punto.z <= maxZ)
    {
      accept++;
    }

    if (accept == 3)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

//----------SOURCE----------
// PROPORCIONADO POR EL DOCENTE
class Source
{
public:
  point initPoint; // Posición
  // triangle IcoFace[20]; // Representación grafica de la fuente
  //  color color;         // Color de la fuente
  // double VisualRadius; // Radio Visual
  double sourceEnergy;     // Energía de la fuente
  int numRays;     // Número de  rayos que parten de la fuente
  vector1 *rays; // Dirección de partida de la fuente

  Source()
  { // Inicializando las variables de la clase
    initPoint = 0.0;
    sourceEnergy = 0.0;
    numRays = 0;
    rays = NULL;
  }

  void createRay(double x, double y, double z)
  { // Crea el Rayo
    if (numRays > 0)
      delete[] rays;
    numRays = 1;
    rays = new vector1[numRays];
    rays[0].x = x;
    rays[0].y = y;
    rays[0].z = z;
    rays[0] = rays[0] / rays[0].modulo(); // Vector unitario del rayo
  }

  void changeEnergy(double energy)
  { // Cambia la Energia de la fuente
    sourceEnergy = energy;
  }

  void createRays(double NumberOfRays)
    {
        int i, n, RAY;
        double S, R;
        // create Rays matrix
        if (numRays > 0)
            delete[] rays;
        n = int(floor(sqrt((NumberOfRays - 2) / 10) + 0.5));
        numRays = int(2 + 10 * pow(n, 2));
        rays = new vector1[numRays];


        S = 2 / sqrt(5);
        R = (5 - sqrt(5)) / 5;
        rays[0].x = 0;
        rays[0].y = 0;
        rays[0].z = 1;
        for (i = 1; i < 6; i++)
        {
            rays[i].x = S * cos((PI * i * 72) / 180);
            rays[i].y = S * sin((PI * i * 72) / 180);
            rays[i].z = 1 - R;
            rays[i + 5].x = S * cos((72 * PI * i) / 180 + (36 * PI) / 180);
            rays[i + 5].y = S * sin((72 * PI * i) / 180 + (36 * PI) / 180);
            rays[i + 5].z = R - 1;
        }
        rays[11].x = 0;
        rays[11].y = 0;
        rays[11].z = -1;
        RAY = 12;
    };

};
//----------REFLECTION----------
// Para almacenar los reflejos de los rayos
struct reflection
{     
  //Points of reflection happens, including the origin
  point puntos[MaxReflections + 1]; 
  //Vector incidente, starts from every reflection point.
  vector1 vectorIncidenteRays[MaxReflections + 1];
  //Plane where the reflection happens
  int planes[MaxReflections + 1];  
  //total number of reflections
  int timesReflection;      
  //Current energy after every reflection
  double energyCurrent[MaxReflections + 1]; 
  //Check if a ray went out of a plane
  bool lost; 
};

//----------PLANE COLLISION----------
// Para almacenar el plano donde colisiona
struct planeCollision
{
  // Valores -1 para indicar que no tiene asigna nada
  int planeIndex = -1;          // Plano donde choca
  double distance = -1;    // Distancia del punto inicial al punto de choque
  bool moreCollisionAtSame = false; // Si choca en más de un plano (esquinas de 2 ó 3 planos)
};

//----------ROOM----------
class Room
{
public:
  // Pointer to a Plane
  plane *planePointer;
  // Total number of planes in the room
  int numberOfPlanes;
  //Sound source
  Source source;
  //Total number of sound sources
  int numberOfSources;
  /*receptor *r; // receptores/ microfonos
  int NR; // numero de receptores */

  //Constructor
  Room()
  {
    planePointer = NULL;
    numberOfPlanes = 0;
    numberOfSources = 0;
  }

  // Set a room to default values (NP = 0, p -> NULL)
  void clear()
  {
    if (numberOfPlanes > 0)
    {
      delete[] planePointer;
      planePointer = NULL;
    }
    numberOfPlanes = 0;
  }
  //By default, there is no planes in a room, this function creates planes in a room
  void newPlanes(
    //Number of planes to add to the room
    int numberOfNewPlanes
    )
  {
    //Plane index
    int indexPlane;
    // Total planes
    plane *totalPlanes;
    // Create an array of planes with dim of N + NP
    totalPlanes = new plane[numberOfPlanes + numberOfNewPlanes];
    for (indexPlane = 0; indexPlane < numberOfPlanes; indexPlane++)
    {
      //Move the current planes in the room to the totalPlanes array
      totalPlanes[indexPlane] = planePointer[indexPlane];
    }
    //
    for (indexPlane = numberOfPlanes; indexPlane < numberOfPlanes + numberOfNewPlanes; indexPlane++)
    {
      totalPlanes[indexPlane].clear();
    }
    if (numberOfPlanes > 0)
    {
      delete[] planePointer;
      planePointer = NULL;
    }
    planePointer = totalPlanes;
    numberOfPlanes += numberOfNewPlanes;
  }
  // Attach the new source to the room, then increase the numberOfSources
  void NewSource(Source fuente)
  {
    source = fuente;
    numberOfSources++;
  }
  // Calculate the distance between a vector and a point
  double calculateDistance(vector1 normalVector, point PlaneOriginPoint, vector1 vectorIncidente, point originPoint)
  {
    double distance;
    double prodDotIncidNormal = vectorIncidente * normalVector;
    vector1 vectorOriginOrigin = PlaneOriginPoint - originPoint;
    //Vector incidente is rectangular with normal vector of a plane
    if (prodDotIncidNormal == 0)
    {
      distance = -1;
    }
    else
    {
      distance = (normalVector * vectorOriginOrigin) / prodDotIncidNormal;
    }
    return distance;
  }
  //Calculate the unitary of a vector
  vector1 calculateUnitary(vector1 vector)
  {
    double module;
    vector1 unitary;
    module = vector * vector;
    module = sqrt(module);
    unitary = vector / module;
    return unitary;
  }
  // Compare if a distance from planeCollision A is greater than planeCollision A. Return 1 if true, -1 lower, 0 equals.
  static int compararDistancias(const void *_planeCollisionA, const void *_planeCollisionB)
  {
    const planeCollision *planeCollisionA = (const planeCollision *)_planeCollisionA;
    const planeCollision *planeCollisionB = (const planeCollision *)_planeCollisionB;

    if (planeCollisionA->distance < planeCollisionB->distance)
    {
      return -1;
    }
    else if (planeCollisionA->distance > planeCollisionB->distance)
    {
      return 1;
    }
    return 0;
  }

  void toStringPlanes()
  {
    for (int i = 0; i < numberOfPlanes; i++)
    {
      cout << "Plane " << i << ": ";
      cout << "Normal (" << planePointer[i].normalVector.x << ", " << planePointer[i].normalVector.y << ", " << planePointer[i].normalVector.z << "), ";
      cout << "Min (" << planePointer[i].minX << ", " << planePointer[i].minY << ", " << planePointer[i].minZ << "), ";
      cout << "Max (" << planePointer[i].maxX << ", " << planePointer[i].maxY << ", " << planePointer[i].maxZ << ")" << endl;
    }
  }
  // Calculate the planes with which  a ray collidiates. Return a PlaneCollision struct
  planeCollision collisionGetPlane(vector1 vectorIncidente, point originPoint)
  {
    // Value if there is a collision
    int trueCollisionPlaneIndex = -1;
    // Valores -1 para indicar que no tiene asigna nada
    double distanceCollisionPlane = -1;
    // Plano donde colisiona
    planeCollision result;
     // Distancia del origen al punto de choque
    planeCollision *collision = new planeCollision[numberOfPlanes];
    // Loop in all planes
    for (int j = 0; j < numberOfPlanes; j++)
    {
      //If the angle of normalVecto dot vectorIncidente is acute there is a collision
      if (((planePointer[j].normalVector * vectorIncidente) < 0))
      {             
        //Save the index of collision Plane                                         
        collision[j].planeIndex = j;                             
        // Save the distance between the originRay and collisionPlane
        collision[j].distance = calculateDistance(planePointer[j].normalVector, planePointer[j].planePointer[0], vectorIncidente, originPoint); 
      }
      else
      {
        //Save collision Plane
        collision[j].planeIndex = j;     
        //There is no distance becouse there is no collision
        collision[j].distance = -1; 
      }
    }
    //Quicksort the planes based on the distance
    qsort(collision, numberOfPlanes, sizeof(planeCollision), compararDistancias);
    //Loop in all planes
    for (int j = 0; j < numberOfPlanes; j++)
    {
      //If the distances from a plane is the same for two or tree planes
      if (collision[j].distance == distanceCollisionPlane && distanceCollisionPlane != -1)
      {
        //Save the collision Plane
        result.planeIndex = collision[j].planeIndex;
        //Save the distance
        result.distance = collision[j].distance;
        //There is collision at edge
        result.moreCollisionAtSame = true;
        break;
      }
      // Compare the collision plane with less distance, the ones with less distance are the first to collidate
      if ((distanceCollisionPlane == -1 && collision[j].distance > distanceCollisionPlane) || (distanceCollisionPlane != -1 && collision[j].distance < distanceCollisionPlane))
      { 
        //Save a distance for compairing if there is two collisions with same distance
        distanceCollisionPlane = collision[j].distance;
        //Save the plane
        trueCollisionPlaneIndex = collision[j].planeIndex;
        //Output planeIndex
        result.planeIndex = trueCollisionPlaneIndex;
        //Output distance
        result.distance = distanceCollisionPlane;
        //collision just with a plane
        result.moreCollisionAtSame = false;
      }
    }
    printf("\nEdge Collision?: %s\n", result.moreCollisionAtSame ? "Si" : "No");
    return result;
  }
  // Calculates the reflex of a ray after a collision. Returns a reflection struct
  reflection *rayTracing(vector1 ray)
  {
    //Index of a collision index
    int collisionPlaneIndex = -1;
    //number of reflections
    int numReflections = 0; 
    //distance from origin to a plane
    double distance = 0;
    //point where happens the collision
    point collisionPoint;
    //there is no more reflections?
    bool flag = false;
    //Vector incidente, before the collision
    vector1 vectorIncidente;
    //Vector reflejo, after the collision
    vector1 vectorReflejo;
    //Initial Energy
    double energy = source.sourceEnergy;
    //Origin from the ray comes
    point origen;
    // Set the components of the origen source point
    origen.assign(source.initPoint.x, source.initPoint.y, source.initPoint.z);
    //Pointer of reflections
    reflection* raysReflection = new reflection;

      //Set vector incidente
      vectorIncidente = ray;

      raysReflection->timesReflection = 0;
      raysReflection->lost = false;
      raysReflection->puntos[0] = origen;
      raysReflection->vectorIncidenteRays[0] = vectorIncidente;            // Agrega el vector incidente
      raysReflection->planes[0] = -1;            // Agrega el plano (no existe)
      raysReflection->energyCurrent[0] = energy; // Agrega la energia
      while (!flag)
      {
        //Get the collisionPlane based on the vectorIncidente and origen Point
        planeCollision collisionPlane = collisionGetPlane(vectorIncidente, origen);
        distance = calculateDistance(planePointer[collisionPlane.planeIndex].normalVector, planePointer[collisionPlane.planeIndex].planePointer[0], vectorIncidente, origen); // Calcular distancia

        printf("Collision Plane: %d\n", collisionPlane.planeIndex);
        printf("Collision Distance: %f\n", distance);
        printf("Start Point: (%f, %f, %f)\n", collisionPoint.x, collisionPoint.y, collisionPoint.z);

        // If there are collision on a edge
        if (collisionPlane.moreCollisionAtSame)
        {
          //Just turn the vector
          vectorReflejo = vectorIncidente * -1;
        }
        else
        {      
        //Calculate the vectorReflejo based on vectorReflejo = vectorIncidente - (2*(vectorIncidente*vectorNormal)vectorNormalUnitario)
        vector1 vectorNormalUnitario = calculateUnitary(planePointer[collisionPlane.planeIndex].normalVector);
        vectorReflejo = (vectorIncidente - (vectorNormalUnitario * (2 * (vectorIncidente * planePointer[collisionPlane.planeIndex].normalVector))));
       }
        //Calculate the collision point
        collisionPoint = origen + (vectorIncidente * distance); 

        printf("Collision Point: (%f, %f, %f)\n", collisionPoint.x, collisionPoint.y, collisionPoint.z);
        //Check if the collision point is NOT in the collision plane
        if (!planePointer[collisionPlane.planeIndex].pointInPlane(collisionPoint))
        {        
          //No collision, end of program     
           flag = true;
        }
        //Check if there is no plane index or there is no more reflections.
        if (collisionPlane.planeIndex == -1 || flag == true)
        {                                                      
          // The ray was lost                     
          raysReflection->lost = true;   
          //No collisions, end of program                    
          flag = true;  
          //Assign the numReflections, default is 0                                      
          raysReflection->timesReflection = numReflections; 
        }
        //There is a plane of reflections, or there is more reflections
        else
        {    
          // Increment the num of reflections
          numReflections++;
          //Add a reflectionPoint to the list
          raysReflection->puntos[numReflections] = collisionPoint;
          // Add vectorIncidente to the list
          raysReflection->vectorIncidenteRays[numReflections] = vectorReflejo; 
          //Set the new energy
          energy = (energy) * (1 - LostEnergy);
          //Reduce the energy in the ray
          raysReflection->energyCurrent[numReflections] = energy; 
          //Add the plane to the list
          raysReflection->planes[numReflections] = collisionPlane.planeIndex;
          //Print data
          printf("Vector Inicial: (%f %f %f)\n", vectorIncidente.x, vectorIncidente.y, vectorIncidente.z);
          printf("Vector Reflejo: (%f %f %f)\n", vectorReflejo.x, vectorReflejo.y, vectorReflejo.z);
        }
        //Check if the reflections are enough
        if (numReflections == MaxReflections)
        { 
          //Set the max numReflections
          raysReflection->timesReflection = numReflections;
          //No more collisions, end of program 
          flag = true;        
          //Set the last ray to not lost
          raysReflection->lost = false;
        }

        //Set the new vectorIncident for the next loop
        vectorIncidente = vectorReflejo; 
        //Set the origin point to the collision point
        origen = collisionPoint; 
      }

    return raysReflection;
  }
};
