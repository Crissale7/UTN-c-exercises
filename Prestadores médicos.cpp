// Prestadores médicos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Presta
{
    int idPres;
    int idPrac;
    long long fechaHora;
    int minutos;
};

struct Practica
{
    int idPrac;
    char descr[50];
};

int main()
{
    ifstream archivoPresta19("PRESTA19.dat");
    ifstream archivoPresta20("PRESTA20.dat");
    ifstream archivoPracticas("PRACTICAS.dat");

    vector<Presta> presta19;
    vector<Presta> presta20;
    vector<Practica> practicas;

    // leer archivos
    int idPres, idPrac, minutos;
    long long fechaHora;

    while (archivoPresta19 >> idPres >> idPrac >> fechaHora >> minutos)
    {
        presta19.push_back({ idPres, idPrac, fechaHora, minutos });
    }

    while (archivoPresta20 >> idPres >> idPrac >> fechaHora >> minutos)
    {
        presta20.push_back({ idPres, idPrac, fechaHora, minutos });
    }

    while (archivoPracticas >> idPrac)
    {
        char descr[50];
        archivoPracticas.getline(descr, 50);
        practicas.push_back({ idPrac, descr });
    }

    // procesar datos
    set<int> prestadores19; // conjunto de prestadores que trabajaron en 2019
    set<int> prestadores20; // conjunto de prestadores que trabajaron en 2020
    set<int> prestadoresNuevos; // conjunto de prestadores que se incorporaron en 2020

    for (const auto& presta : presta19)
    {
        prestadores19.insert(presta.idPres);
    }

    for (const auto& presta : presta20)
    {
        prestadores20.insert(presta.idPres);
        if (prestadores19.count(presta.idPres) == 0) // si el prestador no trabajó en 2019
        {
            prestadoresNuevos.insert(presta.idPres); // se agrega al conjunto de prestadores nuevos
        }
    }

    // escribir en la consola
    cout << "Un listado ordenado decrecientemente por idPres de los prestadores que se incorporaron en 2020 es:" << endl;

    for (auto it = prestadoresNuevos.rbegin(); it != prestadoresNuevos.rend(); ++it) // iterar el conjunto de forma inversa
    {
        cout << *it << endl; // imprimir el id del prestador
    }

    archivoPresta19.close();
    archivoPresta20.close();
    archivoPracticas.close();

    return 0;
}

// punto 2
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Presta
{
    int idPres;
    int idPrac;
    long long fechaHora;
    int minutos;
};

struct Practica
{
    int idPrac;
    char descr[50];
};

int main()
{
    ifstream archivoPresta19("PRESTA19.dat");
    ifstream archivoPresta20("PRESTA20.dat");
    ifstream archivoPracticas("PRACTICAS.dat");

    vector<Presta> presta19;
    vector<Presta> presta20;
    vector<Practica> practicas;

    // leer archivos
    int idPres, idPrac, minutos;
    long long fechaHora;

    while (archivoPresta19 >> idPres >> idPrac >> fechaHora >> minutos)
    {
        presta19.push_back({ idPres, idPrac, fechaHora, minutos });
    }

    while (archivoPresta20 >> idPres >> idPrac >> fechaHora >> minutos)
    {
        presta20.push_back({ idPres, idPrac, fechaHora, minutos });
    }

    while (archivoPracticas >> idPrac)
    {
        char descr[50];
        archivoPracticas.getline(descr, 50);
        practicas.push_back({ idPrac, descr });
    }

    // procesar datos
    vector<pair<long long, Practica>> practicasRealizadas; // vector de pares (fechaHora, Practica)

    for (const auto& presta : presta19)
    {
        auto it = find_if(practicas.begin(), practicas.end(), [&](const Practica& p) { return p.idPrac == presta.idPrac; });
        if (it != practicas.end())
        {
            practicasRealizadas.push_back({ presta.fechaHora, *it });
        }
    }

    for (const auto& presta : presta20)
    {
        auto it = find_if(practicas.begin(), practicas.end(), [&](const Practica& p) { return p.idPrac == presta.idPrac; });
        if (it != practicas.end())
        {
            practicasRealizadas.push_back({ presta.fechaHora, *it });
        }
    }

    sort(practicasRealizadas.rbegin(), practicasRealizadas.rend()); // ordenar por fechaHora decreciente

    // escribir en la consola
    cout << "Un listado ordenado decrecientemente por fechaHora de las prácticas realizadas por los prestadores que trabajaron durante 2019 y 2020 es:" << endl;

    for (const auto& practicaRealizada : practicasRealizadas)
    {
        cout << practicaRealizada.first << " " << practicaRealizada.second.descr << endl; // imprimir la fecha y la descripción de la práctica
    }

    archivoPresta19.close();
    archivoPresta20.close();
    archivoPracticas.close();

    return 0;
}

// punto 3
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Presta
{
    int idPres;
    int idPrac;
    long long fechaHora;
    int minutos;
};

struct Practica
{
    int idPrac;
    char descr[50];
};

int main()
{
    ifstream archivoPresta19("PRESTA19.dat");
    ifstream archivoPracticas("PRACTICAS.dat");

    vector<Presta> presta19;
    vector<Practica> practicas;

    // leer archivos
    int idPres, idPrac, minutos;
    long long fechaHora;

    while (archivoPresta19 >> idPres >> idPrac >> fechaHora >> minutos)
    {
        presta19.push_back({ idPres, idPrac, fechaHora, minutos });
    }

    while (archivoPracticas >> idPrac)
    {
        char descr[50];
        archivoPracticas.getline(descr, 50);
        practicas.push_back({ idPrac, descr });
    }

    // procesar datos
    vector<pair<int, int>> prestadores2019; // vector de pares (idPres, cantidad de prácticas)

    for (const auto& presta : presta19)
    {
        auto it = find_if(practicas.begin(), practicas.end(), [&](const Practica& p) { return p.idPrac == presta.idPrac; });
        if (it != practicas.end())
        {
            auto it2 = find_if(prestadores2019.begin(), prestadores2019.end(), [&](const pair<int, int>& p) { return p.first == presta.idPres; });
            if (it2 != prestadores2019.end())
            {
                it2->second++; // incrementar la cantidad de prácticas realizadas por el prestador
            }
            else
            {
                prestadores2019.push_back({ presta.idPres, 1 }); // agregar el prestador al vector con una cantidad de prácticas igual a 1
            }
        }
    }

    sort(prestadores2019.begin(), prestadores2019.end()); // ordenar por idPres

    // escribir en la consola
    cout << "Un listado de los prestadores que sólo trabajaron durante 2019 y la cantidad de prácticas que realizaron es:" << endl;

    for (const auto& prestador : prestadores2019)
    {
        cout << prestador.first << " " << prestador.second << endl; // imprimir el id del prestador y la cantidad de prácticas realizadas
    }

    archivoPresta19.close();
    archivoPracticas.close();

    return 0;
}
