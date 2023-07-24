// Gastos por consorcio.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Gasto {
    int idCons;
    int fecha;
    double importe;
    char categoria[20];
};

struct Consorcio {
    int idCons;
    char direccion[50];
    int cantPisos;
    int dtosPorPiso;
};

double mtsPorcentuales(int idCons, int depto);

int main() {
    vector<Gasto> gastos;

    ifstream archivoGastos("GASTOS.dat", ios::binary);
    if (!archivoGastos) {
        cerr << "Error al abrir el archivo GASTOS.dat" << endl;
        return 1;
    }

    Gasto gasto;
    while (archivoGastos.read(reinterpret_cast<char*>(&gasto), sizeof(Gasto))) {
        gastos.push_back(gasto);
    }

    archivoGastos.close();

    vector<Consorcio> consorcios;

    ifstream archivoConsorcios("CONSORCIOS.dat", ios::binary);
    if (!archivoConsorcios) {
        cerr << "Error al abrir el archivo CONSORCIOS.dat" << endl;
        return 1;
    }

    Consorcio consorcio;
    while (archivoConsorcios.read(reinterpret_cast<char*>(&consorcio), sizeof(Consorcio))) {
        consorcios.push_back(consorcio);
    }

    archivoConsorcios.close();

    for (int i = 0; i < consorcios.size(); i++) {
        Consorcio consorcio = consorcios[i];

        double gastosTotales = 0;

        vector<double> mtsPorcentualesPorDepto(consorcio.dtosPorPiso, 0);

        for (int j = 0; j < gastos.size(); j++) {
            Gasto gasto = gastos[j];

            if (gasto.idCons == consorcio.idCons) {
                gastosTotales += gasto.importe;

                int depto = (gasto.fecha % 10000) / 100;

                mtsPorcentualesPorDepto[depto - 1] += mtsPorcentuales(gasto.idCons, depto);
            }
        }

        cout << "Consorcio Calle: " << consorcio.direccion << endl;
        cout << "Gastos totales: $" << gastosTotales << endl;

        vector<pair<double, int>> mtsPorcentualesConDepto;

        for (int j = 0; j < mtsPorcentualesPorDepto.size(); j++) {
            mtsPorcentualesConDepto.push_back(make_pair(mtsPorcentualesPorDepto[j], j + 1));
        }

        sort(mtsPorcentualesConDepto.rbegin(), mtsPorcentualesConDepto.rend());

        for (int j = 0; j < mtsPorcentualesConDepto.size(); j++) {
            pair<double, int> mtsPorcentualesYDepto = mtsPorcentualesConDepto[j];

            cout << "Depto. " << mtsPorcentualesYDepto.second << ": ";
            cout << mtsPorcentualesYDepto.first * 100 << "% ";
            cout << "$" << gastosTotales * mtsPorcentualesYDepto.first / consorcio.dtosPorPiso << endl;
        }

        cout << endl;
    }

    return 0;
}

double mtsPorcentuales(int idCons, int depto) {
    // TODO: Implementar la función para calcular los metros porcentuales
}

//version 2

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Gasto {
    int idCons;
    int fecha;
    double importe;
    char categoria[20];
};

struct Consorcio {
    int idCons;
    char direccion[50];
    int cantPisos;
    int dtosPorPiso;
};

double mtsPorcentuales(int idCons, int depto);

