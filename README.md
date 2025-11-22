
Compilar:
g++ laboratorio_9.cpp -o laboratorio_9

Ejecutar:
./laboratorio_9 L   # Prueba Lineal
./laboratorio_9 C   # Prueba Cuadratica
./laboratorio_9 D   # Doble Hash
./laboratorio_9 E   # Encadenamiento

Menu:
1) Insertar valor
2) Buscar valor
3) Mostrar tabla
4) Salir

Notas importantes:
- La tabla tiene tamano 20 (segun enunciado).
- No se insertan automaticamente los 15 valores; el usuario los ingresa manualmente via menu.
- En cada insercion se informa si hubo colision, la posicion y el desplazamiento final (numero de pruebas necesarias).
- Para encadenamiento la impresion usa el Formato B:
  Posicion 0: 23
  Posicion 1: 42 -> 81 -> 55
  Posicion 2: (vacio)