// Optimización de colas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Mov {
    int idCli;
    char mov;
    int hora;
};

int main() {
    vector<int> cantCajas = { 3, 4, 7, 8, 10 };

    for (int i = 0; i < cantCajas.size(); i++) {
        int cantCajasAbiertas = cantCajas[i];

        ifstream archivoMovimientos("MOVIMIENTOS.dat", ios::binary);
        if (!archivoMovimientos) {
            cerr << "Error al abrir el archivo MOVIMIENTOS.dat" << endl;
            return 1;
        }

        Mov mov;
        vector<queue<int>> colas(cantCajasAbiertas);
        int tiempoOcioso = 0;
        int tiempoEspera = 0;

        while (archivoMovimientos.read(reinterpret_cast<char*>(&mov), sizeof(Mov))) {
            int cajaConMenorCola = 0;

            for (int j = 1; j < cantCajasAbiertas; j++) {
                if (colas[j].size() < colas[cajaConMenorCola].size()) {
                    cajaConMenorCola = j;
                }
            }

            if (mov.mov == 'E') {
                colas[cajaConMenorCola].push(mov.idCli);
            }
            else if (mov.mov == 'S') {
                int idCli = mov.idCli;

                for (int j = 0; j < cantCajasAbiertas; j++) {
                    if (!colas[j].empty() && colas[j].front() == idCli) {
                        colas[j].pop();

                        break;
                    }
                }
            }

            bool hayCajaSinCola = false;

            for (int j = 0; j < cantCajasAbiertas; j++) {
                if (colas[j].empty()) {
                    hayCajaSinCola = true;

                    break;
                }
            }

            if (!hayCajaSinCola) {
                tiempoOcioso += cantCajasAbiertas - colas[cajaConMenorCola].size();
            }
        }

        archivoMovimientos.close();

        double tiempoEsperaPromedio = 0;

        for (int j = 0; j < cantCajasAbiertas; j++) {
            queue<int> cola = colas[j];
            vector<int> tiemposEspera;

            while (!cola.empty()) {
                int idCli = cola.front();
                cola.pop();

                ifstream archivoMovimientos("MOVIMIENTOS.dat", ios::binary);
                if (!archivoMovimientos) {
                    cerr << "Error al abrir el archivo MOVIMIENTOS.dat" << endl;
                    return 1;
                }

                Mov mov;
                bool encontrado = false;

                while (archivoMovimientos.read(reinterpret_cast<char*>(&mov), sizeof(Mov))) {
                    if (mov.idCli == idCli && mov.mov == 'S') {
                        tiemposEspera.push_back(mov.hora - tiemposEspera.size() * 100);

                        encontrado = true;

                        break;
                    }
                }

                archivoMovimientos.close();

                if (!encontrado) {
                    cerr << "No se encontró el movimiento de egreso del cliente " << idCli << endl;

                    return 1;
                }
            }

            double tiempoEsperaPromedioPorCaja;
        }
    }
