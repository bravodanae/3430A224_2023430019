Laboratorio 7 - Algoritmo de Prim (Matrices)

Descripcion:
Este programa implementa el Algoritmo de Prim usando una matriz de distancias ingresada por el usuario.
Genera el grafo original y el arbol de costo minimo (MST) en formato DOT y PNG.

Compilacion:
    g++ -std=c++17 -O2 lab7_prim.cpp -o lab7_prim

Ejecucion:
    ./lab7_prim

Flujo del programa:
1. Ingresar N (numero de nodos, mayor que 2).
2. Ingresar matriz de distancias (usar 9999 para representar INF).
3. Ejecutar Prim, mostrar conjunto L y costo total.
4. Generar archivos:
   - grafo_original.dot / grafo_original.png
   - grafo_prim.dot / grafo_prim.png

Ejemplo de matriz:
6
0 6 1 5 9999 9999
6 0 5 9999 3 9999
1 5 0 5 6 4
5 9999 5 0 9999 2
9999 3 6 9999 0 6
9999 9999 4 2 6 0

