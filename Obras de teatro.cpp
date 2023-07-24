// Obras de teatro.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Obra {
    int idObra;
    char titulo[100];
    int fEstreno;
    int idTeatro;
};

struct Teatro {
    int idTeatro;
    char direccion[50];
    int capacidad;
    int sectores;
};

struct Reserva {
    int idCliente;
    int idObra;
    int idFuncion;
    int sector;
    int cant;
};

int capacidadSector(int idTeatro, int sector) {
    ifstream archivoTeatros("TEATROS.dat", ios::binary);
    if (!archivoTeatros) {
        cerr << "Error al abrir el archivo TEATROS.dat" << endl;

        return -1;
    }

    Teatro teatro;

    while (archivoTeatros.read(reinterpret_cast<char*>(&teatro), sizeof(Teatro))) {
        if (teatro.idTeatro == idTeatro) {
            archivoTeatros.close();

            return teatro.capacidad / teatro.sectores;
        }
    }

    archivoTeatros.close();

    cerr << "No se encontró el teatro con id " << idTeatro << endl;

    return -1;
}

int main() {
    ifstream archivoReservas("Reserva.dat", ios::binary);
    if (!archivoReservas) {
        cerr << "Error al abrir el archivo Reserva.dat" << endl;

        return 1;
    }

    map<pair<int, int>, int> reservasPorSectorYFuncion;

    Reserva reserva;

    while (archivoReservas.read(reinterpret_cast<char*>(&reserva), sizeof(Reserva))) {
        pair<int, int> sectorYFuncion = make_pair(reserva.sector, reserva.idFuncion);

        if (reservasPorSectorYFuncion.find(sectorYFuncion) == reservasPorSectorYFuncion.end()) {
            reservasPorSectorYFuncion[sectorYFuncion] = 0;
        }

        reservasPorSectorYFuncion[sectorYFuncion] += reserva.cant;
    }

    archivoReservas.close();

    ifstream archivoObras("OBRAS.dat", ios::binary);
    if (!archivoObras) {
        cerr << "Error al abrir el archivo OBRAS.dat" << endl;

        return 1;
    }

    Obra obra;

    while (archivoObras.read(reinterpret_cast<char*>(&obra), sizeof(Obra))) {
        cout << "Obra: " << obra.titulo << endl;

        auto funcionesProgramadas = funcionesProgramadas(obra.idObra);

        for (auto it = funcionesProgramadas.begin(); it != funcionesProgramadas.end(); it++) {
            cout << "  Función: " << it->horaInicio << endl;

            for (int i = 1; i <= capacidadSector(it->idTeatro, 1); i++) {
                pair<int, int> sectorYFuncion = make_pair(i, it->idFuncion);

                if (reservasPorSectorYFuncion.find(sectorYFuncion) == reservasPorSectorYFuncion.end()) {
                    reservasPorSectorYFuncion[sectorYFuncion] = 0;
                }

                if (reservasPorSectorYFuncion[sectorYFuncion] < capacidadSector(it->idTeatro, i)) {
                    cout << "    Sector " << i << ": " << reservasPorSectorYFuncion[sectorYFuncion] << endl;
                }
                else {
                    cout << "    Sector " << i << ": Excluidas por falta de capacidad" << endl;
                }
            }
        }
    }

    archivoObras.close();

    return 0;
}

// version 2

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Reserva {
    int idCliente;
    int idObra;
    int idFuncion;
    int sector;
    int cant;
};

struct Funcion {
    int idFuncion;
    int idObra;
    int diaSem;
    int hora;
};

struct Sector {
    int idTeatro;
    int sector;
    int cap;
};

int capacidadSector(int idTeatro, int sector) {
    ifstream archivoSectores("SECTORES.dat", ios::binary);
    if (!archivoSectores) {
        cerr << "Error al abrir el archivo SECTORES.dat" << endl;

        return -1;
    }

    Sector sectorActual;

    while (archivoSectores.read(reinterpret_cast<char*>(&sectorActual), sizeof(Sector))) {
        if (sectorActual.idTeatro == idTeatro && sectorActual.sector == sector) {
            archivoSectores.close();

            return sectorActual.cap;
        }
    }

    archivoSectores.close();

    cerr << "No se encontró el sector " << sector << " del teatro con id " << idTeatro << endl;

    return -1;
}

