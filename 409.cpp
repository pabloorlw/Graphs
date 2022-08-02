#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <list>
using namespace std;

#define MAX_NODOS 1000

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int vertice;				  // variable que guardará el último vértice asignado a npost

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

bool** leeGrafo() {
	// procedimiento para leer un grafo de la entrada
	cin >> nnodos;
	if (nnodos > MAX_NODOS || nnodos < 0) {
		cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    	exit(0);
	}
	bool **G = new bool*[nnodos];
	for (int i= 0; i < nnodos; i++) {
		// iniciamos la matriz de adyacencia
		G[i] = new bool[nnodos];
		for (int j= 0; j< nnodos; j++) {
			G[i][j] = false;
		}
		int pagEnlazada;
		cin >> pagEnlazada;
		if (pagEnlazada != 0) {
			G[i][pagEnlazada-1] = true;
			while (pagEnlazada != 0) {
				cin >> pagEnlazada;
				if (pagEnlazada != 0) G[i][pagEnlazada-1] = true;
			}
		}
	}
	return G;
}

// funciones que se encargarán de la inicializaión y borrado de memoria dinámica de los arrays que usaremos
void liberaGrafo(bool **G) {
	for (int i= 0; i < nnodos; i++) {
		delete[] G[i];
	} delete[] G;
}

bool* iniciaVisitado() {
	bool *visitado = new bool[nnodos];
	for (int i = 0; i < nnodos; i++) {
		visitado[i] = false;
	}
	return visitado;
}

// la idea es buscar las componentes fuertemente conexas
// bpp del grafo no invertido
void bppPosterior(int v, bool *visitado, bool **G, int *npost) {
	visitado[v] = true;
	//los indices del array son los vertices del orden posterior y el contenido son los nodos a los que se corresponde cada uno
	npost[vertice] = v;
	vertice--;
	for (int w= 0; w < nnodos; w++) {
		if (G[v][w] && !visitado[w]) {
			bppPosterior(w, visitado, G, npost);
		}
	}
}

// Procedimiento principal de la busqueda en profundidad
int* busquedaPosterior (bool **G) {
	int *npost = new int[nnodos];
	bool *visitado = iniciaVisitado();
	vertice = nnodos-1;
	for (int v= 0; v<nnodos; v++) {
		if (!visitado[v]) {
			bppPosterior(v, visitado, G, npost);
		}
	}
	delete[] visitado;
	return npost;
}


// funcion que devuelve el grafo invertido del grafo pasado como parametro
/**
bool** invierte(bool **G) {
	bool** invertido = new bool*[nnodos];		// habrá que calcular la matriz traspuesta de la pasada como parámetro
	for (int i= 0; i < nnodos; i++) {
		invertido[i] = new bool[nnodos];
		for (int j = 0; j < nnodos; j++) {
			invertido[i][j] = G[j][i];
		}
	}
	return invertido;
}
**/

void bppInvertido(int v, bool *visitado, bool **Grafo, list<int> *plista) {
	visitado[v] = true;
	list<int>::iterator itlista = plista->begin();
	//hacemos una insercion ordenada del elemento en la lista
	while ((itlista != plista->end()) && (*itlista < v+1)) {
		itlista++;
	} 
	if ((itlista == plista->end()) || (*itlista != v+1)) {
		plista->insert(itlista, v+1);
	}
	for (int w= 0; w < nnodos; w++) {
		if (Grafo[w][v] && !visitado[w]) {
			bppInvertido(w, visitado, Grafo, plista);
		}
	}
}

void muestraPPInvertido (bool **G, int *npost) {
	// v será el vértice en el que se empieza a buscar
	bool *visitado = iniciaVisitado();
	int contador = 0;
	for (int v= nnodos-1; v >= 0; v--) {
		if (!visitado[npost[v]]) {
			list<int> *plista = new list<int>;
			bppInvertido(npost[v], visitado, G, plista);
			contador++;
			cout << "Simple " << contador << ":";
			list<int>::iterator itlista = plista->begin();
			while (itlista != plista->end()) {
				cout << " " << *itlista;
				itlista++;
			}
			cout << endl;
			delete plista;
		}
	}
	delete[] visitado;
}

int BusquedaPPInvertido (bool **G, int *npost, int contadorSimples) {
	// v será el vértice en el que se empieza a buscar
	bool *visitado = iniciaVisitado();
	for (int v= nnodos-1; v >= 0; v--) {
		if (!visitado[npost[v]]) {
			list<int> *plista = new list<int>;
			bppInvertido(npost[v], visitado, G, plista);
			contadorSimples++;
			delete plista;
		}
	}
	delete[] visitado;
	return contadorSimples;
}


//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
  int ncasos;
  cin >> ncasos;
  for (int i= 1; i<=ncasos; i++) {
   bool **grafo = leeGrafo();
   int *npost = busquedaPosterior(grafo);

   //bool **invertido = invierte(grafo);
   int contadorSimples = 0;
  
   contadorSimples = BusquedaPPInvertido(grafo, npost, contadorSimples);
   cout << "Caso " << i << ": total " << contadorSimples << endl;
   muestraPPInvertido(grafo, npost);
   delete[] npost;
   liberaGrafo(grafo);
   //liberaGrafo(invertido);
  }
}