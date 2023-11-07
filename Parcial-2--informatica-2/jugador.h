#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador
{
private:
    int puntaje;
    char color;
    string nombre;

public:
    Jugador();
    void datos_usuario(char _color,string _nombre);
    char getColor() const;
    string getNombre() const;
    void setPuntaje(char** matriz,int filas,int columnas);
    int getPuntaje() const;
    string Tiempo();
};

#endif // JUGADOR_H
