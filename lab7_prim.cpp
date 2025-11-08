#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstdlib> 

using namespace std;

// CONSTANTES GLOBALES
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

// FUNCION PARA GENERAR GRAFO ORIGINAL (DOT)
void generarDOTOriginal(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al crear el archivo DOT\n";
        return;
    }

    archivo << "graph G {\n";
    archivo << "graph [rankdir=LR]\n";
    archivo << "node [style=filled fillcolor=\"#00ff005f\"]\n\n";

    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matriz[i][j] != 0 && matriz[i][j] != INFINITO) {
                archivo << char('a' + i) << " -- " << char('a' + j) 
                        << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    archivo << "}\n";
    archivo.close();
    cout << "\nArchivo DOT del grafo original generado: " << nombreArchivo << endl;
}

// ALGORITMO DE PRIM (USANDO MATRICES)
void prim(const vector<vector<int>>& grafo, int n, vector<int>& padre, int& costoTotal, vector<int>& L) {
    vector<int> clave(n, INFINITO);
    vector<bool> enMST(n, false);
    padre.assign(n, -1);
    clave[0] = 0;
    costoTotal = 0;
    L.clear();

    for (int cont = 0; cont < n - 1; ++cont) {
        int minClave = INFINITO, u = -1;
        for (int i = 0; i < n; ++i) {
            if (!enMST[i] && clave[i] < minClave) {
                minClave = clave[i];
                u = i;
            }
        }
        if (u == -1) break;
        enMST[u] = true;
        L.push_back(u);

        for (int v = 0; v < n; ++v) {
            if (grafo[u][v] && grafo[u][v] != INFINITO && !enMST[v] && grafo[u][v] < clave[v]) {
                clave[v] = grafo[u][v];
                padre[v] = u;
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        if (padre[i] != -1 && grafo[i][padre[i]] != INFINITO)
            costoTotal += grafo[i][padre[i]];
    }
}

// FUNCION PARA GENERAR DOT DEL MST (PRIM)
void generarDOTPrim(const vector<vector<int>>& matriz, const vector<int>& padre, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al crear el archivo DOT del resultado\n";
        return;
    }

    archivo << "graph G {\n";
    archivo << "graph [rankdir=LR]\n";
    archivo << "node [style=filled fillcolor=\"#00ff005f\"]\n\n";

    int n = matriz.size();
    for (int i = 1; i < n; ++i) {
        if (padre[i] != -1) {
            archivo << char('a' + padre[i]) << " -- " << char('a' + i)
                    << " [label=" << matriz[padre[i]][i]
                    << ", color=\"red\", penwidth=2.0];\n";
        }
    }

    archivo << "}\n";
    archivo.close();
    cout << "\nArchivo DOT del grafo de costo minimo generado: " << nombreArchivo << endl;
}


// FUNCION PRINCIPAL CON MENU
int main() {
    int opcion;
    vector<vector<int>> matriz;
    vector<int> padre, L;
    int n = 0, costoTotal = 0;
    bool ejecutado = false;

    do {
        limpiarPantalla();
        cout << " ALGORITMO DE PRIM - LABORATORIO 7\n";
        cout << "_._._._._._._._._._._._._._._._._.\n";
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
            prim(matriz, n, padre, costoTotal, L);
            ejecutado = true;

            cout << "\nConjunto L (orden de inclusion): ";
            for (int nodo : L) cout << char('a' + nodo) << " ";
            cout << endl;

            cout << "Costo total del arbol de costo minimo: " << costoTotal << endl;

            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
        }
        else if (opcion == 2) {
            if (!ejecutado) {
                cout << "\nPrimero debe ejecutar el algoritmo.\n";
            } else {
                generarDOTOriginal(matriz, "grafo_original.dot");
                generarDOTPrim(matriz, padre, "grafo_prim.dot");
                cout << "\nGenerando imagenes PNG...\n";
                system("dot -Tpng grafo_original.dot -o grafo_original.png");
                system("dot -Tpng grafo_prim.dot -o grafo_prim.png");
                cout << "Imagenes generadas correctamente:\n";
                cout << " - grafo_original.png\n";
                cout << " - grafo_prim.png\n";
            }
            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
        }

    } while (opcion != 3);

    limpiarPantalla();
    cout << "Programa finalizado correctamente.\n";
    return 0;
}
