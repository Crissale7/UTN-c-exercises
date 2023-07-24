// Línea de cajas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Mov {
    int caja;
    char mov; // 'E' => Entra, 'S' => Sale
    int hora; // hhmm
};

int main() {
    vector<Mov> movimientos;

    ifstream archivo("MOVIMIENTOS.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo MOVIMIENTOS.dat" << endl;
        return 1;
    }

    Mov movimiento;
    while (archivo.read(reinterpret_cast<char*>(&movimiento), sizeof(Mov))) {
        movimientos.push_back(movimiento);
    }

    archivo.close();

    const int CANT_CAJAS = 10;
    float promedios[CANT_CAJAS] = { 0 };
    int cantCasos[CANT_CAJAS] = { 0 };
    int tiempoOcioso[CANT_CAJAS] = { 0 };
    int longitudMaxima[CANT_CAJAS] = { 0 };
    vector<int> cola[CANT_CAJAS];

    for (int i = 0; i < movimientos.size(); i++) {
        Mov movimiento = movimientos[i];

        if (movimiento.mov == 'E') {
            cola[movimiento.caja].push_back(movimiento.hora);
        }
        else if (movimiento.mov == 'S') {
            int tiempoEspera = movimiento.hora - cola[movimiento.caja].front();
            promedios[movimiento.caja] += tiempoEspera;
            cantCasos[movimiento.caja]++;
            cola[movimiento.caja].erase(cola[movimiento.caja].begin());

            if (cola[movimiento.caja].empty()) {
                tiempoOcioso[movimiento.caja]++;
            }
        }

        longitudMaxima[movimiento.caja] = max(longitudMaxima[movimiento.caja], static_cast<int>(cola[movimiento.caja].size()));
    }

    for (int i = 0; i < CANT_CAJAS; i++) {
        if (cantCasos[i] > 0) {
            promedios[i] /= cantCasos[i];
        }

        cout << "Caja " << i << ":" << endl;
        cout << "Tiempo promedio de espera: " << promedios[i] << endl;
        cout << "Tiempo ocioso: " << tiempoOcioso[i] << endl;
        cout << "Longitud máxima de la cola: " << longitudMaxima[i] << endl;
        cout << endl;
    }

    return 0;
}
