#include <iostream>
#include <string>
using namespace std;

// estructura paciente
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
};

// funcion para imprimir un paciente
void imprimirPaciente(const Paciente& p) {
    cout << "El paciente se llama: " << p.nombre << endl;
    cout << "Su edad es: " << p.edad << " anios" << endl;
    cout << "Su peso es: " << p.peso << " kg" << endl;
    cout << "Su altura es: " << p.altura << " m" << endl;
    cout << "      \n" ;
}

int main() {
    // pacientes de ejemplo
    Paciente a{"Nicolas", 32, 78.5, 1.76};
    Paciente b{"Monica",   56, 60.2, 1.55};
    Paciente c{"Jesus",   16, 54.3, 1.68};

    cout << "Mostrando informacion de pacientes:\n";

    // Mostrar pacientes
    imprimirPaciente(a);
    imprimirPaciente(b);
    imprimirPaciente(c);

    return 0;
}