int main() {
    ifstream archivoReservas("RESERVAS.dat", ios::binary);
    if (!archivoReservas) {
        cerr << "Error al abrir el archivo RESERVAS.dat" << endl;

        return 1;
    }

    map<pair<int, int>, int> reservasPorSectorYFuncion;

    Reserva reserva;

    while (archivoReservas.read(reinterpret_cast<char*>(&reserva), sizeof(Reserva))) {
        pair<int, int> sectorYFuncion = make_pair(reserva.sector, reserva.idFuncion);

        if (reservasPorSectorYFuncion.find(sectorYFuncion) == reservasPorSectorYFuncion.end()) {
            reservasPorSectorYFuncion[sectorYFuncion] = 0;
        }

        reservasPorSectorYFuncion[sectorYFuncion] += reserva.cant;
    }

    archivoReservas.close();

    ifstream archivoFunciones("FUNCIONES.dat", ios::binary);
    if (!archivoFunciones) {
        cerr << "Error al abrir el archivo FUNCIONES.dat" << endl;

        return 1;
    }

    Funcion funcion;

    while (archivoFunciones.read(reinterpret_cast<char*>(&funcion), sizeof(Funcion))) {
        cout << "Obra: " << funcion.idObra << endl;

        cout << "  Función: " << funcion.hora / 100 << ":" << funcion.hora % 100 << endl;

        for (int i = 1; i <= capacidadSector(funcion.idTeatro, 1); i++) {
            pair<int, int> sectorYFuncion = make_pair(i, funcion.idFuncion);

            if (reservasPorSectorYFuncion.find(sectorYFuncion) == reservasPorSectorYFuncion.end()) {
                reservasPorSectorYFuncion[sectorYFuncion] = 0;
            }

            if (reservasPorSectorYFuncion[sectorYFuncion] < capacidadSector(funcion.idTeatro, i)) {
                cout << "    Sector " << i << ": " << reservasPorSectorYFuncion[sectorYFuncion] << endl;
            }
            else {
                cout << "    Sector " << i << ": Excluidas por falta de capacidad" << endl;
            }
        }
    }

    archivoFunciones.close();

    return 0;
}

// version 3

#include <iostream>
#include <fstream>
#include <map>
#include <list>

using namespace std;

struct Obra {
    int idObra;
    char titu[100];

    struct Teatro {
        int idTeatro;
        char nom[50];
        int fEstreno;
        int sectores;
    } teatro;
};

struct Funcion {
    int idFuncion;
    int diaSemana;
    int hora;
};

struct Reserva {
    int idCli;
    int idObra;
    int dia;
    int sector;
    int cant;
};

Obra getObra(int idObra) {
    ifstream archivoObras("OBRAS.dat", ios::binary);
    if (!archivoObras) {
        cerr << "Error al abrir el archivo OBRAS.dat" << endl;

        return Obra();
    }

    Obra obraActual;

    while (archivoObras.read(reinterpret_cast<char*>(&obraActual), sizeof(Obra))) {
        if (obraActual.idObra == idObra) {
            archivoObras.close();

            return obraActual;
        }
    }

    archivoObras.close();

    cerr << "No se encontró la obra con id " << idObra << endl;

    return Obra();
}

Reserva leerReserva() {
    Reserva reserva;

    cout << "Ingrese el ID del cliente: ";
    cin >> reserva.idCli;

    cout << "Ingrese el ID de la obra: ";
    cin >> reserva.idObra;

    cout << "Ingrese el día de la función (1=lunes, 2=martes, ...): ";
    cin >> reserva.dia;

    cout << "Ingrese el sector: ";
    cin >> reserva.sector;

    cout << "Ingrese la cantidad de localidades: ";
    cin >> reserva.cant;

    return reserva;
}

bool continuarOperando() {
    char respuesta;

    do {
        cout << "¿Desea continuar operando? (s/n): ";
        cin >> respuesta;
        cin.ignore();
        respuesta = tolower(respuesta);
    } while (respuesta != 's' && respuesta != 'n');

    return respuesta == 's';
}

list<Funcion> getFuncionesObra(int idObra) {
    ifstream archivoFunciones("FUNCIONES.dat", ios::binary);
    if (!archivoFunciones) {
        cerr << "Error al abrir el archivo FUNCIONES.dat" << endl;

        return list<Funcion>();
    }

    list<Funcion> funciones;

    Funcion funcionActual;

    while (archivoFunciones.read(reinterpret_cast<char*>(&funcionActual), sizeof(Funcion))) {
        Obra obra = getObra(idObra);

        if (obra.teatro.idTeatro == funcionActual.idTeatro && obra.idObra == idObra) {
            funciones.push_back(funcionActual);
        }
    }

    archivoFunciones.close();

    return funciones;
}

int capacidadSector(int idTeatro, int sector) {
    ifstream archivoSectores("SECTORES.dat", ios::binary);
    if (!archivoSectores) {
        cerr << "Error al abrir el archivo SECTORES.dat" << endl;

        return -1;
    }

    int capacidad = -1;

    Sector sectorActual;

    while (archivoSectores.read(reinterpret_cast<char*>(&sectorActual), sizeof(Sector))) {
        if (sectorActual.idTeatro == idTeatro && sectorActual.sector == sector) {
            capacidad = sectorActual.cap;

            break;
        }
    }

    archivoSectores.close();

    if (capacidad == -1) {
        cerr << "No se encontró el sector " << sector << " del teatro con id " << idTeatro << endl;

        return -1;
    }

    return capacidad;
}

void notificarReserva(int idCli, bool acept) {
    cout << "La reserva del cliente con ID " << idCli << " ha sido ";

    if (acept) {
        cout << "aceptada." << endl;
    }
    else {
        cout << "" << endl;
    }
}
