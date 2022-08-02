#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <sstream>
#include <list>
#include <cmath>
using namespace std;


//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de colonias marcianas (nodos del grafo)
int cantidadCable;            // cantidad de cable minima
struct coordenadas            // Estructura que usaremos para guardar las coordenadas de un planeta
{
  int x;
  int y;
};

#define COSTE_GRANDE 99999999

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////



int truncar (int x1, int y1, int x2, int y2) {
 return (int) sqrt(pow(x1-x2, 2) + pow(y1-y2, 2)); 
}


int** lee (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> nnodos;
  coordenadas *posicion = new coordenadas[nnodos];
  for (int i= 0; i< nnodos; i++) {
    int x, y;
    cin >> x >> y;
    posicion[i].x = x;
    posicion[i].y = y;
  }
  int **C = new int*[nnodos];
  for (int i= 0; i< nnodos; i++) {
    C[i] = new int[nnodos];
    for (int j= 0; j< nnodos; j++) {
      C[i][j] = truncar(posicion[i].x, posicion[i].y, posicion[j].x, posicion[j].y);
    }
  }
  delete[] posicion;
  return C;
}


int* iniciaMenorCoste(int **C) {
  int *MenorCoste = new int[nnodos];
  for (int i= 0; i < nnodos; i++) {
    MenorCoste[i] = C[0][i];
  }
  return MenorCoste;
}


void actMenorCoste(int *MenorCoste, int **C, int v) {
// v es el nodo con menor coste 
  MenorCoste[v] = COSTE_GRANDE;
    for (int w= 0; w < nnodos; w++) {
      if ((MenorCoste[w] != COSTE_GRANDE) && (C[v][w] < MenorCoste[w])) {
        MenorCoste[w] = C[v][w];
      }
    }
}


void calculaCantidad(int *MenorCoste, int **C) {
  // empezamos en el nodo 0
  for (int i= 1; i<nnodos; i++) {
    int menor = COSTE_GRANDE;
    int vMenor = 1;
    for (int v= 1; v < nnodos; v++) {
      if (MenorCoste[v] < menor) {
        menor = MenorCoste[v];
        vMenor = v;
      }
    }
    actMenorCoste(MenorCoste, C, vMenor);
    cantidadCable = cantidadCable + menor;
  }
}


void borraCostes (int** C) {
  for (int i= 0; i< nnodos; i++) {
    delete[] C[i];
  }
  delete[] C;
}




int main (void)
{
  int ncasos;
  cin >> ncasos;
  for (int i= 1; i<=ncasos; i++) {
    int **C = lee();
    int *MenorCoste = iniciaMenorCoste(C);
    cantidadCable = 0;
    calculaCantidad(MenorCoste, C);
    cout << cantidadCable << endl;
    borraCostes(C);
    delete[] MenorCoste;
  }
}