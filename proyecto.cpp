#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>  
#include <cctype>    
#include <cstdlib>   

using namespace std;

// Convierte una letra (char) a un indice 0..3, segun A,C,G,T.
// Devuelve -1 si el caracter no es valido.
int letraANumeroIndice(char letra) {
    char mayuscula = letra;
    if (mayuscula >= 'a' && mayuscula <= 'z') {
        // convertir minuscula a mayuscula
        mayuscula = char(mayuscula - 'a' + 'A');
    }
    if (mayuscula == 'A') return 0;
    if (mayuscula == 'C') return 1;
    if (mayuscula == 'G') return 2;
    if (mayuscula == 'T') return 3;
    return -1;
}

// Convierte un indice 0..3 a la letra correspondiente A/C/G/T
char indiceANombreLetra(int indice) {
    if (indice == 0) return 'A';
    if (indice == 1) return 'C';
    if (indice == 2) return 'G';
    if (indice == 3) return 'T';
    return '?';
}

/* --------------------------
   Funcion para leer una secuencia desde un archivo
   - Ignora lineas que comienzan con '>' (encabezados FASTA)
   - Elimina espacios en los extremos de cada linea (operacion explicita)
   - Valida que cada caracter sea A,C,G o T (case-insensitive)
   - Devuelve true si se leyo con exito y secuencia no vacia
   - En caso de error, devuelve false y mensajeError contiene la descripcion
   -------------------------- */
//Esta funcion asegura que el algoritmo reciba secuencias limpias y validas, evitando errores posteriores.
bool leerSecuenciaDesdeArchivo(const string &nombreArchivo, string &secuenciaSalida,string &mensajeError) {

    ifstream archivoEntrada;
    archivoEntrada.open(nombreArchivo.c_str());

    if (!archivoEntrada.is_open()) {
        mensajeError = "No fue posible abrir el archivo: " + nombreArchivo;
        return false;
    }

    secuenciaSalida = "";
    string lineaLeida;
    int numeroLinea = 0;

    while (true) {
        if (!getline(archivoEntrada, lineaLeida)) {
            // fin del archivo o error de lectura
            break;
        }
        numeroLinea = numeroLinea + 1;

        // Eliminar espacios al inicio y al final de la linea (implementacion manual)
        int posicionInicio = 0;
        int posicionFin = (int)lineaLeida.length() - 1;

        // avanzar inicio mientras haya espacios o tabulaciones
        while (posicionInicio <= posicionFin &&
               (lineaLeida[posicionInicio] == ' ' || lineaLeida[posicionInicio] == '\t' ||
                lineaLeida[posicionInicio] == '\r' || lineaLeida[posicionInicio] == '\n')) {
            posicionInicio = posicionInicio + 1;
        }

        // mover fin hacia atras mientras haya espacios o tab
        while (posicionFin >= posicionInicio &&
               (lineaLeida[posicionFin] == ' ' || lineaLeida[posicionFin] == '\t' ||
                lineaLeida[posicionFin] == '\r' || lineaLeida[posicionFin] == '\n')) {
            posicionFin = posicionFin - 1;
        }

        // si la linea queda vacia, la ignoramos
        if (posicionInicio > posicionFin) {
            continue;
        }

        // obtener la subcadena sin espacios extremos
        string lineaSinEspacios = "";
        for (int p = posicionInicio; p <= posicionFin; p = p + 1) {
            lineaSinEspacios.push_back(lineaLeida[p]);
        }

        // ignorar lineas que empiecen con '>' (encabezado FASTA)
        if (lineaSinEspacios[0] == '>') {
            continue;
        }

        // validar cada caracter y agregar mayuscula a la secuencia de salida
        for (int k = 0; k < (int)lineaSinEspacios.length(); k = k + 1) {
            char caracterActual = lineaSinEspacios[k];
            char caracterMayuscula = caracterActual;
            if (caracterMayuscula >= 'a' && caracterMayuscula <= 'z') {
                caracterMayuscula = char(caracterMayuscula - 'a' + 'A');
            }
            int indice = letraANumeroIndice(caracterMayuscula);
            if (indice < 0) {
                // caracter no valido
                // Construimos un mensaje de error explicito con posicion aproximada
                string detalle = "Caracter no valido en archivo " + nombreArchivo + " en la linea " + to_string(numeroLinea) +": '" + string(1, caracterActual) + "'. Solo se permiten A, C, G, T.";
                mensajeError = detalle;
                archivoEntrada.close();
                return false;
            }
            // agregar a la secuencia final ya en mayusculas
            secuenciaSalida.push_back(caracterMayuscula);
        }
    }

    archivoEntrada.close();

    if (secuenciaSalida == "") {
        mensajeError = "No se encontro ninguna secuencia valida en el archivo: " + nombreArchivo;
        return false;
    }

    // exito
    return true;
}

