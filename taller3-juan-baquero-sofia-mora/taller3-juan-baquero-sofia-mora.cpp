#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

//Profe, ya somos poderosos porque aprendímos a portear códigos a Linux con chatGPT :), mira

#ifdef _WIN32 //Si el compilador lee que es Windows pues
    #include <windows.h>
    #define pause(); system("pause");
    #define erase(); system("cls");
    #define slip(milisegundos); Sleep(milisegundos * 1000);

#elif __linux__ //AHHH pero si lee Linux
    #include <unistd.h>
    #include <stdio.h>
    #include <termios.h>
    #include <string.h>
    #define pause(); system("read -p 'Presiona enter para continuar...' var");
    #define erase(); system("clear");
    #define slip(segundos); sleep(segundos);

#endif

using namespace std;

struct Games{
    int pMove[3];
    int sMove[3];
};

struct Tournament{
    int curMain = 0;
    int curSecondary = 0;
    int mScore = 0;
    int sScore = 0;
    int numGames;
    char mName[200];
    char sName[200];
};

void imprimirMenu();

void setColor(int);

void wait(int);

void frames(int); 

void playPvP(bool);

void printWinner(Tournament &tournament, bool);

int compare(char mMove[], char sMove[], int);

int asign(char move[]);

bool fastCompare(char mMove[], char sMove[]);

bool question();

int main(){

    imprimirMenu();
}

void setColor(int n){
    switch(n){
        case 0: cout << "\033[38;2;139;184;214m"; break; //Azul cielo
        
        case 1: cout << "\033[38;2;202;190;207m"; break; //Rosado
        
        case 2: cout << "\033[38;2;139;214;174m"; break; //Verde
        
        case 3: cout << "\033[38;2;213;20;13m"; break; //Rojo
        
        case 4: cout << "\033[38;2;171;149;196m"; break; //Cian
    }
}

void imprimirMenu(){
    
    for(int i = 1; i < 10; i++){
        erase();
        setColor(2);
        cout << R"(
         ____ ___ _____ ____  ____      _      ____   _    ____  _____ _        ___  
        |  _ \_ _| ____|  _ \|  _ \    / \    |  _ \ / \  |  _ \| ____| |      / _ \ 
        | |_) | ||  _| | | | | |_) |  / _ \   | |_) / _ \ | |_) |  _| | |     | | | |
        |  __/| || |___| |_| |  _ <  / ___ \  |  __/ ___ \|  __/| |___| |___  | |_| |
        |_|  |___|_____|____/|_| \_\/_/   \_\ |_| /_/   \_\_|   |_____|_____|  \___/ 

                           _____ ___    ____________      _
                          |_   _|_ _|  | | ____|  _ \    / \                                           
                            | |  | |_  | |  _| | |_) |  / _ \                                          
                            | |  | | |_| | |___|  _ <  / ___ \                                         
                            |_| |___\___/|_____|_| \_\/_/   \_\                                        
               )";
    
        setColor(i % 5);
        cout << R"(

        $$\   $$\ $$\    $$$$$$$$\ $$$$$$\ $$\      $$\  $$$$$$\ $$$$$$$$\ $$$$$$$$\ 
        $$ |  $$ |$$ |   \__$$  __|\_$$  _|$$$\    $$$ |$$  __$$\\__$$  __|$$  _____|
        $$ |  $$ |$$ |      $$ |     $$ |  $$$$\  $$$$ |$$ /  $$ |  $$ |   $$ |      
        $$ |  $$ |$$ |      $$ |     $$ |  $$\$$\$$ $$ |$$$$$$$$ |  $$ |   $$$$$\    
        $$ |  $$ |$$ |      $$ |     $$ |  $$ \$$$  $$ |$$  __$$ |  $$ |   $$  __|   
        $$ |  $$ |$$ |      $$ |     $$ |  $$ |\$  /$$ |$$ |  $$ |  $$ |   $$ |      
        \$$$$$$  |$$$$$$$$\ $$ |   $$$$$$\ $$ | \_/ $$ |$$ |  $$ |  $$ |   $$$$$$$$\ 
         \______/ \________|\__|   \______|\__|     \__|\__|  \__|  \__|   \________|
                                                                                    
                                                                                    
                )";
            slip(0.8);
        }
    cout << endl << endl << "\t\t | Estamos cargando todos los objetos |";

    do{
        cout << "\n\t\t";
        wait(4);
        erase();
        setColor(0);

        cout << endl
            << "\t\t|+--- SUPER PIEDRA PAPEL TIJERA LAGARTO SPOK Z ---+" << endl
            << "\t\t|              -> MENU PRINCIPAL <-               |" << endl
            << "\t\t+-------------------------------------------------+" << endl
            << "\t\t|                                                 |" << endl
            << "\t\t| 1)      JUGAR                                   |" << endl
            << "\t\t| 2)      MIRAR TORNEOS ANTERIORES                |" << endl
            << "\t\t| 3)      SALIR DEL JUEGO                         |" << endl
            << "\t\t|                                                 |" << endl
            << "\t\t+-------------------------------------------------+" << endl
            << "\t\t|    TU RESPUESTA ----> ";

    } while(question());

    setColor(3);
    cout << endl << endl << "\t\tGRACIAS POR JUGAR!";
}

