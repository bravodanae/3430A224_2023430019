#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

// Estructura que representa un termino GO
struct TerminoGO {
    string codigoGO;
    string funcion;
    double score;
};

// Nodo del arbol AVL
struct NodoAVL {
    TerminoGO dato;
    NodoAVL* izq;
    NodoAVL* der;
    int FE; // factor de equilibrio
};

// FUNCIONES DE UTILIDAD
NodoAVL* crearNodo(const TerminoGO& dato) {
    NodoAVL* nuevo = new NodoAVL;
    nuevo->dato = dato;
    nuevo->izq = nullptr;
    nuevo->der = nullptr;
    nuevo->FE = 0;
    return nuevo;
}

// ROTACIONES AVL

// Rotacion simple izquierda-izquierda (II)
NodoAVL* rotacionII(NodoAVL* nodo) {
    NodoAVL* nodo1 = nodo->der;
    nodo->der = nodo1->izq;
    nodo1->izq = nodo;

    int feN = nodo->FE;
    int feN1 = nodo1->FE;

    if (feN1 >= 0) {
        if (feN == 1)
            nodo->FE = 0;
        else
            nodo->FE = 1;
        nodo1->FE = 0;
    } else {
        if (feN == 1)
            nodo->FE = -1;
        else
            nodo->FE = 0;
        nodo1->FE = 1;
    }
    return nodo1;
}

// Rotacion simple derecha-derecha (DD)
NodoAVL* rotacionDD(NodoAVL* nodo) {
    NodoAVL* nodo1 = nodo->izq;
    nodo->izq = nodo1->der;
    nodo1->der = nodo;

    int feN = nodo->FE;
    int feN1 = nodo1->FE;

    if (feN1 <= 0) {
        if (feN == -1)
            nodo->FE = 0;
        else
            nodo->FE = -1;
        nodo1->FE = 0;
    } else {
        if (feN == -1)
            nodo->FE = 1;
        else
            nodo->FE = 0;
        nodo1->FE = -1;
    }
    return nodo1;
}

// Rotacion doble izquierda-derecha (ID)
NodoAVL* rotacionID(NodoAVL* nodo) {
    NodoAVL* nodo1 = nodo->der;
    NodoAVL* nodo2 = nodo1->izq;
    nodo->der = nodo2->izq;
    nodo2->izq = nodo;
    nodo1->izq = nodo2->der;
    nodo2->der = nodo1;

    if (nodo2->FE == 1)
        nodo->FE = -1;
    else
        nodo->FE = 0;

    if (nodo2->FE == -1)
        nodo1->FE = 1;
    else
        nodo1->FE = 0;

    nodo2->FE = 0;
    return nodo2;
}

// Rotacion doble derecha-izquierda (DI)
NodoAVL* rotacionDI(NodoAVL* nodo) {
    NodoAVL* nodo1 = nodo->izq;
    NodoAVL* nodo2 = nodo1->der;
    nodo->izq = nodo2->der;
    nodo2->der = nodo;
    nodo1->der = nodo2->izq;
    nodo2->izq = nodo1;

    if (nodo2->FE == -1)
        nodo->FE = 1;
    else
        nodo->FE = 0;

    if (nodo2->FE == 1)
        nodo1->FE = -1;
    else
        nodo1->FE = 0;

    nodo2->FE = 0;
    return nodo2;
}

// INSERCION AVL

NodoAVL* insertarAVL(NodoAVL* raiz, const TerminoGO& dato, bool* crece) {
    if (raiz == nullptr) {
        raiz = crearNodo(dato);
        *crece = true;
    } 
    else if (dato.codigoGO < raiz->dato.codigoGO) {
        raiz->izq = insertarAVL(raiz->izq, dato, crece);
        if (*crece) {
            switch (raiz->FE) {
                case 1: raiz->FE = 0; *crece = false; break;
                case 0: raiz->FE = -1; break;
                case -1:
                    if (raiz->izq->FE == -1)
                        raiz = rotacionDD(raiz);
                    else
                        raiz = rotacionDI(raiz);
                    *crece = false;
                    break;
            }
        }
    }
    else if (dato.codigoGO > raiz->dato.codigoGO) {
        raiz->der = insertarAVL(raiz->der, dato, crece);
        if (*crece) {
            switch (raiz->FE) {
                case -1: raiz->FE = 0; *crece = false; break;
                case 0: raiz->FE = 1; break;
                case 1:
                    if (raiz->der->FE == 1)
                        raiz = rotacionII(raiz);
                    else
                        raiz = rotacionID(raiz);
                    *crece = false;
                    break;
            }
        }
    }
    else {
        cout << "El termino " << dato.codigoGO << " ya existe en el arbol." << endl;
        *crece = false;
    }
    return raiz;
}

