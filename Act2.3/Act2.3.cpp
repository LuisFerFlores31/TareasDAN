#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <map> // Incluimos la cabecera para usar std::map

using namespace std;

// Estructura para almacenar registros
struct Registro {
    string ip;
    int mes;
    int dia;
    string hora;
    string mensaje;
    Registro* next;
    Registro* prev;  
};

unsigned long long convertirIPANumero(const string& ip); // Convierte una dirección IP a número
Registro* particion(Registro* low, Registro* high); // Función para particionar en QuickSort
void quickSortRecursivo(Registro* low, Registro* high); // Función recursiva de QuickSort
void quickSort(Registro*& head, Registro*& tail); // QuickSort que maneja los punteros de cabeza y cola

// Mapa 
map<string, int> mesAMesNumero = {
    {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6},
    {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
};

// Convierte el mes en texto a número
int convertirMesAInt(const string& mes) {
    auto it = mesAMesNumero.find(mes);
    if (it != mesAMesNumero.end()) {
        return it->second; // Retorna el número del mes si se encuentra
    }
    return 0; // Retorna 0 si no coincide con ningún mes
}

// Convierte el número del mes a texto
string convertirIntAMes(int mes) {
    for (const auto& par : mesAMesNumero) {
        if (par.second == mes) {
            return par.first; // Retorna el mes en texto si se encuentra
        }
    }
    return ""; // Retorna cadena vacía si no es un mes válido
}

// Lee el archivo y llena la lista doblemente ligada
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

        // Crea un nuevo registro
        Registro* nuevo = new Registro{ip, convertirMesAInt(mesTexto), dia, hora, mensaje, nullptr, nullptr};

        if (!head) { // Si la lista está vacía
            head = tail = nuevo; // Inicializa cabeza y cola
        } else {
            tail->next = nuevo; // Añade nuevo al final
            nuevo->prev = tail; // Establece el puntero previo
            tail = nuevo; // Actualiza la cola
        }
    }
    archivo.close();
}

// Intercambia los datos de dos registros
void intercambiarDatos(Registro* a, Registro* b) {
    swap(a->ip, b->ip);
    swap(a->mes, b->mes);
    swap(a->dia, b->dia);
    swap(a->hora, b->hora);
    swap(a->mensaje, b->mensaje);
}

// Función de partición para QuickSort
Registro* particion(Registro* low, Registro* high) {
    unsigned long long pivot = convertirIPANumero(high->ip); // Establece el pivote
    Registro* i = low->prev; // Puntero para rastrear el lugar de intercambio

    // Recorre la lista y realiza el particionamiento
    for (Registro* j = low; j != high; j = j->next) {
        if (convertirIPANumero(j->ip) < pivot || (convertirIPANumero(j->ip) == pivot && (j->mes < high->mes || (j->mes == high->mes && j->dia < high->dia)))) {
            i = (i == nullptr) ? low : i->next; // Mueve el puntero
            intercambiarDatos(i, j); // Intercambia datos
        }
    }
    i = (i == nullptr) ? low : i->next; // Actualiza el puntero
    intercambiarDatos(i, high); // Intercambia con el pivote
    return i; // Devuelve el nuevo pivote
}

// Función recursiva de QuickSort
void quickSortRecursivo(Registro* low, Registro* high) {
    if (high != nullptr && low != high && low != high->next) {
        Registro* pivot = particion(low, high); // Obtiene el pivote
        quickSortRecursivo(low, pivot->prev); // Ordena la parte izquierda
        quickSortRecursivo(pivot->next, high); // Ordena la parte derecha
    }
}

// Función principal para realizar QuickSort
void quickSort(Registro*& head, Registro*& tail) {
    quickSortRecursivo(head, tail); // Llama a la función recursiva
}

// Guarda los registros en un archivo
void guardarEnArchivo(const string& nombreArchivo, Registro* head) {
    ofstream archivo(nombreArchivo); // Abre el archivo
    if (!archivo) {
        return; // Si no se puede abrir, termina la función
    }
    Registro* current = head; // Puntero para recorrer la lista
    while (current) {
        archivo << convertirIntAMes(current->mes) << " " << current->dia << " " << current->hora << " " << current->ip << current->mensaje << endl; // Escribe en el archivo
        current = current->next; // Avanza al siguiente registro
    }
    archivo.close(); // Cierra el archivo
}

// Convierte una dirección IP a un número entero
unsigned long long convertirIPANumero(const string& ip) {
    unsigned long long resultado = 0; // Resultado final
    int octetos[4]; // Arreglo para almacenar octetos
    sscanf(ip.c_str(), "%d.%d.%d.%d", &octetos[0], &octetos[1], &octetos[2], &octetos[3]); // Extrae octetos
    for (int i = 0; i < 4; ++i) { // Convierte cada octeto a número
        resultado = (resultado << 8) | (octetos[i] & 0xFF); // Desplazamiento a la izquierda
    }
    return resultado; // Devuelve el número resultante
}

// Busca registros dentro de un rango de direcciones IP
void buscarIPs(Registro* head) {
    string ipInicio, ipFin; // Variables para las IPs de inicio y fin
    cout << "";
    cin >> ipInicio; // Lee IP de inicio
    cout << "";
    cin >> ipFin; // Lee IP de fin

    // Convierte las IPs a números
    unsigned long long inicioNum = convertirIPANumero(ipInicio);
    unsigned long long finNum = convertirIPANumero(ipFin);

    Registro* registrosEncontradosHead = nullptr;
    Registro* registrosEncontradosTail = nullptr;

    while (head != nullptr) { // Recorre la lista de registros
        unsigned long long ipNum = convertirIPANumero(head->ip);
        if (ipNum >= inicioNum && ipNum <= finNum) { // Comprueba si está en el rango
            // Crea un nuevo registro para almacenar resultados
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

    // Imprime los registros encontrados
    if (registrosEncontradosHead != nullptr) {
        Registro* current = registrosEncontradosTail;
        cout << ipInicio << " a " << ipFin << endl;
        while (current != nullptr) {
            cout << convertirIntAMes(current->mes) << " " << current->dia << " " << current->hora << " " << current->ip << " " << current->mensaje << endl;
            current = current->prev;
        }
    } else {
        cout << " " << endl;
    }
}

// Libera la memoria de la lista
void liberarMemoria(Registro*& head) {
    while (head != nullptr) {
        Registro* temp = head;
        head = head->next;
        delete temp;
    }
}

    // Funci�n principal
    int main() {
        Registro* head = nullptr;
        Registro* tail = nullptr;

        // Lee los registros del archivo
        leerArchivo("bitacora.txt", head, tail);

        // Ordena los registros
        quickSort(head, tail);

        // Guarda los registros ordenados
        guardarEnArchivo("SortedData.txt", head);

        // Busca registros en el rango de IPs
        buscarIPs(head);

        // Libera la memoria
        liberarMemoria(head);

        return 0;
    }
    //omar