#include "juego.h"

Juego::Juego()
{

}

void Juego::definir_datos_jugador() // Gracias a esta funcion, establesco los atributos, nombre y color de ficha,de la clase jugador.
{
    string nombre_jugador1;
    string nombre_jugador2;
    cout<<"Ingrese nombre del jugador 1: ";getline(cin, nombre_jugador1);
    cout<<"Ingrese nombre del jugador 2: ";getline(cin, nombre_jugador2);
    jugador1.datos_usuario('-',nombre_jugador1);
    jugador2.datos_usuario('*',nombre_jugador2);
}

void Juego::turno_del_jugador(Jugador &jugador)//Esta es una de las funciones pricipales del juego ya que involucra la gran normativa del juego.
{
    char numero_fila='0';
    char letra_columna='A';
    jugador.setPuntaje(tablero.getMatriz(),tablero.getFilas(),tablero.getColumnas());//Esta blesco el puntaje del jugador.
    cout<<"\nPuntiacion del juegador: ";
    cout<<jugador.getPuntaje(); //Muetro el puntaje del jugador.
    cout<<"\nTurno del jugador: "<<jugador.getNombre()<< " ,Ingrese las coordenadas (fila columna): ";
    cin>>numero_fila>>letra_columna;//Se ingresan las coordenadas,primero un numero seguido de un espacio y luego una letra(en mayuscula).
    int columna=letra_columna-64;//como ambos son char, le restamos el assci para convertirla en numero, para trabajar con la matriz.
    int fila=numero_fila-48;
    fila--;
    columna--;
    while(comprobar_jugada_valida(jugador,fila,columna,0)==false){ // Con este while, compruebo que el usuario ingrese el formato adecuado.
        cout<<"\nJugada no valida "<<endl; //Se repite hasta que se valido el formato y cumpla las normas.
        cout<<"\nTurno del jugador: "<<jugador.getNombre()<< " ,Ingrese las coordenadas (fila columna): ";
        cin>>numero_fila>>letra_columna;
        columna=letra_columna-64;
        fila=numero_fila-48;
        fila--;
        columna--;
    }
    tablero.movimineto_en_tablero(fila,columna,jugador.getColor()); //Cuando todo es valido, se procede a colocar la ficha en su respectivo lugar.
}