// ELIMINACION AVL 

// Equilibrar tras eliminar desde izquierda
NodoAVL* equilibrarTrasEliminarIzquierda(NodoAVL* nodo, bool* decrece) {
    switch (nodo->FE) {
        case -1: nodo->FE = 0; break;
        case 0: nodo->FE = 1; *decrece = false; break;
        case 1:
            if (nodo->der->FE >= 0)
                nodo = rotacionII(nodo);
            else
                nodo = rotacionID(nodo);
            if (nodo->FE != 0)
                *decrece = false;
            break;
    }
    return nodo;
}

// Equilibrar tras eliminar desde derecha
NodoAVL* equilibrarTrasEliminarDerecha(NodoAVL* nodo, bool* decrece) {
    switch (nodo->FE) {
        case 1: nodo->FE = 0; break;
        case 0: nodo->FE = -1; *decrece = false; break;
        case -1:
            if (nodo->izq->FE <= 0)
                nodo = rotacionDD(nodo);
            else
                nodo = rotacionDI(nodo);
            if (nodo->FE != 0)
                *decrece = false;
            break;
    }
    return nodo;
}

// Eliminacion principal
NodoAVL* eliminarAVL(NodoAVL* raiz, string codigoGO, bool* decrece, bool* eliminado) {
    if (raiz == nullptr) {
        cout << "No se encontro el termino GO: " << codigoGO << endl;
        *eliminado = false;
        return nullptr;
    }

    if (codigoGO < raiz->dato.codigoGO) {
        raiz->izq = eliminarAVL(raiz->izq, codigoGO, decrece, eliminado);
        if (*decrece)
            raiz = equilibrarTrasEliminarDerecha(raiz, decrece);
    }
    else if (codigoGO > raiz->dato.codigoGO) {
        raiz->der = eliminarAVL(raiz->der, codigoGO, decrece, eliminado);
        if (*decrece)
            raiz = equilibrarTrasEliminarIzquierda(raiz, decrece);
    }
    else {
        *eliminado = true;
        // Caso sin hijos
        if (raiz->izq == nullptr && raiz->der == nullptr) {
            delete raiz;
            *decrece = true;
            return nullptr;
        }
        // Caso un solo hijo
        else if (raiz->izq == nullptr) {
            NodoAVL* temp = raiz->der;
            delete raiz;
            *decrece = true;
            return temp;
        }
        else if (raiz->der == nullptr) {
            NodoAVL* temp = raiz->izq;
            delete raiz;
            *decrece = true;
            return temp;
        }
        // Caso dos hijos
        else {
            NodoAVL* sucesor = raiz->der;
            while (sucesor->izq != nullptr)
                sucesor = sucesor->izq;

            raiz->dato = sucesor->dato;
            raiz->der = eliminarAVL(raiz->der, sucesor->dato.codigoGO, decrece, eliminado);
            if (*decrece)
                raiz = equilibrarTrasEliminarIzquierda(raiz, decrece);
        }
    }
    return raiz;
}

// BUSQUEDA EN AVL
void buscarGO(NodoAVL* raiz, string codigo) {
    if (raiz == nullptr) {
        cout << "No se encontro el termino GO: " << codigo << endl;
        return;
    }
    if (codigo == raiz->dato.codigoGO) {
        cout << "Codigo: " << raiz->dato.codigoGO << endl;
        cout << "Funcion: " << raiz->dato.funcion << endl;
        cout << "Score: " << raiz->dato.score << endl;
        cout << "FE: " << raiz->FE << endl;
    } 
    else if (codigo < raiz->dato.codigoGO)
        buscarGO(raiz->izq, codigo);
    else
        buscarGO(raiz->der, codigo);
}


