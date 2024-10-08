#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map> //para hacer mapeos

using namespace std;

// Mapeo de meses
map<string, int> mesAMesNumero = {
    {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6},
    {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
};

// Estructura para almacenar los registros
struct Registro {
    int mes;
    int dia;
    string contenido;
    string fecha; 
};

// Función para convertir fecha numérica (mes/día) a formato de Registro
string fechaNumericaARegistro(int mes, int dia) {
    for (const auto& par : mesAMesNumero) {
        if (par.second == mes) {
            return par.first + " " + to_string(dia);
        }
    }
    return ""; // Fecha no válida
}

// Función para convertir fecha en formato de cadena a formato numérico
bool registroANumeros(const string& fecha, int& mes, int& dia) {
    istringstream stream(fecha);
    string mesStr;
    if (stream >> mesStr >> dia) {
        auto it = mesAMesNumero.find(mesStr);
        if (it != mesAMesNumero.end()) {
            mes = it->second;
            return true;
        }
    }
    return false;
}

// Función para particionar el vector para QuickSort
int particion(vector<Registro>& registros, int inicio, int fin) {
    Registro pivote = registros[fin];
    int i = inicio - 1;
    for (int j = inicio; j < fin; ++j) {
        if (registros[j].mes < pivote.mes || 
            (registros[j].mes == pivote.mes && registros[j].dia < pivote.dia)) {
            ++i;
            swap(registros[i], registros[j]);
        }
    }
    swap(registros[i + 1], registros[fin]);
    return i + 1;
}

// Función de QuickSort de complejidad O(n log n)
void quickSort(vector<Registro>& registros, int inicio, int fin) {
    if (inicio < fin) {
        int pivote = particion(registros, inicio, fin);
        quickSort(registros, inicio, pivote - 1);
        quickSort(registros, pivote + 1, fin);
    }
}

int main() {

    // Lee el archivo bitacora.txt
    ifstream file("bitacora.txt");
    if (!file.is_open()) {
        cout << "El archivo no se pudo abrir" << endl;
        return 1;
    }

    vector<Registro> registros;
    string linea;
    while (getline(file, linea)) {
        istringstream stream(linea);
        Registro registro;
        getline(stream, registro.fecha, ',');
        getline(stream, registro.contenido);
        int mes, dia;
        if (registroANumeros(registro.fecha, mes, dia)) {
            registro.mes = mes;
            registro.dia = dia;
            registros.push_back(registro);
        }
    }
    file.close();

    cout << "Ingrese una fecha de inicio (mes día): ";
    int mesInicio, diaInicio;
    cin >> mesInicio >> diaInicio;
    cout << "Ingrese una fecha límite (mes día): ";
    int mesLimite, diaLimite;
    cin >> mesLimite >> diaLimite;

    string fechaInicioRegistro = fechaNumericaARegistro(mesInicio, diaInicio);
    string fechaLimiteRegistro = fechaNumericaARegistro(mesLimite, diaLimite);

    quickSort(registros, 0, registros.size() - 1);

    vector<Registro> resultados;
    for (const auto& registro : registros) {
        if ((registro.mes > mesInicio || (registro.mes == mesInicio && registro.dia >= diaInicio)) &&
            (registro.mes < mesLimite || (registro.mes == mesLimite && registro.dia <= diaLimite))) {
            resultados.push_back(registro);
        }
    }

    // resultados en sorted.txt
    ofstream output("sorted.txt");
    if (!output.is_open()) {
        cout << "No se pudo abrir el archivo de salida" << endl;
        return 1;
    }

    for (const auto& registro : resultados) {
        output << registro.fecha << ", " << registro.contenido << endl;
    }
    output.close();

    cout << "Ver sorted.txt" << endl;
    return 0;
}
