/*Act 2.1 - Implementación de un ADT de estructura de datos lineales
Luis Fernando Cruz Flores A01738347
Antonio Mendez Rodriguez A01738269
Luis Angel Zempoalteca Serrano A01738862

Fecha: 9 de Octubre*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
    int data;
    Node* next, *prev;
};

void push(struct Node** headRef, int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = key;
    node->prev = NULL;
    node->next = *headRef;
 
    // change `prev` of the existing head node to point to the new node
    if (*headRef != NULL) {
        (*headRef)->prev = node;
    }
 
    // update head pointer
    *headRef = node;
}

// Helper function to print nodes of a doubly linked list
void printDDL(struct Node* head)
{
    while (head != NULL)
    {
        printf("%d ⇔ ", head->data);
        head = head->next;
    }
 
    printf("NULL");
}

void split(struct Node* head, struct Node** a, struct Node** b)
{
    struct Node* slow = head;
    struct Node* fast = head->next;
 
    // advance `fast` by two nodes, and advance `slow` by a single node
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    *b = slow->next;
    slow->next = NULL;
}

// Recursive function to merge nodes of two sorted lists
// into a single sorted list
struct Node* merge(struct Node* a, struct Node* b)
{
    // base cases
    if (a == NULL) {
        return b;
    }
 
    if (b == NULL) {
        return a;
    }
 
    // pick either `a` or `b`, and recur
    if (a->data <= b->data)
    {
        a->next = merge(a->next, b);
        a->next->prev = a;
        a->prev = NULL;
        return a;
    }
    else {
        b->next = merge(a, b->next);
        b->next->prev = b;
        b->prev = NULL;
        return b;
    }
}

// Merge Sort
void mergesort(struct Node** head)
{
    // base case: 0 or 1 node
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
 
    // split head into `a` and `b` sublists
    struct Node* a = *head, *b = NULL;
    split(*head, &a, &b);
 
    // recursively sort the sublists
    mergesort(&a);
    mergesort(&b);
 
    // merge the two sorted lists
    *head = merge(a, b);
}



int main (){
    //open File 
    ifstream file("bitacora.txt");
    if (!file.is_open()) {
        cout << "El archivo no se pudo abrir" << endl;
        return 1;
    }



     // resultados en sorted.txt
    ofstream output("SortedData.txt");
    if (!output.is_open()) {
        cout << "No se pudo abrir el archivo de salida" << endl;
        return 1;
    }

    return 0;  
    
};