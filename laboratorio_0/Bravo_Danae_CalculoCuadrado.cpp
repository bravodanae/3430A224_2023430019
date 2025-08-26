#include<iostream>
using namespace std;

// funcion que calcula el cuadrado de numero
double square(double x){
        return x*x;
}

int main(){

    double numero = 5;
    cout << "el numero es: " << numero << endl;
    cout << "el cuadrado del numero es :" << square(numero) << endl;

    return 0;
}