bool Juego::comprobar_jugada_valida(Jugador &jugador, int fila, int columna, int seleccion) //Esta funcion, verifica las distintas normas del jeugo, como tambien la sitaxis de entrada.
{
    if ((fila < 0 || fila >= tablero.getFilas()) || (columna < 0 || columna >= tablero.getColumnas())){ //Condicion para verificar si la ficha pertenece al rango de la matriz.
        cout<<"Error, la ficha debe pertenecer al tablero"<<endl;
        return false;
    }

    if(tablero.getMatriz()[fila][columna]=='*' || tablero.getMatriz()[fila][columna]=='-'){ //Condicion para no colocar una ficha, es un espacio ocupado por otra.
        return false;
    }

    if(fila >= 0 && fila < tablero.getFilas() && columna >= 0 && columna < tablero.getColumnas()){//Esta condicion, tiene dos diferentes propositos, dependiendo del parametro (seleccion).Primero se verifica si el usuario ingreso el rango correcto.
        if (jugador.getColor()=='-'){//Esta se aplica para las fichas '-'.
            bool verificador=false; //Este bool me asegura que minimo se cumlio una vez.
            for (int i = -1; i <= 1; i++) { //----El proposito principal es recorrer las 8 fichas circundantes en busca de una ficha contraria, para poder seguir con la otra funcion.
                for (int j = -1; j <= 1; j++) {
                    if((0 <= fila + i && fila + i < tablero.getFilas()) && (0 <= columna + j && columna + j < tablero.getColumnas())){//con esta verifico que siempre este en el rango de la matriz, pensada para la restriccion de las filas y columnas externas.
                        if (tablero.getMatriz()[fila + i][columna + j] == '*') {//cuando encuentra una ficha externa, ejecuta la funcion verificacion_y_llenado_de_linea_sandwich().
                            if(verificacion_y_llenado_de_linea_sandwich(i,j,fila,columna,jugador.getColor(),seleccion)==true){//Primero, enviamos los parametros i y j, para que la funcion verificacion_y_llenado_de_linea_sandwich recorra esa misma linea,y si minimo hay un sadwich, se retorna true.
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
                return false;
            }
        }
        if (jugador.getColor()=='*'){ //Esta condicion es exactamente igual a la de arriba pero con la otra ficha.
            bool verificador=false;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if((0 <= fila + i && fila + i < tablero.getFilas()) && (0 <= columna + j && columna + j < tablero.getColumnas())){
                        if (tablero.getMatriz()[fila + i][columna + j] == '-') {
                            if(verificacion_y_llenado_de_linea_sandwich(i,j,fila,columna,jugador.getColor(),seleccion)==true){
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
                return false;
            }
        }
    }
    return false;
}

bool Juego::verificacion_y_llenado_de_linea_sandwich(int i, int j, int fila, int columna, char color, int seleccion)//Esta funcion aplica las dos funcionalidaddes distintas,dependiendo del parametro (seleecion), que varia entre 0 y 1 en enteros.
{
    if(i==1 && j==0){//condicion para moverse hacia abajo.Sumando solo filas para desplazarme.
        short int contador_filas=0;
        while(fila+contador_filas<tablero.getFilas()){ //condicional para mantenerse en el rango del tablero.
            if(tablero.getMatriz()[fila+contador_filas][columna]==color && contador_filas>1){//Esta condicion se detiene conamdo encuantra una ficha del mismo color y esta 2 posiciones mas adelante confimrano el sandwich.
                contador_filas=1;
                if(seleccion==1)return true; //cuando seleccion es =1, esta funcion cumple con el proposito solo de vericiar si existe el sanwitch, esto con el fin de implemetar otra funcion que verifique si hay una jugada valida.
                while(tablero.getMatriz()[fila+contador_filas][columna]!=color){//En el caso que seleccion sea=0, este me llena las casillas con la ficha del jugador.
                    tablero.movimineto_en_tablero(fila+contador_filas,columna,color);//lleno la casilla.
                    contador_filas++;
                }
                return true;
            }
            if(tablero.getMatriz()[fila+contador_filas][columna]==' ' && contador_filas>1){//Con esta condicion verifico si hay un espacio en blanco para no seguir con el while.
                return false;
            }
            contador_filas++;
        }
        return false;
    }

    //----Las otras 7 condicion cumplen el mismo funcionamiento de la primera condicion mensionada, solo que cambia ya sea las columnas o las filas, para desplazarse.

    if(i==-1 && j==0){//condicion para moverse hacia arriba, restando solo filas para desplazarme.
        short int contador_filas=0;
        while(fila+contador_filas>=0){
            if(tablero.getMatriz()[fila+contador_filas][columna]==color && contador_filas<-1){
                contador_filas=-1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila+contador_filas][columna]!=color){
                    tablero.movimineto_en_tablero(fila+contador_filas,columna,color);
                    contador_filas--;
                }
                return true;
            }
            if(tablero.getMatriz()[fila+contador_filas][columna]==' ' && contador_filas<-1){
                return false;
            }
            contador_filas--;
        }
        return false;
    }
    if(i==0 && j==-1){//condicion para moverse hacia la izquierda,restando solo columnas para desplazarme.
        short int contador_columnas=0;
        while(columna+contador_columnas>=0){
            if(tablero.getMatriz()[fila][columna+contador_columnas]==color && contador_columnas<-1){
                contador_columnas=-1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila][columna+contador_columnas]!=color){
                    tablero.movimineto_en_tablero(fila,columna+contador_columnas,color);
                    contador_columnas--;
                }
                return true;
            }
            if(tablero.getMatriz()[fila][columna+contador_columnas]==' ' && contador_columnas<-1){
                return false;
            }
            contador_columnas--;
        }
        return false;
    }
    if(i==0 && j==1){//condicion para moverse hacia la derecha,sumando solo columnas para desplazarme.
        short int contador_columnas=0;
        while(columna+contador_columnas<tablero.getColumnas()){
            if(tablero.getMatriz()[fila][columna+contador_columnas]==color && contador_columnas>1){
                contador_columnas=1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila][columna+contador_columnas]!=color){
                    tablero.movimineto_en_tablero(fila,columna+contador_columnas,color);
                    contador_columnas++;
                }
                return true;
            }
            if(tablero.getMatriz()[fila][columna+contador_columnas]==' ' && contador_columnas>1){
                return false;
            }
            contador_columnas++;
        }
        return false;
    }
    if(i==1 && j==1){//Diagonal (abajo derecha),sumando tanto filas como columnas para desplzarme.
        short int contador_fila=0;
        short int contador_columnas=0;
        while(columna+contador_columnas<tablero.getColumnas() && fila+contador_fila<tablero.getFilas()){
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas>1){
                contador_columnas=1;
                contador_fila=1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                    tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,color);
                    contador_columnas++;
                    contador_fila++;
                }
                return true;
            }
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==' ' && contador_columnas>1){
                return false;
            }
            contador_columnas++;
            contador_fila++;
        }
        return false;
    }
    if(i==1 && j==-1){//Diagonal (abajo izquierda),sumando filas,pero restando columnas para desplzarme.
        short int contador_fila=0;
        short int contador_columnas=0;
        while(columna+contador_columnas>=0 && fila+contador_fila<tablero.getFilas()){
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_fila>1){
                contador_fila=1;
                contador_columnas=-1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                    tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,color);
                    contador_fila++;
                    contador_columnas--;
                }
                return true;
            }
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==' ' && contador_fila>1){
                return false;
            }
            contador_fila++;
            contador_columnas--;
        }
        return false;
    }
    if(i==-1 && j==1){//Diagonal (arriba derecha),restando filas,pero sumando columnas para desplzarme.
        short int contador_fila=0;
        short int contador_columnas=0;
        while(columna+contador_columnas<tablero.getColumnas() && fila+contador_fila>=0){
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas>1){
                contador_fila=-1;
                contador_columnas=1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                    tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,color);
                    contador_fila--;
                    contador_columnas++;
                }
                return true;
            }
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==' ' && contador_columnas>1){
                return false;
            }
            contador_fila--;
            contador_columnas++;
        }
        return false;
    }
    if(i==-1 && j==-1){//Diagonal (arriba izquierda),restando filas y columnas para desplzarme.
        short int contador_fila=0;
        short int contador_columnas=0;
        while(columna+contador_columnas>=0 && fila+contador_fila>=0){
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==color && contador_columnas<-1){
                contador_fila=-1;
                contador_columnas=-1;
                if(seleccion==1)return true;
                while(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]!=color){
                    tablero.movimineto_en_tablero(fila+contador_fila,columna+contador_columnas,color);
                    contador_fila--;
                    contador_columnas--;
                }
                return true;
            }
            if(tablero.getMatriz()[fila+contador_fila][columna+contador_columnas]==' ' && contador_columnas<-1){
                return false;
            }
            contador_fila--;
            contador_columnas--;
        }
        return false;
    }
    return false;
}

