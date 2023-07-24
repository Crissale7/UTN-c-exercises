// Streaming de audiocuentos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Reproduccion
{
    int idUsuario;
    int idCuento;
    int fecha;
    int minutos;
};

struct Cuento
{
    int idCuento;
    int idRelator;
    int idAutor;
    char titulo[50];
    int duracion;
};

struct Relator
{
    int idRelator;
    char nombre[50];
};

int main()
{
    ifstream archivoReproducciones("REPRODUCCIONES.dat");
    ifstream archivoCuentos("CUENTOS.dat");
    ifstream archivoRelatores("RELATORES.dat");

    vector<Reproduccion> reproducciones;
    vector<Cuento> cuentos;
    vector<Relator> relatores;

    // leer archivos
    int idUsuario, idCuento, fecha, minutos;

    while (archivoReproducciones >> idUsuario >> idCuento >> fecha >> minutos)
    {
        reproducciones.push_back({ idUsuario, idCuento, fecha, minutos });
    }

    while (archivoCuentos >> idCuento >> idRelator >> idAutor)
    {
        char titulo[50];
        int duracion;
        archivoCuentos.getline(titulo, 50);
        archivoCuentos >> duracion;
        cuentos.push_back({ idCuento, idRelator, idAutor, titulo, duracion });
    }

    while (archivoRelatores >> idRelator)
    {
        char nombre[50];
        archivoRelatores.getline(nombre, 50);
        relatores.push_back({ idRelator, nombre });
    }

    // procesar datos
    map<int, int> reproduccionesCompletas;
    map<int, int> reproducciones75_100;
    map<int, int> reproducciones50_75;
    map<int, int> reproducciones25_50;
    map<int, int> reproduccionesMenos25;

    for (const auto& cuento : cuentos)
    {
        reproduccionesCompletas[cuento.idCuento] = 0;
        reproducciones75_100[cuento.idCuento] = 0;
        reproducciones50_75[cuento.idCuento] = 0;
        reproducciones25_50[cuento.idCuento] = 0;
        reproduccionesMenos25[cuento.idCuento] = 0;

        for (const auto& reproduccion : reproducciones)
        {
            if (reproduccion.idCuento == cuento.idCuento)
            {
                double porcentaje = (double)reproduccion.minutos / cuento.duracion;

                if (porcentaje >= 1.0)
                {
                    ++reproduccionesCompletas[cuento.idCuento];
                }
                else if (porcentaje >= 0.75)
                {
                    ++reproducciones75_100[cuento.idCuento];
                }
                else if (porcentaje >= 0.5)
                {
                    ++reproducciones50_75[cuento.idCuento];
                }
                else if (porcentaje >= 0.25)
                {
                    ++reproducciones25_50[cuento.idCuento];
                }
                else
                {
                    ++reproduccionesMenos25[cuento.idCuento];
                }
            }
        }
    }

    // escribir en la consola
    for (const auto& cuento : cuentos)
    {
        cout << "Cuento " << cuento.titulo << ":" << endl;
        cout << "Reproducciones completas: " << reproduccionesCompletas[cuento.idCuento] << endl;
        cout << "Reproducciones entre el 75% y el 100%: " << reproducciones75_100[cuento.idCuento] << endl;
        cout << "Reproducciones entre el 50% y el 75%: " << reproducciones50_75[cuento.idCuento] << endl;
        cout << "Reproducciones menos del 25%:" << reproduccionesMenos25[cuento.idCuento] << endl;
    }


// punto 2

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

    using namespace std;

    struct Reproduccion
    {
        int idUsuario;
        int idCuento;
        int fecha;
        int minutos;
    };

    struct Cuento
    {
        int idCuento;
        int idRelator;
        int idAutor;
        char titulo[50];
        int duracion;
    };

    struct Relator
    {
        int idRelator;
        char nombre[50];
    };

    int main()
    {
        ifstream archivoReproducciones("REPRODUCCIONES.dat");
        ifstream archivoCuentos("CUENTOS.dat");
        ifstream archivoRelatores("RELATORES.dat");

        vector<Reproduccion> reproducciones;
        vector<Cuento> cuentos;
        vector<Relator> relatores;

        // leer archivos
        int idUsuario, idCuento, fecha, minutos;

        while (archivoReproducciones >> idUsuario >> idCuento >> fecha >> minutos)
        {
            reproducciones.push_back({ idUsuario, idCuento, fecha, minutos });
        }

        while (archivoCuentos >> idCuento >> idRelator >> idAutor)
        {
            char titulo[50];
            int duracion;
            archivoCuentos.getline(titulo, 50);
            archivoCuentos >> duracion;
            cuentos.push_back({ idCuento, idRelator, idAutor, titulo, duracion });
        }

        while (archivoRelatores >> idRelator)
        {
            char nombre[50];
            archivoRelatores.getline(nombre, 50);
            relatores.push_back({ idRelator, nombre });
        }

        // procesar datos
        map<int, int> reproducciones75_100;

        for (const auto& cuento : cuentos)
        {
            reproducciones75_100[cuento.idRelator] = 0;

            for (const auto& reproduccion : reproducciones)
            {
                if (reproduccion.idCuento == cuento.idCuento)
                {
                    double porcentaje = (double)reproduccion.minutos / cuento.duracion;

                    if (porcentaje >= 0.75 && porcentaje <= 1.0)
                    {
                        ++reproducciones75_100[cuento.idRelator];
                    }
                }
            }
        }

        // ordenar por cantidad de reproducciones entre el 75% y el 100%
        sort(begin(relatores), end(relatores), [&](const Relator& a, const Relator& b) {
            return reproducciones75_100[a.idRelator] > reproducciones75_100[b.idRelator];
            });

        // escribir en la consola
        cout << "Los 10 relatores cuyas lecturas tuvieron la mayor cantidad de reproducciones entre el 75% y el 100% son:" << endl;

        for (int i = 0; i < min(10, (int)relatores.size()); ++i)
        {
            cout << relatores[i].nombre << ": " << reproducciones75_100[relatores[i].idRelator] << endl;
        }

        archivoReproducciones.close();
        archivoCuentos.close();
        archivoRelatores.close();

        return 0;
    }
//programa lee los archivos REPRODUCCIONES.dat, CUENTOS.dat y RELATORES.dat utilizando la clase ifstream y procesa los datos para generar el listado solicitado. 
//El programa utiliza un mapa para contar la cantidad de reproducciones entre el 75% y el 100% para cada relator. 
//Luego ordena los relatores por cantidad de reproducciones entre el 75% y el 100% y escribe los primeros 10 en la consola.