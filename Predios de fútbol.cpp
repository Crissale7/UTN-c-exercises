// Predios de fútbol.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Predio {
    int idPredio;
    char nombre[100];
    char direccion[100];
    int cantCanchas;
    int idBarrio;
};

struct Reserva {
    int idReserva;
    int idCliente;
    int idPredio;
    int diaMes;
    char turno;
    char celContacto[50];
};

struct Cancha {
    int idPredio;
    int nroCancha;
    double precio;
    int flgCubierta;
    char obs[200];
};

struct Rechazo {
    Reserva reserva;
    int motivoRechazo;
};

int main() {
    map<int, map<char, map<int, int>>> reservasPorBarrioYTurno;

    map<int, map<char, map<int, int>>> rechazosPorBarrioYTurno;

    ifstream archivoReservas("RESERVAS.dat", ios::binary);
    if (!archivoReservas) {
        cerr << "Error al abrir el archivo RESERVAS.dat" << endl;
        return 1;
    }

    Reserva reserva;
    while (archivoReservas.read(reinterpret_cast<char*>(&reserva), sizeof(Reserva))) {
        ifstream archivoPredios("PREDIOS.dat", ios::binary);
        if (!archivoPredios) {
            cerr << "Error al abrir el archivo PREDIOS.dat" << endl;
            return 1;
        }

        Predio predio;

        bool encontrado = false;

        while (archivoPredios.read(reinterpret_cast<char*>(&predio), sizeof(Predio))) {
            if (predio.idPredio == reserva.idPredio) {
                encontrado = true;

                break;
            }
        }

        archivoPredios.close();

        if (!encontrado) {
            Rechazo rechazo;

            rechazo.reserva = reserva;

            rechazo.motivoRechazo = 2;

            rechazosPorBarrioYTurno[predio.idBarrio][reserva.turno][reserva.diaMes]++;

            continue;
        }

        ifstream archivoCanchas("CANCHAS.dat", ios::binary);
        if (!archivoCanchas) {
            cerr << "Error al abrir el archivo CANCHAS.dat" << endl;
            return 1;
        }

        Cancha cancha;

        encontrado = false;

        while (archivoCanchas.read(reinterpret_cast<char*>(&cancha), sizeof(Cancha))) {
            if (cancha.idPredio == predio.idPredio) {
                encontrado = true;

                break;
            }
        }

        archivoCanchas.close();

        if (!encontrado) {
            Rechazo rechazo;

            rechazo.reserva = reserva;

            rechazo.motivoRechazo = 1;

            rechazosPorBarrioYTurno[predio.idBarrio][reserva.turno][reserva.diaMes]++;

            continue;
        }

        reservasPorBarrioYTurno[predio.idBarrio][reserva.turno][reserva.diaMes]++;
    }

    archivoReservas.close();

    for (auto itBarrio = reservasPorBarrioYTurno.begin(); itBarrio != reservasPorBarrioYTurno.end(); itBarrio++) {
        int idBarrio = itBarrio->first;

        cout << "Barrio: " << idBarrio << endl;

        cout << "Turno mañana:" << endl;

        for (int dia = 1; dia <= 31; dia++) {
            int aceptadas = itBarrio->second['M'][dia];

            int rechazadas = rechazosPorBarrioYTurno[idBarrio]['M'][dia];

            cout << "  Día: " << dia << " - Aceptadas: " << aceptadas << "";
        }
    }
