#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Registro {
    string mensaje;
};

struct Host {
    string ipCompleta;
    vector<Registro> registros;
};

struct Red {
    string idRed; // Ejemplo: "123.45"
    unordered_map<string, Host> hosts;
};

unordered_map<string, Red> redes;

void agregarRegistro(const string& ip, const string& mensaje) {
    stringstream ss(ip);
    string octeto1, octeto2;
    getline(ss, octeto1, '.'); // primer octeto
    getline(ss, octeto2, '.'); // segundo octeto

    string idRed = octeto1 + "." + octeto2; // "123.45" como ejemplo de ID de red
    string ipCompleta = ip; // IP completa

    Registro registro = {mensaje};
    redes[idRed].idRed = idRed; // Añadir red si no existe
    redes[idRed].hosts[ipCompleta].ipCompleta = ipCompleta;
    redes[idRed].hosts[ipCompleta].registros.push_back(registro);
}

void encontrarRedConMasGradoSalida() {
    int maxGradoSalida = 0;
    vector<string> redesMaxGradoSalida;

    for (const auto& red : redes) {
        int gradoSalida = red.second.hosts.size();
        if (gradoSalida > maxGradoSalida) {
            maxGradoSalida = gradoSalida;
            redesMaxGradoSalida = {red.first};
        } else if (gradoSalida == maxGradoSalida) {
            redesMaxGradoSalida.push_back(red.first);
        }
    }

    for (const auto& red : redesMaxGradoSalida) {
        cout << red << endl;
    }
}

void encontrarHostConMasIncidencia() {
    int maxIncidencias = 0;
    vector<string> hostsMaxIncidencias;

    for (const auto& red : redes) {
        for (const auto& host : red.second.hosts) {
            int numIncidencias = host.second.registros.size();
            if (numIncidencias > maxIncidencias) {
                maxIncidencias = numIncidencias;
                hostsMaxIncidencias = {host.first};
            } else if (numIncidencias == maxIncidencias) {
                hostsMaxIncidencias.push_back(host.first);
            }
        }
    }

    for (const auto& host : hostsMaxIncidencias) {
        cout << host << endl;
    }
}

void imprimirResultados() {
    encontrarRedConMasGradoSalida();
    cout << endl;
    encontrarHostConMasIncidencia();
}

int main() {
    ifstream archivo("bitacora.txt");
    string linea, ip, mensaje;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            // Encontramos la posición del tercer espacio
            size_t posPrimerEspacio = linea.find(' ');
            size_t posSegundoEspacio = linea.find(' ', posPrimerEspacio + 1);
            size_t posTercerEspacio = linea.find(' ', posSegundoEspacio + 1);
            if (posTercerEspacio == string::npos) continue; // Verificar si hay al menos tres espacios

            // Extraemos el resto de la línea después del tercer espacio
            string resto = linea.substr(posTercerEspacio + 1);

            // Procesamos el resto para obtener la IP y el mensaje
            istringstream iss(resto);
            iss >> ip; // Extraemos la IP (con puerto)
            size_t pos = ip.find(':');
            ip = ip.substr(0, pos); // Eliminamos el puerto de la IP
            getline(iss, mensaje); // Leemos el mensaje completo

            agregarRegistro(ip, mensaje);
        }
        archivo.close();
    }

    imprimirResultados();

    return 0;
}
