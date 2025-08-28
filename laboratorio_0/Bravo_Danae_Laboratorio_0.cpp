#include <iostream>
#include <string>
using namespace std;

// funcion para determinar si numero es par
bool NumeroPar(int numero) {
    return numero % 2 == 0;
}

// funcion que devuelve la longitud de string
int longitudString(const string& texto) {
    return texto.size(); // size para contar caracteres
}

int main() {
    // Leer un numero
    int numero;
    cout << "ingresa un numero: ";
    cin >> numero;
    cout << "el numero ingresado es: " << numero << endl; //lo imprimo

    // uso funcion numeropar con el numero ingresado
    if (NumeroPar(numero)) {
        cout << numero << " es par" << endl;
    } else {
        cout << numero << " es impar" << endl;
    }

    // uso numeropar con numeros del 1 al 10
    cout << "probando numeros del 1 al 10:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << (NumeroPar(i) ? " es par" : " es impar") << endl;
    }

    //calculo la longitud de un string ingresado por el usuario
    string textoUsuario;
    cout << "ingresa un texto: ";
    cin.ignore(); // limpia el buffer antes de getline
    getline(cin, textoUsuario);
    cout << "la longitud del texto ingresado es: " << longitudString(textoUsuario) << endl;

    // calculo la longitud de un string almacenado en el programa
    string textoFijo = "algoritmo y estructura de datos";
    cout << "El texto \"" << textoFijo << "\" tiene longitud: " << longitudString(textoFijo) << endl;

    return 0;
}