#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
using namespace std;

class Tablero
{
private:
    char** matriz;
    int filas;
    int columnas;
public:
    Tablero();
    void mostrar_tablero();
    void movimineto_en_tablero(int fila, int columna, char color);
    char** getMatriz();
    int getFilas() const;
    int getColumnas() const;
    ~Tablero();
};

#endif // TABLERO_H
