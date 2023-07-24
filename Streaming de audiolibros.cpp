// Streaming de audiolibros.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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
    int idLibro;
    int fecha;
    int minutos;
};

struct Libro
{
    int idLibro;
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
    ifstream archivoLibros("LIBROS.dat");
    ifstream archivoRelatores("RELATORES.dat");

    vector<Reproduccion> reproducciones;
    vector<Libro> libros;
    vector<Relator> relatores;

    // leer archivos
    int idUsuario, idLibro, fecha, minutos;

    while (archivoReproducciones >> idUsuario >> idLibro >> fecha >> minutos)
    {
        reproducciones.push_back({ idUsuario, idLibro, fecha, minutos });
    }

    while (archivoLibros >> idLibro >> idRelator >> idAutor)
    {
        char titulo[50];
        int duracion;
        archivoLibros.getline(titulo, 50);
        archivoLibros >> duracion;
        libros.push_back({ idLibro, idRelator, idAutor, titulo, duracion });
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

    for (const auto& libro : libros)
    {
        reproduccionesCompletas[libro.idLibro] = 0;
        reproducciones75_100[libro.idLibro] = 0;
        reproducciones50_75[libro.idLibro] = 0;
        reproducciones25_50[libro.idLibro] = 0;
        reproduccionesMenos25[libro.idLibro] = 0;

        for (const auto& reproduccion : reproducciones)
        {
            if (reproduccion.idLibro == libro.idLibro)
            {
                double porcentaje = (double)reproduccion.minutos / libro.duracion;

                if (porcentaje >= 1.0)
                {
                    ++reproduccionesCompletas[libro.idLibro];
                }
                else if (porcentaje >= 0.75 && porcentaje < 1.0)
                {
                    ++reproducciones75_100[libro.idLibro];
                }
                else if (porcentaje >= 0.5 && porcentaje < 0.75)
                {
                    ++reproducciones50_75[libro.idLibro];
                }
                else if (porcentaje >= 0.25 && porcentaje < 0.5)
                {
                    ++reproducciones25_50[libro.idLibro];
                }
                else if (porcentaje >= 0.0 && porcentaje < 0.25)
                {
                    ++reproduccionesMenos25[libro.idLibro];
                }
            }
        }
    }

    // escribir en la consola
    cout << "Listado ordenado por libro:" << endl;

    for (const auto& libro : libros)
    {
        cout << libro.titulo << ":" << endl;
        cout << "Reproducciones completas: " << reproduccionesCompletas[libro.idLibro] << endl;
        cout << "Reproducciones entre el 75% y el 100%: " << reproducciones75_100[libro.idLibro] << endl;
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
        int idLibro;
        int fecha;
        int minutos;
    };

    struct Libro
    {
        int idLibro;
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
        ifstream archivoLibros("LIBROS.dat");
        ifstream archivoRelatores("RELATORES.dat");

        vector<Reproduccion> reproducciones;
        vector<Libro> libros;
        vector<Relator> relatores;

        // leer archivos
        int idUsuario, idLibro, fecha, minutos;

        while (archivoReproducciones >> idUsuario >> idLibro >> fecha >> minutos)
        {
            reproducciones.push_back({ idUsuario, idLibro, fecha, minutos });
        }

        while (archivoLibros >> idLibro >> idRelator >> idAutor)
        {
            char titulo[50];
            int duracion;
            archivoLibros.getline(titulo, 50);
            archivoLibros >> duracion;
            libros.push_back({ idLibro, idRelator, idAutor, titulo, duracion });
        }

        while (archivoRelatores >> idRelator)
        {
            char nombre[50];
            archivoRelatores.getline(nombre, 50);
            relatores.push_back({ idRelator, nombre });
        }

        // procesar datos
        map<int, int> reproducciones75_100;

        for (const auto& libro : libros)
        {
            for (const auto& reproduccion : reproducciones)
            {
                if (reproduccion.idLibro == libro.idLibro)
                {
                    double porcentaje = (double)reproduccion.minutos / libro.duracion;

                    if (porcentaje >= 0.75 && porcentaje <= 1.0)
                    {
                        ++reproducciones75_100[libro.idRelator];
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
        archivoLibros.close();
        archivoRelatores.close();

        return 0;
    }
