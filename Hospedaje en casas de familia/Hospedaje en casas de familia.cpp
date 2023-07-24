// Hospedaje en casas de familia.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Caract {
    int idCaract;
    char descr[100];
};

struct Casa {
    int idCasa;
    char direcc[50];
    int idDueno;
    int caractMask;
    int idUsr;
};

struct Busqueda {
    int idUsr;
    int caractMask;
    int dias;
    double tolerancia;
};

double concordancia(int idCasa, int mask);

Busqueda leerBusqueda();

bool continuarOperando();

void mostrarCasa(int idCasa);

int main() {
    vector<Casa> casasDisponibles;

    ifstream archivoCasas("CASAS.dat", ios::binary);
    if (!archivoCasas) {
        cerr << "Error al abrir el archivo CASAS.dat" << endl;
        return 1;
    }

    Casa casa;
    while (archivoCasas.read(reinterpret_cast<char*>(&casa), sizeof(Casa))) {
        if (casa.idUsr == 0) {
            casasDisponibles.push_back(casa);
        }
    }

    archivoCasas.close();

    map<int, int> caractPorCasa;

    ifstream archivoCaracteristicas("CARACTERISTICAS.dat", ios::binary);
    if (!archivoCaracteristicas) {
        cerr << "Error al abrir el archivo CARACTERISTICAS.dat" << endl;
        return 1;
    }

    Caract caract;
    while (archivoCaracteristicas.read(reinterpret_cast<char*>(&caract), sizeof(Caract))) {
        caractPorCasa[caract.idCaract] = caract.caractMask;
    }

    archivoCaracteristicas.close();

    while (continuarOperando()) {
        Busqueda busqueda = leerBusqueda();

        vector<pair<double, int>> concordanciasPorCasa;

        for (int i = 0; i < casasDisponibles.size(); i++) {
            Casa casa = casasDisponibles[i];

            double concordanciaActual = concordancia(casa.idCasa, busqueda.caractMask);

            if (concordanciaActual >= busqueda.tolerancia) {
                concordanciasPorCasa.push_back(make_pair(concordanciaActual, casa.idCasa));
            }
        }

        sort(concordanciasPorCasa.rbegin(), concordanciasPorCasa.rend());

        for (int i = 0; i < concordanciasPorCasa.size(); i++) {
            pair<double, int> concordanciaYCasa = concordanciasPorCasa[i];

            cout << "Concordancia: " << concordanciaYCasa.first * 100 << "%" << endl;

            mostrarCasa(concordanciaYCasa.second);
        }
    }

    return 0;
}
