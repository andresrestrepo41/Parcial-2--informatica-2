#include "tablero.h"

Tablero::Tablero() //Este es el construcotr de tablero, el cual crea una matriz de 8x8, de forma dinamica.
                   //Este tablero empieza vacio, excepto las 4 posiciones centrales, que contiene fichas.
{
    filas=8;
    columnas=8;

    matriz=new char*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new char[columnas];
    }
    for(int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = ' ';
        }
    }

    matriz[3][3] = '*';
    matriz[3][4] = '-';
    matriz[4][3] = '-';
    matriz[4][4] = '*';


}

void Tablero::mostrar_tablero() //Esta funcion me permite mostrar el estado actual de tablero, incluyyendo todas las fichas.
{
    cout<<"\n\n  A B C D E F G H"<<endl;
    for(int i=0;i<8;i++){
        cout<<i+1;
        for (int j = 0; j < 8; j++){
            cout<<"|"<<matriz[i][j];
        }
        cout<<"|"<<i+1<<endl;
    }
    cout<<"  A B C D E F G H"<<endl;
}

void Tablero::movimineto_en_tablero(int fila, int columna, char color) //Esta funcion me permite ir llenando el talber cuando un jugador coloca una ficha.
{
    matriz[fila][columna]=color;
}

char **Tablero::getMatriz() //Esta funcion me retorna un puntero, el cual tiene la direccion de la matriz, util para otras clases.
{
    return matriz;
}

int Tablero::getFilas() const //Me permite obtener el atributo llamado filas de la clase Tablero.
{
    return filas;
}

int Tablero::getColumnas() const //Me permite obtener el atributo llamado columnas de la clase Tablero.
{
    return columnas;
}

Tablero::~Tablero()
{
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
