#include <iostream>
#include <string>
using namespace std;

//estructura para un paciente
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* next; // puntero al siguiente nodo de la lista
};


//funcion va a ir recibiendo los datos de un paciente y crea un nodo en memoria
Paciente* crearPaciente(const string& nombre, int edad, double peso, double altura) {
    Paciente* nuevo = new Paciente;   //reserva memoria
    nuevo->nombre = nombre;           //asigna nombre,luego edad y asi...
    nuevo->edad = edad;              
    nuevo->peso = peso;               
    nuevo->altura = altura;           
    nuevo->next = nullptr;            //al inicio no apunta a nadie
    return nuevo;                     //retorna el puntero creado para el paciente
}

//funcion que agrega paciente al final de la lista
void agregarPaciente(Paciente*& head, Paciente* nuevo) {
    if (head == nullptr) {
        head = nuevo; //la lista estaba vacia, entonces el paciente sera el inicio de la lista
    } else {
        Paciente* actual = head;
        while (actual->next != nullptr) { //para recorrer hasta la ultima posicion
            actual = actual->next;
        }
        actual->next = nuevo; //enlazo el nuevo al final
    }
}


//funcion para imprimir pacientes
void imprimirPacientes(Paciente* head) {
    cout << "imprimiendo informacion de pacientes...\n";
    cout << "  \n";

    int numero = 1;
    Paciente* actual = head; // comenzamos desde la cabeza
    while (actual != nullptr) { //recorre la lista de inicio hasta fin
        cout << "Paciente numero " << numero << ":\n";
        cout << " - El paciente se llama: " << actual->nombre << endl;
        cout << " - Su edad es: " << actual->edad << " anios" << endl;
        cout << " - Su peso es: " << actual->peso << " kg" << endl;
        cout << " - Su altura es: " << actual->altura << " m" << endl;
        cout << "   \n";

        actual = actual->next; //para ir avanzando al siguiente nodo
        numero++;
    }
}

//funcion para liberar espacio
void liberarLista(Paciente*& head) {
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;     
        delete temp;          
    }
}


int main() {
    Paciente* head = nullptr; //la lista comienzara vacia

    agregarPaciente(head, crearPaciente("Jesus",   23, 60.0, 1.70));
    agregarPaciente(head, crearPaciente("Monica",  56, 80.0, 1.58));
    agregarPaciente(head, crearPaciente("Claudio", 58, 100.0, 1.80));
    agregarPaciente(head, crearPaciente("Tomas",   25, 90.0, 1.86));

    imprimirPacientes(head);

    //llamo funcion para liberar memoria antes de salir
    liberarLista(head);

    return 0;
}
