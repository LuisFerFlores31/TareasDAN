#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &arbol, int n, int i) {
    int largest = i;         // La raiz pues
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Si el hijo izquierdo es mayor que la raíz
    if (left < n && arbol[left] > arbol[largest])
        largest = left;

    // Si el hijo derecho es mayor que la raíz
    if (right < n && arbol[right] > arbol[largest])
        largest = right;

    // Si el más grande no es la raíz
    if (largest != i) {
        swap(arbol[i], arbol[largest]);
        heapify(arbol, n, largest);
    }
}

void pop(vector<int> &arbol) {
    if (arbol.size() == 0) {
        cout << "El árbol está vacío" << endl;
        return;
    }

    // Mover el último elemento a la raíz y eliminar el último elemento
    cout<<arbol[0]<<endl;
    arbol[0] = arbol.back();
    arbol.pop_back();

    // Restablecer el heap desde la raíz
    heapify(arbol, arbol.size(), 0);
}

void test(const vector<int> &arbol) {
    for (int i = 0; i < arbol.size(); i++) {
        cout << arbol[i] << " ";
    }
    cout << "Fin" << endl;
}

void isempty(const vector<int> &arbol) {
    if (arbol.size() == 0){
        cout<<"true"<<endl;
    }
    else{
        cout<<"flase"<<endl;
    }
}

int main(){
    int root, n , i, opc, val,count;
    vector<int> arbol;

    do {
        cin>>opc;
        switch (opc)
        {
        case 1: //push, mete un valor al arbol y lo ordena con heapify
            cin>>val;
            arbol.push_back(val);
            //Heapify 
            for (int i = arbol.size() / 2 - 1; i >= 0; i--) {
                heapify(arbol, arbol.size(), i);
            }
            break;
        case 2: //pop, quita el valor de la raiz y la re-ordena con heapify
            pop(arbol);
            //heapsoting(arbol, root, der,izq);
            break;
        case 3: //print, imprime los valores del arbol
            for (int i = 0; i< arbol.size(); i++){
                cout<<arbol[i]<<" ";
            }
            break;
        case 4: //top, da el valor de la raiz
            cout<<arbol[0]<<endl;
            break;
        case 5 :
            isempty(arbol);
            break;
        case 6: //Size, da el tamaño del arbol 
            cout<<arbol.size()<<endl;
            break;
        
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};