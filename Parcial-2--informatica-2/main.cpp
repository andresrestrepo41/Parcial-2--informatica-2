#include <iostream>
using namespace std;

class Tablero{
private:
    char** matriz;
    int filas;
    int columnas;

public:
    void mostrar_tablero(){
        cout<<"  A B C D E F G H"<<endl;
        for(int i=0;i<8;i++){
            cout<<i+1;
            for (int j = 0; j < 8; j++){
                cout<<"|"<<matriz[i][j];
            }
            cout<<"|"<<i+1<<endl;
        }
        cout<<"  A B C D E F G H"<<endl;
    }
    Tablero(){
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

    void movimineto_en_tablero(int fila, int columna, char color){
        matriz[fila][columna]=color;
    }
    char** getMatriz() {
        return matriz;
    }
};

class Jugador{
private:
    int puntaje;
    char color;
    char* nombre;
public:
    void datos_usuario(char _color,char* _nombre){
        color=_color;
        nombre=_nombre;
        puntaje=0;
    }

    char getColor() const
    {
        return color;
    }
    char* getNombre() const
    {
        return nombre;
    }
    void setPuntaje(char** matriz)
    {
        int contador_de_color=0;
        for(int i=0;i<8;i++) {
            for (int j=0;j<8;j++){
                if (matriz[i][j] == color){
                    contador_de_color++;
                    puntaje = contador_de_color;
                }
            }
        }
    }
    int getPuntaje() const
    {
        return puntaje;
    }
};

class Juego{
private:
    Jugador jugador1;
    Jugador jugador2;
    Tablero tablero;
public:
    Juego(){
        char* nombre_jugador1;
        char* nombre_jugador2;

        nombre_jugador1=new char[20];
        nombre_jugador2=new char[20];
        cout<<"Ingrese nombre del jugador 1: ";cin>>nombre_jugador1;
        cout<<"Ingrese nombre del jugador 2: ";cin>>nombre_jugador2;
        jugador1.datos_usuario('-',nombre_jugador1);
        jugador2.datos_usuario('*',nombre_jugador2);
    }
    void turno_del_jugador(Jugador& jugador){
        int fila,columna;
        jugador.setPuntaje(tablero.getMatriz());
        cout<<"Puntiacion del juegador: ";
        cout<<jugador.getPuntaje();
        cout<<"\nTurno del jugador: "<<jugador.getNombre()<< " ,Ingrese las coordenadas (fila columna): ";
        cin>>fila>>columna;
        tablero.movimineto_en_tablero(fila,columna,jugador.getColor());

    }
    void iniciar_partida(){
        for(int fichas=0;fichas<=64;fichas++){
            tablero.mostrar_tablero();
            turno_del_jugador(jugador1);
            tablero.mostrar_tablero();
            turno_del_jugador(jugador2);
        }
    }

};

int main()
{
    Juego juego;
    juego.iniciar_partida();


}
