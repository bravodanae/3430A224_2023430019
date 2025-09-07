#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Paciente {   //estructura para un paciente
    string nombre;
    int edad;
    double peso;
    double altura;
};

//funcion para ir imprimiendo los pacientes

void imprimirPaciente(const Paciente& p, int indice) {
    cout << "paciente numero " << indice << ":\n";
    cout << "el paciente se llama: " << p.nombre << endl;
    cout << "su edad es: " << p.edad << " anios" << endl;
    cout << "su peso es: " << p.peso << " kg" << endl;
    cout << "su altura es: " << p.altura << " m" << endl;
    cout << "  " << endl;
}

int main() {
    
    //creo 4 pacientes de ejemplo
    Paciente a{"Jesus",   23, 60.0, 1.70};
    Paciente b{"Monica",  56, 80.0, 1.58};
    Paciente c{"Claudio", 58, 100.0, 1.80};
    Paciente d{"Tomas",   25, 90.0, 1.86};

    // Guardarlos en un arreglo dinamico (vector)
    vector<Paciente> pacientes = {a, b, c, d};

    cout << "imprimiendo informacion de pacientes... \n";
    cout << "   " << endl;

    //creo contador y para el ciclo a llegar a 4
    for (size_t i = 0; i < pacientes.size(); i++) { //voy incrementando el contador para que for recorra todos los indices
        imprimirPaciente(pacientes[i], i + 1); //accedo a la posicion i del vector e imprimo
    }

    return 0;
}
