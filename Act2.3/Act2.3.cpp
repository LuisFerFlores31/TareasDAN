/*Act 2.1 - Implementación de un ADT de estructura de datos lineales
Luis Fernando Cruz Flores A01738347
Antonio Mendez Rodriguez A01738269
Luis Angel Zempoalteca Serrano A01738862

Fecha: 9 de Octubre*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* previous;
};

// Estructura para almacenar los registros
struct Registro {
    int mes;
    int dia;
    string contenido;
    string fecha; 
}; 


int main (){
    //open File 
    ifstream file("bitacora.txt");
    if (!file.is_open()) {
        cout << "El archivo no se pudo abrir" << endl;
        return 1;
    }


     // resultados en sorted.txt
    ofstream output("SortedData.txt");
    if (!output.is_open()) {
        cout << "No se pudo abrir el archivo de salida" << endl;
        return 1;
    }

    return 0;  
    
};