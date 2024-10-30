#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void heapify(int n, int i) {
        int largest = i;         
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] > heap[largest])
            largest = left;

        if (right < n && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(n, largest);
        }
    }

public:
    void push(int val) {
        heap.push_back(val);
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapify(heap.size(), i);
        }
    }

    void pop() {
        if (!heap.empty()) {
            cout << heap[0] << endl;
            heap[0] = heap.back();
            heap.pop_back();
            heapify(heap.size(), 0);
        } else {
            cout << "Heap is empty!" << endl;
        }
    }

    void print() const {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }

    int top() const {
        if (!heap.empty()) {
            return heap[0];
        } else {
            cout << "Heap is empty!" << endl;
            return -1; // valor de error si el heap está vacío
        }
    }

    void isempty() {
        if (heap.size() == 0){
            cout<<"true"<<endl;
        }
        else{
            cout<<"flase"<<endl;
        }
}

    //bool isempty() const {
    //    return heap.empty();
    //}

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
            maxHeap.isempty();
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