/* --------------------------
   Lectura de matriz U (4x4)
   - Intenta leer 16 valores enteros de un archivo
   - Si el archivo no existe o esta vacio, se puede usar UporDefecto llamando a otra funcion
   - Formato tolerante: puede contener token de texto (como encabezados), pero solo tomara los enteros
   -------------------------- */


   // si el ususario desea pasar archivo ( -U matrizU.txt)
bool leerMatrizUDesdeArchivo(const string &nombreArchivo, int matrizU[4][4], string &mensajeError) {

    if (nombreArchivo == "") {
        mensajeError = "Nombre de archivo vacio";
        return false;
    }

    ifstream archivoU;
    archivoU.open(nombreArchivo.c_str());
    if (!archivoU.is_open()) {
        mensajeError = "No se pudo abrir el archivo de la matriz U: " + nombreArchivo;
        return false;
    }

    vector<int> valoresLeidos;
    string linea;
    while (true) {
        if (!getline(archivoU, linea)) break;
        // procesar la linea separando por espacios, comas o tabs
        string token = "";
        for (int i = 0; i < (int)linea.length(); i = i + 1) {
            char c = linea[i];
            if (c == ' ' || c == '\t' || c == ',' ) {
                if (token != "") {
                    // intentar convertir token a entero con stringstream
                    stringstream ss(token);
                    int valor;
                    if (ss >> valor) {
                        valoresLeidos.push_back(valor);
                    }
                    token = "";
                }
            } else {
                token.push_back(c);
            }
        }
        if (token != "") {
            stringstream ss(token);
            int valor;
            if (ss >> valor) {
                valoresLeidos.push_back(valor);
            }
            token = "";
        }
        if ((int)valoresLeidos.size() >= 16) break;
    }

    archivoU.close();

    if ((int)valoresLeidos.size() < 16) {
        mensajeError = "Formato invalido para matriz U. Se esperaban 16 enteros (4x4).";
        return false;
    }

    // llenar matriz U en orden de filas (A,C,G,T)
    int indice = 0;
    for (int fila = 0; fila < 4; fila = fila + 1) {
        for (int columna = 0; columna < 4; columna = columna + 1) {
            matrizU[fila][columna] = valoresLeidos[indice];
            indice = indice + 1;
        }
    }

    return true;
}

// crea la matriz U por defecto.
// La matriz U define los puntajes de coincidencia y diferencia
void matrizUPorDefecto(int matrizU[4][4]) {

    int fila = 0;
    int columna = 0;

    // Recorremos las 4 filas de la matriz
    for (fila = 0; fila < 4; fila = fila + 1) {

        // Recorremos las 4 columnas de la matriz
        for (columna = 0; columna < 4; columna = columna + 1) {

            // Si fila == columna significa que estamos comparando la misma letra
            if (fila == columna) {
                matrizU[fila][columna] = 2; // Puntaje por coincidencia
            }
            else {
                // Si fila y columna no son iguales, significa que las dos letras son distintas.
                matrizU[fila][columna] = -1;    // Puntaje por diferencia
            }
        }
    }
}