void wait(int n){

    for(int i = 0; i < n; i++){
        slip(0.35);
        cout << " . ";
    }
}

bool question(){
    int option;
    cin >> option;
    cout << "\n\t\t";
    wait(5);
    
    switch(option){
        case 1:{ //JUGAR
            setColor(1);
            int option;
            erase();
            cout << endl
                << "\t\t|+--- SUPER PIEDRA PAPEL TIJERA LAGARTO SPOCK  ---+" << endl
                << "\t\t|                  -> JUGAR <-                    |" << endl
                << "\t\t+-------------------------------------------------+" << endl
                << "\t\t|                                                 |" << endl
                << "\t\t| 1)      JUGAR CONTRA LA MAQUINA                 |" << endl
                << "\t\t| 2)      JUGAR PVP                               |" << endl
                << "\t\t| 3)      SALIR AL MENU PRINCIPAL                 |" << endl
                << "\t\t| 4+)     SALIR DEL JUEGO                         |" << endl
                << "\t\t|                                                 |" << endl
                << "\t\t+-------------------------------------------------+" << endl
                << "\t\t|    TU RESPUESTA ----> ";
            cin >> option;


            switch(option){
                case 1: playPvP(true); break;
                case 2: playPvP(false); break;
                case 3: return true; break;
                default: return false; break;
            }


        } break;

        case 2: //mirar_puntuaciones
            break; 
        case 3: return false; break;

        default:

        while(option > 3 or option < 0){

            setColor(3);
            cout << endl << endl << "Valor incorrecto. Ingrese su valor --> ";
            setColor(0);
            cin >> option;
            if(option == 3) break;
        }
    }
}

int compare(char mMove[], char sMove[], int machine){
    
    int move1 = asign(mMove);
    if(machine == -1){
        int move2 = asign(sMove);

        if((move1 - move2 + 5) % 5 == 2 || (move1 - move2 + 5) % 5 == 4) return 1;
        if((move1 - move2 + 5) % 5 == 1 || (move1 - move2 + 5) % 5 == 3) return 2;
        return 3;  
    } 
    if((move1 - machine + 5) % 5 == 2 || (move1 - machine + 5) % 5 == 4) return 1;
    if((move1 - machine + 5) % 5 == 1 || (move1 - machine + 5) % 5 == 3) return 2;
    return 3;  
}


bool fastCompare(char a[], const char b[]) {

    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    bool temp = a[i] == '\0' && b[i] == '\0'; 
    return temp;
}

int asign(char move[]){
    if(fastCompare(move, "tijera")) return 0;
    if(fastCompare(move, "papel")) return 1;
    if(fastCompare(move, "piedra")) return 2;
    if(fastCompare(move, "lagarto")) return 3;
    if(fastCompare(move, "spock")) return 4;
}

