// Aseguradora de Riesgos del Trabajo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Empresa {
    int idEmpresa;
    char razonSocial[100];
    int cantTrabAsegurados;
};

struct Accidente {
    int idEmpresa;
    int legajo;
    Fecha fecha;
    int cantDiasLicencia;
};

double porcentaje(int cantTrabajadores, int cantAccidentes);

int main() {
    map<int, pair<int, int>> accidentesPorEmpresa;

    map<int, map<int, int>> diasDeLicenciaPorEmpresaYLegajo;

    ifstream archivoAccidentes("ACCIDENTES.dat", ios::binary);
    if (!archivoAccidentes) {
        cerr << "Error al abrir el archivo ACCIDENTES.dat" << endl;
        return 1;
    }

    Accidente accidente;
    while (archivoAccidentes.read(reinterpret_cast<char*>(&accidente), sizeof(Accidente))) {
        accidentesPorEmpresa[accidente.idEmpresa].first++;

        accidentesPorEmpresa[accidente.idEmpresa].second += accidente.cantDiasLicencia;

        diasDeLicenciaPorEmpresaYLegajo[accidente.idEmpresa][accidente.legajo] += accidente.cantDiasLicencia;
    }

    archivoAccidentes.close();

    cout << "LISTADO DE PORCENTAJE DE REAJUSTE" << endl;

    cout << "Razón social - Porcentaje" << endl;

    ifstream archivoEmpresas("EMPRESAS.dat", ios::binary);
    if (!archivoEmpresas) {
        cerr << "Error al abrir el archivo EMPRESAS.dat" << endl;
        return 1;
    }

    Empresa empresa;

    double mayorPorcentaje = 0;

    int idEmpresaMayorPorcentaje = 0;

    while (archivoEmpresas.read(reinterpret_cast<char*>(&empresa), sizeof(Empresa))) {
        int cantTrabajadores = empresa.cantTrabAsegurados;

        int cantAccidentes = accidentesPorEmpresa[empresa.idEmpresa].first;

        double porcReajuste = porcentaje(cantTrabajadores, cantAccidentes);

        cout << empresa.razonSocial << " - " << porcReajuste << "%" << endl;

        if (porcReajuste > mayorPorcentaje) {
            mayorPorcentaje = porcReajuste;

            idEmpresaMayorPorcentaje = empresa.idEmpresa;
        }
    }

    archivoEmpresas.close();

    cout << "Razón Social: " << empresas[idEmpresaMayorPorcentaje].razonSocial << endl;

    cout << "Legajo - Total de días ausente" << endl;

    for (auto itLegajo = diasDeLicenciaPorEmpresaYLegajo[idEmpresaMayorPorcentaje].begin(); itLegajo != diasDeLicenciaPorEmpresaYLegajo[idEmpresaMayorPorcentaje].end(); itLegajo++) {
        int legajo = itLegajo->first;

        int totalDias = itLegajo->second;

        cout << legajo << " - " << totalDias << endl;
    }

    return 0;
}

double porcentaje(int cantTrabajadores, int cantAccidentes) {
    // TODO: Implementar la función para retornar el porcentaje de reajuste
}
