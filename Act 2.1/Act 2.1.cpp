#include <iostream>
using namespace std;

    struct node{
        int data;
        node* next;
    };

    void insertarInicio(node* &pth,int valor){
        node *tmp = new node;
        tmp -> data = valor;
        tmp -> next = pth;
        pth = tmp;
    }
    void insertarFinal(node* &pth,int valor){
        node* newNode = new node;
        newNode -> next = nullptr;
        newNode -> data = valor;

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

    void eliminarInicio(node* &pth){
        if (pth == nullptr)
            cout<<"ERROR"<<endl;

        else{
            cout<<"eliminar inicio"<<endl;
             node *tmp = pth;
            pth = pth -> next;
            delete tmp;
        }
    }

    void eliminarFinal(node* &pth){
        if (pth == nullptr)
        cout<<"ERROR"<<endl;

        else{
            cout<<"eliminarfinal"<<endl;
            //node* tmp = pth;
           //pth = pth -> 

        }
    }

    void imprimir(node* h){
         if (h == nullptr) {
        cout << "lista esta vacia" << endl;
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
            insertarInicio(list,valor);
            break;
        case 2: // Insertar al final
            cin >> valor;
            insertarFinal(list,valor);
            break;
        case 3: // Eliminar al inicio
            eliminarInicio(list);
            break;
        case 4: // Eliminar al final
            eliminarFinal(list);
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