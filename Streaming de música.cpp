// Streaming de música.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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
    int idAlbum;
    int fecha;
    int minutos;
};

struct Album
{
    int idAlbum;
    int idArtista;
    char titulo[50];
    int duracion;
};

int main()
{
    ifstream archivoReproducciones("REPRODUCCIONES.dat");
    ifstream archivoAlbumes("ALBUMES.dat");

    vector<Reproduccion> reproducciones;
    vector<Album> albumes;

    // leer archivos
    int idUsuario, idAlbum, fecha, minutos;

    while (archivoReproducciones >> idUsuario >> idAlbum >> fecha >> minutos)
    {
        reproducciones.push_back({ idUsuario, idAlbum, fecha, minutos });
    }

    while (archivoAlbumes >> idAlbum >> idArtista)
    {
        char titulo[50];
        int duracion;
        archivoAlbumes.getline(titulo, 50);
        archivoAlbumes >> duracion;
        albumes.push_back({ idAlbum, idArtista, titulo, duracion });
    }

    // procesar datos
    map<int, int> reproduccionesCompletas;
    map<int, int> reproducciones75_100;
    map<int, int> reproducciones50_75;
    map<int, int> reproducciones25_50;
    map<int, int> reproduccionesMenos25;

    for (const auto& album : albumes)
    {
        reproduccionesCompletas[album.idAlbum] = 0;
        reproducciones75_100[album.idAlbum] = 0;
        reproducciones50_75[album.idAlbum] = 0;
        reproducciones25_50[album.idAlbum] = 0;
        reproduccionesMenos25[album.idAlbum] = 0;

        for (const auto& reproduccion : reproducciones)
        {
            if (reproduccion.idAlbum == album.idAlbum)
            {
                double porcentaje = (double)reproduccion.minutos / album.duracion;

                if (porcentaje >= 1.0)
                {
                    ++reproduccionesCompletas[album.idAlbum];
                }
                else if (porcentaje >= 0.75 && porcentaje < 1.0)
                {
                    ++reproducciones75_100[album.idAlbum];
                }
                else if (porcentaje >= 0.5 && porcentaje < 0.75)
                {
                    ++reproducciones50_75[album.idAlbum];
                }
                else if (porcentaje >= 0.25 && porcentaje < 0.5)
                {
                    ++reproducciones25_50[album.idAlbum];
                }
                else if (porcentaje >= 0.0 && porcentaje < 0.25)
                {
                    ++reproduccionesMenos25[album.idAlbum];
                }
            }
        }
    }

    // escribir en la consola
    cout << "Listado ordenado por álbum:" << endl;

    for (const auto& album : albumes)
    {
        cout << "Álbum " << album.titulo << ":" << endl;
        cout << "Reproducciones completas: " << reproduccionesCompletas[album.idAlbum] << endl;
        cout << "Reproducciones entre el 75% y el 100%: " << reproducciones75_100[album.idAlbum] << endl;
        cout << "Reproducciones entre el 50% y el 75%: " << reproducciones50_75[album.idAlbum] << endl;
        cout << "Reproducciones entre el 25% y el 50%: " << reproducciones25_50[album.idAlbum] << endl;
        cout << "Reproducciones menos del 25%: " << reproduccionesMenos25[album.idAlbum] << endl;
        cout << endl;
    }

    archivoReproducciones.close();
    archivoAlbumes.close();

    return 0;
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
    int idAlbum;
    int fecha;
    int minutos;
};

struct Album
{
    int idAlbum;
    int idArtista;
    char titulo[50];
    int duracion;
};

struct Artista
{
    int idArtista;
    char nombre[50];
};

int main()
{
    ifstream archivoReproducciones("REPRODUCCIONES.dat");
    ifstream archivoAlbumes("ALBUMES.dat");
    ifstream archivoArtistas("ARTISTAS.dat");

    vector<Reproduccion> reproducciones;
    vector<Album> albumes;
    vector<Artista> artistas;

    // leer archivos
    int idUsuario, idAlbum, fecha, minutos;

    while (archivoReproducciones >> idUsuario >> idAlbum >> fecha >> minutos)
    {
        reproducciones.push_back({ idUsuario, idAlbum, fecha, minutos });
    }

    while (archivoAlbumes >> idAlbum >> idArtista)
    {
        char titulo[50];
        int duracion;
        archivoAlbumes.getline(titulo, 50);
        archivoAlbumes >> duracion;
        albumes.push_back({ idAlbum, idArtista, titulo, duracion });
    }

    while (archivoArtistas >> idArtista)
    {
        char nombre[50];
        archivoArtistas.getline(nombre, 50);
        artistas.push_back({ idArtista, nombre });
    }

    // procesar datos
    map<int, int> reproducciones75_100_por_artista;

    for (const auto& artista : artistas)
    {
        reproducciones75_100_por_artista[artista.idArtista] = 0;

        for (const auto& album : albumes)
        {
            if (album.idArtista == artista.idArtista)
            {
                for (const auto& reproduccion : reproducciones)
                {
                    if (reproduccion.idAlbum == album.idAlbum)
                    {
                        double porcentaje = (double)reproduccion.minutos / album.duracion;

                        if (porcentaje >= 0.75 && porcentaje < 1.0)
                        {
                            ++reproducciones75_100_por_artista[artista.idArtista];
                        }
                    }
                }
            }
        }
    }

    // ordenar por cantidad de reproducciones
    vector<pair<int, int>> reproducciones75_100_por_artista_vector(reproducciones75_100_por_artista.begin(), reproducciones75_100_por_artista.end());
    sort(reproducciones75_100_por_artista_vector.begin(), reproducciones75_100_por_artista_vector.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; });

    // escribir en la consola
    cout << "Los 10 artistas cuyos álbumes tuvieron la mayor cantidad de reproducciones entre el 75% y el 100% son:" << endl;

    for (int i = 0; i < min(10, (int)reproducciones75_100_por_artista_vector.size()); ++i)
    {
        const auto& artista = find_if(artistas.begin(), artistas.end(), [&](const Artista& a) { return a.idArtista == reproducciones75_100_por_artista_vector[i].first; })->nombre;

        cout << i + 1 << ". " << artista << " (" << reproducciones75_100_por_artista_vector[i].second << " reproducciones)" << endl;
    }

    archivoReproducciones.close();
    archivoAlbumes.close();
    archivoArtistas.close();

    return 0;
}