bool Juego::verificacion_proxima_jugada(Jugador &jugador)//Esta condicion, implementa el parametro de seleccion =1, para verificar si hay minumo un sanwitch valido.
{
    for(int i = 0; i < tablero.getFilas(); i++) { // se recorre todo el tablero y se verifica.
        for (int j = 0; j < tablero.getColumnas(); j++) {
            if(comprobar_jugada_valida(jugador,i,j,1)==true){
                return true;
            }
        }
    }
    return false;
}

void Juego::escribir_archivo(string name, string info) //funcion escribir un archivo.
{
    fstream file;
    file.open(name,ios::out | ios::app| ios::binary);
    file << info;
    file.close();
}

string Juego::leer_archivo(string name) //funcion para leer un archivo.
{
    char caracter;
    fstream file;
    string data;
    file.open(name,ios::in | ios::binary);
    if(file.is_open()){
        while(file.get(caracter)){
            data.push_back(caracter);
        }
    }
    file.close();
    return data;
}

void Juego::menu_principal(Juego &juego)//Funcion que contiene el menu principal.
{
    char opcion='8';
    while (opcion!='3') {
        cout << "\nBienvenido al juego Othello" <<endl <<endl;
        cout << "Ingrese 1 si quiere jugar" <<endl;
        cout << "Ingrese 2 si quiere ver el historial de partidas" << endl;
        cout << "Ingrese 3 si quiere salir" << endl;

        cout<<"\nEscriba su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case '1':
            cout << "Comenzando una nueva partida..."<<endl;
            cin.ignore(); //Este codigo, me permite borrar el buffer de la consola para evitar errores a la hora de escribir el nombre de los usuarios.
            juego.definir_datos_jugador();
            juego.iniciar_partida();
            break;
        case '2':
            cout << "Mostrando el historial de partidas..." << endl<<endl;
            cout<<leer_archivo("historial_de_partidas.txt");
            break;
        case '3':
            cout << "Saliendo del juego. !Hasta luego!" << endl;
            break;
        default:
            cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
            break;
        }
    }
}

