/*
Equipo:
Antonio Méndez Rodríguez A01738269
Luis Fernando Flores Cruz A017388347
Luis Angel Zempoalteca Serrano A01738862
*/

#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;
    //Complejidad O(log n)
    void heapify(int n, int i) {
        int largest = i;         
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Si el hijo izquierdo es mayor que la raíz
        if (left < n && heap[left] > heap[largest])
            largest = left;

         // Si el hijo derecho es mayor que la raíz
        if (right < n && heap[right] > heap[largest])
            largest = right;

         // Si el más grande no es la raíz
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(n, largest);
        }
    }

public:
    //Complejidad O(log n)
    void push(int val) {
        heap.push_back(val);
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapify(heap.size(), i);
        }
    }
    //Complejidad O(log n)
    void pop(){
        cout << heap[0] << endl;
        heap[0] = heap.back();
        heap.pop_back();
        heapify(heap.size(), 0);
    } 
    //Complejidad O(n)
    void print() const {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
    //Complejidad O(1)
    int top() const {
        if (!heap.empty()) {
            return heap[0];
        } else {
            cout << "Heap is empty!" << endl;
            return -1; // valor de error si el heap está vacío
        }
    }
    //Complejidad O(1)
    void empty() {
        if (heap.size() == 0){
            cout<<"true"<<endl;
        }
        else{
            cout<<"flase"<<endl;
        }
}
    //Complejidad O(1)
    int size() const {
        return heap.size();
    }
};

int main() {
    MaxHeap maxHeap;
    int opc, val;

    do {
        cin >> opc;
        switch (opc) {
        case 1: // Push
            cin >> val;
            maxHeap.push(val);
            break;
        case 2: // Pop
            maxHeap.pop();
            break;
        case 3: // Print
            maxHeap.print();
            break;
        case 4: // Top
            cout << maxHeap.top() << endl;
            break;
        case 5: // Is Empty
            maxHeap.empty();
            break;
        case 6: // Size
            cout << maxHeap.size() << endl;
            break;
        default:
            break;
        }
    } while (opc != 0);

    return 0;
}