/* --------------------------
   Algoritmo Needleman-Wunsch 
   - Entradas: S (secuencia 1), T (secuencia 2) (ambas sin espacios y en mayusculas ACGT)
   - GAP: penalizacion por gap (numero negativo)
   - matrizU: 4x4 de puntajes
   - Salidas: matrizF (n+1 x m+1), alineamientoS, alineamientoT, puntajeFinal
   -------------------------- */

struct ResultadoNW {
    vector< vector<int> > matrizF;
    string alineamientoS;
    string alineamientoT;
    int puntajeFinal;
};


// Funcion que implementa el algoritmo de Needleman-Wunsch
// para alinear dos secuencias S y T.
// Entradas:
//   - secuenciaS: primera secuencia de ADN (string)
//   - secuenciaT: segunda secuencia de ADN (string)
// Salida:
//   - Un objeto ResultadoNW con:
//       matrizF: matriz de programacion dinamica
//       alineamientoS: secuencia S alineada
//       alineamientoT: secuencia T alineada
//       puntajeFinal: puntaje total del alineamiento
// -------------------------------------------------------------------------
ResultadoNW resolverNeedlemanWunsch(const string &secuenciaS, const string &secuenciaT, int penalizacionGap, int matrizU[4][4])
{
    ResultadoNW resultado;

    // Largo de cada secuencia
    int largoS = (int)secuenciaS.length();
    int largoT = (int)secuenciaT.length();


    // CREACION E INICIALIZACION DE LA MATRIZ F
    // La matriz F tendra (largoS + 1) filas y (largoT + 1) columnas.
    // La primera fila y columna representan el alineamiento contra vacio

    int numeroFilas = largoS + 1;
    int numeroColumnas = largoT + 1;

    vector< vector<int> > matrizF;
    matrizF.resize(numeroFilas);

    for (int fila = 0; fila < numeroFilas; fila = fila + 1) {
        matrizF[fila].resize(numeroColumnas);

        for (int columna = 0; columna < numeroColumnas; columna = columna + 1) {
            matrizF[fila][columna] = 0;
        }
    }

    // Inicializar primera columna (solo gaps verticales)
    for (int fila = 1; fila < numeroFilas; fila = fila + 1) {
        matrizF[fila][0] = matrizF[fila - 1][0] + penalizacionGap;
    }

    // Inicializar primera fila (solo gaps horizontales)
    for (int columna = 1; columna < numeroColumnas; columna = columna + 1) {
        matrizF[0][columna] = matrizF[0][columna - 1] + penalizacionGap;
    }

    //  RELLENAR LA MATRIZ F (PROGRAMACION DINAMICA)
    //  Para cada celda (fila, columna) calculamos:
    //   - puntajeDiagonal  (match o mismatch)
    //   - puntajeArriba    (gap en T)
    //   - puntajeIzquierda (gap en S)

    for (int fila = 1; fila < numeroFilas; fila = fila + 1) {
        for (int columna = 1; columna < numeroColumnas; columna = columna + 1) {

            // Letras actuales
            char letraS = secuenciaS[fila - 1];
            char letraT = secuenciaT[columna - 1];

            // Convertimos cada letra a un indice (A=0, C=1, G=2, T=3)
            int indiceS = letraANumeroIndice(letraS);
            int indiceT = letraANumeroIndice(letraT);

            // Movimiento diagonal (coincidencia o diferencia)
            int puntajeDiagonal =
                matrizF[fila - 1][columna - 1] + matrizU[indiceS][indiceT];

            // Movimiento desde arriba (gap en T)
            int puntajeArriba =
                matrizF[fila - 1][columna] + penalizacionGap;

            // Movimiento desde la izquierda (gap en S)
            int puntajeIzquierda =
                matrizF[fila][columna - 1] + penalizacionGap;

            // Elegimos el mejor de los tres
            int mejorPuntaje = puntajeDiagonal;

            if (puntajeArriba > mejorPuntaje) {
                mejorPuntaje = puntajeArriba;
            }
            if (puntajeIzquierda > mejorPuntaje) {
                mejorPuntaje = puntajeIzquierda;
            }

            matrizF[fila][columna] = mejorPuntaje;
        }
    }

    //  TRACEBACK – RECONSTRUIR EL ALINEAMIENTO
    // Se comienza desde matrizF[largoS][largoT] e iremos retrocediendo
    // hasta llegar a la celda [0][0].
    // En cada paso decidimos si el movimiento fue:
    //   - diagonal     match o mismatch
    //   - arriba       gap en T
    //   - izquierda    gap en S

    int fila = largoS;
    int columna = largoT;

    string alineadoSReves = "";
    string alineadoTReves = "";

    while (fila > 0 || columna > 0) {

        bool puedeIrDiagonal = (fila > 0 && columna > 0);

        if (puedeIrDiagonal) {

            char letraS = secuenciaS[fila - 1];
            char letraT = secuenciaT[columna - 1];

            int indiceS = letraANumeroIndice(letraS);
            int indiceT = letraANumeroIndice(letraT);

            int puntajeDiagonal =
                matrizF[fila - 1][columna - 1] + matrizU[indiceS][indiceT];

            // Si el valor actual coincide con la diagonal, venimos de ahi
            if (matrizF[fila][columna] == puntajeDiagonal) {
                alineadoSReves.push_back(letraS);
                alineadoTReves.push_back(letraT);
                fila = fila - 1;
                columna = columna - 1;
                continue;
            }
        }

        // Revision del movimiento hacia arriba (gap en T)
        if (fila > 0) {

            int puntajeArriba = matrizF[fila - 1][columna] + penalizacionGap;

            if (matrizF[fila][columna] == puntajeArriba) {
                alineadoSReves.push_back(secuenciaS[fila - 1]);
                alineadoTReves.push_back('-');
                fila = fila - 1;
                continue;
            }
        }

        // Movimiento hacia la izquierda (gap en S)
        if (columna > 0) {
            alineadoSReves.push_back('-');
            alineadoTReves.push_back(secuenciaT[columna - 1]);
            columna = columna - 1;
            continue;
        }

        // Seguridad si algo inesperado ocurre
        break;
    }

    // INVERTIR LOS ALINEAMIENTOS (se construyeron al reves)

    string alineadoS = "";
    string alineadoT = "";

    for (int x = (int)alineadoSReves.length() - 1; x >= 0; x = x - 1) {
        alineadoS.push_back(alineadoSReves[x]);
    }
    for (int x = (int)alineadoTReves.length() - 1; x >= 0; x = x - 1) {
        alineadoT.push_back(alineadoTReves[x]);
    }

    // Guardar resultados en la estructura ResultadoNW
    resultado.matrizF = matrizF;
    resultado.alineamientoS = alineadoS;
    resultado.alineamientoT = alineadoT;
    resultado.puntajeFinal = matrizF[largoS][largoT];

    return resultado;
}


