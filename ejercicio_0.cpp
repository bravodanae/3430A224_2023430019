#include <iostream>
#include <string>
using namespace std;

struct Paciente {   //estructura para un paciente
    string nombre;
    int edad;
    double peso;
    double altura;
};

//funcion para ir imprimiendo los pacientes
void imprimirPaciente(const Paciente& p) {

    cout << "el paciente se llama: " << p.nombre << endl;
    cout << "su edad es: " << p.edad << " anios" << endl;
    cout << "su peso es: " << p.peso << " kg" << endl;
    cout << "su altura es: " << p.altura << " m" << endl;
    cout << "   " << endl;
}

int main() {
    //creo 4 pacientes de ejemplo
    Paciente a{"Jesus",   23, 60.0, 1.70};
    Paciente b{"Monica",  56, 80.0, 1.58};
    Paciente c{"Claudio", 58, 100.0, 1.80};
    Paciente d{"Tomas",   25, 90.0, 1.86};

    cout << "imprimiendo informacion de pacientes...\n";
    cout << "  " << endl;

    //llamo funcion para ir imprimiendo pacientes
    imprimirPaciente(a);
    imprimirPaciente(b);
    imprimirPaciente(c);
    imprimirPaciente(d);

    return 0;
}
