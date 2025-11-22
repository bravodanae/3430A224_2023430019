#include <bits/stdc++.h>
using namespace std;

const int TABLE_SIZE = 20;
const int EMPTY = INT_MIN; // marcador de casilla vacia

// FUNCIONES HASH

int hash1(int key) {
    int h = key % TABLE_SIZE;
    if (h < 0) h += TABLE_SIZE;
    return h;
}

int hash2(int key) {
    // Debe ser distinto de 0 y preferible primo relativo a TABLE_SIZE
    return 1 + (abs(key) % (TABLE_SIZE - 1));
}

//ESTRUCTURAS

// Tabla para direccion abierta (Lineal, Cuadratica, Doble)
struct OpenTable {
    vector<int> table;
    OpenTable(): table(TABLE_SIZE, EMPTY) {}

    void print() const {
        cout << "\nTabla Hash (direccion abierta):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "[" << i << "]: ";
            if (table[i] == EMPTY) cout << "(vacio)";
            else cout << table[i];
            cout << "\n";
        }
    }

    bool full() const {
        for (int i = 0; i < TABLE_SIZE; ++i)
            if (table[i] == EMPTY) return false;
        return true;
    }
};

// Tabla para encadenamiento (listas enlazadas)
struct ChainTable {
    vector<list<int>> buckets;
    ChainTable(): buckets(TABLE_SIZE) {}

    void print() const {
        cout << "\nTabla Hash (encadenamiento) - Formato B:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Posicion " << i << ": ";
            if (buckets[i].empty()) {
                cout << "(vacio)\n";
            } else {
                bool first = true;
                for (int v : buckets[i]) {
                    if (!first) cout << " -> ";
                    cout << v;
                    first = false;
                }
                cout << "\n";
            }
        }
    }
};

//INSERTAR: PRUEBA LINEAL

void insert_linear(OpenTable &T, int key) {
    if (T.full()) {
        cout << "Tabla llena. No se puede insertar " << key << ".\n";
        return;
    }
    int h = hash1(key);
    cout << "Insertar " << key << " | hash inicial = " << h << "\n";
    int i = 0;
    int pos = -1;
    while (i < TABLE_SIZE) {
        int idx = (h + i) % TABLE_SIZE;
        if (T.table[idx] == EMPTY) {
            T.table[idx] = key;
            pos = idx;
            cout << "Colision? " << (i == 0 ? "no" : "si")
                 << " | desplazamiento final = " << i
                 << " | posicion final = " << pos << "\n";
            break;
        } else {
            if (i == 0) {
                cout << "Colision en posicion " << idx << " (valor existente: " << T.table[idx] << ")\n";
            } else {
                cout << "Prueba " << i << " -> posicion " << idx << " ocupada (valor: " << T.table[idx] << ")\n";
            }
        }
        ++i;
    }
    if (pos == -1) cout << "No se encontro ubicacion para " << key << ".\n";
    T.print();
}

//INSERTAR: PRUEBA CUADRATICA
void insert_quadratic(OpenTable &T, int key) {
    if (T.full()) {
        cout << "Tabla llena. No se puede insertar " << key << ".\n";
        return;
    }
    int h = hash1(key);
    cout << "Insertar " << key << " | hash inicial = " << h << "\n";
    int i = 0;
    int pos = -1;
    while (i < TABLE_SIZE) {
        int idx = (h + i * i) % TABLE_SIZE;
        if (T.table[idx] == EMPTY) {
            T.table[idx] = key;
            pos = idx;
            cout << "Colision? " << (i == 0 ? "no" : "si")
                 << " | desplazamiento final = " << i
                 << " | posicion final = " << pos << "\n";
            break;
        } else {
            if (i == 0) {
                cout << "Colision en posicion " << idx << " (valor existente: " << T.table[idx] << ")\n";
            } else {
                cout << "Prueba " << i << " -> posicion " << idx << " ocupada (valor: " << T.table[idx] << ")\n";
            }
        }
        ++i;
    }
    if (pos == -1) cout << "No se encontro ubicacion para " << key << " (posible ciclo en cuadratica).\n";
    T.print();
}

