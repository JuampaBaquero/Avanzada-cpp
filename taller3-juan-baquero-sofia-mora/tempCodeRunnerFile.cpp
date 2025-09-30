#include <iostream>
#include <conio.h>  // getch()

using namespace std;

string leerClave() {
    string clave;
    char c;

    cout << "Ingresa tu clave: ";
    while (true) {
        c = getch();  // Lee tecla sin mostrarla
        if (c == 13) break;  // Enter (ASCII 13)
        if (c == 8) {        // Backspace (ASCII 8)
            if (!clave.empty()) {
                clave.pop_back();
                cout << "\b \b"; // borra un *
            }
        } else {
            clave.push_back(c);
            cout << '*';   // muestra * en lugar de la tecla
        }
    }
    cout << endl;
    return clave;
}

int main() {
    string clave = leerClave();
    cout << "La clave real es: " << clave << endl;
}
