#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <sstream>
#include <list>
using namespace std;

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nMujeres;				// representa al numero de mujeres 
int nHombres;				// representa al numero de hombres
int nParejas;				// representa al numero de parejas pasadas por la entrada
list<int>** G;				// en este caso se opta por una representacion mediante listas de adyacencia
bool *mujeresEmparejadas;	// array que marca si una mujer está ya emparejada
int contadorParejas;		// cuenta el numero de parejas posibles que se pueden formar

	




//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo() {
	cin >> nHombres;
	cin >> nMujeres;
	cin >> nParejas;
	G = new list<int>*[nHombres];
	int hombre, mujer;
	for (int i= 0; i< nParejas; i++) {
		G[i] = new list<int>;
		cin >> hombre >> mujer;
		G[hombre-1]->push_back(mujer-1);

	}
}

// función para liberar la memoria dinámica asocaida al grafo
void liberaGrafo() {
	for (int i= 0; i < nHombres; i++) {
		delete G[i];
	}
	delete[] G;
}


void cuentaParejas() {
	// reservamos memoria e iniciamos el array de mujeres emparejadas
	mujeresEmparejadas = new bool[nMujeres];
	for (int i= 0; i < nMujeres; i++) {
		mujeresEmparejadas[i] = false;
	}

	list<int>::iterator itLista;
	for (int j= 0; j < nHombres; j++) {
		itLista= G[j]->begin();
		while (itLista != G[j]->end()) {
			if (!mujeresEmparejadas[*itLista]) {
				// marcamos a la mujer como emparejada e incrementamos en 1 el numero total de parejas posibles
				mujeresEmparejadas[*itLista] = true;
				contadorParejas++;
			}
		}
	}
	delete[] mujeresEmparejadas;
}


//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main(void) {
	int ncasos;
	cin >> ncasos;
	for (int i= 0; i < ncasos; i++) {
		leeGrafo();
		contadorParejas = 0;
		cuentaParejas();
		cout << contadorParejas << endl;
		liberaGrafo();
	}
}