// INSERTAR: DOBLE HASH
void insert_double(OpenTable &T, int key) {
    if (T.full()) {
        cout << "Tabla llena. No se puede insertar " << key << ".\n";
        return;
    }
    int h = hash1(key);
    int h2 = hash2(key);
    cout << "Insertar " << key << " | hash1 = " << h << " | hash2 = " << h2 << "\n";
    int i = 0;
    int pos = -1;
    while (i < TABLE_SIZE) {
        int idx = (h + i * h2) % TABLE_SIZE;
        if (T.table[idx] == EMPTY) {
            T.table[idx] = key;
            pos = idx;
            cout << "Colision? " << (i == 0 ? "no" : "si")
                 << " | desplazamiento final = " << i
                 << " | posicion final = " << pos << "\n";
            break;
        } else {
            if (i == 0) {
                cout << "Colision en posicion " << idx << " (valor existente: " << T.table[idx] << ")\n";
            } else {
                cout << "Prueba " << i << " -> posicion " << idx << " ocupada (valor: " << T.table[idx] << ")\n";
            }
        }
        ++i;
    }
    if (pos == -1) cout << "No se encontro ubicacion para " << key << ".\n";
    T.print();
}

//INSERTAR: ENCADENAMIENTO
void insert_chaining(ChainTable &C, int key) {
    int h = hash1(key);
    cout << "Insertar " << key << " | bucket = " << h << "\n";
    if (!C.buckets[h].empty()) {
        cout << "Colision en bucket " << h << " | desplazamiento final = " << C.buckets[h].size() << "\n";
    } else {
        cout << "Colision? no | desplazamiento final = 0\n";
    }
    C.buckets[h].push_back(key);
    C.print();
}

//BUSCAR: LINEAL
void search_linear(const OpenTable &T, int key) {
    int h = hash1(key);
    cout << "Buscar " << key << " | hash inicial = " << h << "\n";
    int i = 0;
    bool found = false;
    while (i < TABLE_SIZE) {
        int idx = (h + i) % TABLE_SIZE;
        if (T.table[idx] == key) {
            cout << "Encontrado en posicion " << idx << " | desplazamiento = " << i << "\n";
            found = true;
            break;
        } else if (T.table[idx] == EMPTY) {
            cout << "No encontrado. Se detuvo en posicion vacia " << idx << " | desplazamiento = " << i << "\n";
            break;
        }
        ++i;
    }
    if (!found && i >= TABLE_SIZE) cout << "No encontrado tras explorar toda la tabla.\n";
}

// BUSCAR: CUADRATICA
void search_quadratic(const OpenTable &T, int key) {
    int h = hash1(key);
    cout << "Buscar " << key << " | hash inicial = " << h << "\n";
    int i = 0;
    bool found = false;
    while (i < TABLE_SIZE) {
        int idx = (h + i * i) % TABLE_SIZE;
        if (T.table[idx] == key) {
            cout << "Encontrado en posicion " << idx << " | desplazamiento = " << i << "\n";
            found = true;
            break;
        } else if (T.table[idx] == EMPTY) {
            cout << "No encontrado. Se detuvo en posicion vacia " << idx << " | desplazamiento = " << i << "\n";
            break;
        }
        ++i;
    }
    if (!found && i >= TABLE_SIZE) cout << "No encontrado tras explorar (posibles colisiones en cuadratica).\n";
}

//BUSCAR: DOBLE HASH

void search_double(const OpenTable &T, int key) {
    int h = hash1(key);
    int h2 = hash2(key);
    cout << "Buscar " << key << " | hash1 = " << h << " | hash2 = " << h2 << "\n";
    int i = 0;
    bool found = false;
    while (i < TABLE_SIZE) {
        int idx = (h + i * h2) % TABLE_SIZE;
        if (T.table[idx] == key) {
            cout << "Encontrado en posicion " << idx << " | desplazamiento = " << i << "\n";
            found = true;
            break;
        } else if (T.table[idx] == EMPTY) {
            cout << "No encontrado. Se detuvo en posicion vacia " << idx << " | desplazamiento = " << i << "\n";
            break;
        }
        ++i;
    }
    if (!found && i >= TABLE_SIZE) cout << "No encontrado tras explorar toda la tabla.\n";
}