void Juego::iniciar_partida() //Esta funcion inicia la partida en bucle.
{
    string datos_partida; //Este string almacena los datos que se guardaran en el archivo de texto, cuando se termine la partida.
    while(verificacion_proxima_jugada(jugador1)==true || verificacion_proxima_jugada(jugador2)==true){ //Cuando este bucle no se cumple, el juego termina y se determina el ganador.
        tablero.mostrar_tablero();//Muestra el estado actual del tablero.
        if(verificacion_proxima_jugada(jugador1)==true){//Se verifica si el usuario tiene un lugar de jugada validia.
            turno_del_jugador(jugador1);//Se realiza el turno en caso valido.
        }else{
            cout<<endl<<"!!!!!No es posible realizar ningun movimineto para el jugador "<<jugador1.getNombre()<<"!!!!!"<<endl<<endl;//Si el usuario no tiene jugada valida se muestra el siguiente mensae, y continua el otro usuario.
        }
        tablero.mostrar_tablero();//Muestra el estado actual del tablero.
        if(verificacion_proxima_jugada(jugador2)==true){//Se verifica si el usuario tiene un lugar de jugada validia.
            turno_del_jugador(jugador2);//Se realiza el turno en caso valido.
        }else{
            cout<<endl<<"!!!!!No es posible realizar ningun movimineto para el jugador "<<jugador2.getNombre()<<"!!!!!"<<endl<<endl;//Si el usuario no tiene jugada valida se muestra el siguiente mensae, y continua el otro usuario.
        }

    }
    jugador1.setPuntaje(tablero.getMatriz(),tablero.getFilas(),tablero.getColumnas());//Cuando el juego finaliza, se actualiza el puntaje para definir el ganador.
    jugador2.setPuntaje(tablero.getMatriz(),tablero.getFilas(),tablero.getColumnas());
    if(jugador1.getPuntaje()>jugador2.getPuntaje()){//Si el jugador 1 obtuvo mas puntaje, se guarda en el archivo como ganador.
        tablero.mostrar_tablero();
        cout<<"Fin del juego, gana el jugador "<<jugador1.getNombre()<<" con "<<jugador1.getPuntaje()<<" puntos"<<endl;
        datos_partida="-Jugador ganador: "+jugador1.getNombre()+" con "+to_string(jugador1.getPuntaje())+" puntos jugo contra: "+jugador2.getNombre() +" que perdio con "+to_string(jugador2.getPuntaje())+" puntos, en la fecha :"+jugador1.Tiempo()+"\n";

    }
    else if(jugador2.getPuntaje()>jugador1.getPuntaje()){//Si el jugador 2 obtuvo mas puntaje, se guarda en el archivo como ganador.
        tablero.mostrar_tablero();
        cout<<"Fin del juego, gana el jugador "<<jugador2.getNombre()<<" con "<<jugador2.getPuntaje()<<" puntos"<<endl;
        datos_partida="-Jugador ganador: "+jugador2.getNombre()+" con "+to_string(jugador2.getPuntaje())+" puntos jugo contra: "+jugador1.getNombre()+" que perdio con "+to_string(jugador2.getPuntaje())+" puntos, en la fecha :"+jugador2.Tiempo()+"\n";
    }
    else{ //Por ultmo el caso de empate.
        tablero.mostrar_tablero();
        cout<<"Fin del juego, el juego termino en empate"<<endl;
        datos_partida="-El juego termino en empate, entre el jugador: "+jugador1.getNombre()+" y el jugador: "+jugador2.getNombre()+" ambos con "+to_string(jugador1.getPuntaje())+" puntos, en la fecha :"+jugador1.Tiempo()+"\n";
    }

    escribir_archivo("historial_de_partidas.txt",datos_partida);//sobreescribimos el archivo.
}
