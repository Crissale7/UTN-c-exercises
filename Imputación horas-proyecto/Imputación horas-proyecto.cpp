// Imputación horas-proyecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Proyecto
{
    int idProyecto;
    char descripcion[100];
    int fechaInicio;
    int horasAsignadas;
    int horasImputadas;
};

struct Hora
{
    int idEmpleado;
    int idProyecto;
    int fecha;
    int horas;
    char tareas[200];
};

struct Empleado
{
    int idEmpleado;
    char nombre[50];
};

int main()
{
    ifstream archivoProyectos("PROYECTOS.dat");
    ifstream archivoHoras("HORAS.dat");
    ifstream archivoEmpleados("EMPLEADOS.dat");

    vector<Proyecto> proyectos;
    vector<Hora> horas;
    vector<Empleado> empleados;

    // leer archivos
    int idProyecto, idEmpleado, idPrac, fecha, horasAsignadas, horasImputadas, horas;

    while (archivoProyectos >> idProyecto)
    {
        char descripcion[100];
        archivoProyectos.getline(descripcion, 100);
        archivoProyectos >> fechaInicio >> horasAsignadas >> horasImputadas;
        proyectos.push_back({ idProyecto, descripcion, fechaInicio, horasAsignadas, horasImputadas });
    }

    while (archivoHoras >> idEmpleado >> idProyecto >> fecha >> horas)
    {
        char tareas[200];
        archivoHoras.getline(tareas, 200);
        horas.push_back({ idEmpleado, idProyecto, fecha, horas, tareas });
    }

    while (archivoEmpleados >> idEmpleado)
    {
        char nombre[50];
        archivoEmpleados.getline(nombre, 50);
        empleados.push_back({ idEmpleado, nombre });
    }

    // procesar datos
    map<int, vector<pair<int, Hora>>> horasPorProyecto; // mapa de vectores de pares (idEmpleado, Hora) por cada idProyecto

    for (const auto& hora : horas)
    {
        auto it = find_if(proyectos.begin(), proyectos.end(), [&](const Proyecto& p) { return p.idProyecto == hora.idProyecto; });
        if (it != proyectos.end())
        {
            horasPorProyecto[hora.idProyecto].push_back({ hora.idEmpleado, hora });
        }
    }

    // ordenar por proyecto, luego por empleado y por fecha descendente
    for (auto& par : horasPorProyecto)
    {
        sort(par.second.begin(), par.second.end(), [](const pair<int, Hora>& a, const pair<int, Hora>& b) {
            if (a.first == b.first) // si tienen el mismo empleado
            {
                return a.second.fecha > b.second.fecha; // ordenar por fecha descendente
            }
            else
            {
                return a.first < b.first; // ordenar por empleado ascendente
            }
            });
    }

    // escribir en la consola
    cout << "Un listado indicando para cada proyecto qué empleados trabajaron y por cada uno qué tareas desarrolló es:" << endl;

    for (const auto& proyecto : proyectos)
    {
        cout << "Proyecto: " << proyecto.descripcion << endl;
        cout << "Hs. Asignadas: " << proyecto.horasAsignadas << endl;
        cout << "Hs. Imputadas: " << proyecto.horasImputadas << endl;

        for (const auto& par : horasPorProyecto[proyecto.idProyecto])
        {
            const auto& empleado = find_if(empleados.begin(), empleados.end(), [&](const Empleado& e) { return e.idEmpleado == par.first; })->nombre;

            cout << "Empleado: " << empleado << endl;

            int totalHoras = 0;

            for (const auto& hora : par.second)
            {
                totalHoras += hora.horas;
            }

            cout << "Total Horas: " << totalHoras << endl;

            cout << "Fecha\t\tTarea desarrollada\t\tHoras" << endl;

            for (const auto& hora : par.second)
            {
                cout << hora.fecha << "\t" << hora.tareas << "\t" << hora.horas << endl;
            }

            cout << endl;
        }

        cout << endl;
    }

    archivoProyectos.close();
    archivoHoras.close();
    archivoEmpleados.close();

    return 0;
}

