/*Act 2.2 - Verificación de las funcionalidades de una estructura de datos lineal
Luis Fernando Cruz Flores A01738347
Antonio Mendez Rodriguez A01738269
Luis Angel Zempoalteca Serrano A01738862

Fecha: 10 de Octubre*/

#include <iostream>
using namespace std;

// Definición de una estructura para los nodos de lista ligada
struct Node {
    int data;
    Node* next;
};

// Función para agregar un nuevo nodo al final de la lista
void append(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = nullptr;

    if (*head_ref == nullptr) {
        *head_ref = new_node;
        return;
    }

    Node* temp = *head_ref;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Función para imprimir los elementos de la lista
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data <<"\n";
        head = head->next;
    }
}
//Complejidad temporal: O(n)
// Función para invertir una lista ligada
Node* reverse(Node** head) {
    Node* prev = nullptr;
    Node* current = *head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    return *head;
}

//Complejidad temporal: O(n)
// Función para verificar si dos listas ligadas son iguales
bool equals(Node* head1, Node* head2) {
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data != head2->data) {
            return false;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    // Si ambas listas han llegado al final, son iguales.
    return (head1 == nullptr && head2 == nullptr);
}

//Complejidad temporal: O(n)
// Función para concatenar dos listas ligadas.
void concat(Node** head1, Node** head2) {
    if (*head1 == nullptr) {
        *head1 = *head2;
        return;
    }

    Node* temp = *head1;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = *head2;
}
//Complejidad temporal: O(n)
// Función para clonar una lista ligada
Node* cloneList(Node* head) {
    if (head == nullptr) return nullptr;

    Node* new_head = new Node();
    new_head->data = head->data;
    new_head->next = nullptr;

    Node* temp = new_head;
    Node* original = head->next;

    while (original != nullptr) {
        Node* new_node = new Node();
        new_node->data = original->data;
        new_node->next = nullptr;
        temp->next = new_node;
        temp = new_node;
        original = original->next;
    }

    return new_head;
}
//Complejidad temporal: O(n)
// Función para liberar la memoria de una lista ligada
void freeList(Node* head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int m, n, value;

    cin >> m;
    Node* list1 = nullptr;
    for (int i = 0; i < m; i++) {
        cin >> value;
        append(&list1, value);
    }

    cin >> n;
    Node* list2 = nullptr;
    for (int i = 0; i < n; i++) {
        cin >> value;
        append(&list2, value);
    }

    // Clonar las listas originales antes de modificarlas
    Node* originalList1 = cloneList(list1);
    Node* originalList2 = cloneList(list2);

    // Invertir ambas listas
    reverse(&list1);
    reverse(&list2);
    printList(list1);
    printList(list2);

    concat(&list2, &list1);
    printList(list2);  // Reversed list 2 + Reversed list 1

    if (equals(originalList1, originalList2)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    freeList(originalList1);  // Liberamos las listas 
    freeList(originalList2);
    freeList(list2);  // list2 ya incluye list1

    return 0;
}
