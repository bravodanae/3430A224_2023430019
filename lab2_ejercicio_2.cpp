#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cstdlib> // para atoi

using namespace std;

// estructura que representa un contenedor
struct Contenedor {
    int numero;
    string empresa;

    Contenedor(int num, string emp) : numero(num), empresa(emp) {}
};

// funcion para mostrar el estado de todas las pilas
void mostrarPilas(const vector<stack<Contenedor>> &pilas) {
    for (int i = 0; i < pilas.size(); i++) {
        cout << "Pila " << i + 1 << ": ";
        stack<Contenedor> temp = pilas[i]; // copia de la pila para imprimir
        while (!temp.empty()) {
            Contenedor c = temp.top();
            cout << "[" << c.numero << "/" << c.empresa << "] ";
            temp.pop();
        }
        cout << endl;
    }
}

// funcion que busca y retira un contenedor especifico
void retirarContenedor(int numero, const string &empresa, vector<stack<Contenedor>> &pilas, int n) {
    bool encontrado = false;

    for (int i = 0; i < pilas.size(); i++) {
        if (!encontrado) {
            vector<Contenedor> movidos; // contenedores que se mueven para liberar
            while (!pilas[i].empty()) {
                Contenedor c = pilas[i].top();
                if (c.numero == numero && c.empresa == empresa) {
                    cout << "retirando contenedor [" << c.numero << "/" << c.empresa << "] de la pila " << i + 1 << endl;
                    pilas[i].pop();
                    encontrado = true;
                    break;
                } else {
                    cout << "moviendo contenedor [" << c.numero << "/" << c.empresa << "] de la pila " << i + 1;
                    movidos.push_back(c);
                    pilas[i].pop();
                    // buscar una pila alternativa para colocarlo
                    for (int j = 0; j < pilas.size(); j++) {
                        if (j != i && pilas[j].size() < n) {
                            pilas[j].push(c);
                            cout << " a la pila " << j + 1 << endl;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (!encontrado) {
        cout << "contenedor [" << numero << "/" << empresa << "] no encontrado \n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Uso: ./programa n m\n";
        cout << "n = tamano maximo de cada pila\n";
        cout << "m = numero de pilas\n";
        return 1;
    }

    int n = atoi(argv[1]); // capacidad maxima por pila
    int m = atoi(argv[2]); // numero de pilas

    vector<stack<Contenedor>> pilas(m);

    int cantidad;
    cout << "ingrese cantidad de contenedores a registrar: ";
    cin >> cantidad;

    for (int i = 0; i < cantidad; i++) {
        int numero;
        string empresa;
        int pilaIndex;
        cout << "ingrese numero del contenedor y la empresa: ";
        cin >> numero >> empresa;
        cout << "ingrese numero de pila (1 a " << m << "): ";
        cin >> pilaIndex;
        pilaIndex--; // ajuste para indices base 0
        if (pilas[pilaIndex].size() < n) {
            pilas[pilaIndex].push(Contenedor(numero, empresa));
        } else {
            cout << "la pila " << pilaIndex + 1 << " esta llena, no se pudo agregar\n";
        }
    }

    cout << "\nestado inicial de las pilas:\n";
    mostrarPilas(pilas);

    int numero;
    string empresa;
    cout << "\ningrese el numero y la empresa del contenedor a retirar: ";
    cin >> numero >> empresa;

    retirarContenedor(numero, empresa, pilas, n);

    cout << "\nestado final de las pilas:\n";
    mostrarPilas(pilas);

    return 0;
}
