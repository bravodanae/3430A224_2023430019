#include<iostream>
#include <string>
using namespace std;

//estructura para el nodo en la cola
struct Nodo {
    string nombre;
    string carrera;
    float promedio;
    Nodo* siguiente;
};

// Puntero para al frente y fin de la cola
Nodo* frente = nullptr;
Nodo* fin = nullptr;

// funcion para validar si la cola esta vacia
bool Cola_Vacia() {
    return frente == nullptr;
}

// funcion para verificar que la cola este llena (siempre retorna falso, cola dinámica)
bool Cola_Llena() {
    return false;
}

// para  insertar un nuevo estudiante a la cola
void Insertar_Cola(string nombre, string carrera, float promedio) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->carrera = carrera;
    nuevo->promedio = promedio;
    nuevo->siguiente = nullptr;

    if (Cola_Vacia()) {
        // si la cola esta vacia, frente y fin apuntan al nuevo nodo
        frente = fin = nuevo;
    } else {
        // si no, el nodo actual al final apunta al nuevo
        fin->siguiente = nuevo;
        fin = nuevo;
    }

    cout << "Estudiante " << nombre << " encolado correctamente \n";
}

// para eliminar el primer estudiante de la cola (el frente)
bool Eliminar_Cola(string& nombre, string& carrera, float& promedio) {
    if (Cola_Vacia())
     return false;

    Nodo* temp = frente;
    nombre = temp->nombre;
    carrera = temp->carrera;
    promedio = temp->promedio;

    frente = frente->siguiente;

    // si eliminamos el ultimo nodo (actualizamos fin)
    if (frente == nullptr) fin = nullptr;

    delete temp;
    return true;
}

// mostrar todos los estudiantes en la cola
void Mostrar_Cola() {
    if (Cola_Vacia()) {
        cout << "La cola está vacía.\n";
        return;
    }

    cout << "\nContenido actual de la cola:\n";
    int pos = 1;
    Nodo* actual = frente;
    while (actual != nullptr) {
        cout << pos << ". " << actual->nombre << " | " 
             << actual->carrera << " | Promedio: " 
             << actual->promedio << endl;
        actual = actual->siguiente;
        pos++;
    }
}

// funcion principal con menu interactivo
int main() {
    int opcion;
    string nombre, carrera;
    float promedio;

    do {
        cout << "\n menu para cola de estudiante \n";
        cout << "1. insertar nuevo estudiante en la cola\n";
        cout << "2. eliminar estudiante del frente de la cola\n";
        cout << "3. mostrar contenido de la cola\n";
        cout << "4. salir\n";
        cout << "seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer 

        switch (opcion) {
            case 1:
                cout << "nombre: ";
                getline(cin, nombre);
                cout << "carrera: ";
                getline(cin, carrera);
                cout << "promedio: ";
                cin >> promedio;
                cin.ignore();
                Insertar_Cola(nombre, carrera, promedio);
                break;

            case 2:
                if (Eliminar_Cola(nombre, carrera, promedio)) {
                    cout << "se elimino al estudiante: " << nombre 
                         << " | " << carrera 
                         << " | Promedio: " << promedio << endl;
                } else {
                    cout << "la cola esta vacai\n";
                }
                break;

            case 3:
                Mostrar_Cola();
                break;

            case 4:
                cout << "saliendo del programa...\n";
                break;

            default:
                cout << "opcion invalida intente de nuevo\n";
        }

    } while (opcion != 4);

    return 0;
}
