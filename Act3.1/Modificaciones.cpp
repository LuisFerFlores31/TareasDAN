#include <iostream>
using namespace std;

struct BST {
    int check;
    BST* right;
    BST* left;
};

BST* tree = nullptr;

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
        return crearNodo(valor);
    }

    if (valor < tree->check) {
        tree->left = insertar(tree->left, valor);
    } else if (valor > tree->check) {
        tree->right = insertar(tree->right, valor);
    }

    return tree;
}

// Función para encontrar el sucesor en orden (el más pequeño en el subárbol derecho)
BST* minValorNodo(BST* nodo) {
    BST* actual = nodo;

    // Recorrer hasta el nodo más a la izquierda
    while (actual && actual->left != nullptr) {
        actual = actual->left;
    }

    return actual;
}

// Función para eliminar un nodo del árbol
BST* eliminarNodo(BST* root, int valor) {
    if (root == nullptr) return root;

    // Buscar el nodo a eliminar
    if (valor < root->check) {
        root->left = eliminarNodo(root->left, valor);
    } else if (valor > root->check) {
        root->right = eliminarNodo(root->right, valor);
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
        root->right = eliminarNodo(root->right, temp->check);
    }

    return root;
}

// Recorridos del árbol
void preorden(BST* tree) {
    if (tree != NULL) {
        cout << tree->check << " ";
        preorden(tree->left);
        preorden(tree->right);
    }
}

void inorder(BST* tree) {
    if (tree != NULL) {
        inorder(tree->left);
        cout << tree->check << " ";
        inorder(tree->right);
    }
}

void postorder(BST* tree) {
    if (tree != NULL) {
        postorder(tree->left);
        postorder(tree->right);
        cout << tree->check << " ";
    }
}

void LevBLev(BST* tree) {
    cout << "Level by Level (función no implementada aún)" << endl;
}

void traversal(int opc) {
    switch (opc) {
        case 1: // Preorden
            preorden(tree);
            break;

        case 2: // Inorden
            inorder(tree);
            break;

        case 3: // Postorden
            postorder(tree);
            break;

        case 4: // Nivel por Nivel
            LevBLev(tree);
            break;

        default:
            cout << "Opción inválida" << endl;
    }
}

int main() {
    int n, m, valor;

    // Inserción de nodos
    cout << "Actividad 3.1: Ingresar número de nodos del árbol" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Ingresa el valor del nodo " << (i + 1) << ": ";
        cin >> valor;
        tree = insertar(tree, valor);
    }

    // Mostrar los recorridos del árbol antes de eliminar nodos
    cout << "Recorrido Preorden: ";
    traversal(1);
    cout << endl;

    cout << "Recorrido Inorden: ";
    traversal(2);
    cout << endl;

    cout << "Recorrido Postorden: ";
    traversal(3);
    cout << endl;

    // Eliminación de nodos
    cout << "Ingresa el número de nodos a eliminar: ";
    cin >> m;
    for (int i = 0; i < m; i++) {
        cout << "Ingresa el valor del nodo a eliminar: ";
        cin >> valor;
        tree = eliminarNodo(tree, valor);
    }

    // Mostrar los recorridos del árbol después de eliminar nodos
    cout << "Recorrido Preorden después de eliminar: ";
    traversal(1);
    cout << endl;

    cout << "Recorrido Inorden después de eliminar: ";
    traversal(2);
    cout << endl;

    cout << "Recorrido Postorden después de eliminar: ";
    traversal(3);
    cout << endl;

    return 0;
}
