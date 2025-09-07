#include <iostream>
#include <string>
#include <iomanip>  //biblioteca para mostrar decimales
using namespace std;


struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* next; //puntero al siguiente paciente en la lista
};


Paciente* crearPaciente(const string& nombre, int edad, double peso, double altura) {
    Paciente* nuevo = new Paciente;
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->peso = peso;
    nuevo->altura = altura;
    nuevo->next = nullptr;
    return nuevo;
}

void agregarPaciente(Paciente*& head, Paciente* nuevo) {
    if (head == nullptr) {
        head = nuevo;
    } else {
        Paciente* actual = head;
        while (actual->next != nullptr) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
}

void imprimirPacientes(Paciente* head) {
    cout << "Lista de pacientes:\n";
    cout << "   \n";

    int numero = 1;
    Paciente* actual = head;
    while (actual != nullptr) {
        cout << "Paciente numero " << numero << ":\n";
        cout << " - Nombre: " << actual->nombre << endl;
        cout << " - Edad: " << actual->edad << " anios" << endl;
        cout << " - Peso: " << actual->peso << " kg" << endl;
        cout << " - Altura: " << actual->altura << " m" << endl;
        cout << "----------------------------------------\n";

        actual = actual->next;
        numero++;
    }
}

//funcion para calcular el promedio de edad
double promedioEdad(Paciente* head) {
    int suma = 0;
    int contador = 0;

    Paciente* actual = head;
    while (actual != nullptr) {
        suma += actual->edad;
        contador++;
        actual = actual->next;
    }

    if (contador == 0) return 0.0;
    return (double) suma / contador;
}

//funcion para calcular promedio peso
double promedioPeso(Paciente* head) {
    double suma = 0.0;
    int contador = 0;

    Paciente* actual = head;
    while (actual != nullptr) {
        suma += actual->peso;
        contador++;
        actual = actual->next;
    }

    if (contador == 0) return 0.0;
    return suma / contador;
}

//mostrar imc de lo pacientes
void imprimirIMC(Paciente* head) {
    cout << fixed << setprecision(2); // mostrar 2 decimales
    cout << "IMC de los pacientes:\n";
    cout << "   \n";

    Paciente* actual = head;
    while (actual != nullptr) {
        double imc = actual->peso / (actual->altura * actual->altura);
        cout << " - " << actual->nombre << " tiene un IMC de " << imc << endl;
        actual = actual->next;
    }

}


void liberarLista(Paciente*& head) {
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }
}


int main() {
    Paciente* head = nullptr;

   
    agregarPaciente(head, crearPaciente("Jesus",   23, 60.0, 1.70));
    agregarPaciente(head, crearPaciente("Monica",  56, 80.0, 1.58));
    agregarPaciente(head, crearPaciente("Claudio", 58, 100.0, 1.80));
    agregarPaciente(head, crearPaciente("Tomas",   25, 90.0, 1.86));

    imprimirPacientes(head);

    //calcular y mostrar promedios
    cout << fixed << setprecision(2);
    cout << "el promedio de edad es: " << promedioEdad(head) << " anios\n";
    cout << "el promedio de peso es: " << promedioPeso(head) << " kg\n";

    //llamo para mostart imc
    imprimirIMC(head);

    //liberar memoria
    liberarLista(head);

    return 0;
}
