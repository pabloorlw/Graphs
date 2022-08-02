#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <sstream>
#include <list>
using namespace std;

#define MAX_NODOS 20000

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int contador;                 // Variable que usaremos para contar los nodos que recorre Pablito hasta salir del laberinto
list<int>* G[MAX_NODOS+1];    // Array que usaremos para guardar punteros a listas
bool visitado[MAX_NODOS+1];   // Array de marcas de visitados
bool salir;                   // Variable que indicará si hay que salir de la búsqueda


//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////


void leeGrafo (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> nnodos;
  if (nnodos<0 || nnodos>MAX_NODOS) {
    cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    exit(0);
  }
  string linea;
  cin.ignore();
  int num;
  for (int i= 1; i <= nnodos; i++) {
    G[i] = new list<int>();
    getline(cin, linea);
    istringstream iss(linea);
    while (iss >> num) {
      G[i]->push_back(num);
    }
  }
}

void borraGrafo (void) {
  for (int i= 1; i<= nnodos; i++) {
    delete G[i];
  }
}


// Haremos uso del recorrido de la búsqueda primero en profundidad modificándolo
void bpp(int v, string & cadena)
// Procedimiento recursivo de la busqueda primero en profundidad
//   v - primer nodo visitado en la bpp
{
  if (!salir) {
    visitado[v]= true;
    contador++;
    cadena = cadena + to_string(v) + "\n";
    list<int>::iterator itLista;
    itLista= G[v]->begin();
    while (itLista != G[v]->end() && v != nnodos) {
      if (!visitado[*itLista]) {
        bpp(*itLista, cadena);
        if (v != nnodos && !salir) {
          contador++;
          cadena = cadena + to_string(v) + "\n";
        } else {
          salir = true;
          return;
        }
      }
    itLista++;
    } 
    if (v == nnodos) salir = true;
  }
}




void busquedaPrincipal (void)
// Procedimiento principal de la busqueda en profundidad
{
  memset(visitado, 0, sizeof(visitado));
  string cadena = "";
  // hacemos una busqueda en profundidad empezando en el primer nodo.
  // Si no se ha encontrado la salida, es decir, el ultimo nodo, entonces es que Pablito no puede salir del laberinto
  contador = 0;
  salir = false;
  bpp(1, cadena);
  if (cadena.find(to_string(nnodos)) != string::npos) {
    cout << contador << endl;
    cout << cadena;
  }
  else {
    cout << "INFINITO" << endl;
  }
}

int main (void)
{
  int ncasos;
  cin >> ncasos;
  for (int i= 1; i<=ncasos; i++) {
    leeGrafo();
    cout << "Caso " << i << endl;
    busquedaPrincipal();
    borraGrafo();
  }
}