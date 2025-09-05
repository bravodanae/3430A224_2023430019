#include <iostream>
#include <string>
using namespace std;

// estructura del paciente con un puntero al siguiente nodo
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* next; // puntero al siguiente paciente en la lista
};

// funcion para crear un nuevo paciente
Paciente* crearPaciente(const string& nombre, int edad, double peso, double altura) {
    Paciente* nuevo = new Paciente;
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->peso = peso;
    nuevo->altura = altura;
    nuevo->next = nullptr; // para que al pricipio no apunte a nadie
    return nuevo;
}

// funciona para ir agregando al final de la lista un paciente
void agregarPaciente(Paciente*& head, Paciente* nuevo) {
    if (head == nullptr) {
        head = nuevo;
    } else {
        Paciente* actual = head;
        while (actual->next != nullptr) {
            actual = actual->next; // recorremos hasta el ultimo
        }
        actual->next = nuevo; // enlazamos el nuevo paciente
    }
}

// Funcion imprimir la lista de pacientes
void imprimirPacientes(Paciente* head) {
    cout << "Mostrando informacion de pacientes en la lista:\n";
    cout << "     \n";
    int numero = 1;
    Paciente* actual = head;
    while (actual != nullptr) {
        cout << "Paciente numero " << numero << ":\n";
        cout << "el paciente se llama: " << actual->nombre << endl;
        cout << "su edad es: " << actual->edad << " anios" << endl;
        cout << "su peso es: " << actual->peso << " kg" << endl;
        cout << "su altura es: " << actual->altura << " m" << endl;
        cout << "   \n";
        actual = actual->next; // avanzamos al siguiente nodo
        numero++;
    }
}

// funcion para liberar la memoria de la lista
void liberarLista(Paciente*& head) {
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Paciente* head = nullptr; // comienzo de lista vacia

    agregarPaciente(head, crearPaciente("Nicolas", 32, 78.5, 1.76));
    agregarPaciente(head, crearPaciente("Monica",   88, 60.2, 1.55));
    agregarPaciente(head, crearPaciente("Jesus",   16, 54.3, 1.68));

    // llamo imprimir toda la lista
    imprimirPacientes(head);

    // liberar memoria
    liberarLista(head);

    return 0;
}