// Funcion: calcularPorcentajeIdentidad
// Esta funcion calcula el porcentaje de identidad entre dos secuencias
// que ya estan alineadas (alineadoS y alineadoT)
// - Se comparan ambas cadenas posicion por posicion.
// - Si en la misma posicion hay la MISMA letra (A,C,G,T), se cuenta
//   como una coincidencia.
// - Si ambos tienen '-', NO se cuenta como coincidencia.
// - El porcentaje final es:
//
//         (coincidencias / largoAlineamiento) * 100
//
// Donde largoAlineamiento es la cantidad total de posiciones del alineamiento
double calcularPorcentajeIdentidad(const string &alineadoS,
                                   const string &alineadoT)
{
    // Si por algun motivo las longitudes no coinciden, el alineamiento es invalido
    if ((int)alineadoS.length() != (int)alineadoT.length()) {
        return 0.0;
    }

    int largoAlineamiento = (int)alineadoS.length();

    // Evitar division por cero en casos extremos
    if (largoAlineamiento == 0) {
        return 0.0;
    }

    int cantidadCoincidencias = 0;

    // Recorrer cada posicion del alineamiento
    for (int posicion = 0; posicion < largoAlineamiento; posicion = posicion + 1) {

        char letraS = alineadoS[posicion];
        char letraT = alineadoT[posicion];

        // Contar coincidencia verdadera: misma letra y que no sea '-'
        if (letraS == letraT && letraS != '-') {
            cantidadCoincidencias = cantidadCoincidencias + 1;
        }
    }

    // Calcular porcentaje de identidad
    double porcentaje =
        (100.0 * (double)cantidadCoincidencias) / (double)largoAlineamiento;

    return porcentaje;
}