void playPvP(bool machine){
    setColor(1);
    int tempMachine;
    char jugada[10];
    char tempJugada[10];
    erase();
    int numGames;
    Tournament tournament;

    cout << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|      INDICA EL NUMERO DE PARTIDAS A JUGAR       |" << endl
         << "\t\t|  (RECUERDA QUE CADA PARTIDA TIENE TRES RONDAS)  |" << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    TU RESPUESTA ----> ";
    cin >> numGames;

    cout << endl
         << "\t\t+-------------------------------------------------+" << endl <<
 (machine ? "\t\t|              INGRESE SU NOMBRE                  |": //parchesito perezoso
            "\t\t|           COMO SE LLAMA EL JUGADOR 1 ?          |")<< endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|    RESPUESTA ----> ";
    cin.ignore();
    cin.getline(tournament.mName, 200);
    
    if(!machine){
        cout << endl
            << "\t\t+-------------------------------------------------+" << endl
            << "\t\t|           COMO SE LLAMA EL JUGADOR 2 ?          |" << endl
            << "\t\t+-------------------------------------------------+" << endl
            << "\t\t|    RESPUESTA ----> ";
        cin.getline(tournament.sName, 200);
    }

    setColor(3);
    cout << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|           VA A ARRANCAR EL JUEGO $_$            |" << endl
         << "\t\t+-------------------------------------------------+" << endl << "\t\t";
    wait(15);

    tournament.numGames = numGames;
    Games games[numGames];

    for(int i = 0; i < numGames; i++){
        for(int j = 0; j < 6; j++){

            if(machine){
                char temp[] = "MAQUINA HUMILLA BOTS  /(ToT)/";

                for(int i = 0; i < 31; i++){
                        tournament.sName[i] = temp[i];
                }
            }
            
            erase();
            setColor(3);

            if(!(machine and j % 2 == 1)){ //nand
                cout << endl
                     << "\t\t+-------------------------------------------------+" << endl
                     << "\t\t|               RONDA " << i + 1 << " - PARTIDA " << j / 2 + 1 << "               |" << endl
                     << "\t\t+-------------------------------------------------+" << endl;
                setColor(2);
                cout << "\t\tPUNTAJE |" << endl
                     << "\t\t        |" << tournament.mName << ": " << tournament.mScore << endl
                     << "\t\t        |" << tournament.sName << ": " << tournament.sScore << endl;
                setColor(3);
                cout << "\t\t+-------------------------------------------------+" << endl
                     << "\t\t|               JUEGA JUGADOR " << (j % 2 == 0 ? "UNO": "DOS") << "                 |" << endl
                     << "\t\t+-------------------------------------------------+" << endl;

                setColor(1);
                cout << endl
                    << "\t\t+-------------------------------------------------+" << endl
                    << "\t\t|     PARA JUGAR RECUERDA PONER EN MINUSCULA      |" << endl
                    << "\t\t|                    'piedra'                     |" << endl
                    << "\t\t|                    'papel'                      |" << endl
                    << "\t\t|                    'tijera'                     |" << endl
                    << "\t\t|                    'lagarto'                    |" << endl
                    << "\t\t|                    'spock'                      |" << endl
                    << "\t\t+-------------------------------------------------+" << endl
                    << "\t\t|    TU RESPUESTA ----> ";
                setColor(2);
                cin >> jugada;
                wait(3);
            } else{
                srand(time(NULL));
                tempMachine = rand() % 5;    
            }

            while(!(fastCompare(jugada, "piedra") || 
                    fastCompare(jugada, "papel") ||
                    fastCompare(jugada, "tijera") ||
                    fastCompare(jugada, "spock") ||
                    fastCompare(jugada, "lagarto"))){ //Dios mio, que horror hacer esto
                setColor(3);
                cout << endl 
                     <<"\t\t |Respuesta incorrecta." << endl
                     << "\t\t |TU RESPUESTA ----> ";
                cin >> jugada;
            }
            if(j % 2 == 0){
                for(int k = 0; k < 10; k++){ tempJugada[k] = jugada[k]; }

            } else{
                setColor(2);
                cout << endl 
                     << "\t\t| FINALIZA LA RONDA " << i + 1 << "!|" << endl
                     << "\t\t| LOS RESULTADOS FUERON |" << endl
                     << "\t\t| " << tournament.mName << " saca ";
                setColor(4);
                frames(asign(tempJugada));
                setColor(2);
                pause();

                cout << endl 
                     << "\t\t| " << tournament.sName << " saca ";
                (!machine ? frames(asign(jugada)): frames(tempMachine));
                
                setColor(3);
                if(!machine) tempMachine = -1;
                    

                if(compare(tempJugada, jugada, tempMachine) == 1){
                    tournament.curMain += 1;
                    cout << endl 
                         << "GANA " << tournament.mName << " APLASTANTEMENTE!";
                } 

                if(compare(tempJugada, jugada, tempMachine) == 2){
                    tournament.curSecondary += 1;
                    cout << endl 
                         << "GANA " << tournament.sName << " HUMILLANTEMENTE!";
                }
                if(compare(tempJugada, jugada, tempMachine) == 3){
                    cout << endl
                         << "BUUUUUU, HUBO EMPATE :-(";
                }
                cout << endl;
                pause();
                wait(5);
            }

            if(j % 2 == 0 and (tournament.mScore == 2 or tournament.sScore == 2)){
                break;
            }
        }
        printWinner(tournament, false);
    }
    printWinner(tournament, true);
}

