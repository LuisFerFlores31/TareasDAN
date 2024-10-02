#include <iostream>
using namespace std;

    void insertarInicio(int valor){
        cout<<"insertar inicio"<<endl;
    }
    void insertarFinal(int valor){
        cout<<"insertar al final"<<endl;
    }

    void eliminarInicio(){
        cout<<"eliminar inicio"<<endl;
    }

    void eliminarFinal(){
        cout<<"eliminarfinal"<<endl;
    }

    void imprimir(){
        cout<<"imprimir lista"<<endl;
    }

int main (){
    int opc, valor;
   do {
        cin >> opc;
        switch (opc) {
        case 1: // Insertar al inicio
            cin >> valor;
            cout<<valor<<endl;
            insertarInicio(valor);
            break;
        case 2: // Insertar al final
            cin >> valor;
            insertarFinal(valor);
            break;
        case 3: // Eliminar al inicio
            eliminarInicio();
            break;
        case 4: // Eliminar al final
            eliminarFinal();
            break;
        case 5: // Imprimir la lista
            imprimir();
            break;
        case 0: // Salir
            break;
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};