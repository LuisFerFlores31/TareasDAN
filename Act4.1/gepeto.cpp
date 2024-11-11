#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// Convierte el índice de un nodo a su etiqueta en el formato A, B, ..., Z, AA, AB, etc.
string nodoEtiqueta(int index) {
    string etiqueta;
    while (index >= 0) {
        etiqueta = char('A' + (index % 26)) + etiqueta;
        index = index / 26 - 1;
    }
    return etiqueta;
}

// Imprime la matriz de adyacencias
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

// Imprime la lista de adyacencias
void imprimirLista(const vector<vector<int>>& lista) {
    for (int i = 0; i < lista.size(); ++i) {
        cout << nodoEtiqueta(i) << " - ";
        for (int j = 0; j < lista[i].size(); ++j) {
            cout << nodoEtiqueta(lista[i][j]);
            if (j < lista[i].size() - 1) cout << " - ";
        }
        cout << endl;
    }
}

// Realiza el recorrido BFS
void recorridoBFS(const vector<vector<int>>& lista, int inicio) {
    vector<bool> visitado(lista.size(), false);
    queue<int> cola;
    cola.push(inicio);
    visitado[inicio] = true;

    cout << "\nRecorrido BFS: ";
    while (!cola.empty()) {
        int nodo = cola.front();
        cola.pop();
        cout << nodoEtiqueta(nodo) << " ";

        for (int vecino : lista[nodo]) {
            if (!visitado[vecino]) {
                cola.push(vecino);
                visitado[vecino] = true;
            }
        }
    }
    cout << endl;
}

// Realiza el recorrido DFS
void recorridoDFS(const vector<vector<int>>& lista, int inicio) {
    vector<bool> visitado(lista.size(), false);
    stack<int> pila;
    pila.push(inicio);

    cout << "\nRecorrido DFS: ";
    while (!pila.empty()) {
        int nodo = pila.top();
        pila.pop();

        if (!visitado[nodo]) {
            cout << nodoEtiqueta(nodo) << " ";
            visitado[nodo] = true;
        }

        for (auto it = lista[nodo].rbegin(); it != lista[nodo].rend(); ++it) {
            if (!visitado[*it]) {
                pila.push(*it);
            }
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Ingrese el número de nodos: ";
    cin >> n;

    // Leer la matriz de adyacencias
    vector<vector<int>> matriz(n, vector<int>(n));
    cout << "Ingrese la matriz de adyacencias:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matriz[i][j];
        }
    }

    // Convertir a lista de adyacencias
    vector<vector<int>> listaAdyacencia(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == 1) {
                listaAdyacencia[i].push_back(j);
            }
        }
    }

    // Imprimir la matriz de adyacencias
    cout << "\nMatriz de Adyacencias:" << endl;
    imprimirMatriz(matriz);

    // Imprimir la lista de adyacencias
    cout << "\nLista de Adyacencias:" << endl;
    imprimirLista(listaAdyacencia);

    // Recorridos BFS y DFS desde el primer nodo (índice 0)
    recorridoBFS(listaAdyacencia, 0);
    recorridoDFS(listaAdyacencia, 0);

    return 0;
}
