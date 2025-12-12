# Proyecto: Alineamiento Global de Secuencias (Needleman-Wunsch)

Estudiante: Danae Bravo 
Asignatura: Algoritmos y Estructuras de Datos 
Archivo principal: proyecto.cpp 


## Descripcion general del proyecto

Este programa implementa el algoritmo de alineamiento global Needleman-Wunsch para comparar dos secuencias de ADN compuestas por las bases A, C, G y T.

El programa permite:

- Leer dos secuencias desde archivos (formato simple o FASTA).
- Ignorar encabezados que comienzan con ">".
- Validar que solo existan letras A, C, G y T.
- Cargar una matriz U desde archivo o usar una matriz por defecto.
- Ejecutar el algoritmo completo: creacion de matriz F, llenado y traceback.
- Mostrar la matriz U, matriz F, alineamiento final y puntaje.
- Calcular el porcentaje de identidad entre las secuencias alineadas.
- Generar un archivo .dot y una imagen PNG usando Graphviz.

## Caracteristicas principales

### Lectura correcta de secuencias
Lee archivos de ADN, limpia encabezados, espacios y valida caracteres.

### Matriz U configurable
- Si se entrega archivo: se carga desde ahi.
- Si no: se usa una matriz simple (match = +2, mismatch = -1).

### Implementacion de Needleman-Wunsch
Incluye:
1. Creacion e inicializacion de matriz F.
2. Llenado por programacion dinamica.
3. Traceback para reconstruir el alineamiento optimo.

### Herramientas extra
- Porcentaje de identidad.
- Archivo .dot para Graphviz.
- Generacion de PNG del alineamiento
