#include <iostream>
#include <array>

// Añadir std para fácil llamado de funciones
using namespace std;

//// Declaración de funciones
//Definimos un template (un tipo de dato) para nuestra matriz
template <typename matriz>
void LlenarMatriz(matriz & miMatriz);

template <typename matriz>
void ImprimirMatriz(matriz & miMatriz);

template <typename matriz>
void GaussJordan(matriz & miMatriz);

template <typename matriz>
void Resta(matriz & miMatriz);

template <typename matriz>
void Dividir(matriz & miMatriz);

template <typename matriz>
void ImprimirSolucion(matriz & miMatriz);

template <typename matriz>
int buscarPivote(matriz &miMatriz, int fila, int numFilas);



int main()
{
    // Definimos el número de variables de nuestro sistema
    const int variables = 3;
    // El número de columnas será el número de variables más su solición para cada ecuación
    const int columnas = variables + 1;

    // Inicializamos la matriz que vamos a ocupar
    array <array<float, columnas>, variables> miMatriz = { 0 };

    // Pedimos al usuario que llene la matriz
    LlenarMatriz(miMatriz);

    // Aplicamos el método de Gauss-Jordan sobre nuestra matriz
    GaussJordan(miMatriz);

    // Imprimimos la solución de la matriz
    ImprimirSolucion(miMatriz);

    return 0; // Indicamos que salimos del programa con éxito
}

/*
Llena 'miMatriz' con valores ingresados por el usuario para cada elemento.
No regresa ningún valor.
*/
template <typename matriz>
void LlenarMatriz(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        for (int j = 0; j <= variables; j++) {
            cout << "Valor elemento [" << i << "][" << j << "]: ";
            cin >> miMatriz[i][j];
        }
    }
}

/*
Imprime cada elemento de 'miMatriz' emulando una matriz con corchetes cuadrados.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirMatriz(matriz & miMatriz)
{
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++)
            cout << miMatriz[i][j] << '\t';
        cout << "]\n";
    }
}

/*
Imprime en pantalla la solución para cada variable del sistema de ecuaciones correspondiente a los valores en 'miMatriz'.
No regresa ningún valor.
*/
template <typename matriz>
void ImprimirSolucion(matriz & miMatriz)
{
    cout<<"\n\nMatriz Solucion: \n";
    int variables = miMatriz.size();
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++)
            cout << miMatriz[i][j] << '\t';
        cout << "]\n";
    }
    //TODO
}
//fila=???

/*
 * Esta función busca un pivote empleando la técnica de pivoteo parcial
 * Parámetros: Matriz, fila actual y número de filas.
 * Salida: Índice de la fila que contiene el pivote. (El pivote se debe posiciónar en la diagonal principal i == j)
 */
template <typename matriz> // Se definen dos typenames el primero es para la matriz el segundo para variables
int buscarPivote(matriz &miMatriz, int fila, int numFilas){
    int col = fila; // El pivote se ubica en la diagonal principal por lo tanto i = j => fila = fila.
    int indicePivote = -1;
    // Se asume que el elemento mayor se encuentra inicialmente en la primero posición
    float max = miMatriz[fila][col];
    // Se itera sobre las filas para encontrar el menor elemento
    for(int i = fila; i<numFilas; i++){ // Itera desde la fila actual hasta numFilas.
        if(miMatriz[i][col] != 0 & miMatriz[i][col] >= max){ // Si el elemento es distinto de cero y mayor.
            max = miMatriz[i][col];
            indicePivote = i;
        }

    }
    return indicePivote;
}

template <typename matriz>
void intercambiarFilas(matriz &miMatriz, int fila1, int fila2, int cols){
    // Alternativa: Usar la función swap.
    for(int j = 0; j < cols; j++){
        float temp = miMatriz[fila1][j];
        miMatriz [fila1][j] = miMatriz[fila2][j];
        miMatriz[fila2][j] = temp;

    }
}

template <typename matriz>
void Resta(matriz &miMatriz, int f, int c, int f1){
    float iv;
    for (int i = f+1; i < f1; i++) {
        if (miMatriz[i][f] != 0) {
            iv = miMatriz[i][f];
            for (int j = 0; j < c; j++) {
                miMatriz[i][j] = miMatriz[i][j] - miMatriz[f][j] * iv;
            }
        }
    }
}

template <typename matriz>
void Dividir(matriz &miMatriz, int f, int c, int f1){
    float div;
    for (int i = f; i < f1; i++) {
        if (miMatriz[i][f] != 0) {
            div = miMatriz[i][f];
            for (int j = 0; j < c; j++) {
                miMatriz[i][j] = miMatriz[i][j] / div;
            }
        }
    }
}

/*
Implementa el algoritmo de Gauss-Jordan sobre 'miMatriz', finalizando en ella la solución del algoritmo.
No regresa ningún valor.
*/
template <typename matriz>
void GaussJordan(matriz &miMatriz){

    cout << "Matriz original" << endl;
    ImprimirMatriz(miMatriz);

    // Definir número de filas y cols de la matriz
    int filas = miMatriz.size(), cols = miMatriz.size()+1;

    for(int i = 0; i<miMatriz.size(); i++){
        // retorna el índice de la fila en la que se encuentra el pivote (elemento mayo != 0)
        int indicePivote = buscarPivote(miMatriz, i, filas);  // se usa la técnica de pivoteo parcial.

        if(indicePivote != -1){ // Si se encontraron elementos != 0
            //intercambiar filas actual y fila de pivote)
            intercambiarFilas(miMatriz, i, indicePivote, cols);
            ImprimirSolucion(miMatriz);
            Dividir(miMatriz, i, cols, filas);
            ImprimirSolucion(miMatriz);
            Resta(miMatriz, i, cols, filas);
            ImprimirSolucion(miMatriz);
            if(i==filas-1){
                int f=filas;
                float vi;
                for (int j = 0; j < filas-1; j++) {
                    f--;
                    for (int k = 0; k <= f; k++) {
                        vi=miMatriz[j][k+1];
                        ImprimirSolucion(miMatriz);
                        for (int l = 0; l < cols; l++) {
                            cout<<vi * miMatriz[k][l]<<"\t";
                            miMatriz[j][l] = miMatriz[j][l] - vi * miMatriz[k][l];
                        }
                    }
                }
            }

        }
        else{
            cout << "El sistema no tiene solucion" << endl;
            exit(0);
        }


        // TODO: Realizar la eliminación de Gauss Jordan
    }
}
