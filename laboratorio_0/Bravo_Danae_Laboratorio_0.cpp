#include <iostream>
#include <string>
using namespace std;

// Función que determina si un número es par
bool esPar(int numero) {
    return numero % 2 == 0;
}

// Función que devuelve la longitud de un string
int longitudString(const string& texto) {
    return texto.size(); // usamos size() para contar caracteres
}

int main() {
    // 1. Leer un número y mostrarlo
    int numero;
    cout << "Ingresa un numero: ";
    cin >> numero;
    cout << "El numero ingresado es: " << numero << endl;

    // 2. Usar la función esPar con el número ingresado
    if (esPar(numero)) {
        cout << numero << " es par." << endl;
    } else {
        cout << numero << " es impar." << endl;
    }

    // 2. Usar la función esPar con números del 1 al 10
    cout << "Probando numeros del 1 al 10:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << (esPar(i) ? " es par" : " es impar") << endl;
    }

    // 3. Calcular la longitud de un string ingresado por el usuario
    string textoUsuario;
    cout << "Ingresa un texto: ";
    cin.ignore(); // limpia el buffer antes de getline
    getline(cin, textoUsuario);
    cout << "La longitud del texto ingresado es: " << longitudString(textoUsuario) << endl;

    // 3. Calcular la longitud de un string almacenado en el programa
    string textoFijo = "Programacion en C++";
    cout << "El texto \"" << textoFijo << "\" tiene longitud: " << longitudString(textoFijo) << endl;

    return 0;
}