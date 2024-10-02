#include <iostream>
using namespace std;

class Listaligada{

    public:
    Listaligada();

    void insertarInicio(int valor){
        cout<<"insertar inicio"<<endl;
    }
    void insertarFinal(int valor){
        cout<<"insertar al final"<<endl;
    }

    private:
    int valor;
};

int main (){
    ListaLigada lista;
    int opc, valor;
   do {
        cin >> opc;
        switch (opc) {
        case 1: // Insertar al inicio
            cin >> valor;
            cout<<valor<<endl;
            lista.insertarInicio(valor);
            break;
        case 2: // Insertar al final
            cin >> valor;
            lista.insertarFinal(valor);
            break;
        case 3: // Eliminar al inicio
            //lista.eliminarInicio();
            break;
        case 4: // Eliminar al final
            //lista.eliminarFinal();
            break;
        case 5: // Imprimir la lista
            //lista.imprimir();
            break;
        case 0: // Salir
            break;
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};