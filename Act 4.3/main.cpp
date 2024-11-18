/*Act 4.3 - Actividad Integral de Grafos (Evidencia Competencia)
Luis Fernando Cruz Flores A01738347
Antonio Mendez Rodriguez A01738269
Luis Angel Zempoalteca Serrano A01738862

Fecha: 15 de Novembre*/
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
    string idRed;
    unordered_map<string, Host> hosts;
};

unordered_map<string, Red> redes;

// Complejidad: O(n) 
void agregarRegistro(const string& ip, const string& mensaje) {
    stringstream ss(ip);
    string octeto1, octeto2;
    getline(ss, octeto1, '.'); 
    getline(ss, octeto2, '.'); 

    string idRed = octeto1 + "." + octeto2;
    string ipCompleta = ip;

    Registro registro = {mensaje};
    redes[idRed].idRed = idRed; 
    redes[idRed].hosts[ipCompleta].ipCompleta = ipCompleta;
    redes[idRed].hosts[ipCompleta].registros.push_back(registro); 
}

// Complejidad: O(n)
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

    for (const auto& red : redesMaxGradoSalida) { // O(n)
        cout << red << endl;
    }
}

// Complejidad: O(n * h), donde n es el número de redes y h es el número promedio de hosts por red
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

// Complejidad: O(n * h) debido a las funciones llamadas
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
            size_t posPrimerEspacio = linea.find(' ');
            size_t posSegundoEspacio = linea.find(' ', posPrimerEspacio + 1);
            size_t posTercerEspacio = linea.find(' ', posSegundoEspacio + 1);
            if (posTercerEspacio == string::npos) continue;

            string resto = linea.substr(posTercerEspacio + 1);

            istringstream iss(resto); 
            iss >> ip; 
            size_t pos = ip.find(':'); 
            ip = ip.substr(0, pos); 
            getline(iss, mensaje); 

            agregarRegistro(ip, mensaje);
        }
        archivo.close();
    }

    imprimirResultados();

    return 0;
}
