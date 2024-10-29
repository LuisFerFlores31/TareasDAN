#include <iostream>
#include <vector>
using namespace std;

void heapsoting(vector<int>arbol,int root,int der, int izq){
    cout<<"algorithmo de ordenamiento"<<endl;
    
}

void pop(vector<int> arbol){
    if (arbol.size() == 0){
        cout<<"El arbol esta vacio";
    }
    arbol[0] = arbol.back();
    arbol.pop_back(); //No se si se pueda usar esta funcion alch
}

bool isempty(vector<int>arbol){
    if (arbol.size() == 0){
                return true;
            }
            return false;
}

int main(){
    int root, der, izq, opc, val;
    vector<int> arbol;

    do {
        cin>>opc;
        switch (opc)
        {
        case 1:
            cin>>val;
            arbol.push_back(val);
            heapsoting(arbol, root, der,izq);
            break;
        case 2:
            cout<<"pop"<<endl;
            pop(arbol);
            heapsoting(arbol, root, der,izq);
            break;
        case 3:
            cout<<"print"<<endl;
            for (int i; i< arbol.size(); i++){
                cout<<arbol[i]<<" ";
            }
            break;
        case 4:
            cout<<"top"<<endl;
            cout<<arbol[0];
            break;
        case 5 :
            cout<<"is empty"<<endl;
            isempty(arbol);
            break;
        case 6:
            cout<<"size"<<endl;
            cout<<arbol.size();
            break;
        
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};