// punto 2

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Proyecto
{
    int idProyecto;
    char descripcion[100];
    int fechaInicio;
    int horasAsignadas;
    int horasImputadas;
};

struct Hora
{
    int idEmpleado;
    int idProyecto;
    int fecha;
    int horas;
    char tareas[200];
};

int main()
{
    ifstream archivoProyectos("PROYECTOS.dat");
    ifstream archivoHoras("HORAS.dat");

    vector<Proyecto> proyectos;
    vector<Hora> horas;

    // leer archivos
    int idProyecto, idEmpleado, idPrac, fecha, horasAsignadas, horasImputadas, horas;

    while (archivoProyectos >> idProyecto)
    {
        char descripcion[100];
        archivoProyectos.getline(descripcion, 100);
        archivoProyectos >> fechaInicio >> horasAsignadas >> horasImputadas;
        proyectos.push_back({ idProyecto, descripcion, fechaInicio, horasAsignadas, horasImputadas });
    }

    while (archivoHoras >> idEmpleado >> idProyecto >> fecha >> horas)
    {
        char tareas[200];
        archivoHoras.getline(tareas, 200);
        horas.push_back({ idEmpleado, idProyecto, fecha, horas, tareas });
    }

    // procesar datos
    for (auto& proyecto : proyectos)
    {
        int totalHoras = 0;

        for (const auto& hora : horas)
        {
            if (hora.idProyecto == proyecto.idProyecto)
            {
                totalHoras += hora.horas;
            }
        }

        if (totalHoras > proyecto.horasAsignadas)
        {
            proyecto.horasImputadas = totalHoras;
            cout << "El proyecto " << proyecto.descripcion << " quedó excedido en cantidad de horas." << endl;
        }
        else
        {
            proyecto.horasImputadas = totalHoras;
        }
    }

    // escribir en el archivo PROYECTOS.dat
    ofstream archivoNovedades("NOVEDADES.dat");

    for (const auto& proyecto : proyectos)
    {
        archivoNovedades << proyecto.idProyecto << " " << proyecto.descripcion << endl;
        archivoNovedades << proyecto.fechaInicio << " " << proyecto.horasAsignadas << " " << proyecto.horasImputadas << endl;
    }

    archivoNovedades.close();

    // escribir en la consola
    cout << "El archivo NOVEDADES.dat se ha actualizado con los proyectos excedidos en cantidad de horas." << endl;

    archivoProyectos.close();
    archivoHoras.close();

    return 0;
}
// punto extra

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Proyecto
{
    int idProyecto;
    char descripcion[100];
    int fechaInicio;
    int horasAsignadas;
    int horasImputadas;
};

struct Hora
{
    int idEmpleado;
    int idProyecto;
    int fecha;
    int horas;
    char tareas[200];
};

int main()
{
    ifstream archivoProyectos("PROYECTOS.dat");
    ifstream archivoHoras("HORAS.dat");

    vector<Proyecto> proyectos;
    vector<Hora> horas;

    // leer archivos
    int idProyecto, idEmpleado, idPrac, fecha, horasAsignadas, horasImputadas, horas;

    while (archivoProyectos >> idProyecto)
    {
        char descripcion[100];
        archivoProyectos.getline(descripcion, 100);
        archivoProyectos >> fechaInicio >> horasAsignadas >> horasImputadas;
        proyectos.push_back({ idProyecto, descripcion, fechaInicio, horasAsignadas, horasImputadas });
    }

    while (archivoHoras >> idEmpleado >> idProyecto >> fecha >> horas)
    {
        char tareas[200];
        archivoHoras.getline(tareas, 200);
        horas.push_back({ idEmpleado, idProyecto, fecha, horas, tareas });
    }

    // procesar datos
    for (int i = 1; i <= 100; ++i