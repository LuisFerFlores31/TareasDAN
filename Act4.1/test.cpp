#include <iostream>
#include <vector>
using namespace std;

int main(){
     int MAT[7][7], n, nodo1, nodo2;

    cin>>n;

    while(n--){
        cin >> nodo1 >> nodo2;
        MAT[nodo1][nodo2] = 1;
        MAT[nodo2][nodo1] = 1;

        cout<<nodo1<<","<<nodo2<< " Valor "<< MAT [nodo1][nodo2]<<endl;
    }
//no jala
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << MAT[i][j] << " ";
        }
        cout << endl;
    }
}