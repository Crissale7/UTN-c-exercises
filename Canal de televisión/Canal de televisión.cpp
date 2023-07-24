// Canal de televisión.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Planificacion {
    int idPlanif;
    int idProg;
    int horaInicio;
    int minutoInicio;
};

struct Programa {
    int idProg;
    char titulo[100];
    int duracion;
    int atp;
};

struct Descartado {
    int idPlanif;
    int causa;
};

struct Bache {
    int horaDesde;
    int minDesde;
    int duracion;
};

bool haySuperposicion(int hi1, int dur, int hi2);

Hora calcularBache(Hora hi1, int durp, Hora hi2, int& durb);

int main() {
    vector<Planificacion> planificacion;

    ifstream archivoPlanificacion("PLANIFICACION.dat", ios::binary);
    if (!archivoPlanificacion) {
        cerr << "Error al abrir el archivo PLANIFICACION.dat" << endl;
        return 1;
    }

    Planificacion planif;
    while (archivoPlanificacion.read(reinterpret_cast<char*>(&planif), sizeof(Planificacion))) {
        planificacion.push_back(planif);
    }

    archivoPlanificacion.close();

    map<int, Programa> programas;

    ifstream archivoProgramas("PROGRAMAS.dat", ios::binary);
    if (!archivoProgramas) {
        cerr << "Error al abrir el archivo PROGRAMAS.dat" << endl;
        return 1;
    }

    Programa prog;
    while (archivoProgramas.read(reinterpret_cast<char*>(&prog), sizeof(Programa))) {
        programas[prog.idProg] = prog;
    }

    archivoProgramas.close();

    vector<Descartado> descartados;

    for (int i = 0; i < planificacion.size(); i++) {
        Planificacion planif = planificacion[i];

        Programa prog = programas[planif.idProg];

        int horaInicio = planif.horaInicio * 100 + planif.minutoInicio;

        bool descartar = false;

        for (int j = 0; j < i; j++) {
            Planificacion planifAnterior = planificacion[j];

            Programa progAnterior = programas[planifAnterior.idProg];

            int horaInicioAnterior = planifAnterior.horaInicio * 100 + planifAnterior.minutoInicio;

            if (haySuperposicion(horaInicioAnterior, progAnterior.duracion, horaInicio)) {
                descartar = true;

                Descartado descartado;

                descartado.idPlanif = planif.idPlanif;

                descartado.causa = 1;

                descartados.push_back(descartado);

                break;
            }
        }

        if (!descartar) {
            if (prog.atp == 0 && (horaInicio < 700 || horaInicio + prog.duracion > 2200)) {
                descartar = true;

                Descartado descartado;

                descartado.idPlanif = planif.idPlanif;

                descartado.causa = 2;

                descartados.push_back(descartado);
            }
        }
    }

    ofstream archivoDescartados("DESCARTADOS.dat", ios::binary);
    if (!archivoDescartados) {
        cerr << "Error al abrir el archivo DESCARTADOS.dat" << endl;
        return 1;
    }

    for (int i = 0; i < descartados.size(); i++) {
        Descartado descartado = descartados[i];

        archivoDescartados.write(reinterpret_cast<char*>(&descartado), sizeof(Descartado));
    }
}