void printWinner(Tournament &tournament, bool finish){
    erase(); erase();
    
    setColor(0);
    if(finish) setColor(3);
    cout << endl
         << "\t\t+-------------------------------------------------+" << endl
         << "\t\t|                FINALIZA LA RONDA                |" << endl
         << "\t\t+-------------------------------------------------+" << endl << "\t\t";
    slip(3);
        cout << endl
             << "\t\t+-------------------------------------------------+" << endl
             << "\t\t|         FELICIDADES! ";
 
        if(!finish){
            if(tournament.curMain > tournament.curSecondary){
                tournament.mScore++;
                cout << tournament.mName;

            } else if(tournament.curMain < tournament.curSecondary){
                tournament.sScore++;
                cout << tournament.sName;

            } else{
                cout << "NADIE!, NINGUNO FUE COMPETENTE PARA GANAR!"; //xd
            }



        } else{

            if(tournament.mScore > tournament.sScore){
                cout << tournament.mName;

            } else if(tournament.mScore < tournament.sScore){
                cout << tournament.sName;

            } else{
                cout << "NADIE!, HA SIDO UN TORNEO JUSTO..."; //xd
            }
        }
        cout << "\n\t\t+-------------------------------------------------+" << endl << "\t\t";
        pause();
}

void frames(int n){

    switch (n){
    case 3: 
        cout << R"(

         @@@@@@@@@@@@@@@@@@@@@@@@
       @@@*====================+%@
      @*                        :#@
      @-  *@@@@@@@@@@@@@@@@@@@%:  +@
     @@#  :=***************@@@@@=  -@
      @@%=:                :%@@@@+  :%@
       @@@@@@@@@@@@@@@@@*  =@@@@@@#:  *@
           @@@@%%%%%%%%#  :%@@@@@@@@:  +@
          @@*             %@@@@@@@@@@-  -@
         @@-  -%@@@@@@@@@@@@@@@@@@@@@@#  :%@
         @%: :@@@@@@@@@@@@@@@@@@@@@@@@@%: :#@
         @@=             :=*@@@@@@@@@@@@#: =@
          @@@%#########*=:    :+@@@@@@@@%: -@
            @@@@@@@@@@@@@@@%*-  =@@@@@@@%: -@
                          @@@*  -+++++++=: -@
                           @@*             -@
                            @@@@@@@@@@@@@@@@@

        )";
        break;

    case 4:
        cout << R"(          
          
                 @@@@@@@@@@@@@@@@                 
             @@@@@@@%#*    *#%@@@@@@@             
          @@@@%*                  #%@@@@          
        @@@@                         *@@@@        
      @@@%                              %@@@      
    @@@@               *                  @@@@    
   %@@*             ##*@@                  #@@%   
  @@@*             %@@ @@#      @@#         *@@@  
 @@@*              %@@*%@%     @@@*          #@@@ 
 @@%               #@@##@@    #@@##@#         @@@@
@@@                #@@%#@@*   @@@*@@           @@@
@@#                *@@%*@@#  @@@ %@%           %@@
@@*                *@@@*%@% %@@*#@@            #@@
@@*                *@@%@@@@@@@# @@%            #@@
@@*                *@@@@@@@@@@@@@@*            #@@
@@%      @@@@%     *@@@@@@@@@@@@@@             %@@
@@@        @@@@@#  %@@@@@@@@@@@@@@             @@@
@@@%         @@@@@@@@@@# %@@@@@@@%            @@@@
 @@@*         %@@@@@@@@@@ #@@@@@@%           #@@@ 
  @@@*         *@@@@@@@@@@*@@@@@@*          #@@@  
   @@@#          %@@@@@@@@%@@@@@           %@@@   
    @@@@           %@@@@@@@@@@@           @@@@    
      @@@%          @@@@@@@@@@%         %@@@      
        @@@@*       %@@@@@@@@@%      *@@@@@       
         @@@@@@#    %@@@@@@@@@%   #@@@@@@         
             @@@@@@@@@@@@@@@@@@@@@@@@@            
                %@@@@@@@@@@@@@@@@%    
                                                  
        )";
        break;

    case 0:
        cout << R"(

       @@@@@@@@@@                                 
     @@@@@@@@@@@@@@@@%                            
    @@@@@@    @@@@@@@@@@@@@                       
    @@@@          @@@@@@@@@@@@@@@@@@@@@@@@@@      
    @@@@%              @@@@@@@@@@@@@@@@@@@@@@@@@  
     @@@@@@                 %@@@@@@@@@@@@@@@@@@@@@
        @@@@@@@              @@@%           @@@@@
            @@@@@@@@@        @@@              @@@@
                @@@@@@@@@   @@                @@@@
  @@@@@@@@@@@@@@@@@@@@@@@   @@                @@@@
