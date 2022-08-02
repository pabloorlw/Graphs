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
list<int> **G;				// en este caso se opta por una representacion mediante listas de adyacencia
int contadorParejas;		// cuenta el numero de parejas posibles que se pueden formar


//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo() {
	cin >> nHombres;
	cin >> nMujeres;
	cin >> nParejas;
	G = new list<int>*[nHombres];
	for (int i= 0; i < nHombres; i++) {
		G[i] = new list<int>;
	}
	int hombre, mujer;
	for (int i= 0; i< nParejas; i++) {
		cin >> hombre >> mujer;
		G[hombre-1]->push_back(mujer-1-nHombres);

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
	// reservamos memoria e iniciamos el array de mujeres y hombres emparejados
	bool *mujeresEmparejadas = new bool[nMujeres];
	for (int i= 0; i < nMujeres; i++) {
		mujeresEmparejadas[i] = false;
	}
	bool *hombresEmparejados = new bool[nHombres];
	for (int k= 0; k < nHombres; k++) {
		hombresEmparejados[k] = false;
	}

	list<int>::iterator itLista;
	for (int j= 0; j < nHombres; j++) {
		itLista= G[j]->begin();
		while (itLista != G[j]->end()) {
			if (mujeresEmparejadas[*itLista] == false) {
				// marcamos a la mujer y al hombre como emparejados e incrementamos en 1 el numero total de parejas posibles
				mujeresEmparejadas[*itLista] = true;
				//cout << *itLista << " ";
				hombresEmparejados[j] = true;
				contadorParejas++;
				break;
			}
			itLista++;
		}
	}
	//cout << "Parejas tras la primera asignacion: " << contadorParejas << endl;
	// tras la primera asignacion de parejas (cada uno con quien queria) vemos cuantos hombres y mujeres quedan libres
	int hombresLibres = 0;
	int mujeresLibres = 0;
	for (int i= 0; i < nHombres; i++) {
		if (!hombresEmparejados[i]) {
			hombresLibres++;
		}
		//cout << hombresEmparejados[i] << " ";
	}
	//cout << endl;
	//cout << "Hombres libres tras la primera asignacion: " << hombresLibres << endl;
	for (int i= 0; i < nMujeres; i++) {
		if (!mujeresEmparejadas[i]) {
			mujeresLibres++;
		}
		//cout << mujeresEmparejadas[i] << " ";
	}
	//cout << endl;
	//cout << "Mujeres libres tras la primera asignacion: " << mujeresLibres << endl;	
	if (mujeresLibres < hombresLibres) {
		contadorParejas = contadorParejas + mujeresLibres;
	} else {
		contadorParejas = contadorParejas + hombresLibres;
	}
	delete[] mujeresEmparejadas;
	delete[] hombresEmparejados;	
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
		/**
		cout << "num de hombres: " << nHombres << endl;
		cout << "num de mujeres: " << nMujeres << endl;
		**/
		cout << contadorParejas << endl;
		liberaGrafo();
	}
}