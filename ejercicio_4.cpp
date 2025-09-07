#include <iostream>
#include <string>
#include <fstream>    //para leer archivos
#include <sstream>    //para separar campos del CSV
#include <limits>     //para limpiar entradas
#include <iomanip>    //para mostrar decimales
using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* next; //puntero al siguiente nodo de la lista
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

//funcion para eliminar paciente por nombre
bool eliminarPaciente(Paciente*& head, const string& nombre) {
    if (head == nullptr) return false;

    //para eliminar el paciente que es el inicio
    if (head->nombre == nombre) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    //recorremos hasta encontrar el nombre
    Paciente* actual = head;
    while (actual->next != nullptr && actual->next->nombre != nombre) {
        actual = actual->next;
    }

    if (actual->next != nullptr) {
        Paciente* temp = actual->next;
        actual->next = temp->next;
        delete temp;
        return true;
    }
    return false;
}


void imprimirPacientes(Paciente* head) {
    if (head == nullptr) {
        cout << "no hay pacientes registrados.\n";
        return;
    }

    cout << "Lista de pacientes:\n";
    cout << "   \n";

    int numero = 1;
    Paciente* actual = head;
    while (actual != nullptr) {
        cout << "paciente numero " << numero << ":\n";
        cout << "nombre: " << actual->nombre << endl;
        cout << "edad: " << actual->edad << " anios" << endl;
        cout << "peso: " << actual->peso << " kg" << endl;
        cout << "altura: " << actual->altura << " m" << endl;
        cout << "  \n";

        actual = actual->next;
        numero++;
    }
}


void imprimirIMC(Paciente* head) {
    if (head == nullptr) {
        cout << "no hay pacientes registrados \n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "IMC de los pacientes:\n";
    cout << "   \n";

    Paciente* actual = head;
    while (actual != nullptr) {
        double imc = actual->peso / (actual->altura * actual->altura);
        cout << " - " << actual->nombre << " tiene un IMC de " << imc << endl;
        actual = actual->next;
    }
    cout << "    \n";
}

double promedioEdad(Paciente* head) {
    int suma = 0, contador = 0;
    Paciente* actual = head;

    while (actual != nullptr) {
        suma += actual->edad;
        contador++;
        actual = actual->next;
    }
    return (contador == 0) ? 0.0 : (double) suma / contador;
}

double promedioPeso(Paciente* head) {
    double suma = 0.0;
    int contador = 0;
    Paciente* actual = head;

    while (actual != nullptr) {
        suma += actual->peso;
        contador++;
        actual = actual->next;
    }
    return (contador == 0) ? 0.0 : suma / contador;
}

//para cargar del archivo
int cargarDesdeArchivo(Paciente*& head, const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "error " << ruta << endl;
        return 0;
    }

    string linea;
    int cargados = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string nombre, sEdad, sPeso, sAltura;

        if (!getline(ss, nombre, ',')) continue;
        if (!getline(ss, sEdad, ',')) continue;
        if (!getline(ss, sPeso, ',')) continue;
        if (!getline(ss, sAltura, ',')) continue;

        try {
            int edad = stoi(sEdad);
            double peso = stod(sPeso);
            double altura = stod(sAltura);
            agregarPaciente(head, crearPaciente(nombre, edad, peso, altura));
            cargados++;
        } catch (...) {
            cerr << "linea invalida: " << linea << endl;
        }
    }

    return cargados;
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

    int opcion;

    do {
        cout << "\n Menu de gestion de pacientes\n";
        cout << "1) agregar paciente\n";
        cout << "2) eliminar paciente por nombre\n";
        cout << "3) listar pacientes\n";
        cout << "4) mostrar IMC de cada paciente\n";
        cout << "5) mostrar promedio de edad y peso\n";
        cout << "6) cargar pacientes desde archivo CSV/TXT\n";
        cout << "0) salir\n";
        cout << "ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == 1) {
            string nombre; int edad; double peso, altura;
            cout << "ingrese nombre: "; getline(cin, nombre);
            cout << "ingrese edad: "; cin >> edad;
            cout << "ingrese peso (kg): "; cin >> peso;
            cout << "ingrese altura (m): "; cin >> altura;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            agregarPaciente(head, crearPaciente(nombre, edad, peso, altura));
            cout << "paciente agregado correctamente.\n";
        }
        else if (opcion == 2) {
            string nombre;
            cout << "ingrese el nombre del paciente a eliminar: ";
            getline(cin, nombre);

            if (eliminarPaciente(head, nombre)) {
                cout << "paciente eliminado correctamente\n";
            } else {
                cout << "no se encontro el paciente \n";
            }
        }
        else if (opcion == 3) {
            imprimirPacientes(head);
        }
        else if (opcion == 4) {
            imprimirIMC(head);
        }
        else if (opcion == 5) {
            cout << fixed << setprecision(2);
            cout << "promedio de edad: " << promedioEdad(head) << " anios\n";
            cout << "promedio de peso: " << promedioPeso(head) << " kg\n";
        }
        else if (opcion == 6) {
            string ruta;
            cout << "ingrese la ruta del archivo CSV/TXT: ";
            getline(cin, ruta);
            int n = cargarDesdeArchivo(head, ruta);
            cout << n << " pacientes cargados desde archivo.\n";
        }
        else if (opcion == 0) {
            cout << "saliendo del programa...\n";
        }
        else {
            cout << "ppcion invalida \n";
        }

    } while (opcion != 0);

    liberarLista(head);
    return 0;
}
