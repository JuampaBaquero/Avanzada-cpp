//Taller 2. Autores: Juan Pablo Baquero y Sofía Mora Calderón

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>

using namespace std;

struct Player{
    char name[100];
    char opc;
};

struct Board {
    char cells[3][3];
};

struct Tournament{
    Player play1;
    Player play2;
    Board board;
    int rounds;
};

struct Lecture{ 
    int mainScore;
    int secScore;
    char mainName[100];
    char secName[100];
};

void wait(); //Esperar . . ., meramente visual

void otherTournaments(); //Mirar otros torneos

void printBoard(Board* board); //Imprime el tablero

bool move(Board* board); //

bool placeMove(Board* board, int row, int col, char opc); //

void machineMove(Board* board, Player* machine); //Generador aleatorio

void strtournament(Tournament* t);

void jugarRonda(Tournament* t, int gameMode, int& victorias1, int& victorias2);

void jugarTorneo(Tournament* t, int gameMode);

void playAllGame(); //Compila un main que usamos para unir lógica del juego y archivos

void saveStruct(int mainScore, int secScore, char mainName[], char secName[]);
//Salva la estructura lecture para que luego se pueda leer en binario

int main()
{
    int election = 0;

    while(election != 3)
    {
        system("cls");
        cout << "\t\t+--- TRIQUI INTERDIMENSIONAL GALACTICO CAOTICO ---+" << endl
             << "\t\t|              -> MENU PRINCIPAL <-               |" << endl
             << "\t\t+-------------------------------------------------+" << endl
             << "\t\t|                                                 |" << endl
             << "\t\t| 1)      JUGAR                                   |" << endl
             << "\t\t| 2)      MIRAR TORNEOS ANTERIORES                |" << endl
             << "\t\t| 3)      SALIR DEL JUEGO                         |" << endl
             << "\t\t|                                                 |" << endl
             << "\t\t+-------------------------------------------------+" << endl
             << "\t\t|    TU RESPUESTA ----> ";
        cin >> election;

        cout << "\t";
        wait();

        switch(election){
            case 1: playAllGame(); break;
            case 2: otherTournaments(); break;
            default:
                cout << endl << "ERROR!. VUELVE A INTENTARLO: ";
                cin >> election;
        }
    }
}

void wait()
{
    for(int i = 0; i < 3; i++){
        cout << " . ";
        Sleep(350);
    }
}

void otherTournaments()
{
    system("cls");
    char fileName[50] = "";
    Lecture lecture;

    cout << "\t\t+--- TRIQUI INTERDIMENSIONAL GALACTICO CAOTICO ---+" << endl
         << "\t\t|            -> TORNEOS ANTERIORES <-             |" << endl
         << "\t\t|                                                 |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|     POR FAVOR, INGRESA EL NOMBRE DEL ARCHIVO    |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    TU RESPUESTA ----> ";
    cin >> fileName;

    cout << "\t";
    wait();


    //Leyendo el archivo binario
    ifstream flow(fileName, ios::in);

    if(!flow){
        cout << endl << "No se pudo abrir " << fileName << endl;
        return;
    }
    flow.read((char *)&lecture, sizeof(lecture));
    flow.close();

    //Imprimiendo los resultados
    cout << endl;
    cout << "\t\t+--- TRIQUI INTERDIMENSIONAL GALACTICO CAOTICO ---+" << endl
         << "\t\t|            -> TORNEOS ANTERIORES <-             |" << endl
         << "\t\t|                                                 |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|     - Nombre del primer jugador: " << lecture.mainName << endl
         << "\t\t|     - Puntuacion: " << lecture.mainScore << endl << endl
         << "\t\t|     - Nombre del segundo jugador: " << lecture.secName << endl
         << "\t\t|     - Puntuacion:" << lecture.secScore << endl;

    system("pause");

}

void saveStruct(int mainScore, int secScore, char mainName[], char secName[]){
    Lecture lecture;
    char fileName[50];

    for(int i = 0; i < 100; i++){
        *(lecture.mainName + i) = *(mainName + i);
        *(lecture.secName + i) = *(secName + i);
    }

    lecture.mainScore = mainScore;
    lecture.secScore = secScore;
    bool fail = true;

    do{
    
        cout << endl << endl;
        cout << "\t\t+--- TRIQUI INTERDIMENSIONAL GALACTICO CAOTICO ---+" << endl
            << "\t\t|              -> GUARDAR TORNEOS <-              |" << endl
            << "\t\t|                                                 |" << endl
            << "\t\t+-------------------------------------------------+" << endl
            << "\t\t|     INGRESA EL NOMBRE DEL ARCHIVO CON EL QUE    |" << endl
            << "\t\t|     QUIERES ENCONTRAR LUEGO ESTE TORNEO.        |" << endl
            << "\t\t|     OJO: TAMBIEN CON SU EXTENSION (EJ .bin)     |" << endl
            << "\t\t+-------------------------------------------------+" << endl
            << "\t\t|    TU RESPUESTA ----> ";
        cin >> fileName;

        ofstream flow(fileName, ios::out);

        if(!flow){ 
            cout << endl << "Error al crear " << fileName;
            fail = true;
        }
        else{
            flow.write((char *)&lecture, sizeof(lecture));
            fail = false;
        }
        flow.close();
        cout << endl << "\t\t\tARCHIVO CREADO EXITOSAMENTE!" << endl;

        system("pause");

    } while(fail);
}


///////////////////////////////////////////////////////////////////////////


