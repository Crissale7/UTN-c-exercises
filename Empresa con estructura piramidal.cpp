// Empresa con estructura piramidal.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

struct Socio {
    int idSocio;
    char nombre[50];
    int idSocioRef;
    Fecha fechaIngreso;
    double totalVentasAcumuladas;
    double liquidacionAnterior;
    double liquidacionesAcumuladas;
};

struct Venta {
    int idSocio;
    int idProducto;
    char observ[100];
    Fecha fecha;
    double importe;
};

int main() {
    map<int, Socio> socios;

    ifstream archivoSocios("SOCIOS.dat", ios::binary);
    if (!archivoSocios) {
        cerr << "Error al abrir el archivo SOCIOS.dat" << endl;
        return 1;
    }

    Socio socio;

    while (archivoSocios.read(reinterpret_cast<char*>(&socio), sizeof(Socio))) {
        socios[socio.idSocio] = socio;
    }

    archivoSocios.close();

    map<int, double> ventasPorSocio;

    ifstream archivoVentas("VENTAS.dat", ios::binary);
    if (!archivoVentas) {
        cerr << "Error al abrir el archivo VENTAS.dat" << endl;
        return 1;
    }

    Venta venta;

    while (archivoVentas.read(reinterpret_cast<char*>(&venta), sizeof(Venta))) {
        ventasPorSocio[venta.idSocio] += venta.importe * 0.3;

        int idSocioRef = socios[venta.idSocio].idSocioRef;

        while (idSocioRef != -1) {
            ventasPorSocio[idSocioRef] += ventasPorSocio[venta.idSocio] * 0.3;

            idSocioRef = socios[idSocioRef].idSocioRef;
        }
    }

    archivoVentas.close();

    for (auto& [idSocio, socio] : socios) {
        double liquidacionActual = ventasPorSocio[idSocio];

        double porcentajeIncrementoDecremento = 0;

        if (socio.liquidacionAnterior != 0) {
            porcentajeIncrementoDecremento = (liquidacionActual - socio.liquidacionAnterior) / socio.liquidacionAnterior * 100;
        }

        socio.liquidacionesAcumuladas += liquidacionActual;

        socio.totalVentasAcumuladas += liquidacionActual;

        socio.liquidacionAnterior = liquidacionActual;

        socios[idSocio] = socio;

        cout << "Id Socio: " << socio.idSocio << endl;

        cout << "Nombre: " << socio.nombre << endl;

        cout << "Fecha de ingreso: " << socio.fechaIngreso << endl;

        cout << "Liquidación anterior: " << socio.liquidacionAnterior << endl;

        cout << "Liquidación actual: " << liquidacionActual << endl;

        cout << "Porcentaje de incremento o decremento: " << porcentajeIncrementoDecremento << "%" << endl;

        cout << "Total acumulado desde su ingreso a la empresa: " << socio.totalVentasAcumuladas << endl;
    }

    ofstream archivoSalida("SOCIOS.dat", ios::binary);
    if (!archivoSalida) {
        cerr << "Error al abrir el archivo SOCIOS.dat" << endl;
        return 1;
    }

    for (auto& [idSocio, socio] : socios) {
        archivoSalida.write(reinterpret_cast<const char*>(&socio), sizeof(Socio));
    }

    archivoSalida.close();

    return 0;
}
