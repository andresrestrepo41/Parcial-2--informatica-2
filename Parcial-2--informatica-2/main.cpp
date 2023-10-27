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
    char** copia_de_matriz(){
        char** copia_de_matriz=new char*[filas];
        for (int i = 0; i < filas; i++) {
            copia_de_matriz[i] = new char[columnas];
            for (int j = 0; j < columnas; j++) {
                copia_de_matriz[i][j] = getMatriz()[i][j];
            }
        }
        return copia_de_matriz;
    }
    void eliminar_copia_de_matriz(char** matriz){
        for (int i = 0; i < filas; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
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
        while(comprobar_jugada_valida(jugador,fila,columna)==false){
            cout<<"\nJugada no valida "<<endl;
            cout<<"\nTurno del jugador: "<<jugador.getNombre()<< " ,Ingrese las coordenadas (fila columna): ";
            cin>>fila>>columna;
        }
        tablero.movimineto_en_tablero(fila,columna,jugador.getColor());

    }
    bool comprobar_jugada_valida(Jugador& jugador,int fila,int columna){
        if ((fila < 0 || fila >= 8) || (columna < 0 || columna >= 8)){
            cout<<"Error, la ficha debe pertenecer al tablero"<<endl;
            return false;
        }

        if(tablero.getMatriz()[fila][columna]=='*' || tablero.getMatriz()[fila][columna]=='-'){
            cout<<"Espacio ocupada por una ficha"<<endl;
            return false;
        }

        if(fila >= 1 && fila < 7 && columna >= 1 && columna < 7){
            if (jugador.getColor()=='-'){
                    for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            if (tablero.getMatriz()[fila + i][columna + j] == '*') {
                                return verificacion_linea_sandwich(i,j,fila,columna,jugador.getColor());
                            }
                        }
                    }
                    cout<<"La ficha no cumple la condicion de sandwich"<<endl;
                    return false;
                }
            if (jugador.getColor()=='*'){
                    for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            if (tablero.getMatriz()[fila + i][columna + j] == '-') {
                                return verificacion_linea_sandwich(i,j,fila,columna,jugador.getColor());
                            }
                        }
                    }
                    cout<<"La ficha no cumple la condicion de sandwich"<<endl;
                    return false;
                }
        }
        return true;
    }

    bool verificacion_linea_sandwich(int i,int j,int fila,int columna,char color){
        if(i==1 && j==0){//condicion para moverse hacia abajo
                short int contador_filas=0;
                while(fila+contador_filas<8){
                    contador_filas++;
                    if(tablero.getMatriz()[fila+contador_filas][columna]==color && contador_filas>1){
                        return true;
                    }
                }
                return false;
        }
        if(i==-1 && j==0){//condicion para moverse hacia arriba
                short int contador_filas=0;
                while(fila+contador_filas>=0){
                    contador_filas--;
                    if(tablero.getMatriz()[fila+contador_filas][columna]==color && contador_filas<-1){
                        return true;
                    }
                }
                return false;
        }
        if(i==0 && j==-1){//condicion para moverse hacia la izquierda
                short int contador_columnas=0;
                while(columna+contador_columnas>=0){
                    contador_columnas--;
                    if(tablero.getMatriz()[fila][columna+contador_columnas]==color && contador_columnas<-1){
                        return true;
                    }
                }
                return false;
        }
        if(i==0 && j==1){//condicion para moverse hacia la derecha
                short int contador_columnas=0;
                while(columna+contador_columnas<8){
                    contador_columnas++;
                    if(tablero.getMatriz()[fila][columna+contador_columnas]==color && contador_columnas>1){
                        return true;
                    }
                }
                return false;
        }
        if(i==1 && j==1){//Diagonal (abajo derecha)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas<8 && fila+contador_fila<8){
                    contador_columnas++;
                    contador_fila++;
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas>1){
                        return true;
                    }
                }
                return false;
        }
        if(i==1 && j==-1){//Diagonal (abajo izquierda)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas>=0 && fila+contador_fila<8){
                    contador_fila++;
                    contador_columnas--;
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_fila>1){
                        return true;
                    }
                }
                return false;
        }
        if(i==-1 && j==1){//Diagonal (arriba derecha)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas<8 && fila+contador_fila>=0){
                    contador_fila--;
                    contador_columnas++;
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas>1){
                        return true;
                    }
                }
                return false;
        }
        if(i==-1 && j==-1){//Diagonal (arriba izquierda)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas>=0 && fila+contador_fila>=0){
                    contador_fila--;
                    contador_columnas--;
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas<-1){
                        return true;
                    }
                }
                return false;
        }
        return false;
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
