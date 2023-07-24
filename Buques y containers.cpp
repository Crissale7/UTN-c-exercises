// Buques y containers.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Buque {
    int idBuque;
    char nombre[50];
    int darsena;
    int grua;
    int cantContainers;
    Fecha fecha;
    int cteFlotacion;
    char oriODest[100];
};

struct Container {
    int idContainer;
    int peso;
    int longitud;
    int idBuque;
};

bool estable(int peso, int longitud, int cteFlotacion);

char actividad(Fecha f);

int main() {
    map<int, Buque> buques;

    ifstream archivoBuques("BUQUES.dat", ios::binary);
    if (!archivoBuques) {
        cerr << "Error al abrir el archivo BUQUES.dat" << endl;
        return 1;
    }

    Buque buque;
    while (archivoBuques.read(reinterpret_cast<char*>(&buque), sizeof(Buque))) {
        buques[buque.idBuque] = buque;
    }

    archivoBuques.close();

    map<int, vector<Container>> contenedoresPorBuque;

    ifstream archivoContenedores("CONTAINERS.dat", ios::binary);
    if (!archivoContenedores) {
        cerr << "Error al abrir el archivo CONTAINERS.dat" << endl;
        return 1;
    }

    Container container;
    while (archivoContenedores.read(reinterpret_cast<char*>(&container), sizeof(Container))) {
        contenedoresPorBuque[container.idBuque].push_back(container);
    }

    archivoContenedores.close();

    cout << "LISTADO DE CARGAS Y DESCARGAS DEL PUERTO AL DÍA: " << obtenerFechaActual() << endl;

    for (auto itBuque = buques.begin(); itBuque != buques.end(); itBuque++) {
        Buque buque = itBuque->second;

        cout << "Id. Buque: " << buque.idBuque << " [" << actividad(buque.fecha) << "]" << endl;

        cout << "Grúa: " << buque.grua << endl;

        cout << "Nombre: " << buque.nombre << endl;

        cout << "Dársena: " << buque.darsena << endl;

        cout << "Fecha: " << buque.fecha << " de [" << (actividad(buque.fecha) == 'C' ? "SALIDA" : "LLEGADA") << "]" << endl;

        cout << "Cant. Containers: " << buque.cantContainers << endl;

        cout << "#Orden Id. Container Peso Longitud" << endl;

        vector<Container> contenedores = contenedoresPorBuque[buque.idBuque];

        int orden = 1;

        int pesoTotal = 0;

        for (int i = 0; i < contenedores.size(); i++) {
            Container container = contenedores[i];

            cout << orden++ << " " << container.idContainer << " "
                << container.peso << " "
                << container.longitud
                << endl;

            pesoTotal += container.peso;
        }

        cout << "Peso total transportado: " << pesoTotal
            << endl;
    }

    return 0;
}

bool estable(int peso, int longitud, int cteFlotacion) {
    // TODO: Implementar la función para determinar si el buque permanecerá estabilizado
}

char actividad(Fecha f) {
    // TODO: Implementar la función para retornar 'C' o 'D' según la fecha sea posterior o anterior a la fecha actual
}
