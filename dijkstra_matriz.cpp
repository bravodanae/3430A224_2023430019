#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstdlib> 

using namespace std;

//CONSTANTES GLOBALES
// 9999 representa "infinito" (no hay conexion entre nodos)
const int INFINITO = 9999;

// FUNCION PARA LIMPIAR PANTALLA
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// FUNCION PARA MOSTRAR MATRIZ
void mostrarMatriz(const vector<vector<int>>& matriz) {
    int n = matriz.size();
    cout << "\nMatriz de distancias:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == INFINITO)
                cout << "INF\t";
            else
                cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}


// FUNCION PARA GENERAR ARCHIVO DOT (GRAFO ORIGINAL)
void generarDOTOriginal(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al crear el archivo DOT\n";
        return;
    }

    archivo << "digraph G {\n";
    archivo << "graph [rankdir=LR]\n";
    archivo << "node [style=filled fillcolor=\"#00ff005f\"]\n\n";

    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] != 0 && matriz[i][j] != INFINITO) {
                archivo << i << " -> " << j << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    archivo << "}\n";
    archivo.close();
    cout << "\nArchivo DOT del grafo original generado: " << nombreArchivo << endl;
}

// ESTRUCTURA PARA RESULTADOS
struct ResultadoDijkstra {
    vector<int> distancias;
    vector<int> padre;
};

// ALGORITMO DE DIJKSTRA
ResultadoDijkstra dijkstra(const vector<vector<int>>& grafo, int origen) {
    int n = grafo.size();
    vector<int> distancia(n, INFINITO);
    vector<int> padre(n, -1);
    vector<bool> visitado(n, false);

    distancia[origen] = 0;

    for (int cont = 0; cont < n - 1; ++cont) {
        int minDist = INFINITO;
        int nodoMin = -1;

        for (int i = 0; i < n; ++i) {
            if (!visitado[i] && distancia[i] < minDist) {
                minDist = distancia[i];
                nodoMin = i;
            }
        }

        if (nodoMin == -1) break;

        visitado[nodoMin] = true;

        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && grafo[nodoMin][j] != INFINITO && grafo[nodoMin][j] != 0) {
                int nuevaDist = distancia[nodoMin] + grafo[nodoMin][j];
                if (nuevaDist < distancia[j]) {
                    distancia[j] = nuevaDist;
                    padre[j] = nodoMin;
                }
            }
        }
    }

    return {distancia, padre};
}

// FUNCION PARA GRAFO RESULTANTE
void generarDOTResultado(const vector<vector<int>>& matriz, const vector<int>& padre, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al crear el archivo DOT del resultado\n";
        return;
    }

    archivo << "digraph G {\n";
    archivo << "graph [rankdir=LR]\n";
    archivo << "node [style=filled fillcolor=\"#00ff005f\"]\n\n";

    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        if (padre[i] != -1) {
            archivo << padre[i] << " -> " << i 
                    << " [label=" << matriz[padre[i]][i]
                    << ", color=\"red\", penwidth=2.0];\n";
        }
    }

    archivo << "}\n";
    archivo.close();
    cout << "\nArchivo DOT del grafo resultante generado: " << nombreArchivo << endl;
}

// FUNCION PRINCIPAL CON MENU
int main() {
    int opcion;
    vector<vector<int>> matriz;
    ResultadoDijkstra resultado;
    bool ejecutado = false;
    int n = 0, origen = 0;

    do {
        limpiarPantalla();
        cout << " ALGORITMO DE DIJKSTRA - LABORATORIO 6\n";
        cout << "1. Ingresar grafo y ejecutar algoritmo\n";
        cout << "2. Generar grafos (Graphviz)\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            limpiarPantalla();

            cout << "Ingrese el numero de nodos (mayor que 2): ";
            cin >> n;

            if (n <= 2) {
                cerr << "Error: el numero de nodos debe ser mayor que 2.\n";
                cout << "Presione Enter para continuar...";
                cin.ignore(); cin.get();
                continue;
            }

            matriz.assign(n, vector<int>(n));
            cout << "\nIngrese la matriz de distancias (use " << INFINITO << " para representar INF):\n";

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cin >> matriz[i][j];
                    if (matriz[i][j] < 0) {
                        cerr << "Error: no se permiten distancias negativas.\n";
                        cout << "Presione Enter para continuar...";
                        cin.ignore(); cin.get();
                        return 1;
                    }
                }
            }

            mostrarMatriz(matriz);

            cout << "\nIngrese el vertice origen (0 a " << n - 1 << "): ";
            cin >> origen;

            if (origen < 0 || origen >= n) {
                cerr << "Error: vertice de origen invalido.\n";
                cout << "Presione Enter para continuar...";
                cin.ignore(); cin.get();
                continue;
            }

            resultado = dijkstra(matriz, origen);
            ejecutado = true;

            cout << "\nDistancias minimas desde el vertice " << origen << ":\n";
            for (int i = 0; i < n; ++i) {
                cout << " -> Nodo " << i << ": ";
                if (resultado.distancias[i] == INFINITO)
                    cout << "INF";
                else
                    cout << resultado.distancias[i];
                cout << endl;
            }

            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
        }
        else if (opcion == 2) {
            if (!ejecutado) {
                cout << "\nPrimero debe ejecutar el algoritmo.\n";
            } else {
                generarDOTOriginal(matriz, "grafo_original.dot");
                generarDOTResultado(matriz, resultado.padre, "grafo_resultado.dot");

                cout << "\nGenerando imagenes PNG...\n";
                system("dot -Tpng grafo_original.dot -o grafo_original.png");
                system("dot -Tpng grafo_resultado.dot -o grafo_resultado.png");
                cout << "Imagenes generadas correctamente:\n";
                cout << " - grafo_original.png\n";
                cout << " - grafo_resultado.png\n";
            }

            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
        }

    } while (opcion != 3);

    limpiarPantalla();
    cout << "Programa finalizado correctamente.\n";
    return 0;
}
