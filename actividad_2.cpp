#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  
using namespace std;

struct Nodo {
    string resn;      // nombre del residuo (
    string resid;     // identificador del residuo (
    Nodo* siguiente;  // puntero al siguiente nodo
};

// insertar un nuevo residuo al final de la secuencia
void insertarFinal(Nodo*& lista, string resn, string resid) {
    Nodo* nuevo = new Nodo();
    nuevo->resn = resn;
    nuevo->resid = resid;
    nuevo->siguiente = nullptr;

    if (lista == nullptr) {
        // si la lista esta vacia nuevo nodo es la cabeza
        lista = nuevo;
    } else {
        // recorrer hasta el ultimo nodo
        Nodo* temp = lista;
        while (temp->siguiente != nullptr)
            temp = temp->siguiente;
        // insertar nuevo nodo al final
        temp->siguiente = nuevo;
    }
    cout << "Residuo " << resn << resid << " insertado al final \n";
}

// d) Mostrar la lista de residuos en consola
void mostrarLista(Nodo* lista) {
    if (lista == nullptr) {
        cout << "La lista esta vacia \n";
        return;
    }
    cout << "\nLista de residuos: \n";
    Nodo* temp = lista;
    int pos = 1;
    while (temp != nullptr) {
        cout << pos << ". " << temp->resn << " " << temp->resid << endl;
        temp = temp->siguiente;
        pos++;
    }
}

//  modificar el resn de un residuo 
bool modificarResn(Nodo* lista, int posicion, string nuevoResn) {
    if (posicion < 1) return false;
    Nodo* temp = lista;
    int contador = 1;
    // recorrer hasta la posicion deseada
    while (temp != nullptr && contador < posicion) {
        temp = temp->siguiente;
        contador++;
    }
    if (temp == nullptr) return false; // posicion fuera de rango
    temp->resn = nuevoResn;  // modificar resn
    return true;
}

// eliminar un residuo en una posicion especifica
bool eliminarPosicion(Nodo*& lista, int posicion) {
    if (lista == nullptr || posicion < 1) return false;

    if (posicion == 1) {
        // eliminar el primer nodo (cabeza)
        Nodo* aux = lista;
        lista = lista->siguiente;
        delete aux;
        return true;
    }

    Nodo* temp = lista;
    Nodo* prev = nullptr;
    int contador = 1;
    // recorrer hasta la posicion
    while (temp != nullptr && contador < posicion) {
        prev = temp;
        temp = temp->siguiente;
        contador++;
    }
    if (temp == nullptr) return false; // fuera de rango

    // enlazar el nodo anterior con el siguiente del actual
    prev->siguiente = temp->siguiente;
    delete temp;
    return true;
}

// exportar la lista a archivo .dot para Graphviz
bool exportarDot(Nodo* lista, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para escritura.\n";
        return false;
    }

    archivo << "digraph G {\n";
    archivo << "rankdir=LR;\n";  // grafo de izquierda a derecha
    archivo << "node [style=filled, fillcolor=yellow];\n";

    if (lista == nullptr) {
        archivo << "}\n";
        archivo.close();
        return true;
    }

    // crear aristas entre nodos consecutivos
    Nodo* temp = lista;
    while (temp->siguiente != nullptr) {
        archivo << temp->resn << temp->resid << " -> " << temp->siguiente->resn << temp->siguiente->resid << ";\n";
        temp = temp->siguiente;
    }

    archivo << "}\n";
    archivo.close();
    cout << "Archivo " << nombreArchivo << " exportado correctamente.\n";
    return true;
}

// generar automaticamente imagen .png usando comando del sistema
bool generarImagen(const string& archivoDot, const string& archivoPng) {
    string comando = "dot -Tpng " + archivoDot + " -o " + archivoPng;
    int resultado = system(comando.c_str());  // ejecuta el comando dot
    if (resultado != 0) {
        cout << "Error al ejecutar el comando dot.\n";
        return false;
    }
    cout << "Imagen " << archivoPng << " generada correctamente.\n";
    return true;
}

// cargar lista desde archivo PDB procesado con bash
bool cargarDesdeArchivo(Nodo*& lista, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << "\n";
        return false;
    }
    string linea;
    while (getline(archivo, linea)) {
        if (linea.size() < 4) continue;  // evitar errores si linea es muy corta
        string resn = linea.substr(0,3);  // primeros 3 caracteres: resn
        string resid = linea.substr(3);   // resto: resid
        insertarFinal(lista, resn, resid);
    }
    archivo.close();
    cout << "Lista cargada desde " << nombreArchivo << endl;
    return true;
}

int main() {
    Nodo* lista = nullptr;
    int opcion;
    string resn, resid;
    int pos;

    string archivoProcesado = "2KJH_Resids_ChainA_Format_Uniq.pdb"; // cambiar segun archivo usado

    // cargar lista desde archivo procesado por bash 
    cargarDesdeArchivo(lista, archivoProcesado);

    do {
        cout << "\n MENU LISTA DE RESIDUOS \n";
        cout << "1. Insertar residuo al final\n";
        cout << "2. Modificar resn de residuo\n";
        cout << "3. Eliminar residuo en posicion\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Exportar a archivo .dot\n";
        cout << "6. Generar imagen .png con dot\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                // insertar residuo al final 
                cout << "Ingrese resn (3 letras): ";
                getline(cin, resn);
                cout << "Ingrese resid: ";
                getline(cin, resid);
                insertarFinal(lista, resn, resid);
                break;
            case 2:
                // modificar resn 
                cout << "Ingrese posicion a modificar: ";
                cin >> pos;
                cin.ignore();
                cout << "Ingrese nuevo resn (3 letras): ";
                getline(cin, resn);
                if (modificarResn(lista, pos, resn))
                    cout << "Residuo modificado\n";
                else
                    cout << "Posion invalida \n";
                break;
            case 3:
                // eliminar residuo en posicion 
                cout << "Ingrese posicion a eliminar: ";
                cin >> pos;
                cin.ignore();
                if (eliminarPosicion(lista, pos))
                    cout << "Residuo eliminado\n";
                else
                    cout << "Posicion invalida\n";
                break;
            case 4:
                // mostrar lista 
                mostrarLista(lista);
                break;
            case 5:
                // exportar archivo .dot 
                if (!exportarDot(lista, "secuencia.dot"))
                    cout << "Error al exportar archivo .dot\n";
                break;
            case 6:
                // generar imagen .png
                if (!generarImagen("secuencia.dot", "secuencia.png"))
                    cout << "Error al generar imagen .png\n";
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida \n";
        }
    } while (opcion != 7);

    // liberar memoria al finalizar
    while (lista != nullptr) {
        Nodo* aux = lista;
        lista = lista->siguiente;
        delete aux;
    }

    return 0;
}
