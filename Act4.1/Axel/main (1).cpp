//Elian Cantalapiedra Sabugal A01738462
//Axel Javier Rosas Rodriguez A01738607
//Carolina Ivette Ramírez Monfil A00839173

#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct nodo {
    string letra;
    vector<nodo*> apuntador; 
};

vector<nodo> generarLetras(int n) {
    vector<nodo> etiquetas;
    for (char letra = 'A'; letra <= 'Z' && etiquetas.size() < n; letra++) {
        nodo tmp;
        tmp.letra = string(1,letra);
        etiquetas.push_back(tmp);
    }
    if (n > 26) {
        for (char letra1 = 'A'; letra1 <= 'Z' && etiquetas.size() < n; letra1++) {
            for (char letra2 = 'A'; letra2 <= 'Z' && etiquetas.size() < n; letra2++) {
                nodo tmp;
                tmp.letra = string(1,letra1) + letra2;
                etiquetas.push_back(tmp);
            }
        }
    }
    return etiquetas;
}

string indiceLetra(int n) {
    string resultado;
    while (n >= 0) {
        char letra = 'A' + (n % 26);
        resultado = letra + resultado;
        n = (n / 26) - 1;
    }
    return resultado; 
}

// Recorrido de DFS (Profundidad)
vector<bool> visitado;
void DFS(vector<vector<int>>& matrizAdy, int inicio) {
    visitado[inicio] = true;
    cout << indiceLetra(inicio) << " ";

    for (int i = 0; i < matrizAdy.size(); i++) {
        if (matrizAdy[inicio][i] == 1 && !visitado[i]) {
            DFS(matrizAdy, i);
        }
    }
}

// Recorrido de BFS (Anchura)
void BFS(vector<nodo>& listaAdy, int inicio) {
    vector<bool> visitado(listaAdy.size(), false); // vector auxiliar para verificar si un nodo ya fue visitado
    vector<nodo*> cola;

    visitado[inicio] = true;
    cola.push_back(&listaAdy[inicio]);

    while (!cola.empty()) {
        nodo* tmp = cola[0];
        cola.erase(cola.begin());
        cout << tmp->letra << " ";
        
        for (nodo* vecino : tmp->apuntador) {
            int indiceVecino = vecino - &listaAdy[0];
            if (!visitado[indiceVecino]) {
                visitado[indiceVecino] = true;
                cola.push_back(vecino);
            }
        }
    }
    cout << endl;
}

int main() {
    int n = 0;
    cin >> n;
    vector<vector<int>> matrizAdy(n, vector<int>(n));
    vector<nodo> listaAdy = generarLetras(n);

    // introducimos los elementos a la matriz de Ady
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrizAdy[i][j];
        }
    }

    // generamos la lista de Adyacencias
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrizAdy[i][j] == 1) {
                listaAdy[i].apuntador.push_back(&listaAdy[j]);
            }
        }
    }

    // imprimimos la matriz de Adyacencias
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < n-1)
                cout << matrizAdy[i][j] << " ";
            else
                cout << matrizAdy[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // imprimimos la lista de Adyacencias
    for (int i = 0; i < listaAdy.size(); i++){
        cout << listaAdy[i].letra;
        if (!listaAdy[i].apuntador.empty()){
            for (int j = 0; j < listaAdy[i].apuntador.size(); j++){
                cout << " - " << listaAdy[i].apuntador[j]->letra;
            }
        }
        cout << endl;
    }
    cout << endl;

    // imprimimos el recorrido BFS
    BFS(listaAdy, 0);
    cout << endl;

    // imprimimos el recorrido DFS
    visitado = vector<bool>(matrizAdy.size(), false);
    DFS(matrizAdy, 0);
    cout << endl;

    return 0;
}