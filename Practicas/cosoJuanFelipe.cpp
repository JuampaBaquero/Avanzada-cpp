#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Libreria {
    int codigo;
    string nombre;
    int valor;
    int cantidad;
};

struct Pedido{
    int codigo;
    int numpedido;
};
    
int main()
{
    fstream archivoEntradaL("libreria.txt");
    fstream archivoEntradaP("pedido.txt");
    
    ofstream archivoSalida("pedidos_salida.txt", ios::app);
    
    if (!archivoEntradaL) {
        cout << "Error al abrir el archivo de entrada." << endl;
        return 1;  
    }
    if (!archivoEntradaP) {
        cout << "Error al abrir el archivo de entrada." << endl;
        return 1;  
    }
     if (!archivoSalida) {
        cout << "Error al abrir el archivo de salida." << endl;
        return 1;  
    }
    string linea;
    int numLibros = 0;

    while(getline(archivoEntradaL, linea)){
        numLibros++;
    }

    Libreria libros[numLibros];
    int numL = 0;
    
    while(){
        
    }
    Pedido pedidos[100];
    int numP = 0;      
    
     while (getline(archivoEntradaL, linea)) {
        istringstream iss(linea);
        
        string campo;              
        Libreria L;
        
        getline(iss, campo, ',');
        Libreria.codigo = stoi(campo);
        
        getline(iss, campo,',')
        Libreria.nombre = campo;
        
        getline(iss, campo, ',');
        Libreria.valor = stoi(campo);
        
        getline(iss, campo, ',');
        Libreria.cantidad = stoi(campo);
        
        Libreria[numL] = estudiante;
        numL++;
    }
       while (getline(archivoEntradaP, linea)) {
        istringstream iss(linea);
        
        getline(iss, campo, ',');
        Pedido.codigo = stoi(campo);
        
        getline(iss, campo, ',');
        Pedido.numpedido = stoi(campo);
        
        Pedido[numP] = estudiante;
        numP++
        
       }
        

    return 0;
}