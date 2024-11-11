#include <iostream>
#include <vector>
using namespace std;

//imprimir la matriz
void printMat(const vector<vector<int>>&matriz){
    for(const auto& fila : matriz){
        for (int valor : fila){
            cout <<valor<< " ";
        } 
        cout<<endl;
    }
}

// Convierte el índice de un nodo a su etiqueta en el formato A, B, ..., Z, AA, AB, etc.
string nodoEtiqueta(int index) {
    string etiqueta;
    while (index >= 0) {
        etiqueta = char('A' + (index % 26)) + etiqueta;
        index = index / 26 - 1;
    }
    return etiqueta;
}

// Imprime la lista de adyacencias
void printlist(const vector<vector<int>>& lista) {
    for (int i = 0; i < lista.size(); ++i) {
        cout << nodoEtiqueta(i) << " - ";
        for (int j = 0; j < lista[i].size(); ++j) {
            cout << nodoEtiqueta(lista[i][j]);
            if (j < lista[i].size() - 1) cout << " - ";
        }
        cout << endl;
    }
}

int main(){
    int n = 0;
    cin>>n;
    //vector
    vector<vector<int>> matriz(n,vector<int>(n));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >>matriz[i][j];
        }
    }

    //lista de adyacencia
    vector<vector<int>> listaAdyacencia(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (matriz [i][j] == 1){
                listaAdyacencia[i].push_back(j);
            }
        }
    }
    cout<<endl;
    printMat(matriz);
    cout<<endl;
    printlist(listaAdyacencia);

    return 0;
}