#include <iostream>
#include <windows.h> //Sleep() (solo estético)
#include <fstream>

using namespace std;

struct Strategies{
    char num_strategy = 0;
    int myScore = 0;
    int yourScore = 0;
};


int read_num_goblin(); //Lee el primer número (quizás me compliqué un poco la vida)

void read_master(Strategies strategies[], int); //Lee el resto y llena un array

int transform(char); //Pasa de A, B, C, X, Y, Z a 1, 2, 3

int comparation(int, int, Strategies strategies[], int); //Dice quien gana

void xport(Strategies strategies[], int); //Crea el archivo binario

void read_extras(Strategies strategies[], int); //Lee cada estrategia

void wait();

int main(){

    system("cls");
    cout << "Bienvenido, espere un segundo";
    wait(); 
    
    int n = 0;

    while(n != 3){
        system("cls");
        cout << "\t+------ MENU PRINCIPAL ------+" << endl
             << "\t|  1. Leer las estrategias   |" << endl
             << "\t|  2. Exportar e imprimir    |" << endl
             << "\t|  3. Salir                  |" << endl
             << "\t+----------------------------+" << endl
             << "\t| Su respuesta --> ";
        cin >> n;
        int files = read_num_goblin();

        switch(n){
            
            case 1: 
            {
                cout << "Estamos revisando los archivos existentes"; 
                wait();
                Strategies strategies[files];
                read_master(strategies, files);
                system("pause");

            } break;

            case 2:
            {
                Strategies strategies[files];
                read_master(strategies, files); //Hago esto porque o si no, no existe acá
                system("cls");
                read_extras(strategies, files);
                system("pause");
            } break;
        }
    }
}

int read_num_goblin(){

    ifstream master("torneo.txt", ios::in);
    string line;

    if(!master){
        cout << endl << "Error al abrir el archivo torneo.txt" << "\n\n";
    }
    getline(master, line);
    master.close();
    
    return stoi(line); //Quería prevenir errores por si coje un string y no un int
}                      //Pero chatgpt me dijo que usara try catch y no sé usarlo

void read_master(Strategies strategies[], int n){

    ifstream master("torneo.txt", ios::in);
    string line;
    int i = 0;

    if(!master){
        cout << endl << "Error al abrir el archivo torneo.txt";
    }
    getline(master, line); //Me salto la primera línea
    
    while(getline(master, line)){              // 0 1 2 3 4 5 6 7 8 9 10
        strategies[i].num_strategy = line[10]; // e s t r a t e g i a 1 
        i++;
    }
    system("cls");
    cout << endl << "El duende dijo que habían " << n << " estrategias." << endl
         << endl << "De las cuales: " << endl;

    for(int i = 1; i <= n; i++){
        bool found = false;

        for(int j = 0; j < n; j ++){

            if(strategies[j].num_strategy - '0' == i){ //Vi que es la forma de pasar un char a un int
            found = true;
            break;
        }
        }

        if(!found){
            cout << i << " "; 
        }
    }
    cout << endl << "No existe" << endl;

    master.close();
}

int transform(char input){

    switch (input){
    case 'A': return 1; break;
    case 'B': return 2; break;
    case 'C': return 3; break;
    case 'X': return 1; break;
    case 'Y': return 2; break;
    case 'Z': return 3; break;
    }
    return 0;
}

int comparation(int a, int b, Strategies strategies[], int n){

    if(a == 1 && b == 3 || 
       a == 2 && b == 1 || //a gana
       a == 3 && b == 2 ){
        strategies[n].myScore += 6;
        return 0;
    }
    if(b == 1 && a == 3 || 
       b == 2 && a == 1 || //b gana
       b == 3 && a == 2 ){
        strategies[n].yourScore += 6;
        return 0;
    }
    if(a == b){
        strategies[n].myScore += 3;
        strategies[n].yourScore += 3;
        return 0;
    }
    return 1;
}

void xport(Strategies strategies[], int n){

    ofstream output("salida.bin", ios::binary);
    if(!output){
        cout << endl << "Error al crear salida.bin" << endl;
    }
    output.write((char*)strategies, n * sizeof(strategies)); //porque son n structs

    output.close();

    cout << "Archivo binario creado con exito!" << endl
         << "Los resultados del duende fueron: " << endl << endl;

    for(int i = 0; i < n; i++){

        if(strategies[i].num_strategy != 0){
            int j = strategies[i].num_strategy - '0';
            cout << "--- ESTRATEGIA " << strategies[i].num_strategy << " ---" << endl
                << "TU PUNTAJE: " << strategies[j].myScore << endl
                << "PUNTAJE ENEMIGO: " << strategies[j].yourScore << endl
                << "FUE RENTABLE? ";

            if(strategies[j].myScore <= strategies[j].yourScore){
                cout << "NO, que pena";
            } else{
                cout << "SI, ve por tu silla gamer RGB";
            }
            wait();
            cout << endl << endl;
        }
    }
    cout << endl;
}

void read_extras(Strategies strategies[], int n){
    
    string name = "estrategia";
    for(int i = 0; i < n; i++){

        if (strategies[i].num_strategy == 0) continue;

        int j = strategies[i].num_strategy - '0';
        ifstream flow(name + to_string(j) + ".txt", ios::in);

        if(!flow){
            cout << endl << "Error al abrir " << name + to_string(j) + ".txt" << endl;
        }
        char myMove, yourMove;
        int iteration = 0;

        while(flow >> myMove >> yourMove){
            iteration++;
            int myNew = transform(myMove);
            int yourNew = transform(yourMove);
            
            strategies[j].myScore += myNew;
            strategies[j].yourScore += yourNew;

            int result = comparation(myNew, yourNew, strategies, j);
            if(result == 1) cout << "Error en la iteracion " << iteration;
        }   
        flow.close();
    }
    xport(strategies, n);
}

void wait(){

    for(int i = 0; i < 3; i++){
        Sleep(350);
        cout << " . ";
    }
    cout << endl;
}