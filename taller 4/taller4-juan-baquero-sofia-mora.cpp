#include <iostream>
#include <windows.h>

struct Actividad2{ 
    int filas; 
    int columnas;
};

void actividad2();

void actividad1();

int main(){
    actividad1();
}

void actividad1(){
    system("cls");
    int integers;
    int max;
    int *array = nullptr;
    int *newArray = nullptr;

    std::cout << "\nIngrese el numero de integers magicos que van a entrar a la mochila de Bytey inicialmente -> ";
    std::cin >> integers;
    array = new int[integers];

    //Llenamos el primer array
    for(int i = 0; i < integers; i ++){
        std::cout << "Ingrese el " << i + 1 << " elemento -> ";
        std::cin >> *(array + i);
    }

    std::cout << "La mochila de Bytey se ve algo asi: \n\n";

    for(int i = 0; i < integers; i ++){
        std::cout << *(array + i) << "\t";
    }
    std::cout << "\n\n";
    system("pause");
    system("cls");
    std::cout << "Ingrese ahora cuantos integers magicos quieres ingresar" 
              << "\n(la mochila duplicara su tamano hasta que pueda almacenar todo)"
              << "\n-> ";
    std::cin >> max;
    Sleep(500);

    int newTamano = integers;
    while(newTamano < max + integers){
        std::cout << "\nDuplicando tamano . . .";
        Sleep(400);
        newTamano *= 2;
        std::cout << "\nTamano actual: " << newTamano;
    }
    newArray = new int[newTamano];

    for(int i = 0; i < integers; i ++){
        *(newArray + i) = *(array + i);
    }
    for(int i = integers; i < newTamano; i ++){
        *(newArray + i) = 0;
    }
    delete[] array;

    std::cout << "\n\nYA SE HIZO EL PASO!"
              << "\nIngresa ahora los nuevos numeros: ";
    for(int i = integers; i < max + integers; i ++){
        std::cout << "\n" << i - integers + 1 << " -> ";
        std::cin >> *(newArray + i);
    }

    std::cout << "\nEstamos cargando su input . . .";
    Sleep(400);
    std::cout << "\nSu nueva mochila es esta: \n\n";

    for(int i = 0; i < newTamano; i ++){
        std::cout << *(newArray + i) << "\t";
    }
    std::cout << "\n\n";
    delete[] newArray;
    system("pause");
}


void actividad2(){
    system("cls");
    int numPatron;
    Actividad2 *a = new Actividad2;
    
    std::cout << "Ingresa el numero de filas de la matriz: ";
    std::cin >> a -> filas;
    
    std::cout << "Ingresa el numero de columnas de la matriz: ";
    std::cin >> a -> columnas;
    
    int **matriz = new int*[a ->filas];
    
    for(int i = 0; i < a -> filas; i++){
        *(matriz + i) = new int[a -> columnas];
    }

    std::cout << "\nIngrese el numero del patron que quiere:"
              << "\n\t1) Patron secuencial"
              << "\n\t2) Patron zigzag"
              << "\n\t3) Patron espiral"
              << "\n\t4) Patron Fibonacci"
              << "\n\t5) Patron de 2 en 2"
              << "\n--> ";
    std::cin >> numPatron;
    
    switch(numPatron){
        case 1:
        {
            int n = 0;
            for(int i = 0; i < a -> filas; i ++){
                for(int j = 0; j < a -> columnas; j ++){
                    n++;
                    *(*(matriz + i) + j) = n;
                }
            }
        } break;
        case 2:
        {
            bool alDerecho = true;
            int n = 0;

            for(int i = 0; i < a -> filas; i ++){
                for(int j = 0; j < a -> columnas; j++){
                    n++;
                    
                    if(alDerecho){
                        *(*(matriz + i) + j) = n;
                    } else{
                        *(*(matriz + i) + a -> columnas - j - 1) = n;
                    }
                }
                alDerecho = !alDerecho;
            }
        } break;
        case 3:
        {
            int n = 1;
            int k = 0;
            bool continuar = true;

            
            for(int i = 0; i < a -> filas; i ++){
                for(int j = 0; j < a -> columnas; j ++){
                    *(*(matriz + i) + j) = 0;
                }
            }
            while(continuar){
                continuar = false;

                for(int i = k; i < a -> columnas - k; i++){
                    if(*(*(matriz + k) + i) == 0){ 
                        continuar = true;
                        *(*(matriz + k) + i) = n++;
                    }
                }
                for(int i = k + 1; i < a -> filas - k; i++){
                    if(*(*(matriz + i) + a -> columnas - 1 - k) == 0){ 
                        continuar = true;
                        *(*(matriz + i) + a -> columnas - 1 - k) = n++;
                    }
                }
                for(int i = a -> columnas - k - 2; i >= k; i--){
                    if(*(*(matriz + a -> filas - 1 - k) + i) == 0){ 
                        continuar = true;
                        *(*(matriz + a -> filas - 1 - k) + i) = n++;
                    }
                }
                for(int i = a -> filas - k - 2; i > k; i--){
                    if(*(*(matriz + i) + k) == 0){
                        continuar = true;
                        *(*(matriz + i) + k) = n++;
                    }
                }
                k++;
            }
                
        } break;
        case 4: 
        {
            int primero = 0;
            int segundo = 1;
            for(int i = 0; i < a -> filas; i ++){
                for(int j = 0; j < a -> columnas; j++){
                    if(i == 0 and j == 0){
                        *(*(matriz + i) + j) = primero;
                    } else if((i == 0 and j == 1) or (i == 1 and a -> columnas == 1 and j == 0)){
                        *(*(matriz + i) + j) = segundo;
                    } else{
                        *(*(matriz + i) + j) = primero + segundo;
                        primero = segundo;
                        segundo += primero;
                    } 
                }
            }
        } break;
        case 5:
        {
            int n = 0;
            for(int i = 0; i < a -> filas; i ++){
                for(int j = 0; j < a -> columnas; j ++){
                    *(*(matriz + i) + j) = n += 2;
                }
            }
        }
    }
    //Imprimir la matriz
    for(int i = 0; i < a -> filas; i ++){
        for(int j = 0; j < a-> columnas; j++){
            std::cout << *(*(matriz + i) + j);
            std::cout << "\t";
        }
        std::cout << "\n";
    }

    delete a;
