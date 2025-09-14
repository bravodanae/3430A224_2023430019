#include <iostream>
using namespace std;

//clase Pila que implementa una pila de enteros usando arreglos
class Pila {
private:
    int *datos;   // arreglo para almacenar los elementos
    int tope;     // indica la posicion actual del tope
    int max;      // capacidad maxima 

public:
    // constructor: inicializa la pila con el tamano dado
    Pila(int n) {
        datos = new int[n];
        tope = 0;
        max = n;
    }

    // destructor:libera memoria
    ~Pila() {
        delete[] datos;
    }

    // metodo que verifica si la pila esta vacia
    bool pilaVacia() {
        return (tope == 0);
    }

    // metodo que verifica si la pila esta llena
    bool pilaLlena() {
        return (tope == max);
    }

    // metodo para insertar un elemento en la pila
    void push(int valor) {
        if (pilaLlena()) {
            cout << "pila llena\n";
        } else {
            tope++;
            datos[tope - 1] = valor;
            cout << "elemento " << valor << " agregado a la pila\n";
        }
    }

    // metodo para eliminar un elemento de la pila
    void pop() {
        if (pilaVacia()) {
            cout <<  "pila vacia\n";
        } else {
            cout << "elemento " << datos[tope - 1] << " eliminado de la pila\n";
            tope--;
        }
    }

    // metodo para mostrar los elementos de la pila en formato vertical
    void mostrar() {
        if (pilaVacia()) {
            cout << "la pila esta vacia\n";
        } else {
            cout << "contenido de la pila:\n";
            for (int i = tope - 1; i >= 0; i--) {
                cout << "|" << datos[i] << "|\n";
            }
        }
    }
};

int main() {
    int n, opcion, valor;

    cout << "ingrese tamaño maximo de la pila: ";
    cin >> n;

    Pila pila(n);

    while (true) {
        cout << "_._._._._._._._._._._._._\n";
        cout << "menu de opciones\n";
        cout << "1. Push (agregar)\n";
        cout << "2. Pop (eliminar)\n";
        cout << "3. Ver pila\n";
        cout << "0. Salir\n";
        cout << "_._._._._._._._._._._._._\n";
        cout << "opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "ingrese valor: ";
                cin >> valor;
                pila.push(valor);
                break;
            case 2:
                pila.pop();
                break;
            case 3:
                pila.mostrar();
                break;
            case 0:
                cout << "saliendo del programa \n";
                return 0;
            default:
                cout << "opcion no valida \n";
        }
    }
}
