#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
using namespace std;

#define MAX_NODOS 500

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados
int isla[MAX_NODOS];          // Usaremos el array almacenar la isla a la que pertenece cada usuario
int contador;                 // Lo usaremos para contar el numero de islas 

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> nnodos >> naristas;
  if (nnodos<0 || nnodos>MAX_NODOS) {
    cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    exit(0);
  }
  memset(G, 0, sizeof(G));
  int e1, e2;
  for (int i= 1; i<=naristas; i++) {
    cin >> e1 >> e2;
    G[e1][e2]= true;
    G[e2][e1]= true;
  }
}

// Nos basaremos en los algoritmos de la busqueda primero en profundidad

void bpp(int v)
// Procedimiento recursivo de la busqueda primero en profundidad
//   v - primer nodo visitado en la bpp
{
  visitado[v]= true;
  isla[v] = contador;
  for (int w= 1; w<=nnodos; w++)
    if (!visitado[w] && G[v][w])
      bpp(w);
}

void busquedaPP (void)
// Procedimiento principal de la busqueda en profundidad
{
  memset(isla, 0, sizeof(isla));
  memset(visitado, 0, sizeof(visitado));
  contador = 0;
  for (int v= 1; v<=nnodos; v++) {
    if (!visitado[v]) {
      contador++; 
      bpp(v);
    }
  }
  cout << contador << endl;
  for (int v= 1; v<= nnodos; v++) {
    cout << isla[v] << endl;
  }
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
  int ncasos;
  cin >> ncasos;
  for (int i= 1; i<=ncasos; i++) {
    leeGrafo();
    cout << "Caso " << i << endl;
    busquedaPP();
  }
}
