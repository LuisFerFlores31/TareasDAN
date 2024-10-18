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

//Funcion para borrar nodos
BST* minValorNodo(BST* nodo) {
    BST* actual = nodo;

    // Recorrer hasta el nodo más a la izquierda
    while (actual && actual->left != nullptr) {
        actual = actual->left;
    }

    return actual;
}

// Función para eliminar un nodo del árbol
BST* eliminar(BST* root, int valor) {
    if (root == nullptr) return root;

    // Buscar el nodo a eliminar
    if (valor < root->check) {
        root->left = eliminar(root->left, valor);
    } else if (valor > root->check) {
        root->right = eliminar(root->right, valor);
    } else {
        // Caso 1: El nodo no tiene hijos o tiene un hijo
        if (root->left == nullptr) {
            BST* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            BST* temp = root->left;
            delete root;
            return temp;
        }

        // Caso 2: El nodo tiene dos hijos, se busca el sucesor en orden
        BST* temp = minValorNodo(root->right);

        // Reemplazar el valor del nodo actual por el sucesor
        root->check = temp->check;

        // Eliminar el sucesor en orden
        root->right = eliminar(root->right, temp->check);
    }

    return root;
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

void LevBLev(BST* tree) {
    if (tree != NULL) {

        vector<BST*> levels;  // Vector para almacenar los nodos por niveles
        levels.push_back(tree);  
        int i = 0; 
        while (i < levels.size()) {
            BST* actual = levels[i];
            i++;  
            cout << actual->check << " "; 

            // Agrega a los hijos left y right
            if (actual->left != nullptr) {
            levels.push_back(actual->left);
            }
            if (actual->right != nullptr) {
            levels.push_back(actual->right);
            }
        }
        
    }
}
    

void traversal (int opc){
    switch (opc){
        case 1:
        preorden(tree);
        break;

        case 2:
        inorder(tree);
        break;

        case 3:
        postorder(tree);
        break;

        case 4:
        LevBLev(tree);
        break;
    }
}

BST* ancestros(BST* tree, int valor) {
    if (tree == nullptr) {
        return nullptr;  // El nodo no existe
    }

    // Si el nodo es el que buscamos, terminamos y lo retornamos
    if (tree->check == valor) {
        return tree;
    }

    // Si el nodo está en el subárbol izquierdo
    if (valor < tree->check) {
        BST* leftResult = ancestros(tree->left, valor);
        if (leftResult != nullptr) {
            cout << tree->check << " ";  // Imprimir el ancestro
            return leftResult;
        }
    }
    // Si el nodo está en el subárbol derecho
    else {
        BST* rightResult = ancestros(tree->right, valor);
        if (rightResult != nullptr) {
            cout << tree->check << " ";  // Imprimir el ancestro
            return rightResult;
        }
    }

    return nullptr;  // Si no encontramos el valor
}


int main(){
    int n,m,q,valor;
    //inicio
    cin>> n;
    for (int i = 0; i < n; i++){
        cin >> valor;
        tree = insertar(tree,valor);
    }
    //Eliminar
    cin>> m;
    for (int i = 0; i < m; i++){
        cin >> valor;
        tree = eliminar(tree,valor);
    }

    //traversal pruebas
    traversal(1);
    cout<<endl;
    traversal(2);
    cout<<endl;
    traversal(3);
    cout<<endl;
    traversal(4);
    
    //El misterioso 3

    //Ancestros
    cin>> q;
    for (int i = 0; i < q; i++){
        cin >> valor;
        tree = ancestros(tree,valor);
    }

};