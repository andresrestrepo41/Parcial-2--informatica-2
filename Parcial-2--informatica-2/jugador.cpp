#include "jugador.h"

Jugador::Jugador()
{

}

void Jugador::datos_usuario(char _color, string _nombre)//Esta funcion me permite asignarle una ficha a los jugadores y su respectivo nombre.
{                                                       //Tambien inicia la puntuacion en 0.
    color=_color;
    nombre=_nombre;
    puntaje=0;
}

char Jugador::getColor() const //Esta funcion me permite obtener el color de un jugador.
{
    return color;
}

string Jugador::getNombre() const //Esta funcion me permite obtener el nombre de un jugador.
{
    return nombre;
}

void Jugador::setPuntaje(char **matriz,int filas,int columnas) //Esta funcon recorre la matriz dinamica, contando las fichas de un jugador especifico.
{                                       //Gracias a esto se puede saber cuantas fichas tine un jugador, y asi poder estblecer su puntaje.
    int contador_de_color=0;
    for(int i=0;i<filas;i++) {
        for (int j=0;j<columnas;j++){
            if (matriz[i][j] == color){
                contador_de_color++;
                puntaje = contador_de_color;
            }
        }
    }
}

int Jugador::getPuntaje() const //Me permite obtener el putaje del atributo puntaje, de la clase jugador.
{
    return puntaje;
}

string Jugador::Tiempo(){  //Esta funcion me permite obtener la fecha y hora actual.
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    return buffer;
}
