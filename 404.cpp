#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
using namespace std;

#define INFINITO 99999999
//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
int nodoinicio;				  // nodo del inicio del recorrido
int nodofin;				  // nodo del fin del recorrido
int nodointermedio;			  // nodo intermedio del recorrido
int **G; 					  // Matriz de costes
int *D;						  // array de costes del camino especial minimo para cada nodo
bool *S;					  // array de nodos escogidos
int sumaCostes;				  // variable que almacenara el coste
	


//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo() {
	cin >> nnodos;
	cin.ignore();
	cin >> naristas;
	cin.ignore();
	cin >> nodoinicio >> nodofin >> nodointermedio;
	G = new int*[nnodos];
	// iniciamos el grafo
	for (int i= 0; i < nnodos; i++) {
		G[i] = new int[nnodos];
		for (int j= 0; j < nnodos; j++) {
			G[i][j] = INFINITO;					// INFINITO significa que los nodos no son adyacentes
		}
	}
	for (int i= 0; i < naristas; i++) {
		int n1, n2, coste;
		cin >> n1 >> n2 >> coste;
		G[n1-1][n2-1] = coste;
		G[n2-1][n1-1] = coste;
	}
	// aprovechamos para reservar memoria de los arrays D P y S
	D = new int[nnodos];
	S = new bool[nnodos];
}

void liberaGrafo() {
	for (int i= 0; i <nnodos; i++) {
		delete[] G[i];
	}
	delete[] G;
}


void iniciaDPS(int nodo) {	// nodo es el nodo por el que se quiere comenzar el recorrido
	// iniciamos los arrays D, P y S
	for (int v= 0; v < nnodos; v++) {
		D[v] = G[nodo-1][v];
		S[v] = false;
	}
}


// funcion principal
void recorreMinimo(int nodoini, int nodofin) {		// nodoini es el nodo por el que se comienza el recorrido y nodofin en el que se termina
	for (int i= 0; i < nnodos; i++) {
		// iniciamos el nodo v a un nodo no escogido.
		int v= 0;
		while (v < nnodos && S[v]) {
			v++;
		}
		// hay que coger un nodo v no escogido tal que D[v] sea minimo
		for (int k= 0; k < nnodos; k++) {
			if ((!S[k]) && (D[k] < D[v])) {
				v = k;
			}
		}
		S[v] = true;
		
		for(int w= 0; w < nnodos; w++) {
			if ((G[v][w] != INFINITO) && (!S[w]) && ((D[v] + G[v][w]) < D[w])) {		//hay que hacer un recorrido sobre los nodos adyacentes NO escogidos
				D[w] = D[v] + G[v][w];
			}
		}
		// si ya hemos llegado al nodo final paramos
		if (S[nodofin-1]) {
			sumaCostes = sumaCostes + D[nodofin-1];	
			break;
		}
	}

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
		sumaCostes = 0;
		
		iniciaDPS(nodoinicio);
		recorreMinimo(nodoinicio, nodointermedio);
		
		iniciaDPS(nodointermedio);
		recorreMinimo(nodointermedio, nodofin);
		
		if (sumaCostes >= INFINITO) {
			cout << "IMPOSIBLE" << endl;
		} else {
			cout << sumaCostes << endl;
		}
		liberaGrafo();
		delete[] D;
		delete[] S;
  	}
}
