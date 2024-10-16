#include <iostream>
#include <vector>
using namespace std;

struct BST{
    int check;
    BST * right;
    BST * left;
};

BST *tree = nullptr;

// Función para crear un nuevo nodo
BST* crearNodo(int valor) {
    BST* nuevoNodo = new BST();
    nuevoNodo->check = valor;
    nuevoNodo->left = nullptr;
    nuevoNodo->right = nullptr;
    return nuevoNodo;
}

// Función para insertar valores en el árbol
BST* insertar(BST* tree, int valor) {
    if (tree == nullptr) {
        // Si el árbol está vacío, se crea el nodo raíz
        return crearNodo(valor);
    }

    // Inserción recursiva en el subárbol izquierdo o derecho
    if (valor < tree->check) {
        tree->left = insertar(tree->left, valor);
    } else if (valor > tree->check) {
        tree->right = insertar(tree->right, valor);
    }

    // Retornar el árbol (o subárbol) actualizado
    return tree;
}

void preorden(BST*tree){
    if (tree != NULL){
        cout<< tree->check<<" ";
        preorden(tree->left);
        preorden(tree->right);
    }
} 

void inorder(BST*tree){
    if (tree != NULL){
        inorder(tree->left);
        cout<< tree->check<<" ";
        inorder(tree->right);
    }
}

void postorder(BST*tree){
    if (tree != NULL){
        postorder(tree->left);
        postorder(tree->right);
        cout<< tree->check<<" ";
    }
}

void LevBLev (BST* tree){
    cout<<"Level by Level"<<endl;
}
    

void traversal (int opc){
    switch (opc){
        case 1: //Preorder
        preorden(tree);
        break;

        case 2://inorder
        inorder(tree);
        break;

        case 3://postorder
        postorder(tree);
        break;

        case 4://Level by Level
        LevBLev(tree);
        break;
    }
}

int main(){
    int opc = 0;
    int n,valor;
    //inicio
    cout<<"Actividad 3.1"<<endl;
    cin>> n;
    for (int i = 0; i < n; i++){
        cin >> valor;
        tree = insertar(tree,valor);
    }

    //traversal
    traversal(1);
    cout<<endl;
    traversal(2);
    cout<<endl;
    traversal(3);
    cout<<endl;
    traversal(4);
};