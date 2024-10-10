/*Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
Luis Fernando Cruz Flores A01738347
Antonio Mendez Rodriguez A01738269
Luis Angel Zempoalteca Serrano A01738862

Fecha: 10 de Octubre*/
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <map> 
using namespace std;

struct Registro {
    string ip;
    int mes;
    int dia;
    string hora;
    string mensaje;
    Registro* next;
    Registro* prev; 
};

unsigned long long IPANumero(const string& ip); 
Registro* particion(Registro* low, Registro* high); 
void quickSortRecursivo(Registro* low, Registro* high); 
void quickSort(Registro*& head, Registro*& tail); 

// Mapa 
map<string, int> mesAMesNumero = {
    {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6},
    {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
};

int convertirMesAInt(const string& mes) {
    auto it = mesAMesNumero.find(mes);
    if (it != mesAMesNumero.end()) {
        return it->second; 
    }
    return 0; // por si no coincide con ningún mes
}

string convertirIntAMes(int mes) {
    for (const auto& par : mesAMesNumero) {
        if (par.second == mes) {
            return par.first; 
        }
    }
    return ""; // Rpor si no es un mes válido
}

void leerArchivo(const string& nombreArchivo, Registro*& head, Registro*& tail) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string mesTexto, hora, ip, mensaje;
        int dia;
        ss >> mesTexto >> dia >> hora >> ip; // Extrae datos de la línea
        getline(ss, mensaje); // Obtiene el resto de la línea como mensaje

        Registro* nuevo = new Registro{ip, convertirMesAInt(mesTexto), dia, hora, mensaje, nullptr, nullptr};
        //los nodosfeos
        if (!head) { 
            head = tail = nuevo; 
        } else {
            tail->next = nuevo; 
            nuevo->prev = tail; 
            tail = nuevo; 
        }
    }
    archivo.close();
}

// Intercambia datos
void intercambiarDatos(Registro* a, Registro* b) {
    swap(a->ip, b->ip);
    swap(a->mes, b->mes);
    swap(a->dia, b->dia);
    swap(a->hora, b->hora);
    swap(a->mensaje, b->mensaje);
}

// Función de partición para QuickSort
Registro* particion(Registro* low, Registro* high) {
    unsigned long long pivot = IPANumero(high->ip); // Establece el pivote
    Registro* i = low->prev; // Puntero para rastrear el lugar de intercambio

    // Recorre la lista y realiza el particionamiento
    for (Registro* j = low; j != high; j = j->next) {
        if (IPANumero(j->ip) < pivot || (IPANumero(j->ip) == pivot && (j->mes < high->mes || (j->mes == high->mes && j->dia < high->dia)))) {
            i = (i == nullptr) ? low : i->next; // Mueve el puntero
            intercambiarDatos(i, j); // Intercambia datos
        }
    }
    i = (i == nullptr) ? low : i->next;
    intercambiarDatos(i, high); 
    return i; 
}
// sort recursivo
void quickSortRecursivo(Registro* low, Registro* high) {
    if (high != nullptr && low != high && low != high->next) {
        Registro* pivot = particion(low, high); // Obtiene el pivote
        quickSortRecursivo(low, pivot->prev); // Ordena la parte izquierda
        quickSortRecursivo(pivot->next, high); // Ordena la parte derecha
    }
}

//sort normal
void quickSort(Registro*& head, Registro*& tail) {
    quickSortRecursivo(head, tail); // Llama a la función recursiva
}

void guardarEnArchivo(const string& nombreArchivo, Registro* head) {
    ofstream archivo(nombreArchivo); 
    if (!archivo) {
        return; 
    }
    Registro* current = head; // Puntero para recorrer la lista
    while (current) {
        archivo << convertirIntAMes(current->mes) << " " << current->dia << " " << current->hora << " " << current->ip << current->mensaje << endl; // Escribe en el archivo
        current = current->next; 
    }
    archivo.close(); 
}

//IP a  número entero
unsigned long long IPANumero(const string& ip) {
    unsigned long long resultado = 0; 
    int octetos[4]; // Arreglo para almacenar octetos
    sscanf(ip.c_str(), "%d.%d.%d.%d", &octetos[0], &octetos[1], &octetos[2], &octetos[3]); // Extrae octetos
    for (int i = 0; i < 4; ++i) { // Convierte cada octeto a número
        resultado = (resultado << 8) | (octetos[i] & 0xFF); // Desplazamiento a la izquierda
    }
    return resultado; // Devuelve el número resultante
}

// Busca IP dentro del rango
void buscarIPs(Registro* head) {
    string ipInicio, ipFin;
    cout << "";
    cin >> ipInicio; 
    cout << "";
    cin >> ipFin; 

    //IPs a números
    unsigned long long inicioNum = IPANumero(ipInicio);
    unsigned long long finNum = IPANumero(ipFin);
    Registro* registrosEncontradosHead = nullptr;
    Registro* registrosEncontradosTail = nullptr;

    while (head != nullptr) { 
        unsigned long long ipNum = IPANumero(head->ip);
        if (ipNum >= inicioNum && ipNum <= finNum) { // Comprueba  el rango
            // almacena resultados
            Registro* nuevoRegistro = new Registro{
                head->ip,
                head->mes,
                head->dia,
                head->hora,
                head->mensaje,
                nullptr,
                nullptr
            };

            if (!registrosEncontradosHead) {
                registrosEncontradosHead = registrosEncontradosTail = nuevoRegistro;
            } else {
                nuevoRegistro->prev = registrosEncontradosTail;
                registrosEncontradosTail->next = nuevoRegistro;
                registrosEncontradosTail = nuevoRegistro;
            }
        }
        head = head->next;
    }

    // Imprime los registros 
    if (registrosEncontradosHead != nullptr) {
        Registro* current = registrosEncontradosTail;
        while (current != nullptr) {
            cout << convertirIntAMes(current->mes) << " " << current->dia << " " << current->hora << " " << current->ip << " " << current->mensaje << endl;
            current = current->prev;
        }
    } else {
        cout << " " << endl;
    }
}

void liberarMemoria(Registro*& head) {
    while (head != nullptr) {
        Registro* temp = head;
        head = head->next;
        delete temp;
    }
}

 int main() {
        Registro* head = nullptr;
        Registro* tail = nullptr;

        leerArchivo("bitacora.txt", head, tail);
        quickSort(head, tail);
        guardarEnArchivo("SortedData.txt", head);
        buscarIPs(head);
        liberarMemoria(head);

        return 0;
    }