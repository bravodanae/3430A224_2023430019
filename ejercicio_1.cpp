#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
};

void imprimirPaciente(const Paciente& p, int indice) {
    cout << "Paciente numero " << indice << ":\n";
    cout << " - El paciente se llama: " << p.nombre << endl;
    cout << " - Su edad es: " << p.edad << " anios" << endl;
    cout << " - Su peso es: " << p.peso << " kg" << endl;
    cout << " - Su altura es: " << p.altura << " m" << endl;
    cout << "  \n";
}

int main() {
    // pacientes de ejemplo
    Paciente a{"Nicolas", 32, 78.5, 1.76};
    Paciente b{"Monica",   88, 60.2, 1.55};
    Paciente c{"Jesus",   16, 54.3, 1.68};

    // Arreglo de pacientes
    vector<Paciente> pacientes;
    pacientes.push_back(a);
    pacientes.push_back(b);
    pacientes.push_back(c);

    cout << "Mostrando informacion de pacientes almacenados en el arreglo:\n";
    

    // imprimo pacientes desde el vector
    for (size_t i = 0; i < pacientes.size(); i++) {
        imprimirPaciente(pacientes[i], i + 1);
    }

    return 0;
}