void printBoard(Board* board) {

    for (int i = 0; i < 3; i++) {
        cout << "\t\t\t\t   |";

        for (int j = 0; j < 3; j++) {
            cout << " " << *(*(board->cells + i) + j) << " ";
        }
        cout << "|" << endl;
        if (i < 2) cout << "      " << endl;
    }

}

bool move(Board* board) {
    for (int i = 0; i < 3; i++) {

        if (*(*(board -> cells + i) + 0) == *(*(board -> cells + i) + 1) &&
            *(*(board -> cells + i) + 1) == *(*(board -> cells + i) + 2) &&
            *(*(board -> cells + i) + 0) != '-')

            return true;

        if (*(*(board -> cells + 0) + i) == *(*(board -> cells + 1) + i) &&
            *(*(board -> cells + 1) + i) == *(*(board -> cells + 2) + i) &&
            *(*(board -> cells + 0) + i) != '-')

            return true;
    }

    if (*(*(board -> cells + 0) + 0) == *(*(board -> cells + 1) + 1) &&
        *(*(board -> cells + 1) + 1) == *(*(board -> cells + 2) + 2) &&
        *(*(board -> cells + 0) + 0) != '-')

        return true;

    if (*(*(board -> cells + 0) + 2) == *(*(board -> cells + 1) + 1) &&
        *(*(board -> cells + 1) + 1) == *(*(board -> cells + 2) + 0) &&
        *(*(board -> cells + 0) + 2) != '-')

        return true;

    return false;
}

bool placeMove(Board* board, int row, int col, char opc) {

    if (row < 0 || row > 2 || col < 0 || col > 2)
        return false;

    if (*(*(board -> cells + row) + col) != '-')
        return false;

    *(*(board -> cells + row) + col) = opc;
    return true;
}

void machineMove(Board* board, Player* machine) {

    int row, column;

    do {
        row = rand() % 3;
        column = rand() % 3;

   } while (!placeMove(board, row, column, machine -> opc));
}

void strtournament(Tournament* t) {
    system("cls");
    t -> play1.opc = 'X';
    t -> play2.opc = 'O';

    cout << "\t\t+--- TRIQUI INTERDIMENSIONAL GALACTICO CAOTICO ---+" << endl
         << "\t\t|               -> INFORMACION <-                 |" << endl
         << "\t\t|                                                 |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|              NOMBRE DEL JUGADOR 1               |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    TU RESPUESTA ----> ";
    cin >> t -> play1.name;

    cout << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|              NOMBRE DEL JUGADOR 2               |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    TU RESPUESTA ----> ";
    cin >> t -> play2.name;

    cout << "\n";
    cout << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|               NUMERO DE RONDAS                  |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    TU RESPUESTA ----> ";
    cin >> t -> rounds;
}

void jugarRonda(Tournament* t, int gameMode, int& victorias1, int& victorias2) {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){

            *(*(t -> board.cells + i) + j) = '-';

        }
    }
    bool ganador = false;
    int movimientos = 0;

    while (movimientos < 9 && !ganador){
        printBoard(&t->board);

        Player* current = (movimientos % 2 == 0) ? &t->play1 : &t->play2;

        if (gameMode == 2 && current == &t->play2) {
            machineMove(&t -> board, current);

        } else {
            int row, col;
            cout << "\t\t\t\t" << current -> opc << ", fila y columna (1 - 3): ";
            cin >> row >> col;

            if (!placeMove(&t->board, row - 1, col - 1, current->opc)) {
                cout << "Movimiento invalido, intenta de nuevo :)" << endl;
                continue;
            }
        }

        movimientos++;

        if (move(&t->board)) {
            printBoard(&t->board);
            cout << endl << "Felicidades, el ganador es: " << current->name << endl;

            if (current == &t->play1) victorias1++;
            else victorias2++;
            ganador = true;
        }
    }

    if (!ganador) {
        printBoard(&t->board);
        cout << "Empataron" << endl;
    }
}

void jugarTorneo(Tournament* t, int gameMode) {
    system("cls");
    int victorias1 = 0, victorias2 = 0;

    for (int r = 0; r < t -> rounds; r++) {

        cout << "\t\t+-------------------------------------------------+" << endl
             << "\t\t|                    RONDA " << r + 1
                                             << "                      |" << endl
             << "\t\t+-------------------------------------------------+" << endl;
        jugarRonda(t, gameMode, victorias1, victorias2);
    }

    cout << "\t\tResultado del torneo:"<<endl;
    cout << t -> play1.name << ": " << victorias1 << " victorias"<<endl;
    cout << t -> play2.name << ": " << victorias2 << " victorias";

    cout << endl;
    if (victorias1 > victorias2){
        cout << "Felicidades " << t -> play1.name << " eres el ganador del torneo" << endl;
    }
    else if (victorias2 > victorias1){
        cout << "Felicidades " << t -> play2.name << " eres el ganador del torneo" << endl;
    }
    else{
        cout << "El torneo termino en EMPATE AAA" << endl;
    }

    saveStruct(victorias1, victorias2, t -> play1.name, t -> play2.name);
}

void playAllGame() {

    srand(time(0));
    Tournament tournament;
    strtournament(&tournament);

    int gameMode;
    cout << endl;
    cout << "\t\t+--- TRIQUI INTERDIMENSIONAL GALACTICO CAOTICO ---+" << endl
         << "\t\t|              -> MODO DE JUEGO <-                |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|                                                 |" << endl
         << "\t\t| 1)      JUGAR PVP                               |" << endl
         << "\t\t| 2)      JUGAR CONTRA LA MAQUINA                 |" << endl
         << "\t\t|                                                 |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    TU RESPUESTA ----> ";
    cin >> gameMode;

    jugarTorneo(&tournament, gameMode);
    return;
}
