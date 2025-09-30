#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

#define MAX_CHAR 4096

struct Tam {
    int f;
    int c;
};

struct Indice {
    int fila1;
    int columna1;
    int fila2;
    int columna2;
};

void calcularHoja(char**, int, int, float**);
Tam leerArchivo(char[], char**&);
int calcularToken(char*);
void crearSalida(float **, Tam);

int main() {
    int opcion;
    cout << "+------BIENVENID@-------+\n" 
         << "|                       |\n" 
         << "| 1) Leer un archivo    |\n" 
         << "| 2) Salir              |\n" 
         << "+-----------------------+\n"
         << "--> ";
    cin >> opcion;

    while(opcion != 1 && opcion != 2){
        cout << "\nIngrese algo valido --> ";
        cin >> opcion;
    }

    if(opcion == 1){
        char** matriz;
        char nomArchivo[50];
        cout << "Ingrese el nombre del archivo --> ";
        cin >> nomArchivo;

        Tam tam = leerArchivo(nomArchivo, matriz);     
        
        if(tam.f <= 0 || tam.c <= 0){
            cout << "Error al leer el archivo";
            return 0;
        }

        float **nuevaMatriz = new float*[tam.f];
        for(int i = 0; i < tam.f; i++){
            *(nuevaMatriz + i) = new float[tam.c];
            for(int j = 0; j < tam.c; j++){
                *(*(nuevaMatriz + i) + j) = 0.0f;
            }
        }

        calcularHoja(matriz, tam.f, tam.c, nuevaMatriz);
    }
}

Tam leerArchivo(char n[], char** &input) {
    Tam tam;
    tam.f = -1;
    tam.c = -1;
    ifstream flujo(n, ios::in);
    
    if(!flujo.is_open()){
        cout << "error al abrir el archivo\n";
        return tam;
    }

    tam.c = 0;
    tam.f = 0;
    char linea[MAX_CHAR];

    int m = 0;
    while(flujo.getline(linea, MAX_CHAR)){
        if(m == 0){
            char *token = strtok(linea, ",");
            while(token){
                tam.c++;
                token = strtok(nullptr, ",");
            }
            m = 1;
        }
        tam.f++;
    }

    input = new char*[tam.f];

    flujo.clear();           
    flujo.seekg(0, ios::beg);   

    for(int i = 0; i < tam.f; i++){
        *(input + i) = new char[MAX_CHAR]; 
        flujo.getline(*(input + i), MAX_CHAR);
    }
    return tam;
}

void calcularHoja(char** input, int f, int numCol, float** output) {
    Tam tam;
    tam.c = numCol;
    tam.f = f;

    for(int i = 0; i < f; i++){
        char* token = strtok(*(input + i), ",");
        int col = 0;
        while(token != nullptr){
            Indice indice;

            switch(calcularToken(token)){
                case -1: // número
                    *(*(output + i) + col) = atof(token);
                    break;

                case 1: // PROM
                {
                    indice.columna1 = *(token + 6) - 'A';
                    indice.fila1    = *(token + 7) - '1';
                    indice.columna2 = *(token + 9) - 'A';
                    indice.fila2    = *(token + 10) - '1';
                    float suma = 0;
                    int cuenta = 0;
                    for(int r = indice.fila1; r <= indice.fila2; r++){
                        for(int c = indice.columna1; c <= indice.columna2; c++){
                            suma += *(*(output + r) + c);
                            cuenta++;
                        }
                    }
                    *(*(output + i) + col) = (cuenta > 0) ? suma / cuenta : 0;
                } break;
                
                case 2: // MIN
                {
                    indice.columna1 = *(token + 5) - 'A';
                    indice.fila1    = *(token + 6) - '1';
                    indice.columna2 = *(token + 8) - 'A';
                    indice.fila2    = *(token + 9) - '1';
                    float minimo = *(*(output + indice.fila1) + indice.columna1);
                    for(int r = indice.fila1; r <= indice.fila2; r++){
                        for(int c = indice.columna1; c <= indice.columna2; c++){
                            if(*(*(output + r) + c) < minimo) 
                                minimo = *(*(output + r) + c);
                        }
                    }
                    *(*(output + i) + col) = minimo;
                } break;

                case 3: // MAX
                {
                    indice.columna1 = *(token + 5) - 'A';
                    indice.fila1    = *(token + 6) - '1';
                    indice.columna2 = *(token + 8) - 'A';
                    indice.fila2    = *(token + 9) - '1';
                    float maximo = *(*(output + indice.fila1) + indice.columna1);
                    for(int r = indice.fila1; r <= indice.fila2; r++){
                        for(int c = indice.columna1; c <= indice.columna2; c++){
                            if(*(*(output + r) + c) > maximo) 
                                maximo = *(*(output + r) + c);
                        }
                    }
                    *(*(output + i) + col) = maximo;
                } break;
                
                case 0: // operación
                {
                    indice.columna1 = *(token + 1) - 'A';
                    indice.fila1    = *(token + 2) - '1';
                    char operacion  = *(token + 3);
                    indice.columna2 = *(token + 4) - 'A';
                    indice.fila2    = *(token + 5) - '1';

                    float v1 = *(*(output + indice.fila1) + indice.columna1);
                    float v2 = *(*(output + indice.fila2) + indice.columna2);

                    switch(operacion){
                        case '+': *(*(output + i) + col) = v1 + v2; break;
                        case '-': *(*(output + i) + col) = v1 - v2; break;
                        case '*': *(*(output + i) + col) = v1 * v2; break;
                        case '/': *(*(output + i) + col) = (v2 != 0) ? v1 / v2 : 0; break;
                    }
                } break;
            }
            col++;
            token = strtok(nullptr, ",");
        }
    }

    crearSalida(output, tam);
}

int calcularToken(char* token) {
    if(token == nullptr) return -1;
    if(*token != '=') return -1;
    if(strstr(token, "PROM") != nullptr) return 1;
    if(strstr(token, "MIN")  != nullptr) return 2;
    if(strstr(token, "MAX")  != nullptr) return 3;
    return 0; 
}

void crearSalida(float **output, Tam tam) {
    ofstream salida("salida.txt", ios::out);
    if(!salida.is_open()) return;

    for(int i = 0; i < tam.f; i++){
        for(int j = 0; j < tam.c; j++){
            salida << *(*(output + i) + j);
            if(j < tam.c - 1) salida << ", ";
        }
        salida << endl;
    }

    cout << "Documento salida.txt creado con éxito!";
}
