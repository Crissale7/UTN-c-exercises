// Medición de audiencia.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Muestra {
    int idMonitor;
    int hora;
    int min;
    char accion;
    int canal;
};

struct MinAMin {
    int canal;
    int min;
    int cant;
};

int main() {
    map<int, map<int, int>> muestras;

    ifstream archivoMuestras("MUESTRAS.dat", ios::binary);
    if (!archivoMuestras) {
        cerr << "Error al abrir el archivo MUESTRAS.dat" << endl;
        return 1;
    }

    Muestra muestra;
    while (archivoMuestras.read(reinterpret_cast<char*>(&muestra), sizeof(Muestra))) {
        if (muestra.accion == 'E') {
            muestras[muestra.canal][muestra.hora * 60 + muestra.min]++;
        }
        else if (muestra.accion == 'C') {
            muestras[muestra.canal][muestra.hora * 60 + muestra.min]--;
        }
    }

    archivoMuestras.close();

    ofstream archivoMinAMin("MINAMIN.dat", ios::binary);
    if (!archivoMinAMin) {
        cerr << "Error al abrir el archivo MINAMIN.dat" << endl;
        return 1;
    }

    for (auto itCanal = muestras.begin(); itCanal != muestras.end(); itCanal++) {
        int canal = itCanal->first;

        for (auto itMin = itCanal->second.begin(); itMin != itCanal->second.end(); itMin++) {
            int minuto = itMin->first;

            int cantidad = itMin->second;

            MinAMin minAMin;

            minAMin.canal = canal;

            minAMin.min = minuto;

            minAMin.cant = cantidad;

            archivoMinAMin.write(reinterpret_cast<char*>(&minAMin), sizeof(MinAMin));
        }
    }

    archivoMinAMin.close();

    return 0;
}