// BUSCAR: ENCADENAMIENTO 

void search_chaining(const ChainTable &C, int key) {
    int h = hash1(key);
    cout << "Buscar " << key << " | bucket = " << h << "\n";
    int disp = 0;
    bool found = false;
    for (int v : C.buckets[h]) {
        if (v == key) {
            cout << "Encontrado en bucket " << h << " | desplazamiento = " << disp << "\n";
            found = true;
            break;
        }
        ++disp;
    }
    if (!found) cout << "No encontrado en bucket " << h << ".\n";
}

//MENUS

void menu_linear() {
    OpenTable T;
    while (true) {
        cout << "\n--- Menu Hash (Prueba Lineal) ---\n";
        cout << "1) Insertar valor\n2) Buscar valor\n3) Mostrar tabla\n4) Salir\nElige una opcion: ";
        int op;
        if (!(cin >> op)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
        if (op == 1) {
            cout << "Ingresa valor a insertar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            insert_linear(T, v);
        } else if (op == 2) {
            cout << "Ingresa valor a buscar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            search_linear(T, v);
        } else if (op == 3) {
            T.print();
        } else if (op == 4) {
            cout << "Saliendo...\n";
            break;
        } else {
            cout << "Opcion invalida.\n";
        }
    }
}

void menu_quadratic() {
    OpenTable T;
    while (true) {
        cout << "\n--- Menu Hash (Prueba Cuadratica) ---\n";
        cout << "1) Insertar valor\n2) Buscar valor\n3) Mostrar tabla\n4) Salir\nElige una opcion: ";
        int op;
        if (!(cin >> op)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
        if (op == 1) {
            cout << "Ingresa valor a insertar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            insert_quadratic(T, v);
        } else if (op == 2) {
            cout << "Ingresa valor a buscar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            search_quadratic(T, v);
        } else if (op == 3) {
            T.print();
        } else if (op == 4) {
            cout << "Saliendo...\n";
            break;
        } else {
            cout << "Opcion invalida.\n";
        }
    }
}

void menu_double() {
    OpenTable T;
    while (true) {
        cout << "\n--- Menu Hash (Doble Hash) ---\n";
        cout << "1) Insertar valor\n2) Buscar valor\n3) Mostrar tabla\n4) Salir\nElige una opcion: ";
        int op;
        if (!(cin >> op)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
        if (op == 1) {
            cout << "Ingresa valor a insertar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            insert_double(T, v);
        } else if (op == 2) {
            cout << "Ingresa valor a buscar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            search_double(T, v);
        } else if (op == 3) {
            T.print();
        } else if (op == 4) {
            cout << "Saliendo...\n";
            break;
        } else {
            cout << "Opcion invalida.\n";
        }
    }
}

void menu_chaining() {
    ChainTable C;
    while (true) {
        cout << "\n--- Menu Hash (Encadenamiento) ---\n";
        cout << "1) Insertar valor\n2) Buscar valor\n3) Mostrar tabla\n4) Salir\nElige una opcion: ";
        int op;
        if (!(cin >> op)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
        if (op == 1) {
            cout << "Ingresa valor a insertar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            insert_chaining(C, v);
        } else if (op == 2) {
            cout << "Ingresa valor a buscar: ";
            int v; if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Entrada invalida.\n"; continue; }
            search_chaining(C, v);
        } else if (op == 3) {
            C.print();
        } else if (op == 4) {
            cout << "Saliendo...\n";
            break;
        } else {
            cout << "Opcion invalida.\n";
        }
    }
}

//MAIN 

int main(int argc, char* argv[]) {
    cout << "Laboratorio 9 - Tabla Hash\n";
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " {L|C|D|E}\n";
        cout << "L = Prueba Lineal, C = Prueba Cuadratica, D = Doble Hash, E = Encadenamiento\n";
        return 1;
    }
    string metodo = argv[1];
    if (metodo == "L") {
        menu_linear();
    } else if (metodo == "C") {
        menu_quadratic();
    } else if (metodo == "D") {
        menu_double();
    } else if (metodo == "E") {
        menu_chaining();
    } else {
        cout << "Parametro invalido. Use L, C, D o E.\n";
        return 1;
    }
    return 0;
}