/* Generar archivo .dot simple para representar alineamiento
   - Estructura: un grafo con dos nodos principales (S y T) que contienen tablas con las columnas del alineamiento */

bool generarArchivoDot(const string &alineadoS, const string &alineadoT, const string &nombreArchivoDot, string &mensajeError) {
    if ((int)alineadoS.length() != (int)alineadoT.length()) {
        mensajeError = "Alineamientos tienen longitudes distintas, no se puede generar .dot";
        return false;
    }
    ofstream archivoDot;
    archivoDot.open(nombreArchivoDot.c_str());
    if (!archivoDot.is_open()) {
        mensajeError = "No se pudo abrir para escribir el archivo .dot: " + nombreArchivoDot;
        return false;
    }

    archivoDot << "digraph alineamiento {\n";
    archivoDot << "  rankdir = LR;\n";
    archivoDot << "  node [shape=plaintext,fontname=\"Monospace\"];\n";

    archivoDot << "  S [label=<\n";
    archivoDot << "    <table border='0' cellborder='1' cellspacing='0'>\n";
    archivoDot << "      <tr>\n";
    for (int i = 0; i < (int)alineadoS.length(); i = i + 1) {
        archivoDot << "        <td>" << alineadoS[i] << "</td>\n";
    }
    archivoDot << "      </tr>\n";
    archivoDot << "    </table>\n";
    archivoDot << "  >];\n";

    archivoDot << "  T [label=<\n";
    archivoDot << "    <table border='0' cellborder='1' cellspacing='0'>\n";
    archivoDot << "      <tr>\n";
    for (int i = 0; i < (int)alineadoT.length(); i = i + 1) {
        archivoDot << "        <td>" << alineadoT[i] << "</td>\n";
    }
    archivoDot << "      </tr>\n";
    archivoDot << "    </table>\n";
    archivoDot << "  >];\n";

    archivoDot << "}\n";

    archivoDot.close();
    return true;
}

// Funcion: imprimirMatrizU
// Esta funcion muestra en pantalla la matriz U utilizada para calcular los
// puntajes de coincidencias y diferencias entre las bases A, C, G y T.
// La matriz se muestra de forma ordenada, con filas y columnas claramente
// etiquetadas para que cualquier persona pueda interpretarla facilmente.
void imprimirMatrizU(int matrizU[4][4])
{
    // Encabezado de columnas
    cout << "\nMatriz U (match/mismatch):\n\n";
    cout << "       A    C    G    T\n";
    cout << "     ---------------------\n";

    // Recorremos las filas
    for (int fila = 0; fila < 4; fila = fila + 1) {

        // Nombre de la base correspondiente a la fila (A, C, G o T)
        char letraFila = indiceANombreLetra(fila);

        // Imprimir etiqueta de fila
        cout << "  " << letraFila << " |";

        // Recorrer columnas de la matriz
        for (int columna = 0; columna < 4; columna = columna + 1) {

            // Imprimir el valor alineado
            cout << setw(5) << matrizU[fila][columna];
        }

        cout << "\n";
    }

    cout << "\n";
}


