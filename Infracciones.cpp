// Infracciones.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Acta {
    int idInspector;
    char pat[10];
    int fecha;
    int hora;
    int idInfraccion;
};

struct Infraccion {
    int idInfraccion;
    char descr[100];
    double penalidad;
    int diasPromo;
    double dtoPromo;
};

int main() {
    map<int, map<int, int>> infraccionesPorTipoYDia;

    map<string, double> importeAdeudadoPorPatente;

    ifstream archivoActas("ACTAS.dat", ios::binary);
    if (!archivoActas) {
        cerr << "Error al abrir el archivo ACTAS.dat" << endl;
        return 1;
    }

    Acta acta;
    while (archivoActas.read(reinterpret_cast<char*>(&acta), sizeof(Acta))) {
        ifstream archivoInfracciones("INFRACCIONES.dat", ios::binary);
        if (!archivoInfracciones) {
            cerr << "Error al abrir el archivo INFRACCIONES.dat" << endl;
            return 1;
        }

        Infraccion infraccion;

        bool encontrado = false;

        while (archivoInfracciones.read(reinterpret_cast<char*>(&infraccion), sizeof(Infraccion))) {
            if (infraccion.idInfraccion == acta.idInfraccion) {
                encontrado = true;

                break;
            }
        }

        archivoInfracciones.close();

        if (!encontrado) {
            cerr << "No se encontró la infracción con id " << acta.idInfraccion << endl;
            return 1;
        }

        int tipo = acta.idInfraccion;

        int dia = acta.fecha % 100;

        infraccionesPorTipoYDia[tipo][dia]++;

        string patente = acta.pat;

        double penalidad = infraccion.penalidad;

        importeAdeudadoPorPatente[patente] += penalidad;
    }

    archivoActas.close();

    for (auto itTipo = infraccionesPorTipoYDia.begin(); itTipo != infraccionesPorTipoYDia.end(); itTipo++) {
        int tipo = itTipo->first;

        cout << "Tipo de infracción: " << tipo << endl;

        for (auto itDia = itTipo->second.begin(); itDia != itTipo->second.end(); itDia++) {
            int dia = itDia->first;

            int cantidad = itDia->second;

            cout << "  Día: " << dia << " - Cantidad: " << cantidad << endl;
        }
    }

    cout << "Patente - Total Deuda - Total Descuento - Neto a pagar" << endl;

    for (auto itPatente = importeAdeudadoPorPatente.begin(); itPatente != importeAdeudadoPorPatente.end(); itPatente++) {
        string patente = itPatente->first;

        double totalDeuda = itPatente->second;

        double totalDescuento = 0;

        ifstream archivoActas("ACTAS.dat", ios::binary);
        if (!archivoActas) {
            cerr << "Error al abrir el archivo ACTAS.dat" << endl;
            return 1;
        }

        Acta acta;
        while (archivoActas.read(reinterpret_cast<char*>(&acta), sizeof(Acta))) {
            if (patente == acta.pat) {
                ifstream archivoInfracciones("INFRACCIONES.dat", ios::binary);
                if (!archivoInfracciones) {
                    cerr << "Error al abrir el archivo INFRACCIONES.dat" << endl;
                    return 1;
                }

                Infraccion infraccion;

                bool encontrado = false;

                while (archivoInfracciones.read(reinterpret_cast<char*>(&infraccion), sizeof(Infraccion))) {
                    if (infraccion.idInfraccion == acta.idInfraccion) {
                        encontrado = true;

                        break;
                    }
                }

                archivoInfracciones.close();

                if (!encontrado) {
                    cerr << "No se encontró la infracción con id " << acta.idInfraccion << endl;
                    return 1;
                }

                int diasPromo = infraccion.diasPromo;

                double dtoPromo = infraccion.dtoPromo;

                Fecha fechaActa = crearFecha(acta.fecha / 10000, (acta.fecha / 100) % 100, acta.fecha % 100);

                Fecha fechaActual = obtenerFechaActual();

                int diasDiferencia = diferenciaEnDias(fechaActa, fechaActual);

                if (diasDiferencia <= diasPromo) {
                    double penalidad = infraccion.penalidad;

                    double descuento = penalidad * dtoPromo;

                    totalDescuento += descuento;
                }
            }
        }

        archivoActas.close();

        double netoAPagar = totalDeuda - totalDescuento;

        cout << patente << " - " << totalDeuda << " - " << totalDescuento << " - " << netoAPagar << endl;
    }

    return 0;
}
