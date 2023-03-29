#include <iostream>
#include <array>
#include <iomanip> //para usar setprecision
#include <cmath> //para usar trunc

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
void ImprimirSolucion(matriz & miMatriz);


int main()
{
    while (true) {
        cout<<"\nCALCULADORA DE MATRICES 3X3\n";
        // Definimos el número de variables de nuestro sistema
        const int variables = 3;
        // El número de columnas será el número de variables más su solición para cada ecuación
        const int columnas = variables + 1;

        // Inicializamos la matriz que vamos a ocupar
        array<array<float, columnas>, variables> miMatriz = {0};

        // Pedimos al usuario que llene la matriz
        LlenarMatriz(miMatriz);

        //Imprimir
        ImprimirMatriz(miMatriz);

        // Aplicamos el método de Gauss-Jordan sobre nuestra matriz
        GaussJordan(miMatriz);

        // Imprimimos la solución de la matriz
        ImprimirSolucion(miMatriz);
    }
    return 0; // Indicamos que salimos del programa con éxito
}

/*
Llena 'miMatriz' con valores ingresados por el usuario para cada elemento.
No regresa ningún valor.
*/
template <typename matriz>
void LlenarMatriz(matriz & miMatriz)
{
    cout<<"\n";
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
    int variables = miMatriz.size();
    cout<<"Matriz solucion:\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++){
            cout << setprecision( 3 ) << trunc( miMatriz[i][j] * 100 ) / 100 <<"\t";
        }
        cout << "]\n";
    }
    //TODO
    float tip=0;
    for (int i = 0; i < variables; i++) {
        for (int j = 0; j < variables; j++){
            tip=tip+miMatriz[i][j];
        }
    }
    if (tip==3.00){
        cout<<"\nLa matriz tiene solucion\n\n";
        cout << "x= " << setprecision(4) << trunc(miMatriz[0][3] * 1000) / 1000 << "\n";
        cout << "y= " << setprecision(4) << trunc(miMatriz[1][3] * 1000) / 1000 << "\n";
        cout << "z= " << setprecision(4) << trunc(miMatriz[2][3] * 1000) / 1000 << "\n";
    }
    else
        if(miMatriz[1][1]==0&&miMatriz[1][2]==0&&miMatriz[1][3]==0){
            cout<<"\nLa matriz tiene multiples soluciones\n\n";
        }
        else
            if (miMatriz[2][1]==0&&miMatriz[2][2]==0&&miMatriz[2][3]==0){
            cout<<"\nLa matriz tiene multiples soluciones\n\n";
            }
            else
                cout<<"La matriz no tiene solucion\n\n";
}

/*
Implementa el algoritmo de Gauss-Jordan sobre 'miMatriz', finalizando en ella la solución del algoritmo.
No regresa ningún valor.
*/
template <typename matriz>
void GaussJordan(matriz & miMatriz) {

    int variables = miMatriz.size();
    float div = 0;
    for (int i = 0; i < variables; i++) {
        div = miMatriz[i][0];
        for (int j = 0; j < variables + 1; j++) {
            if (div != 0) {
                miMatriz[i][j] = miMatriz[i][j] / div;
            }
        }
    }
    cout << "Paso 1\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++) {
            cout << setprecision(3) << trunc(miMatriz[i][j] * 100) / 100 << "\t";
        }
        cout << "]\n";
    }
    for (int i = 1; i < variables; i++) {
        if (miMatriz[i][0] != 0) {
            div = miMatriz[i][0];
            for (int j = 0; j < variables + 1; j++) {
                miMatriz[i][j] = miMatriz[i][j] - div * miMatriz[0][j];
            }
        }
    }
    cout << "Paso 2\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++) {
            cout << setprecision(3) << trunc(miMatriz[i][j] * 100) / 100 << "\t";
        }
        cout << "]\n";
    }
    for (int i = 1; i < variables; i++) {
        div = miMatriz[i][1];
        for (int j = 0; j < variables + 1; j++) {
            if (div != 0) {
                miMatriz[i][j] = miMatriz[i][j] / div;
            }
        }
    }
    //Las matrices están en 1 en la 2da variables
    cout << "Paso 3\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++) {
            cout << setprecision(3) << trunc(miMatriz[i][j] * 100) / 100 << "\t";
        }
        cout << "]\n";
    }

    if (miMatriz[1][1] != 0) {
        div = miMatriz[2][1];
        for (int j = 0; j < variables + 1; j++) {
            miMatriz[2][j] = miMatriz[2][j] - div * miMatriz[1][j];
        }
    }
    cout << "Paso 4\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++) {
            cout << setprecision(3) << trunc(miMatriz[i][j] * 100) / 100 << "\t";
        }
        cout << "]\n";
    }
    for (int i = 1; i < variables; i++) {
        if (miMatriz[i][1] == 0) {
            div = miMatriz[i][2];
            for (int j = 2; j < variables + 1; j++) {
                if (div != 0) {
                    miMatriz[i][j] = miMatriz[i][j] / div;
                }
            }
        }
    }
    cout << "Paso 5\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++) {
            cout << setprecision(3) << trunc(miMatriz[i][j] * 100) / 100 << "\t";
        }
        cout << "]\n";
    }
    if (miMatriz[1][1] == 1) {
        if (miMatriz[2][1] == 0) {
            div = miMatriz[1][2];
            for (int j = 0; j < variables + 1; j++) {
                miMatriz[1][j] = miMatriz[1][j] - div * miMatriz[2][j];
            }
        }
    } else {
        if (miMatriz[2][1] == 1) {
            div = miMatriz[2][2];
            for (int j = 0; j < variables + 1; j++) {
                miMatriz[2][j] = miMatriz[2][j] - div * miMatriz[1][j];
            }
        } else {
            div = miMatriz[1][2];
            for (int j = 0; j < variables + 1; j++) {
                miMatriz[1][j] = miMatriz[1][j] - div * miMatriz[2][j];
            }
        }
    }
    cout << "Paso 6\n";
    for (int i = 0; i < variables; i++) {
        cout << "[ ";
        for (int j = 0; j < variables + 1; j++) {
            cout << setprecision(3) << trunc(miMatriz[i][j] * 100) / 100 << "\t";
        }
        cout << "]\n";
    }
    if (miMatriz[1][1] == 1) {
        div = miMatriz[0][1];
        for (int j = 0; j < variables + 1; j++) {
            miMatriz[0][j] = miMatriz[0][j] - div * miMatriz[1][j];
        }
        div = miMatriz[0][2];
        for (int j = 0; j < variables + 1; j++) {
            miMatriz[0][j] = miMatriz[0][j] - div * miMatriz[2][j];
        }
    }
    if (miMatriz[2][1] == 1) {
        div = miMatriz[0][1];
        for (int j = 0; j < variables + 1; j++) {
            miMatriz[0][j] = miMatriz[0][j] - div * miMatriz[2][j];
        }
        div = miMatriz[0][2];
        for (int j = 0; j < variables + 1; j++) {
            miMatriz[0][j] = miMatriz[0][j] - div * miMatriz[1][j];
        }
        //TODO
    }
}
