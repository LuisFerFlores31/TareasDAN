/*
Equipo:
Antonio Mendez Rodriguez A01738269
Luis Fernando Flores Cruz A017388347
Luis Angel Zempoalteca Serrano A01738862
Fecha: 09/11/2024
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Función para imprimir la matriz de adyacencia
// Complejidad: O(n^2)
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int val : fila) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Función para imprimir la lista de adyacencia en el formato solicitado
// Complejidad: O(n)
void imprimirLista(unordered_map<int, vector<int>>& listaAdyacencia) {
    vector<int> nodos;  
    for (const auto& it : listaAdyacencia) {
        nodos.push_back(it.first);
    }
    sort(nodos.begin(), nodos.end());  // Complejidad de ordenamiento: O(n log n)

    for (int nodo : nodos) {
        cout << static_cast<char>('A' + nodo) << " - ";
        vector<int>& adyacentes = listaAdyacencia[nodo];
        sort(adyacentes.begin(), adyacentes.end()); // Ordenar los adyacentes, complejidad: O(n log n)
        for (size_t i = 0; i < adyacentes.size(); ++i) {
            cout << static_cast<char>('A' + adyacentes[i]);
            if (i < adyacentes.size() - 1) {
                cout << " - "; 
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Conversión de matriz de adyacencia a lista de adyacencia
// Complejidad: O(n^2)
unordered_map<int, vector<int>> convertirAMatrizALista(const vector<vector<int>>& matriz) {
    unordered_map<int, vector<int>> listaAdyacencia;
    int n = matriz.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == 1) {
                listaAdyacencia[i].push_back(j);
            }
        }
    }
    return listaAdyacencia;
}

// Recorrido BFS
// Complejidad: O(v+e)
void BFS(const unordered_map<int, vector<int>>& listaAdyacencia, int nodoInicial) {
    vector<bool> visitado(listaAdyacencia.size(), false);
    queue<int> q;
    q.push(nodoInicial);
    visitado[nodoInicial] = true;

    while (!q.empty()) {
        int nodo = q.front();
        q.pop();
        cout << static_cast<char>('A' + nodo) << " ";

        for (int ady : listaAdyacencia.at(nodo)) {
            if (!visitado[ady]) {
                q.push(ady);
                visitado[ady] = true;
            }
        }
    }
    cout << endl << endl;
}

// Recorrido DFS
// Complejidad: O(v+e)
void DFS(const vector<vector<int>>& matriz, int nodoInicial) {
    vector<bool> visitado(matriz.size(), false);
    stack<int> pila;
    pila.push(nodoInicial);

    while (!pila.empty()) {
        int nodo = pila.top();
        pila.pop();

        if (!visitado[nodo]) {
            visitado[nodo] = true;
            cout << static_cast<char>('A' + nodo) << " ";
        }

        for (int i = matriz.size() - 1; i >= 0; --i) {
            if (matriz[nodo][i] == 1 && !visitado[i]) {
                pila.push(i);
            }
        }
    }
    cout << endl << endl;
}

int main() {
    int N;
    cin >> N;

    // Cargar matriz de adyacencia
    vector<vector<int>> matriz(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matriz[i][j];
        }
    }

    // Imprimir matriz de adyacencia
    cout << endl << endl;
    imprimirMatriz(matriz);

    // Convertir a lista de adyacencia
    unordered_map<int, vector<int>> listaAdyacencia = convertirAMatrizALista(matriz);

    // Imprimir lista de adyacencia en formato solicitado
    imprimirLista(listaAdyacencia);

    // Realizar BFS y DFS
    BFS(listaAdyacencia, 0);
    DFS(matriz, 0);

    return 0;
}