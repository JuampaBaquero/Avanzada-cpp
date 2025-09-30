#include <iostream>

/*
    A  continuación la implementación más inutil y que voy a dejarla solo como comentario porque
    probablemente no sirva en Linux, ya que es nativa de Windows (no se usar Linux)
    Para usarla solo quita las barras de comentario. Es meramente estético.
*/
//#include <windows.h>
//#include <locale>
using namespace std;

struct Jugadas{
    char miJugada;
    char suJugada;
    int miPuntaje;
    int suPuntaje;
};

void jugar(struct Jugadas &jugadas){

    switch(jugadas.miJugada){
        case 'A': jugadas.miPuntaje += 1; break;
        case 'B': jugadas.miPuntaje += 2; break;
        case 'C': jugadas.miPuntaje += 3; break;
    }

    switch(jugadas.miJugada){
        case 'X': jugadas.suPuntaje += 1; break;
        case 'Y': jugadas.suPuntaje += 2; break;
        case 'Z': jugadas.suPuntaje += 3; break;
    }

    //Gano yo
    if((jugadas.miJugada == 'A' && jugadas.suJugada == 'Z') ||
       (jugadas.miJugada == 'B' && jugadas.suJugada == 'X') ||
       (jugadas.miJugada == 'C' && jugadas.suJugada == 'Y')){

        jugadas.miPuntaje += 6;
       }

    //Gana el
    else if((jugadas.miJugada == 'A' && jugadas.suJugada == 'Y') ||
            (jugadas.miJugada == 'B' && jugadas.suJugada == 'Z') ||
            (jugadas.miJugada == 'C' && jugadas.suJugada == 'X')){

        jugadas.suPuntaje += 6;
       }
    else{
        jugadas.suPuntaje += 3;
        jugadas.miPuntaje += 3;
    }
}

string comparacion(struct Jugadas jugadas){

    if(jugadas.miPuntaje > jugadas.suPuntaje){
        return "completamente verdad. Hazle caso";

    } else{
        return "MENTIRA. Es un duende estafador";
    }
}

//void carga(int);
//void col(int);

int main(){
    setlocale(LC_ALL, "spanish");

    Jugadas jugadas;
    jugadas.miPuntaje = 0;
    jugadas.suPuntaje = 0;
    char validador = 'a';

    //col(135);
    //system("cls");

    //col(113);
    cout << "\t+--------------------------------------------------------+\n"
         << "\t|Bienvenido al sistema calculador de jugadas del duende. |\n"
         << "\t+--------------------------------------------------------+\n\n\t";
    //carga(300);

    while(true){

        //col(125);
        cout << endl << "\n\tIngrese su jugada en MAYUSCULA(0 para terminar) ---> ";
        cin >> validador;

        if(validador == '0') break;

        while(validador != 'A' && validador != 'B' && validador != 'C'){
            cout << endl << "  Valor ingresado incorrecto. Vuelvalo a ingresar --> ";
            cin >> validador;
        }
        jugadas.miJugada = validador;

        //col(122);
        cout << endl << "\tIngrese la jugada del oponente según el duende---> ";
        cin >> jugadas.suJugada;

        while(jugadas.suJugada != 'X' && jugadas.suJugada != 'Y' && jugadas.suJugada != 'Z'){
            cout << endl << "  Valor ingresado incorrecto. Vuelvalo a ingresar --> ";
            cin >> jugadas.suJugada;
        }

        jugar(jugadas);
    }
    cout << "\n\t";
    //carga(300);
    //col(124);
    cout << "\n\nTu puntuación fue de " << jugadas.miPuntaje << endl
         << "La de tu rival fue de " << jugadas.suPuntaje << endl;

    //col(125);
    cout << endl << "Lo que dijo el duende fue " << comparacion(jugadas);
}
/*
void carga(int n){

    for(int i = 0; i < 5; i++){
        Sleep(n); //Solo espera n tiempo en milisegundos
        cout << " . ";
    }
}
void col(int n){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, n);
}

*/
