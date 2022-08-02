#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <queue>     // Para la cola
using namespace std;

#define MAX_NODOS 26

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados

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
  char c1, c2;
  for (int i= 0; i<naristas; i++) {
    cin >> c1 >> c2;
    G[c1-'A'][c2-'A']= true;
  }
}

void bpa(int v)
// Procedimiento de la busqueda primero en amplitud
//   v - primer nodo visitado en la bpa
{
	queue<int> C;
	int x, y;
	visitado[v] = true;
	C.push(v);
	while (!C.empty()) {
		x = C.front();
		cout << char(x+'A');
		C.pop();
		for (int y = 0; y<nnodos; y++) {
			if (!visitado[y] && G[x][y]) {
				visitado[y] = true;
				C.push(y);
			}
		}
	}
}

void busquedaPA (void)
// Procedimiento principal de la busqueda en amplitud
{
  memset(visitado, 0, sizeof(visitado));
  for (int v= 0; v<nnodos; v++)
    if (!visitado[v])
      bpa(v);
  cout << endl;
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
  int ncasos;
  cin >> ncasos;
  for (int i= 0; i<ncasos; i++) {
    leeGrafo();
    busquedaPA();
  }
}