// Funcion: imprimirMatrizF
// Esta funcion muestra en pantalla la matriz F generada por el algoritmo
// Needleman-Wunsch. La matriz F es la base del proceso de programacion
// dinamica y contiene los puntajes usados para construir el alineamiento.
void imprimirMatrizF(const vector< vector<int> > &matrizF)
{
    int numeroFilas = matrizF.size();
    int numeroColumnas = matrizF[0].size();

    cout << "\n---------------------------------------------\n";
    cout << " MATRIZ F (Programacion Dinamica - Needleman-Wunsch)\n";
    cout << "---------------------------------------------\n\n";

    // Imprimir encabezado columnas
    cout << "         "; // espacio inicial

    for (int columna = 0; columna < numeroColumnas; columna = columna + 1) {
        cout << setw(6) << columna;  // Numero de columna
    }
    cout << "\n";

    // Linea separadora
    cout << "         ";
    for (int columna = 0; columna < numeroColumnas; columna = columna + 1) {
        cout << "------";
    }
    cout << "\n";

    // Imprimir filas de la matriz
    for (int fila = 0; fila < numeroFilas; fila = fila + 1) {

        cout << "Fila " << setw(2) << fila << " |";  // Etiqueta de fila

        for (int columna = 0; columna < numeroColumnas; columna = columna + 1) {
            cout << setw(6) << matrizF[fila][columna];  // Valor de celda
        }

        cout << "\n";
    }

    cout << "\n";
}



