// Inscripción en la facultad.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// dara error pero porque este ejercicio te lo hice todo junto, porque en realidad se tendria que hacer por separado


//punto 1
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

struct Inscripcion {
    int idAlu;
    int idCur;
    int fecha; // aaaammdd
};

struct Curso {
    int idCur;
    char turno; // M, T o N
    int cap;
    char materia[20];
};

int main() {
    ifstream inscripciones("INSCRIPCIONES.dat", ios::binary);
    ifstream cursos("CURSOS.dat", ios::binary);

    map<int, vector<string>> materiasRechazadas;

    Inscripcion inscripcion;
    Curso curso;

    while (inscripciones.read((char*)&inscripcion, sizeof(Inscripcion))) {
        bool rechazada = false;
        string materiaRechazada = "";

        cursos.seekg(0, ios::beg);

        while (cursos.read((char*)&curso, sizeof(Curso))) {
            if (curso.idCur == inscripcion.idCur) {
                if (curso.cap == 0) {
                    rechazada = true;
                    materiaRechazada = curso.materia;
                }
                else {
                    curso.cap--;
                    cursos.seekp(-sizeof(Curso), ios::cur);
                    cursos.write((char*)&curso, sizeof(Curso));
                }
                break;
            }
        }

        if (rechazada) {
            materiasRechazadas[inscripcion.idAlu].push_back(materiaRechazada);
        }
    }

    inscripciones.close();
    cursos.close();

    cout << "Materias rechazadas por alumno:" << endl;

    for (auto par : materiasRechazadas) {
        cout << "Alumno " << par.first << ":" << endl;
        for (string materia : par.second) {
            cout << materia << endl;
        }
        cout << endl;
    }

    return 0;
}

// punto 2

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

struct Inscripcion {
    int idAlu;
    int idCur;
    int fecha; // aaaammdd
};

struct Curso {
    int idCur;
    char turno; // M, T o N
    int cap;
    char materia[20];
};

int main() {
    ifstream inscripciones("INSCRIPCIONES.dat", ios::binary);
    ifstream cursos("CURSOS.dat", ios::binary);

    map<string, vector<int>> cursosDisponibles;

    Inscripcion inscripcion;
    Curso curso;

    while (inscripciones.read((char*)&inscripcion, sizeof(Inscripcion))) {
        cursos.seekg(0, ios::beg);

        while (cursos.read((char*)&curso, sizeof(Curso))) {
            if (curso.idCur == inscripcion.idCur) {
                if (curso.cap > 0) {
                    cursosDisponibles[curso.materia].push_back(curso.idCur);
                    curso.cap--;
                    cursos.seekp(-sizeof(Curso), ios::cur);
                    cursos.write((char*)&curso, sizeof(Curso));
                }
                break;
            }
        }
    }

    inscripciones.close();
    cursos.close();

    //punto 3

#include <iostream>
#include <fstream>
    using namespace std;

    // Definición de las estructuras
    struct Inscripcion {
        int idAlu;
        int idCur;
        int fecha; // aaaammdd
    };

    struct Curso {
        int idCur;
        char turno; // M, T o N
        int cap;
        char materia[20];
    };

    struct Reasignacion {
        int idAlu;
        int idCurReasig;
    };

    // Función que busca un curso con cupo disponible que coincida con el idCur de una inscripción rechazada
    int buscarCurso(Curso cursos[], int n, int idCur) {
        for (int i = 0; i < n; i++) {
            if (cursos[i].idCur == idCur && cursos[i].cap > 0) {
                return i; // Retorna el índice del curso encontrado
            }
        }
        return -1; // Retorna -1 si no se encuentra ningún curso
    }

    // Función principal
    int main() {
        // Abrir los archivos INSCRIPCIONES.dat y REASIGNACION.dat
        ifstream inscripciones("INSCRIPCIONES.dat", ios::binary);
        ofstream reasignacion("REASIGNACION.dat", ios::binary);

        // Crear las variables de tipo Inscripcion y Reasignacion
        Inscripcion ins;
        Reasignacion rea;

        // Leer el primer registro del archivo INSCRIPCIONES.dat
        inscripciones.read((char*)&ins, sizeof(Inscripcion));

        // Crear un arreglo de tipo Curso con los datos del archivo CURSOS.dat
        Curso cursos[10]; // Suponemos que hay 10 cursos disponibles
        ifstream cursosFile("CURSOS.dat", ios::binary);
        cursosFile.read((char*)cursos, sizeof(Curso) * 10);
        cursosFile.close();

        // Mientras no se llegue al final del archivo INSCRIPCIONES.dat
        while (!inscripciones.eof()) {
            // Si el estado de la inscripción es 'R' (rechazado)
            if (ins.estado == 'R') {
                // Buscar un curso con cupo disponible que coincida con el idCur de la inscripción
                int indice = buscarCurso(cursos, 10, ins.idCur);
                // Si se encuentra un curso con cupo disponible
                if (indice != -1) {
                    // Asignar el idAlu de la inscripción al idAlu de la reasignación
                    rea.idAlu = ins.idAlu;
                    // Asignar el idCur del curso encontrado al idCurReasig de la reasignación
                    rea.idCurReasig = cursos[indice].idCur;
                    // Escribir la reasignación en el archivo REASIGNACION.dat
                    reasignacion.write((char*)&rea, sizeof(Reasignacion));
                    // Disminuir el cupo del curso encontrado en uno
                    cursos[indice].cap--;
                }
            }
            // Leer el siguiente registro del archivo INSCRIPCIONES.dat
            inscripciones.read((char*)&ins, sizeof(Inscripcion));
        }

        // Cerrar los archivos INSCRIPCIONES.dat y REASIGNACION.dat
        inscripciones.close();
        reasignacion.close();

        return 0;
    }

    // punto 4

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

    using namespace std;

    struct Inscripcion
    {
        int idAlu;
        int idCur;
        int fecha;
    };

    struct Curso
    {
        int idCur;
        char turno;
        int cap;
        char materia[20];
    };

    struct Revision
    {
        int idAlu;
        char materia[20];
    };

    bool compararPorIdAlu(const Revision& a, const Revision& b)
    {
        return a.idAlu < b.idAlu;
    }

    int main()
    {
        ifstream archivoInscripciones("INSCRIPCIONES.dat");
        ifstream archivoCursos("CURSOS.dat");
        ofstream archivoRevision("REVISION.dat");

        vector<Inscripcion> inscripciones;
        vector<Curso> cursos;

        // leer archivos
        int idAlu, idCur, fecha;

        while (archivoInscripciones >> idAlu >> idCur >> fecha)
        {
            inscripciones.push_back({ idAlu, idCur, fecha });
        }

        while (archivoCursos >> idCur >> turno >> cap)
        {
            char materia[20];
            archivoCursos.getline(materia, 20);
            cursos.push_back({ idCur, turno, cap, materia });
        }

        // procesar datos
        vector<Revision> revisiones;

        for (const auto& inscripcion : inscripciones)
        {
            bool encontrado = false;

            for (const auto& curso : cursos)
            {
                if (inscripcion.idCur == curso.idCur)
                {
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado)
            {
                Revision revision = { inscripcion.idAlu };
                copy(begin(curso.materia), end(curso.materia), begin(revision.materia));
                revisiones.push_back(revision);
            }
        }

        sort(begin(revisiones), end(revisiones), compararPorIdAlu);

        // escribir en el archivo
        for (const auto& revision : revisiones)
        {
            archivoRevision << revision.idAlu << " " << revision.materia << endl;
        }

        archivoInscripciones.close();
        archivoCursos.close();
        archivoRevision.close();

        return 0;
    }
