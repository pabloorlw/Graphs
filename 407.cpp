#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
using namespace std;

#define MAX_NODOS 200
#define INFINITO 99999999

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
string *nombreCiudades;		  // array que guardara el nombre de cada ciudad
int **G;					  // matriz de costes
int *maximo;				  // array que almacena el camino minimo mas largo de cada ciudad
int capital;				  // variable que guardará el nodo que se corresponderá con la capital 	


//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo ()
// Procedimiento para leer un grafo de la entrada
{
	cin >> nnodos;
  	if (nnodos<0 || nnodos>MAX_NODOS) {
    	cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    	exit(0);
  	}
  	cin.ignore();
  	string nombre;
  	nombreCiudades = new string[nnodos];
  	for (int i= 0; i < nnodos; i++) {
  		getline(cin, nombre);
  		nombreCiudades[i] = nombre;
  	}
  	G = new int*[nnodos];
  	for (int i= 0; i < nnodos; i++) {
  		G[i] = new int[nnodos];
  		for (int j= 0; j < nnodos; j++) {
  			G[i][j] = INFINITO;						// INFINITO para indicar que los nodos no son adyacentes

  		}
  	}
  	int A, B, L;
  	while ((cin >> A >> B >> L) && ((A != 0 ) || (B != 0) || (L != 0))) {
  		G[A][B] = L;
  		G[B][A] = L;
  	}
  	
}

// libera la memoria dinamica asociada al grafo
void liberaGrafo() {
	for (int i= 0; i < nnodos; i++) {
		delete G[i];
	} 
	delete[] G;
}


void caminosMinimos() {			// algoritmo de Floyd para calculo de caminos minimos entre todos los pares
	for (int k= 0; k < nnodos; k++) {
		for (int j= 0; j < nnodos; j++) {
			for (int i= 0; i < nnodos; i++) {
				if (((G[i][k] + G[k][j]) < G[i][j])) {		
					G[i][j] = G[i][k] + G[k][j]; 
				}
			}
		}
	}
}

int calculaExcentricidad() {
	maximo = new int[nnodos];
	int max;
	for (int i= 0; i < nnodos; i++) {
		max = 0;
		for (int j= 0; j < nnodos; j++) {
			if (G[i][j] > max && i != j) {				// no tiene sentido comparar la distancia de una ciudad con ella misma
				max = G[i][j];
			}
		}
		maximo[i] = max;
	}
	int distancia = maximo[0];
	// elegimos la ciudad con menor excentricidad
	for (int k= 0; k < nnodos; k++) {
		if (maximo[k] < distancia) {
			distancia = maximo[k];
			capital = k;
		}
	}
	string ciudad = nombreCiudades[capital];
	for (int h= 0; h < nnodos; h++) {
		if (maximo[h] == distancia) {
			if (nombreCiudades[h].compare(ciudad) < 0) {
				ciudad = nombreCiudades[h];
				capital = h;
			}
		}
	}
	delete[] maximo;
	return distancia;
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
    capital = 0;
    caminosMinimos();
    int excentricidad = calculaExcentricidad();
    cout << nombreCiudades[capital] << endl;
    cout << excentricidad << endl;
    delete[] nombreCiudades;
    liberaGrafo();
  }
}