int main(int cantidadArgumentos, char *listaArgumentos[])
{
    string nombreArchivoSecuencia1 = "";
    string nombreArchivoSecuencia2 = "";
    string nombreArchivoMatrizU = "";
    int penalizacionPorGap = -2;   // Valor por defecto 

    // LECTURA DE ARGUMENTOS DESDE LA TERMINAL
    
    for (int indice = 1; indice < cantidadArgumentos; indice = indice + 1) {

        string argumento = listaArgumentos[indice];

        if (argumento == "-C1" && indice + 1 < cantidadArgumentos) {
            nombreArchivoSecuencia1 = listaArgumentos[indice + 1];
            indice = indice + 1;
        }
        else if (argumento == "-C2" && indice + 1 < cantidadArgumentos) {
            nombreArchivoSecuencia2 = listaArgumentos[indice + 1];
            indice = indice + 1;
        }
        else if (argumento == "-U" && indice + 1 < cantidadArgumentos) {
            nombreArchivoMatrizU = listaArgumentos[indice + 1];
            indice = indice + 1;
        }
        else if (argumento == "-V" && indice + 1 < cantidadArgumentos) {

            string textoNumero = listaArgumentos[indice + 1];
            stringstream convertidor(textoNumero);
            int numeroLeido = 0;

            if (convertidor >> numeroLeido) {
                penalizacionPorGap = numeroLeido;
            }

            indice = indice + 1;
        }
        // cualquier otro argumento se ignora
    }

    // SI NO SE ENTREGAN ARCHIVOS POR PARAMETRO, SE PIDEN POR CONSOLA
    if (nombreArchivoSecuencia1 == "") {
        cout << "Ingrese el archivo de la secuencia 1 (o Enter para salir): ";
        getline(cin, nombreArchivoSecuencia1);

        if (nombreArchivoSecuencia1 == "") {
            cout << "No se ingreso archivo de secuencia 1. Saliendo.\n";
            return 0;
        }
    }

    if (nombreArchivoSecuencia2 == "") {
        cout << "Ingrese el archivo de la secuencia 2 (o Enter para salir): ";
        getline(cin, nombreArchivoSecuencia2);

        if (nombreArchivoSecuencia2 == "") {
            cout << "No se ingreso archivo de secuencia 2. Saliendo.\n";
            return 0;
        }
    }


    // LECTURA DE LAS SECUENCIAS DESDE ARCHIVO
    string secuencia1;
    string secuencia2;
    string mensajeError;

    if (!leerSecuenciaDesdeArchivo(nombreArchivoSecuencia1, secuencia1, mensajeError)) {
        cout << "Error al leer la secuencia 1: " << mensajeError << "\n";
        return 1;
    }

    if (!leerSecuenciaDesdeArchivo(nombreArchivoSecuencia2, secuencia2, mensajeError)) {
        cout << "Error al leer la secuencia 2: " << mensajeError << "\n";
        return 1;
    }


    // LECTURA DE MATRIZ U O USAR MATRIZ POR DEFECTO
    int matrizU[4][4];
    bool lecturaCorrecta = false;

    if (nombreArchivoMatrizU != "") {

        lecturaCorrecta = leerMatrizUDesdeArchivo(nombreArchivoMatrizU, matrizU, mensajeError);

        if (!lecturaCorrecta) {
            cout << "Advertencia: No se pudo leer la matriz U desde archivo.\n";
            cout << "Motivo: " << mensajeError << "\n";
            cout << "Se utilizara la matriz U por defecto.\n";
            matrizUPorDefecto(matrizU);
        }

    } else {
        matrizUPorDefecto(matrizU);
    }


    // EJECUTAR NEEDLEMAN–WUNSCH
    ResultadoNW resultado =
        resolverNeedlemanWunsch(secuencia1, secuencia2, penalizacionPorGap, matrizU);


    // MENU INTERACTIVO DEL PROGRAMA
    while (true) {

        cout << "\n============== MENU PRINCIPAL ==============\n";
        cout << "1) Mostrar matriz U (puntajes)\n";
        cout << "2) Mostrar matriz F (programacion dinamica)\n";
        cout << "3) Generar archivo .dot del alineamiento\n";
        cout << "4) Generar imagen PNG (Graphviz requerido)\n";
        cout << "5) Mostrar porcentaje de identidad\n";
        cout << "6) Mostrar alineamiento y puntaje final\n";
        cout << "7) Salir\n";
        cout << "Ingrese su opcion (1-7): ";

        string opcion;
        getline(cin, opcion);

        // ------------------------
        // OPCION 1: Matriz U
        // ------------------------
        if (opcion == "1") {
            imprimirMatrizU(matrizU);
        }

        // ------------------------
        // OPCION 2: Matriz F
        // ------------------------
        else if (opcion == "2") {
            imprimirMatrizF(resultado.matrizF);
        }

        // ------------------------
        // OPCION 3: archivo .dot
        // ------------------------
        else if (opcion == "3") {

            string nombreDot = "alignment.dot";

            if (generarArchivoDot(resultado.alineamientoS, resultado.alineamientoT,
                                  nombreDot, mensajeError))
            {
                cout << "Archivo .dot generado: " << nombreDot << "\n";
            }
            else {
                cout << "Error al generar .dot: " << mensajeError << "\n";
            }
        }

        // ------------------------
        // OPCION 4: imagen PNG
        // ------------------------
        else if (opcion == "4") {

            string nombreDot = "alignment.dot";
            string nombrePNG = "alignment.png";

            if (!generarArchivoDot(resultado.alineamientoS, resultado.alineamientoT,
                                   nombreDot, mensajeError))
            {
                cout << "Error al generar .dot: " << mensajeError << "\n";
            }
            else {
                string comando = "dot -Tpng " + nombreDot + " -o " + nombrePNG;

                int estado = system(comando.c_str());

                if (estado == 0) {
                    cout << "Imagen generada: " << nombrePNG << "\n";
                } else {
                    cout << "Error ejecutando Graphviz. Verifique instalacion.\n";
                }
            }
        }

        // ------------------------
        // OPCION 5: porcentaje identidad
        // ------------------------
        else if (opcion == "5") {

            double identidad =
                calcularPorcentajeIdentidad(resultado.alineamientoS, resultado.alineamientoT);

            cout.setf(ios::fixed);
            cout << setprecision(2);

            cout << "Porcentaje de identidad: " << identidad << "%\n";

            cout.unsetf(ios::fixed);
        }

        // ------------------------
        // OPCION 6: alineamiento final
        // ------------------------
        else if (opcion == "6") {

            cout << "\nPuntaje final del alineamiento: "
                 << resultado.puntajeFinal << "\n\n";

            cout << "Secuencia 1 alineada:\n" << resultado.alineamientoS << "\n\n";
            cout << "Secuencia 2 alineada:\n" << resultado.alineamientoT << "\n\n";
        }

        // ------------------------
        // OPCION 7: salir
        // ------------------------
        else if (opcion == "7") {
            cout << "Saliendo del programa.\n";
            break;
        }

        else {
            cout << "Opcion invalida, intente de nuevo.\n";
        }
    }

    return 0;
}
