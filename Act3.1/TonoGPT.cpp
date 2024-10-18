/*
Equipo:
Antonio Méndez Rodríguez A01738269
Luis Fernando Flores Cruz A017388347
Luis Angel Zempoalteca Serrano A01738862
*/

#include <iostream>
#include <vector>
using namespace std;

struct node {
    int valor;
    struct node *izq;
    struct node *der;
};

typedef struct node *nodo;

// Función para insertar valores en el árbol binario de búsqueda
// Complejidad: O(n)
void insertar(int val_ins, nodo& raiz) {
    if (raiz == NULL) {
        nodo nuevo = new (struct node);
        nuevo->valor = val_ins;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    } else {
        if (val_ins < raiz->valor) {
            insertar(val_ins, raiz->izq);
        } else if (val_ins > raiz->valor) {
            insertar(val_ins, raiz->der);
        }
    }
}

// Función para encontrar el sucesor in-order (mínimo del subárbol derecho)
// Complejidad: O(n).
nodo minValueNode(nodo raiz) {
    nodo actual = raiz;
    while (actual && actual->izq != NULL)
        actual = actual->izq;
    return actual;
}

// Función para eliminar nodos en el árbol binario de búsqueda
// Complejidad: O(n).
nodo eliminar(nodo raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->izq = eliminar(raiz->izq, valor);
    } else if (valor > raiz->valor) {
        raiz->der = eliminar(raiz->der, valor);
    } else {
        if (raiz->izq == NULL) {
            nodo temp = raiz->der;
            delete raiz;
            return temp;
        } else if (raiz->der == NULL) {
            nodo temp = raiz->izq;
            delete raiz;
            return temp;
        }

        nodo temp = minValueNode(raiz->der);
        raiz->valor = temp->valor;
        raiz->der = eliminar(raiz->der, temp->valor);
    }
    return raiz;
}

// Función para mostrar Preorder
// Complejidad: O(n)
void preorder(nodo raiz) {
    if (raiz != NULL) {
        cout << raiz->valor << " ";
        preorder(raiz->izq);
        preorder(raiz->der);
    }
}

// Función para mostrar Inorder
// Complejidad: O(n)
void inorder(nodo raiz) {
    if (raiz != NULL) {
        inorder(raiz->izq);
        cout << raiz->valor << " ";
        inorder(raiz->der);
    }
}

// Función para mostrar Postorder
// Complejidad: O(n)
void postorder(nodo raiz) {
    if (raiz != NULL) {
        postorder(raiz->izq);
        postorder(raiz->der);
        cout << raiz->valor << " ";
    }
}

// Función para mostrar Level Order
// Complejidad: O(n)
int height(nodo raiz) {
    if (raiz == NULL)
        return 0;
    int left_height = height(raiz->izq);
    int right_height = height(raiz->der);
    return max(left_height, right_height) + 1;
}

void printCurrentLevel(nodo raiz, int level) {
    if (raiz == NULL)
        return;
    if (level == 1)
        cout << raiz->valor << " ";
    else if (level > 1) {
        printCurrentLevel(raiz->izq, level - 1);
        printCurrentLevel(raiz->der, level - 1);
    }
}

void levelOrder(nodo raiz) {
    int h = height(raiz);
    for (int i = 1; i <= h; i++) {
        printCurrentLevel(raiz, i);
    }
}

// Función para encontrar los ancestros de un nodo
// Complejidad: O(n).
bool ancestors(nodo raiz, int val, vector<int>& ancestros) {
    if (raiz == NULL)
        return false;
    if (raiz->valor == val)
        return true;

    if (ancestors(raiz->izq, val, ancestros) || ancestors(raiz->der, val, ancestros)) {
        ancestros.push_back(raiz->valor);
        return true;
    }
    return false;
}

// Función para determinar el nivel de un nodo en el árbol
// Complejidad: O(n).
int whatlevelamI(nodo raiz, int val, int nivel = 0) {
    if (raiz == NULL)
        return -1;
    if (raiz->valor == val)
        return nivel;
    int nivelIzq = whatlevelamI(raiz->izq, val, nivel + 1);
    if (nivelIzq != -1)
        return nivelIzq;
    return whatlevelamI(raiz->der, val, nivel + 1);
}

int main() {
    nodo arbol = NULL;
    int n, m, q, r;

    // Leer la cantidad de nodos a insertar
    cin >> n;
    vector<int> valores(n);
    for (int i = 0; i < n; ++i) {
        cin >> valores[i];
        insertar(valores[i], arbol);
    }

    // Leer la cantidad de nodos a eliminar
    cin >> m;
    vector<int> valores_eliminar(m);
    for (int i = 0; i < m; ++i) {
        cin >> valores_eliminar[i];
        arbol = eliminar(arbol, valores_eliminar[i]);
    }

    // Imprimir recorridos
    preorder(arbol);
    cout << endl;

    inorder(arbol);
    cout << endl;

    postorder(arbol);
    cout << endl;

    levelOrder(arbol);
    cout << endl;

    cout << height(arbol) << endl;

    // Leer la cantidad de valores para desplegar ancestros
    cin >> q;
    vector<int> valores_ancestros(q);
    for (int i = 0; i < q; ++i) {
        cin >> valores_ancestros[i];
        vector<int> ancestros;
        if (ancestors(arbol, valores_ancestros[i], ancestros)) {
            for (int j = ancestros.size() - 1; j >= 0; --j) {
                cout << ancestros[j] << " ";
            }
        }
        cout << endl;
    }

    // Leer la cantidad de valores para desplegar niveles
    cin >> r;
    vector<int> valores_niveles(r);
    for (int i = 0; i < r; ++i) {
        cin >> valores_niveles[i];
        cout << whatlevelamI(arbol, valores_niveles[i]) << endl;
    }

    return 0;
}