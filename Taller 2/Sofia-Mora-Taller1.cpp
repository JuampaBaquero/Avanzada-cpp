#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Resultado {
    char nombre[80];
    int puntosTu = 0;
    int puntosOpo = 0;
};

int calcularPuntaje(char tu, char opo) {
    int puntosForma = 0;
    if (tu == 'X') puntosForma = 1;
    else if (tu == 'Y') puntosForma = 2;
    else if (tu == 'Z') puntosForma = 3;

    int puntosResultado = 0;
    if ((tu == 'X' && opo == 'C') ||
        (tu == 'Y' && opo == 'A') ||
        (tu == 'Z' && opo == 'B')) {
        puntosResultado = 6;
    }
    else if ((tu == 'X' && opo == 'A') ||
             (tu == 'Y' && opo == 'B') ||
             (tu == 'Z' && opo == 'C')) {
        puntosResultado = 3;
    }
    else {
        puntosResultado = 0;
    }
    return puntosForma + puntosResultado;
}

void analisisTorneo() {
    ifstream jugadas("torneo.txt");
    if (!jugadas.is_open()) {
        cout << "No se pudo abrir el archivo torneo" << endl;
        return;
    }

    int z;
    jugadas >> z;

    Resultado resultados[100]; // m�ximo 100
    int totalResultados = 0;

    for (int i = 0; i < z; i++) {
        string estrategia;
        jugadas >> estrategia;

        ifstream estrategias("estrategia" + to_string(i + 1) + ".txt");
        if (!estrategias.is_open()) {
            cout << "No se pudo abrir:" << "estrategia" + to_string(i + 1) + ".txt " << " vuelva a cargarlo o comprueba" << endl;
            continue;
        }

        int puntajeTu = 0;
        int puntajeOpo = 0;
        char opo, tu;

        while (estrategias >> tu >> opo) {
            puntajeTu += calcularPuntaje(tu, opo);

            char jugadaOpo;
            if (opo == 'A') jugadaOpo = 'X';
            else if (opo == 'B') jugadaOpo = 'Y';
            else jugadaOpo = 'Z';

            char jugadaTu;
            if (tu == 'X') jugadaTu = 'A';
            else if (tu == 'Y') jugadaTu = 'B';
            else jugadaTu = 'C';

            puntajeOpo += calcularPuntaje(jugadaOpo, tu);
        }
        estrategias.close();

        int j;
        for (j = 0; j < estrategia.size() && j < 79; j++) {
            resultados[totalResultados].nombre[j] = estrategia[j];
        }
        resultados[totalResultados].nombre[j] = '\0';

        resultados[totalResultados].puntosTu = puntajeTu;
        resultados[totalResultados].puntosOpo = puntajeOpo;

        totalResultados++;
    }
    jugadas.close();

    ofstream binario("resultados.ns", ios::binary);
    binario.write((char*)resultados, sizeof(Resultado) * totalResultados);
    binario.close();
    cout << "Los resutados en binario seran guarados en resultados.ns :)" << endl;
}

void mostrarResultados() {
    ifstream jugadas("torneo.txt");
    if (!jugadas.is_open()) {
        cout << "No se pudo abrir el archivo torneo" << endl;
        return;
    }

    int z;
    jugadas >> z;

    ifstream binario("resultados.ns", ios::binary);
    if (!binario.is_open()) {
        cout << "No se pudo abrir resultados.ns"<<endl;
        return;
    }

    int totalResultados = z;
    Resultado resultados[50];
    binario.read((char*)resultados, sizeof(Resultado) * totalResultados);
    binario.close();

    for (int i = 0; i < totalResultados; i++) {
        
        cout << "Estrategia: " << resultados[i].nombre << endl;
        cout << "  Tus puntos son: " << resultados[i].puntosTu << endl;
        cout << "  Los puntos de tu oponente: " << resultados[i].puntosOpo << endl;
        if (resultados[i].puntosTu > resultados[i].puntosOpo) cout << "  Ganaste" << endl;
        else if (resultados[i].puntosTu < resultados[i].puntosOpo) cout << "  Perdiste"<< endl;
        else cout << "  Empate" << endl;
        
    }
}

int main() {
    int opcion;
    do {
        cout << "1. Jugar torneos"<<endl;
        cout << "2. Leer archivo binario y mostrar resultados"<<endl;
        cout << "3. Salir"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) analisisTorneo();
        else if (opcion == 2) mostrarResultados();
        else if (opcion != 3) cout << "Opcion invalida, selecciona por favor alguna valida";

    } while (opcion != 3);

    return 0;
}


