/*
Actividad 5.1
Equipo:
Antonio Mendez Rodriguez A01738269
Luis Fernando Flores Cruz A017388347
Luis Angel Zempoalteca Serrano A01738862
Fecha: 17/11/2024
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Car {
    string placa;  // Llave
    string marca;
    string modelo;
    int anio;

    Car() : placa(""), marca(""), modelo(""), anio(0) {}
};
class HashTable {
private:
    vector<Car> table; 
    vector<bool> occupied; 
    static const int SIZE = 97; 

    int hashFunction(const string &placa) {
        int sum = 0;
        for (char c : placa) {
            sum += c;
        }
        return sum % SIZE;
    }

public:
    HashTable() : table(SIZE), occupied(SIZE, false) {}

    void insert(const Car &car) { //O(n)
        int index = hashFunction(car.placa);
        int originalIndex = index;
        do {
            if (!occupied[index]) { 
                table[index] = car;
                occupied[index] = true;
                cout << endl;
                return;
            }
            if (table[index].placa == car.placa) { 
                cout << "imposible insertar, placa duplicada" << endl << endl;
                return;
            }
            index = (index + 1) % SIZE; 
        } while (index != originalIndex);

        cout << "tabla llena, imposible insertar" << endl << endl;
    }

    void remove(const string &placa) { //O(n)
        int index = hashFunction(placa);
        int originalIndex = index;
        do {
            if (occupied[index] && table[index].placa == placa) {
                occupied[index] = false; 
                cout << endl;
                return;
            }
            index = (index + 1) % SIZE;
        } while (index != originalIndex);

        cout << "dato no encontrado" << endl << endl;
    }

    void search(const string &placa) { //O(n)
        int index = hashFunction(placa);
        int originalIndex = index;
        do {
            if (occupied[index] && table[index].placa == placa) {
                cout << table[index].placa << " " << table[index].marca << " " 
                     << table[index].modelo << " " << table[index].anio << endl << endl;
                return;
            }
            index = (index + 1) % SIZE;
        } while (index != originalIndex);

        cout << "dato no encontrado" << endl << endl;
    }

    void print() {
        for (int i = 0; i < SIZE; ++i) {
            cout << i;
            if (occupied[i]) {
                cout << " " << table[i].placa << " " << table[i].marca << " " 
                     << table[i].modelo << " " << table[i].anio;
            }
            cout << endl;
        }
        cout << endl;
    }
};
int main() {
    HashTable hashTable;
    int option;
    do {
        cout << "1. Insertar\n2. Eliminar\n3. Imprime la tabla\n4. Buscar un dato\n0. Salir\n";
        cin >> option;
        if (option == 1) {
            Car car;
            cin >> car.placa >> car.marca >> car.modelo >> car.anio;
            hashTable.insert(car);
        } else if (option == 2) {
            string placa;
            cin >> placa;
            hashTable.remove(placa);
        } else if (option == 3) {
            hashTable.print();
        } else if (option == 4) {
            string placa;
            cin >> placa;
            hashTable.search(placa);
        }
    } while (option != 0);
    return 0;
}