int main() {
    vector<Gasto> gastos;

    ifstream archivoGastos("GASTOS.dat", ios::binary);
    if (!archivoGastos) {
        cerr << "Error al abrir el archivo GASTOS.dat" << endl;
        return 1;
    }

    Gasto gasto;
    while (archivoGastos.read(reinterpret_cast<char*>(&gasto), sizeof(Gasto))) {
        gastos.push_back(gasto);
    }

    archivoGastos.close();

    vector<Consorcio> consorcios;

    ifstream archivoConsorcios("CONSORCIOS.dat", ios::binary);
    if (!archivoConsorcios) {
        cerr << "Error al abrir el archivo CONSORCIOS.dat" << endl;
        return 1;
    }

    Consorcio consorcio;
    while (archivoConsorcios.read(reinterpret_cast<char*>(&consorcio), sizeof(Consorcio))) {
        consorcios.push_back(consorcio);
    }

    archivoConsorcios.close();

    for (int i = 0; i < consorcios.size(); i++) {
        Consorcio consorcio = consorcios[i];

        double gastosTotales = 0;

        vector<double> mtsPorcentualesPorDepto(consorcio.dtosPorPiso, 0);

        map<string, double> gastosPorCategoria;

        for (int j = 0; j < gastos.size(); j++) {
            Gasto gasto = gastos[j];

            if (gasto.idCons == consorcio.idCons) {
                gastosTotales += gasto.importe;

                int depto = (gasto.fecha % 10000) / 100;

                mtsPorcentualesPorDepto[depto - 1] += mtsPorcentuales(gasto.idCons, depto);

                string categoria(gasto.categoria);

                if (gastosPorCategoria.find(categoria) == gastosPorCategoria.end()) {
                    gastosPorCategoria[categoria] = 0;
                }

                gastosPorCategoria[categoria] += gasto.importe;
            }
        }

        cout << "Consorcio Calle: " << consorcio.direccion << endl;
        cout << "Gastos totales: $" << gastosTotales << endl;

        vector<pair<double, int>> mtsPorcentualesConDepto;

        for (int j = 0; j < mtsPorcentualesPorDepto.size(); j++) {
            mtsPorcentualesConDepto.push_back(make_pair(mtsPorcentualesPorDepto[j], j + 1));
        }

        sort(mtsPorcentualesConDepto.rbegin(), mtsPorcentualesConDepto.rend());

        for (int j = 0; j < mtsPorcentualesConDepto.size(); j++) {
            pair<double, int> mtsPorcentualesYDepto = mtsPorcentualesConDepto[j];

            cout << "Depto. " << mtsPorcentualesYDepto.second << ": ";
            cout << mtsPorcentualesYDepto.first * 100 << "% ";
            cout << "$" << gastosTotales * mtsPorcentualesYDepto.first / consorcio.dtosPorPiso << endl;
        }

        cout << endl;

        vector<pair<double, string>> gastosConCategoria;

        for (auto it = gastosPorCategoria.begin(); it != gastosPorCategoria.end(); it++) {
            pair<string, double> categoriaYGasto = *it;

            gastosConCategoria.push_back(make_pair(categoriaYGasto.second, categoriaYGasto.first));
        }

        sort(gastosConCategoria.rbegin(), gastosConCategoria.rend());

        cout << "Distribución de los gastos por categoría:" << endl;
    }

        //for (int aca a medias porque no se como terminar el recorrido for





// version 3

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

    using namespace std;

    struct Gasto {
        int idCons;
        int fecha;
        double importe;
        char categoria[20];
    };

    struct Consorcio {
        int idCons;
        char direccion[50];
        int cantPisos;
        int dtosPorPiso;
    };

    struct Distribucion {
        int idCons;
        int tipoDto;
        double mtsPorc;
    };

    int main() {
        vector<Gasto> gastos;

        ifstream archivoGastos("GASTOS.dat", ios::binary);
        if (!archivoGastos) {
            cerr << "Error al abrir el archivo GASTOS.dat" << endl;
            return 1;
        }

        Gasto gasto;
        while (archivoGastos.read(reinterpret_cast<char*>(&gasto), sizeof(Gasto))) {
            gastos.push_back(gasto);
        }

        archivoGastos.close();

        vector<Consorcio> consorcios;

        ifstream archivoConsorcios("CONSORCIOS.dat", ios::binary);
        if (!archivoConsorcios) {
            cerr << "Error al abrir el archivo CONSORCIOS.dat" << endl;
            return 1;
        }

        Consorcio consorcio;
        while (archivoConsorcios.read(reinterpret_cast<char*>(&consorcio), sizeof(Consorcio))) {
            consorcios.push_back(consorcio);
        }

        archivoConsorcios.close();

        vector<Distribucion> distribuciones;

        ifstream archivoDistribuciones("DISTRIBUCION.dat", ios::binary);
        if (!archivoDistribuciones) {
            cerr << "Error al abrir el archivo DISTRIBUCION.dat" << endl;
            return 1;
        }

        Distribucion distribucion;
        while (archivoDistribuciones.read(reinterpret_cast<char*>(&distribucion), sizeof(Distribucion))) {
            distribuciones.push_back(distribucion);
        }

        archivoDistribuciones.close();

        map<pair<int, int>, double> mtsPorcentualesPorTipoDepto;

        for (int i = 0; i < distribuciones.size(); i++) {
            Distribucion distribucion = distribuciones[i];

            mtsPorcentualesPorTipoDepto[make_pair(distribucion.idCons, distribucion.tipoDto)] = distribucion.mtsPorc / 100.0;
        }

        for (int i = 0; i < consorcios.size(); i++) {
            Consorcio consorcio = consorcios[i];

            double gastosTotales = 0;

            map<int, double> mtsPorcentualesPorDepto;

            map<string, double> gastosPorCategoria;

            for (int j = 0; j < gastos.size(); j++) {
                Gasto gasto = gastos[j];

                if (gasto.idCons == consorcio.idCons) {
                    gastosTotales += gasto.importe;

                    int depto = (gasto.fecha % 10000) / 100;

                    double mtsPorcentuales = mtsPorcentualesPorTipoDepto[make_pair(gasto.idCons, depto)];

                    if (mtsPorcentualesPorDepto.find(depto) == mtsPorcentualesPorDepto.end()) {
                        mtsPorcentualesPorDepto[depto] = 0;
                    }

                    mtsPorcentualesPorDepto[depto] += mtsPorcentuales;

                    string categoria(gasto.categoria);

                    if (gastosPorCategoria.find(categoria) == gastosPorCategoria.end()) {
                        gastosPorCategoria[categoria] = 0;
                    }

                    gastosPorCategoria[categoria] += gasto.importe;
                }
            }

            cout << "Consorcio Calle: " << consorcio.direccion << endl;
            cout << "Gastos totales: $" << gastosTotales << endl;

            vector<pair<double, int>> mtsPorcentualesConDepto;

            for (auto it = mtsPorcentualesPorDepto.begin(); it != mtsPorcentualesPorDepto.end(); it++) {
                pair<int, double> deptoYMtsPorcentuales = *it;

                mtsPorcentualesConDepto.push;