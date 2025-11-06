# Algoritmo de Dijkstra (Laboratorio 6)
### Universidad de Talca — Ingenieria Civil en Bioinformatica  
**Asignatura:** Algoritmos y Estructuras de Datos  
**Unidad II — Implementacion con Matrices**

---

## 📘 Descripcion general

Este programa implementa el **algoritmo de Dijkstra** en **C++**, utilizando una **matriz de adyacencia** para representar un grafo dirigido con pesos no negativos.  
El objetivo es calcular la **distancia minima desde un vertice origen** hasta todos los demas vertices y generar una **visualizacion del grafo original y del grafo resultante** mediante Graphviz.

El programa incluye un **menu interactivo** que permite:
1. Ingresar el grafo y ejecutar el algoritmo de Dijkstra.  
2. Generar automaticamente los grafos visuales (en formato `.png` con Graphviz).  
3. Salir del programa.

---

## Estructura del proyecto

```plaintext
Laboratorio6_Dijkstra/
│
├── dijkstra_matriz.cpp      # Codigo fuente principal en C++
├── grafo_original.dot       # Grafo original generado
├── grafo_resultado.dot      # Grafo resultante del algoritmo
├── grafo_original.png       # Imagen del grafo original
├── grafo_resultado.png      # Imagen del grafo resultante
├── ejemplo_entrada.txt      # Ejemplo de entrada
└── README.md                # Documentacion del proyecto
