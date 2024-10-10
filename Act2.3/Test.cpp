#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Nodo {
    string fecha;
    string hora;
    string ip;
    string mensaje;
    Nodo* siguiente;
    Nodo* anterior;
};

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}

    void agregarNodo(string fecha, string hora, string ip, string mensaje) {
        Nodo* nuevo = new Nodo{fecha, hora, ip, mensaje, nullptr, nullptr};
        if (!cabeza) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
    }

    void bubbleSort() {
        if (!cabeza) return;
        bool swapped;
        Nodo* actual;
        Nodo* fin = nullptr;

        do {
            swapped = false;
            actual = cabeza;

            while (actual->siguiente != fin) {
                if (comparar(actual, actual->siguiente) > 0) {
                    intercambiar(actual, actual->siguiente);
                    swapped = true;
                }
                actual = actual->siguiente;
            }
            fin = actual;
        } while (swapped);
    }

    int comparar(Nodo* a, Nodo* b) {
        if (a->ip != b->ip) return a->ip > b->ip ? 1 : -1;
        if (a->fecha != b->fecha) return a->fecha > b->fecha ? 1 : -1;
        if (a->hora != b->hora) return a->hora > b->hora ? 1 : -1;
        return a->mensaje > b->mensaje ? 1 : -1;
    }

    void intercambiar(Nodo* a, Nodo* b) {
        swap(a->fecha, b->fecha);
        swap(a->hora, b->hora);
        swap(a->ip, b->ip);
        swap(a->mensaje, b->mensaje);
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        Nodo* actual = cabeza;
        while (actual) {
            archivo << actual->fecha << " " << actual->hora << " " << actual->ip << " " << actual->mensaje << endl;
            actual = actual->siguiente;
        }
        archivo.close();
    }

    void buscarPorIP(string ipInicio, string ipFin) {
        Nodo* actual = cola; // Empezamos desde el final para mostrar en orden descendente
        while (actual) {
            if (actual->ip >= ipInicio && actual->ip <= ipFin) {
                cout << actual->fecha << " " << actual->hora << " " << actual->ip << " " << actual->mensaje << endl;
            }
            actual = actual->anterior;
        }
    }

    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        string linea, fecha, hora, ip, mensaje;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            ss >> fecha >> hora >> ip;
            getline(ss, mensaje);
            agregarNodo(fecha, hora, ip, mensaje);
        }
        archivo.close();
    }
};
int main() {
    ListaDoble bitacora;

    // Cargar la bitácora desde el archivo
    string archivoEntrada;
    cout << " "; // El usuario ingresará el nombre del archivo aquí
    cin >> archivoEntrada;
    bitacora.cargarDesdeArchivo(archivoEntrada);

    // Ordenar los datos
    bitacora.bubbleSort();

    // Guardar el archivo ordenado
    bitacora.guardarEnArchivo("bitacora.txt");

    // Realizar búsqueda por rango de IPs
    string ipInicio, ipFin;
    cout << " "; // El usuario ingresará el IP de inicio aquí
    cin >> ipInicio;
    cout << " "; // El usuario ingresará el IP de fin aquí
    cin >> ipFin;

    bitacora.buscarPorIP(ipInicio, ipFin);

    return 0;
}