#include <iostream>
#include <vector>
using namespace std;

void heapsoting(vector<int>arbol,int root,int der, int izq){
    cout<<"algorithmo de ordenamiento"<<endl;
    
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
            cout<<"push"<<endl;
            cin>>val;
            //meter valor al arbol
            heapsoting(arbol, root, der,izq);
            break;
        case 2:
            cout<<"pop"<<endl;
            //remover valor del arbol
            heapsoting(arbol, root, der,izq);
            break;
        case 3:
            cout<<"print"<<endl;
            for (int i; i< arbol.size(); i++){
                cout<<arbol[i];
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
            break;
        
        default:
            break;
        }
    } while (opc != 0);
    return 0;
};