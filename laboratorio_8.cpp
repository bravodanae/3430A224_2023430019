#include <bits/stdc++.h>
using namespace std;


// Funcion para imprimir un vector

void print_array(const vector<int>& a) {
    for(size_t i = 0; i < a.size(); i++) {
        cout << "a[" << i << "]=" << a[i];
        if(i + 1 < a.size()) cout << " ";
    }
    cout << "\n";
}


// Funcion para generar un vector aleatorio de tamano n

vector<int> generate_random(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = rand() % 100000; // numeros entre 0 y 99999
    }
    return v;
}

// Mtodos de ordenamiento

// Burbuja
void bubble_sort(vector<int>& a) {
    int n = a.size();
    for(int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for(int j = 0; j < n - 1 - i; j++) {
            if(a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        // Si no hubo intercambios, el arreglo ya esta ordenado
        if(!swapped) break;
    }
}

// Insercion
void insertion_sort(vector<int>& a) {
    int n = a.size();
    for(int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Seleccion
void selection_sort(vector<int>& a) {
    int n = a.size();
    for(int i = 0; i < n - 1; i++) {
        int minidx = i;
        for(int j = i + 1; j < n; j++) {
            if(a[j] < a[minidx]) minidx = j;
        }
        swap(a[i], a[minidx]);
    }
}

// Shellsort
void shell_sort(vector<int>& a) {
    int n = a.size();
    for(int gap = n / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = a[i];
            int j = i;
            // Comparacion saltando de gap en gap
            while(j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

// Quicksort clasico
int partition_q(vector<int>& a, int low, int high) {
    int pivot = a[high]; // pivote = ultimo elemento
    int i = low - 1;
    for(int j = low; j < high; j++) {
        if(a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quick_sort_rec(vector<int>& a, int low, int high) {
    if(low < high) {
        int pi = partition_q(a, low, high);
        quick_sort_rec(a, low, pi - 1);
        quick_sort_rec(a, pi + 1, high);
    }
}

void quick_sort(vector<int>& a) {
    if(!a.empty()) quick_sort_rec(a, 0, a.size() - 1);
}

// PROGRAMA PRINCIPAL CON MENU INTERACTIVO

int main() {
    srand(time(NULL));

    int N = 0;               // cantidad de elementos
    char ver = 'n';          // mostrar o no mostrar vectores
    bool datos_listos = false;
    vector<int> original;    // vector aleatorio generado

    while(true) {

    
        // Menu principal
        cout << "\n===== Menu Laboratorio 8 =====\n";
        cout << "1) Ingresar cantidad de elementos\n";
        cout << "2) Elegir si mostrar vectores (s/n)\n";
        cout << "3) Ejecutar ordenamientos\n";
        cout << "4) Salir del programa\n";
        cout << "Seleccione una opcion: ";

        int opcion;
        cin >> opcion;

        // Opcion 1: generar vector
        if(opcion == 1) {
            cout << "Ingrese cantidad de elementos: ";
            cin >> N;

            if(N <= 0) {
                cout << "Valor invalido.\n";
            } else {
                original = generate_random(N);
                datos_listos = true;
                cout << "Vector generado correctamente.\n";
            }
        }

        // Opcion 2: elegir si mostrar vectores
        else if(opcion == 2) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Mostrar vectores? (s/n): ";
            cin >> ver;

            if(ver!='s' && ver!='n'){
                cout << "Entrada invalida, se usara 'n'.\n";
                ver = 'n';
            }
        }


        // Opcion 3: ejecutar metodos de ordenamiento
        else if(opcion == 3) {

            if(!datos_listos) {
                cout << "Debe generar el vector primero (opcion 1).\n";
                continue;
            }

            if(ver == 's') {
                cout << "\nVector original:\n";
                print_array(original);
            }

            vector<int> a;
            auto t1 = chrono::high_resolution_clock::now();
            auto t2 = chrono::high_resolution_clock::now();

            cout << "\n--- Tiempos de ejecucion (ms) ---\n";

            // burbuja
            a = original;
            t1 = chrono::high_resolution_clock::now();
            bubble_sort(a);
            t2 = chrono::high_resolution_clock::now();
            cout << "Burbuja: " << chrono::duration<double,milli>(t2 - t1).count() << "\n";

            // insercion
            a = original;
            t1 = chrono::high_resolution_clock::now();
            insertion_sort(a);
            t2 = chrono::high_resolution_clock::now();
            cout << "Insercion: " << chrono::duration<double,milli>(t2 - t1).count() << "\n";

            // seleccion
            a = original;
            t1 = chrono::high_resolution_clock::now();
            selection_sort(a);
            t2 = chrono::high_resolution_clock::now();
            cout << "Seleccion: " << chrono::duration<double,milli>(t2 - t1).count() << "\n";

            // shellsort
            a = original;
            t1 = chrono::high_resolution_clock::now();
            shell_sort(a);
            t2 = chrono::high_resolution_clock::now();
            cout << "Shellsort: " << chrono::duration<double,milli>(t2 - t1).count() << "\n";

            // quicksort
            a = original;
            t1 = chrono::high_resolution_clock::now();
            quick_sort(a);
            t2 = chrono::high_resolution_clock::now();
            cout << "Quicksort: " << chrono::duration<double,milli>(t2 - t1).count() << "\n";

            if(ver == 's') {
                cout << "\nVectores ordenados:\n";

                a = original; bubble_sort(a);
                cout << "Burbuja: ";
                print_array(a);

                a = original; insertion_sort(a);
                cout << "Insercion: ";
                print_array(a);

                a = original; selection_sort(a);
                cout << "Seleccion: ";
                print_array(a);

                a = original; shell_sort(a);
                cout << "Shellsort: ";
                print_array(a);

                a = original; quick_sort(a);
                cout << "Quicksort: ";
                print_array(a);
            }
        }

        
        // Opcion 4: salir del programa
        else if(opcion == 4) {
            cout << "Cerrando programa...\n";
            break; // fin del ciclo, finaliza el programa
        }

        // Opcion invalida
        else {
            cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
