// Torneo de Futbol.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Resultado {
    int idEq1;
    int idEq2;
    int codRes;
    char estadio[20];
};

struct Equipo {
    int idEq;
    char nombre[20];
    int puntos;
};

bool compararEquipos(Equipo e1, Equipo e2) {
    return e1.puntos > e2.puntos;
}

int main() {
    ifstream resultados("RESULTADOS.dat", ios::binary);
    ifstream equipos("EQUIPOS.dat", ios::binary);
    ofstream equiposActualizados("EQUIPOS.dat", ios::binary);

    vector<Equipo> listaEquipos;
    vector<Resultado> listaResultados;

    Equipo equipo;
    Resultado resultado;

    while (equipos.read((char*)&equipo, sizeof(Equipo))) {
        listaEquipos.push_back(equipo);
    }

    while (resultados.read((char*)&resultado, sizeof(Resultado))) {
        listaResultados.push_back(resultado);
    }

    equipos.close();
    resultados.close();

    for (Resultado r : listaResultados) {
        if (r.codRes < 0) {
            // Ganó el equipo 1
            for (Equipo& e : listaEquipos) {
                if (e.idEq == r.idEq1) {
                    e.puntos += 3;
                    break;
                }
            }
        }
        else if (r.codRes > 0) {
            // Ganó el equipo 2
            for (Equipo& e : listaEquipos) {
                if (e.idEq == r.idEq2) {
                    e.puntos += 3;
                    break;
                }
            }
        }
        else {
            // Empataron
            for (Equipo& e : listaEquipos) {
                if (e.idEq == r.idEq1 || e.idEq == r.idEq2) {
                    e.puntos += 1;
                }
            }
        }
    }

    sort(listaEquipos.begin(), listaEquipos.end(), compararEquipos);

    cout << "Tabla de posiciones:" << endl;

    for (Equipo e : listaEquipos) {
        cout << e.nombre << " " << e.puntos << endl;
        equiposActualizados.write((char*)&e, sizeof(Equipo));
    }

    equiposActualizados.close();

    cout << "Estadísticas por estadio:" << endl;

    for (Resultado r : listaResultados) {
        int partidos = 0;
        int empates = 0;
        for (Resultado r2 : listaResultados) {
            if (strcmp(r.estadio, r2.estadio) == 0) {
                partidos++;
                if (r2.codRes == 0) {
                    empates++;
                }
            }
        }
        cout << r.estadio << ": " << partidos << " partidos, " << empates << " empates" << endl;
    }

    return 0;
}
