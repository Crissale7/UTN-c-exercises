// Empresa de gas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Categoria {
    char idCat[3];
    char descrip[50];
    int m3Desde;
    int m3Hasta;
    double valorM3;
};

struct Medicion {
    int idCli;
    int lecturaActual;
    Fecha fecha;
};

struct Cliente {
    int idCli;
    char nombre[100];
    char direccion[200];
    char idCatAnt[3];
    int lecturaAnterior;
    unsigned char consumos[36];
};

struct Consumo {
    int mmaaaa;
    int m3Consumidos;
};

Array<Consumo> decodeConsumo(unsigned char acumulado[]);

unsigned char* encodeConsumo(Array<Consumo> arr);

int calcularConsumoAnual(Array<Consumo> arr, int actual);

int main() {
    map<string, Categoria> categorias;

    ifstream archivoCategorias("CATEGORIAS.dat", ios::binary);
    if (!archivoCategorias) {
        cerr << "Error al abrir el archivo CATEGORIAS.dat" << endl;
        return 1;
    }

    Categoria categoria;

    while (archivoCategorias.read(reinterpret_cast<char*>(&categoria), sizeof(Categoria))) {
        categorias[categoria.idCat] = categoria;
    }

    archivoCategorias.close();

    map<int, Cliente> clientes;

    ifstream archivoClientes("CLIENTES.dat", ios::binary);
    if (!archivoClientes) {
        cerr << "Error al abrir el archivo CLIENTES.dat" << endl;
        return 1;
    }

    Cliente cliente;

    while (archivoClientes.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        clientes[cliente.idCli] = cliente;
    }

    archivoClientes.close();

    map<string, vector<int>> clientesPorCategoria;

    ifstream archivoMediciones("MEDICIONES.dat", ios::binary);
    if (!archivoMediciones) {
        cerr << "Error al abrir el archivo MEDICIONES.dat" << endl;
        return 1;
    }

    Medicion medicion;

    while (archivoMediciones.read(reinterpret_cast<char*>(&medicion), sizeof(Medicion))) {
        Cliente cliente = clientes[medicion.idCli];

        Array<Consumo> consumos = decodeConsumo(cliente.consumos);

        int consumoActual = medicion.lecturaActual - cliente.lecturaAnterior;

        int consumoAnual = calcularConsumoAnual(consumos, consumoActual);

        string nuevaCategoria;

        for (auto& [idCat, categoria] : categorias) {
            if (consumoAnual >= categoria.m3Desde && consumoAnual <= categoria.m3Hasta) {
                nuevaCategoria = idCat;

                break;
            }
        }

        clientesPorCategoria[nuevaCategoria].push_back(cliente.idCli);

        consumos.push_back({ medicion.fecha.mes * 100 + medicion.fecha.anio, consumoActual });

        consumos.pop_front();

        unsigned char* nuevosConsumos = encodeConsumo(consumos);

        for (int i = 0; i < 36; i++) {
            cliente.consumos[i] = nuevosConsumos[i];
        }

        cliente.lecturaAnterior = medicion.lecturaActual;

        strcpy(cliente.idCatAnt, nuevaCategoria.c_str());

        clientes[cliente.idCli] = cliente;
    }

    archivoMediciones.close();

    for (auto& [idCat, categoria] : categorias) {
        cout << "Categoría: " << idCat << " - " << categoria.descrip << endl;

        cout << "Clientes nuevos en esta categoría:" << endl;

        for (int idCli : clientesPorCategoria[idCat]) {
            Cliente cliente = clientes[idCli];

            if (cliente.idCatAnt != idCat) {
                cout << "  Id: " << cliente.idCli << " - Nombre: " << cliente.nombre << endl;
            }
        }
    }

    ofstream archivoSalida("CLIENTES.dat", ios::binary);
    if (!archivoSalida) {
        cerr << "Error al abrir el archivo CLIENTES.dat" << endl;
        return 1;
    }

    for (auto& [idCli, cliente] : clientes) {
        archivoSalida.write(reinterpret_cast<const char*>(&cliente), sizeof(Cliente));
    }

    archivoSalida.close();

    return 0;
}

Array<Consumo> decodeConsumo(unsigned char acumulado[]) {
    // TODO: Implementar la función para retornar un array con 6 estructuras Consumo
}

unsigned char* encodeConsumo(Array<Consumo> arr) {
    // TODO: Implementar la función para retornar un array de unsigned char con el acumulado
}

int calcularConsumoAnual(Array<Consumo> arr, int actual) {
    // TODO: Implementar la función para retornar el consumo anual según el actual y el acumulado
}