// GENERAR GRAFO CON GRAPHVIZ
void generarGrafoRec(ofstream& archivo, NodoAVL* nodo) {
    if (nodo != nullptr) {
        archivo << "\"" << nodo->dato.funcion << "\\n" << nodo->dato.score 
                << "\\nFE:" << nodo->FE << "\";" << endl;
        if (nodo->izq != nullptr) {
            archivo << "\"" << nodo->dato.funcion << "\\n" << nodo->dato.score 
                    << "\\nFE:" << nodo->FE << "\" -> \"" 
                    << nodo->izq->dato.funcion << "\\n" 
                    << nodo->izq->dato.score << "\\nFE:" 
                    << nodo->izq->FE << "\";" << endl;
            generarGrafoRec(archivo, nodo->izq);
        }
        if (nodo->der != nullptr) {
            archivo << "\"" << nodo->dato.funcion << "\\n" << nodo->dato.score 
                    << "\\nFE:" << nodo->FE << "\" -> \"" 
                    << nodo->der->dato.funcion << "\\n" 
                    << nodo->der->dato.score << "\\nFE:" 
                    << nodo->der->FE << "\";" << endl;
            generarGrafoRec(archivo, nodo->der);
        }
    }
}

void generarGrafo(NodoAVL* raiz) {
    ofstream archivo("grafoGO.txt");
    archivo << "digraph G {\nnode [style=filled fillcolor=lightyellow shape=box];\n";
    generarGrafoRec(archivo, raiz);
    archivo << "}" << endl;
    archivo.close();
    system("dot -Tpng -ografoGO.png grafoGO.txt");
    system("eog grafoGO.png &");
}

// CARGAR DESDE CSV
NodoAVL* cargarDesdeCSV(string nombreArchivo, NodoAVL* raiz) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return raiz;
    }

    string linea;
    getline(archivo, linea); // salta encabezado

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        TerminoGO dato;
        string scoreStr;

        getline(ss, dato.codigoGO, ',');
        getline(ss, dato.funcion, ',');
        getline(ss, scoreStr, ',');

        try {
            dato.score = stod(scoreStr);
        } catch (...) {
            dato.score = 0.0;
        }

        bool crece = false;
        raiz = insertarAVL(raiz, dato, &crece);
    }

    archivo.close();
    return raiz;
}


void liberarArbol(NodoAVL* raiz) {
    if (raiz == nullptr) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    delete raiz;
}

void menu() {
    cout << "\n MENU AVL " << endl;
    cout << "1. Insertar termino GO" << endl;
    cout << "2. Eliminar termino GO" << endl;
    cout << "3. Buscar termino GO" << endl;
    cout << "4. Mostrar grafo" << endl;
    cout << "0. Salir" << endl;
    cout << " " << endl;
    cout << "Seleccione una opcion: ";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: ./arbolGO archivoCSV" << endl;
        return 1;
    }

    NodoAVL* raiz = nullptr;
    raiz = cargarDesdeCSV(argv[1], raiz);

    int opcion;
    do {
        menu();
        cin >> opcion;
        switch (opcion) {
            case 1: {
                TerminoGO nuevo;
                cout << "Codigo GO: ";
                cin >> nuevo.codigoGO;
                cin.ignore();
                cout << "Funcion: ";
                getline(cin, nuevo.funcion);
                cout << "Score: ";
                cin >> nuevo.score;
                bool crece = false;
                raiz = insertarAVL(raiz, nuevo, &crece);
                break;
            }
            case 2: {
                string codigo;
                cout << "Ingrese codigo GO a eliminar: ";
                cin >> codigo;
                bool decrece = false, eliminado = false;
                raiz = eliminarAVL(raiz, codigo, &decrece, &eliminado);
                if (eliminado)
                    cout << "Nodo eliminado y arbol rebalanceado." << endl;
                break;
            }
            case 3: {
                string codigo;
                cout << "Ingrese codigo GO a buscar: ";
                cin >> codigo;
                buscarGO(raiz, codigo);
                break;
            }
            case 4:
                generarGrafo(raiz);
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    liberarArbol(raiz);
    return 0;
}
