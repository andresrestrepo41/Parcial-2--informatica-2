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
    string nombre;
public:
    void datos_usuario(char _color,string _nombre){
        color=_color;
        nombre=_nombre;
        puntaje=0;
    }

    char getColor() const
    {
        return color;
    }
    string getNombre() const
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
        string nombre_jugador1;
        string nombre_jugador2;
        cout<<"Ingrese nombre del jugador 1: ";getline(cin, nombre_jugador1);
        cout<<"Ingrese nombre del jugador 2: ";getline(cin, nombre_jugador2);
        jugador1.datos_usuario('-',nombre_jugador1);
        jugador2.datos_usuario('*',nombre_jugador2);
    }
    void turno_del_jugador(Jugador& jugador){
        int fila=0;
        char letra_columna='A';
        jugador.setPuntaje(tablero.getMatriz());
        cout<<"Puntiacion del juegador: ";
        cout<<jugador.getPuntaje();
        cout<<"\nTurno del jugador: "<<jugador.getNombre()<< " ,Ingrese las coordenadas (fila columna): ";
        cin>>fila>>letra_columna;
        int columna=letra_columna-64;
        fila--;
        columna--;
        while(comprobar_jugada_valida(jugador,fila,columna)==false){
            cout<<"\nJugada no valida "<<endl;
            cout<<"\nTurno del jugador: "<<jugador.getNombre()<< " ,Ingrese las coordenadas (fila columna): ";
            cin>>fila>>letra_columna;
            columna=letra_columna-64;
            fila--;
            columna--;
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

        if(fila >= 0 && fila < 8 && columna >= 0 && columna < 8){
            if (jugador.getColor()=='-'){
                bool verificador=false;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if((0 <= fila + i && fila + i < 8) && (0 <= columna + j && columna + j < 8)){
                            if (tablero.getMatriz()[fila + i][columna + j] == '*') {
                                if(verificacion_y_llenado_de_linea_sandwich(i,j,fila,columna,jugador.getColor(),jugador)==true){
                                    verificador=true;
                                    continue;
                                }
                            }
                        }
                    }
                }
                if(verificador==true){
                    return true;
                }
                else{
                    cout<<"La ficha no cumple la condicion de sandwich"<<endl;
                    return false;
                }
            }
            if (jugador.getColor()=='*'){
                bool verificador=false;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if((0 <= fila + i && fila + i < 8) && (0 <= columna + j && columna + j < 8)){
                            if (tablero.getMatriz()[fila + i][columna + j] == '-') {
                                if(verificacion_y_llenado_de_linea_sandwich(i,j,fila,columna,jugador.getColor(),jugador)==true){
                                    verificador=true;
                                    continue;
                                }
                            }
                        }
                    }
                }
                if(verificador==true){
                    return true;
                }
                else{
                    cout<<"La ficha no cumple la condicion de sandwich"<<endl;
                    return false;
                }
            }
        }
        return false;
    }

    bool verificacion_y_llenado_de_linea_sandwich(int i,int j,int fila,int columna,char color,Jugador& jugador){
        if(i==1 && j==0){//condicion para moverse hacia abajo
                short int contador_filas=0;
                while(fila+contador_filas<8){
                    if(tablero.getMatriz()[fila+contador_filas][columna]==color && contador_filas>1){
                        contador_filas=1;
                        while(tablero.getMatriz()[fila+contador_filas][columna]!=color){
                            tablero.movimineto_en_tablero(fila+contador_filas,columna,jugador.getColor());
                            contador_filas++;
                        }
                        return true;
                    }
                    contador_filas++;
                }
                return false;
        }
        if(i==-1 && j==0){//condicion para moverse hacia arriba
                short int contador_filas=0;
                while(fila+contador_filas>=0){
                    if(tablero.getMatriz()[fila+contador_filas][columna]==color && contador_filas<-1){
                        contador_filas=-1;
                        while(tablero.getMatriz()[fila+contador_filas][columna]!=color){
                            tablero.movimineto_en_tablero(fila+contador_filas,columna,jugador.getColor());
                            contador_filas--;
                        }
                        return true;
                    }
                    contador_filas--;
                }
                return false;
        }
        if(i==0 && j==-1){//condicion para moverse hacia la izquierda
                short int contador_columnas=0;
                while(columna+contador_columnas>=0){
                    if(tablero.getMatriz()[fila][columna+contador_columnas]==color && contador_columnas<-1){
                        contador_columnas=-1;
                        while(tablero.getMatriz()[fila][columna+contador_columnas]!=color){
                            tablero.movimineto_en_tablero(fila,columna+contador_columnas,jugador.getColor());
                            contador_columnas--;
                        }
                        return true;
                    }
                    contador_columnas--;
                }
                return false;
        }
        if(i==0 && j==1){//condicion para moverse hacia la derecha
                short int contador_columnas=0;
                while(columna+contador_columnas<8){
                    if(tablero.getMatriz()[fila][columna+contador_columnas]==color && contador_columnas>1){
                        contador_columnas=1;
                        while(tablero.getMatriz()[fila][columna+contador_columnas]!=color){
                            tablero.movimineto_en_tablero(fila,columna+contador_columnas,jugador.getColor());
                            contador_columnas++;
                        }
                        return true;
                    }
                    contador_columnas++;
                }
                return false;
        }
        if(i==1 && j==1){//Diagonal (abajo derecha)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas<8 && fila+contador_fila<8){
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas>1){
                        contador_columnas=1;
                        contador_fila=1;
                        while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                            tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,jugador.getColor());
                            contador_columnas++;
                            contador_fila++;
                        }
                        return true;
                    }
                    contador_columnas++;
                    contador_fila++;
                }
                return false;
        }
        if(i==1 && j==-1){//Diagonal (abajo izquierda)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas>=0 && fila+contador_fila<8){
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_fila>1){
                        contador_fila=1;
                        contador_columnas=-1;
                        while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                            tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,jugador.getColor());
                            contador_fila++;
                            contador_columnas--;
                        }
                        return true;
                    }
                    contador_fila++;
                    contador_columnas--;
                }
                return false;
        }
        if(i==-1 && j==1){//Diagonal (arriba derecha)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas<8 && fila+contador_fila>=0){
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas>1){
                        contador_fila=-1;
                        contador_columnas=1;
                        while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                            tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,jugador.getColor());
                            contador_fila--;
                            contador_columnas++;
                        }
                        return true;
                    }
                    contador_fila--;
                    contador_columnas++;
                }
                return false;
        }
        if(i==-1 && j==-1){//Diagonal (arriba izquierda)
                short int contador_fila=0;
                short int contador_columnas=0;
                while(columna+contador_columnas>=0 && fila+contador_fila>=0){
                    if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas<-1){
                        contador_fila=-1;
                        contador_columnas=-1;
                        while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                            tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,jugador.getColor());
                            contador_fila--;
                            contador_columnas--;
                        }
                        return true;
                    }
                    contador_fila--;
                    contador_columnas--;
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
