/*Act 2.1 - Implementación de un ADT de estructura de datos lineales
Luis Fernando Cruz Flores A01738347
Antonio Mendez Rodriguez A01738269
Luis Angel Zempoalteca Serrano A01738862

Fecha: 10 de Octubre*/

#include <iostream>
using namespace std;

    struct node{
        int data;
        node* next;
    };
    //Complejidad constante O (1)
    void insertarInicio(node* &pth,int valor){
        node *tmp = new node;
        tmp -> data = valor;
        tmp -> next = pth;
        pth = tmp;
    }
    //Complejidad lineal O(n)
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
    //complejidad constante O(1)
    void eliminarInicio(node* &head){
        if (head == nullptr)
            cout<<"ERROR"<<endl;

        else{
            node *tmp = head;
            head = head -> next;
            delete tmp;
        }
    }
    //Complejidad lineal O(n)
    void eliminarFinal(node* &pth){
        if (pth == nullptr)
            cout << "ERROR" << endl;
            
        else if (pth -> next == nullptr){
            delete pth;
            pth = nullptr;
        }
        else {
            node* tmp = pth;
            while (tmp -> next -> next != nullptr) {
                tmp = tmp -> next;
            }
        delete tmp -> next;
        tmp -> next = nullptr;
    }
}
    //Complejidad lineal O(n)
    void imprimir(node* h){
        while(h != nullptr) {
            cout << h -> data << endl;
            h = h -> next;
        }
    }
    //Complejidad lineal O(n) 
    void Freeup(node* &pth){
        while (pth != nullptr){
            node* tmp = pth;
            pth = pth -> next;
            delete tmp;
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
            Freeup(list);
            break;
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};