@@@@@                       @@     @@         @@@@
@@@@                        @@     @@         @@@@
@@@@@                   @@@@@@     @@         @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@%  @@     @@         @@@@
  @@@@@@@@@@@@@@@@@@@@       @@   @@@         @@@@
     @@@@@@@@@@@@@@          @@@@@%@@@        @@@@
              @@@@%      %@@@@%      @@       @@@@
              @@@@@@%%@@@@@          @@       @@@@
               %@@@@@@@           @@@%        @@@@
                 @@@@@        @@@@@@     %@@@@@@@@
                  @@@@@   %@@@@@  %@@@@@@@@@@@@@@ 
                  %@@@@@@@@@@@@@@@@@@@@@@@@@@%    
                    @@@@@@@@@@@@@@@@@@@           

        )";
        break;
    
    case 1:
        cout << R"(

                        @@@@@@@
                      @@@+   *@@@@@@@@
                @@@@@@@-       -    *@@@
               @@%-      -@@%         #@@@@@@
               @+        =@@@   #@@=       +@@
               @   #@@=  =@@@   #@@+         @@
               @   %@@+  =@@@   #@@+   @@@   *@
               @   %@@+  =@@@   #@@+   @@@   *@
               @   %@@+  =@@@   #@@+   @@@   *@
               @   %@@+  =@@@   #@@+   @@@   *@
               @   %@@+  =@@@   #@@+   @@@   *@
       @@@@@@@@@   %@@@@@@@@@@@@@@@@@@@@@@   *@
     @@@     =@@   %@@@@@@@@@@@@@@@@@@@@@@   *@
    @@*            %@@@@@@@@@@@@@@@@@@@@@@   *@
    @%   %@@@-     %@@@@@@@@@@@@@@@@@@@@@@   *@
    @@    %@@@@=   %@@@@@@@@@@@@@@@@@@@@@@   *@
     @@-    @@@@@# %@@@@@@@@@@@@@@@@@@@@@*   @@
      @@@    -@@@@@@@@@@@@@@@@@@@@@@@@@@@   +@
        @@@     @@@@@@@@@@@@@@@@@@@@@@@%   -@@
          @@@     *@@@@@@@@@@@@@@@@@@@-   =@@
            @@@-      +@@@@@@@@@@@%-     %@@
              @@@@=                   +@@@@
                 @@@@@%*-        -*@@@@@
                     @@@@@@@@@@@@@@@

        )";
        break;

    case 2: 
        cout << R"(

          @@@@@@@@@
        @@@       @@@@@@@@@@@@@@
       @@   @@@@@          @@%%@@@@
       @   @@@@@@   @@@@@         @@
      @@  @@@@@@%  @@@@@@  %@@@@   @@@@@@@
      @%  @@@@@@  @@@@@@%  @@@@@%        @@
      @%  @@@@@%  @@@@@@  @@@@@@   @@@@   @
      @   @@@@@   %% %%@  @@@@@%  @@@@@@  @
      @   @%              @@@@@  %@@@@@@  @
    @@@      @@@@@@@@@@@   @@@   @@@@@    @
   @@%   @@@@@@@@@@@@@@@%  @@@  %@@@@     @
   @   @@@@@@@@@@@@@@@@%        @@@@@    @@
   @  %@@@@@@@@@@@%      %   %    %      @
   @  %@@@@@@@@     %%@@@@@@@@@@%   %@  %@
   @   @@@@@@@  %@@@@@@@@@@@@@@@@@@@@@  @@
   @@  %@@@@@@%@@@@@@@@@@@@@@@@@@@@@@  %@
    @@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@
     @@   @@@@@@@@@@@@@@@@@@@@@@@@@@  %@
      @@%   @@@@@@@@@@@@@@@@@@@@@@@  %@@
       @@@%   @@@@@@@@@@@@@@@@@@@   @@@
         @@@%  @@@@@@@@@@@@@@@@   %@@
           @@  @@@@@@@@@@@@@@@@  @@@
           @@  @@@@@@@@@@@@@@@@  @
           @%  %%%%%%%%%%%%%%%%  @
           @@                    @
            @@@@@@@@@@@@@@@@@@@@@@

    )";
        break;
        default: cout << "Error al retornar xdnt";
    }
    cout << endl;
}