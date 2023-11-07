#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "jugador.h"
#include <fstream>
#include <ctime>

class Juego
{
private:
    Jugador jugador1;
    Jugador jugador2;
    Tablero tablero;
public:
    Juego();
    void definir_datos_jugador();
    void turno_del_jugador(Jugador& jugador);
    bool comprobar_jugada_valida(Jugador& jugador,int fila,int columna,int seleccion);
    bool verificacion_y_llenado_de_linea_sandwich(int i,int j,int fila,int columna,char color,int seleccion);
    bool verificacion_proxima_jugada(Jugador& jugador);
    void escribir_archivo(string name, string info);
    string leer_archivo(string name);
    void menu_principal(Juego& juego);
    void iniciar_partida();
};

#endif // JUEGO_H
