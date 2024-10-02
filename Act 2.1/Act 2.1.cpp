#include <iostream>
using namespace std;

    struct node{
        int data;
        node* next;
    };

    void insertarInicio(node* &pth,int valor){
        cout<<"insertar inicio"<<endl;
         node *tmp = new node;
        tmp -> data = valor;
        tmp -> next = pth;
        pth = tmp;
    }
    void insertarFinal(node* &pth,int valor){
        cout<<"insertar al final"<<endl;
         node* newNode = new node;
        newNode -> data = valor;
        newNode -> next = nullptr;

        if (pth== nullptr)
        pth = newNode;

        else{
            node* tmp = pth;    
            while (tmp -> next != nullptr) {
                tmp = tmp -> next;
        }
        tmp -> next = newNode;
        }
    }

    void eliminarInicio(){
        cout<<"eliminar inicio"<<endl;
    }

    void eliminarFinal(){
        cout<<"eliminarfinal"<<endl;
    }

    void imprimir(node* h){
        cout<<"imprimir lista"<<endl;
         if (h == nullptr) {
        cout << "La lista esta vacia" << endl;
    }
    else {
        while(h != nullptr) {
            cout << h -> data << endl;
            h = h -> next;
        }
    }
    }

int main (){
    node* list = nullptr;
    int opc, valor;
   do {
        cin >> opc;
        switch (opc) {
        case 1: // Insertar al inicio
            cin >> valor;
            cout<<valor<<endl;
            insertarInicio(list,valor);
            break;
        case 2: // Insertar al final
            cin >> valor;
            insertarFinal(list,valor);
            break;
        case 3: // Eliminar al inicio
            eliminarInicio();
            break;
        case 4: // Eliminar al final
            eliminarFinal();
            break;
        case 5: // Imprimir la lista
            imprimir(list);
            break;
        case 0: // Salir
            break;
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};